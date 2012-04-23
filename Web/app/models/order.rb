class Order < ActiveRecord::Base
	belongs_to :drink
	belongs_to :user

	scope :pending, where(:completed=>false)
	scope :completed, where(:completed=>true)
end
