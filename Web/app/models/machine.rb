require 'singleton'

class Machine
  include Singleton
  require 'net/http'
  require 'open-uri'

  attr_accessor :running, :bottle_count, :ip_address, :drink_count, :pending_orders, :completed_orders

  def initialize
    self.bottle_count = 6
    self.ip_address = 'localhost:3000'
    self.running = false
    self.drink_count = 0
    self.completed_orders = []
    self.pending_orders = []
    @queue = Queue.new
  end

  def start
    self.running = true
    @queue ||= Queue.new
    @thread = Thread.new do
      while order = @queue.pop
        begin
          Rails.logger.info "*** BEGINNING POUR ***"
          pour(order)
        rescue Exception => e
          handle_exception e
        end
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
    if order.class.eql?(Order) and order.persisted?
      json_order = order.as_json(:only=>[:id, :completed], :include=>{:pours=>{:only=>[:seconds],:methods=>:bottle}})
      @queue << json_order
      self.pending_orders << order.id
      return order
    else
      return nil
    end
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
    Rails.logger.info order.inspect
    if web_request_successful?(order)
      self.drink_count += 1
      self.completed_orders << order['id']
      self.pending_orders.delete_if {|i| i.eql? order['id']}
      Rails.logger.info "*** POUR COMPLETE ***"
    end
  end

  def web_request_successful?(order)
    params = Hash.new
    order[:pours].each {|pour| params['b'+pour[:bottle].to_s] = pour['seconds'] }
    Rails.logger.info "*** SENT: "+params.inspect
    response = Net::HTTP.post_form(self.uri, params)
    return response.code == "200"
  end

  def handle_exception(e)
    Rails.logger.error "Job Error: #{e.message}\n#{e.backtrace.join("\n")}"
  end
end