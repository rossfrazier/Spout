class IngredientsController < ApplicationController
  def index
    @ingredients = Ingredient.all
    @ingredient = Ingredient.new
  end

  def create
    Ingredient.create(params[:ingredient])
    flash[:success] = "Ingredient added."
    redirect_to :back
  end

  def edit
    @ingredients = Ingredient.all
    @ingredient = Ingredient.find(params[:id])
    render 'index'
  end

  def update
    ingredient = Ingredient.find(params[:id])
    ingredient.update_attributes(params[:ingredient])
    flash[:success] = "Ingredient updated."
    redirect_to :back
  end

  def destroy
    ingredient = Ingredient.find(params[:id])
    ingredient.destroy
    flash[:info] = "Ingredient deleted."
    redirect_to :back
  end
end
