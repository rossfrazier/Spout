class Order < ActiveRecord::Base
  #an order is a drink, ordered by a user, and placed in the queue.

  belongs_to :user
  belongs_to :drink
  has_many :pours, :through=>:drink

  default_scope order('updated_at DESC')
  scope :pending, where(:id=>$machine.pending_orders)
  scope :completed, where(:id=>$machine.completed_orders)

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