class Pour < ActiveRecord::Base
  belongs_to :drink, :dependent=>:destroy
  belongs_to :ingredient

  def bottle
    self.ingredient.bottle
  end
end
