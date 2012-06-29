class Machine < ActiveRecord::Base
  include Singleton
  require 'net/http'
  require 'open-uri'

  attr_accessor :pouring

  def self.bottles
    return 5
  end

  def start
    @queue = Queue.new
    @thread = Thread.new do
      while order = @queue.pop
        self.pour(order)
      end
    end
  end

  def stop
    @queue.clear
    @thread.join
  end

  def <<(order)
    @queue << order
  end

  def uri
    return URI.parse('http://'+@@machine_ip+'/spout')
  end

  private
  def pour(order)
    if web_request_successful?(order)
      Machine.increment_counter(:drinks_count, self.id)
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