class Drink < ActiveRecord::Base
	#a drink is a collection of pour objects, which is a reference to an ingredient being
	#poured for a set amount of time.
	#a drink can be ordered by many different people and put in the orders queue.
  has_many :pours, :dependent => :destroy
  has_many :ingredients, :through=>:pours
  has_many :orders, :dependent => :destroy

  mount_uploader :image, ImageUploader

  before_save do |drink|
  	drink.name = drink.name.titleize
  end
end
