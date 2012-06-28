class Order < ActiveRecord::Base
  #an order is a drink, ordered by a user, and placed in the queue.

  belongs_to :user
  belongs_to :drink
  has_many :pours, :through=>:drink

  scope :pending, where(:completed=>false)
  scope :completed, where(:completed=>true)

  after_create do |order|
    #self.send_to_chomper
  end

  def self.next
    Order.pending.order('updated_at').first
  end

  def send_to_chomper
    $redis.multi do
      $redis.rpush("orders",self.to_json)
      $redis.publish("ignition", 1)
    end
  end
end