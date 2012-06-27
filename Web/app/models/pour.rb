class Pour < ActiveRecord::Base
  #a pour is an ingredient (which bottle?) and a volume (or pouring time) of that ingredient
  belongs_to :drink, :dependent=>:destroy
  belongs_to :ingredient

  def bottle
    self.ingredient.bottle
  end
end
