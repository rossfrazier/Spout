class Pour < ActiveRecord::Base
	belongs_to :drink
	belongs_to :ingredient

	def bottle
		self.ingredient.bottle
	end
end
