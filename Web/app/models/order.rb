class Order < ActiveRecord::Base
  require 'chomper'
  include Chomper

  belongs_to :user
  belongs_to :drink
  has_many :pours, :through=>:drink

  scope :pending, where(:completed=>false)
  scope :completed, where(:completed=>true)

  after_create do |order|
    Order.chomp!
  end

  def self.next
    Order.pending.order('updated_at DESC').first
  end
end