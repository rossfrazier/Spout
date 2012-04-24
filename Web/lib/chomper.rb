=begin
The Chomper module is responsible for 'chomping' away at the queue of drink orders and sending a request to the Arduino for the drink to be poured. The Chomper should be started (Chomper.start) any time a new order has been created. 

The chomper will check to see if the machine is chomping (a db attribute). If it is, nothing happens (because the chomper is running elsewhere already). If it is not, the chomper will keep popping off the next item on the list of orders, send a web request to the Arduino based on its attributes, and mark the order as complete.  It will keep looping through this until it runs out of orders and tell the machine it is done chomping.  This will start again the next time an order is added.

The chomper is designed to run on another thread to keep other requests from blocking, but this needs to be tested more throughly.
=end

module Chomper
  require 'net/http'
  require 'open-uri'
  
  def self.start
    machine = Machine.first
    @@machine_ip = machine.ip_address
    return false if machine.chomping

    thread = Thread.new do
      machine.update_attributes(:chomping=>true)
      while machine.chomping do
        if order = Order.next
          order.update_attributes(:completed=>order.request_sent?)
          Machine.increment_counter(:drinks_count, machine.id)
        else
          machine.update_attributes(:chomping=>false)
        end
      end
      thread.kill
    end
  end

  def request_sent?
    self.send_request
  end

  def send_request
    uri = URI.parse('http://'+@@machine_ip+'/spout')
    params = Hash.new
    self.pours.each do |pour|
      pour.bottle
      params['p'+pour.bottle.to_s] = pour.seconds
    end

    response = Net::HTTP.post_form(uri, params)
    return response.code == 200
  end
end