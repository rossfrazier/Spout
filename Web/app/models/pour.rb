class Pour < ActiveRecord::Base
	belongs_to :drink
	belongs_to :ingredient
end
