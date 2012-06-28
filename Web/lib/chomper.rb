=begin
The Chomper module is responsible for 'chomping' away at the queue of drink orders and sending a request to the Arduino for the drink to be poured. The Chomper should be started (Chomper.start) any time a new order has been created. 

The chomper will check to see if the machine is chomping (a db attribute). If it is, nothing happens (because the chomper is running elsewhere already). If it is not, the chomper will keep popping off the next item on the list of orders, send a web request to the Arduino based on its attributes, and mark the order as complete.  It will keep looping through this until it runs out of orders and tell the machine it is done chomping.  This will start again the next time an order is added.

The chomper is designed to run on another thread to keep other requests from blocking, but this needs to be tested more throughly.
=end

module Chomper
  require 'net/http'
  require 'open-uri'

  @queue = Queue.new

  def self.add(order)
    @queue << order
  end

  def self.start
    @thread = Thread.new do
      puts '** IN A NEW THREAD **'
      while order = @queue.pop
        puts '** POPPED OBJECT:'+order.inspect
      end
      #redis = Redis.new
      #redis.subscribe(:ignition) do |on|
      #  on.subscribe do |channel, subscriptions|
      #    puts '** Waiting for ignition message **'
      #  end

      #  on.message do |channel,message|
      #    puts '** Ignition message received **'
      #    self.chomp
      #  end
      #end
    end
  end

  def self.stop
    @thread.join
  end

  def self.status
    Rails.logger.info @thread.inspect
  end

  def self.chomp
    while order = $redis.lpop("orders")
      order = JSON.parse(order)
      order = Order.find(order['id'])
      self.pour(order)
      puts "** CHOMPED AN ORDER **"
    end
  end

  def self.pour(order)
    puts '*** POURING!!! ***'
  end

  def send_request
    uri = URI.parse('http://'+@@machine_ip+'/spout')
    Rails.logger.info "***SENDING TO: "+uri.to_s+" ***"
    params = Hash.new
    self.pours.each { |pour| params['b'+pour.bottle.to_s] = pour.seconds }
    Rails.logger.info "***ABOUT TO SEND REQUEST. PARAMS: "+ params.inspect + " ***"

    response = Net::HTTP.post_form(uri, params)
    Rails.logger.info "*** RECEIVED A RESPONSE. CODE: "+response.code.to_s+" ***"
    return response.code == "200"
  end

end