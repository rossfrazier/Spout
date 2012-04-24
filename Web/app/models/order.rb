class Order < ActiveRecord::Base
require 'net/http'
require 'open-uri'
require 'chomper'

belongs_to :user
belongs_to :drink
has_many :pours, :through=>:drink

scope :pending, where(:completed=>false)
scope :completed, where(:completed=>true)

end
