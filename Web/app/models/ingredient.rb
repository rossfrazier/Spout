class Ingredient < ActiveRecord::Base
  has_many :pours, :dependent=>:destroy
  has_many :drinks, :through=>:pours

  before_save do |ingredient|
  	ingredient.name = ingredient.name.titleize
  end

  def available
    return self.bottle.to_i > 0
  end

end
