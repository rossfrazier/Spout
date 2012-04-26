class Ingredient < ActiveRecord::Base
  has_many :pours, :dependent=>:destroy
  has_many :drinks, :through=>:pours

  def available
    return self.bottle.to_i > 0
  end

end
