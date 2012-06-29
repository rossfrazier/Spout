class Order < ActiveRecord::Base
  #an order is a drink, ordered by a user, and placed in the queue.

  belongs_to :user
  belongs_to :drink
  has_many :pours, :through=>:drink

  scope :pending, where(:completed=>false)
  scope :completed, where(:completed=>true)

  after_create do |order|
    send_to_queue
  end

  def processing
    if $machine.queued_orders.include? self
      return true
    else
      return false
    end
  end

  private

  def send_to_queue
    $machine << self
  end
end