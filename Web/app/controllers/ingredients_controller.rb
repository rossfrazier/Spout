class IngredientsController < ApplicationController
	def create
		Ingredient.create(params[:ingredient])
		flash[:success] = "Ingredient added."
		redirect_to :back
	end
end
