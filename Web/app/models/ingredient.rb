class Ingredient < ActiveRecord::Base
  #an ingredient is tied directly to a bottle, and is poured into a drink.
  has_many :pours, :dependent=>:destroy
  has_many :drinks, :through=>:pours

  before_save do |ingredient|
    ingredient.name = ingredient.name.titleize
  end

  def available
    return self.bottle.to_i > 0
  end

end
