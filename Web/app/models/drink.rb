class Drink < ActiveRecord::Base
  has_many :pours, :dependent => :destroy
  has_many :ingredients, :through=>:pours
  has_many :orders, :dependent => :destroy

  mount_uploader :image, ImageUploader
end
