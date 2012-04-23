class Ingredient < ActiveRecord::Base
	has_many :pours

	def available
		return self.bottle.to_i > 0
	end
end
