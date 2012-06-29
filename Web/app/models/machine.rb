require 'singleton'

class Machine
  include Singleton
  require 'net/http'
  require 'open-uri'

  attr_accessor :running, :bottle_count, :ip_address, :drink_count

  def initialize
    self.bottle_count = 6
    self.ip_address = 'localhost:3000'
    self.running = false
    self.drink_count = 0
    @queue = Queue.new
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
    @queue << order if order.class.eql?(Order) and order.persisted?
  end

  def queue
    return @queue
  end

  def queued_orders
    return self.queue.instance_variable_get :@que
  end

  def thread
    return @thread
  end

  def uri
    return URI.parse('http://'+ip_address+'/spout')
  end

  def active
    return self.running
  end

  private
  def pour(order)
    if web_request_successful?(order)
      self.drink_count += 1
      order.update_attributes(:completed=>true)
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