require 'singleton'

class Machine
  include Singleton
  require 'net/http'
  require 'open-uri'

  attr_accessor :running, :bottle_count, :ip_address

  def initialize
    self.bottle_count = 5
    self.ip_address = '127.0.0.1'
    self.running = false
  end

  def start
    self.running = true
    @queue ||= Queue.new
    @thread = Thread.new do
      while order = @queue.pop
        pour(order)
      end
    end
  end

  def stop
    self.running = false
    @thread.kill
  end

  def reset
    @queue.clear
  end

  def <<(order)
    @queue << order if order.class.eql? Order
  end

  def uri
    return URI.parse('http://'+ip_address+'/spout')
  end

  private
  def pour(order)
    if web_request_successful?(order)
      Drink.increment_counter(:served_count, order.drink_id)
    end
  end

  def web_request_successful?(order)
    params = Hash.new
    order.pours.each { |pour| params['b'+pour.bottle.to_s] = pour.seconds }
    response = Net::HTTP.post_form(self.uri, params)
    return response.code == "200"
  end
end