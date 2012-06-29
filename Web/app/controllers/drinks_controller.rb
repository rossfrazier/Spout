class DrinksController < ApplicationController
  before_filter :authenticate!

  def index
    @drinks = Drink.order('name').limit(25).includes(:ingredients)
  end

  def show
    @drink = Drink.find(params[:id], :include=>[:ingredients])
  end

  def new
    @drink = Drink.new
    @ingredients = Ingredient.all
    @pour_ids=Array.new

    $machine.bottle_count.times { @drink.pours.build }
  end

  def create
    drink = Drink.new
    drink.name = params[:drink][:name]
    drink.image = params[:drink][:image]
    params[:drink][:pours].each do |pour|
      drink.pours.build(:ingredient=>Ingredient.find(pour[:ingredient].to_i), :seconds=>pour[:seconds]) if !pour[:seconds].blank?
    end
    drink.save!
    flash[:success]="New drink added!"
    redirect_to drinks_path
  end

  def edit
    @drink = Drink.find(params[:id])
    @pour_ids = @drink.pour_ids
    new_ingredient_fields_to_be_added = $machine.bottle_count - @pour_ids.length
    new_ingredient_fields_to_be_added.times { |x| @pour_ids << "new"+x.to_s; @drink.pours.build }
    @ingredients = Ingredient.all
  end

  def update
    drink = Drink.find(params[:id])
    drink.name = params[:drink][:name]
    drink.image = params[:drink][:image]
    drink.remove_image = params[:drink][:remove_image]
    params[:drink][:pours].each do |pour_id,pour|
      if pour_id[0..2]=="new"
        if pour[:seconds].to_i > 0
          new_pour = drink.pours.build(:ingredient_id=>Ingredient.find(pour[:ingredient].to_i), :seconds=>pour[:seconds].to_i)
        end
      else
        existing_pour = drink.pours.find(pour_id)
        existing_pour.destroy and next if pour[:ingredient].to_i==0
        ingredient = Ingredient.find(pour[:ingredient].to_i)
        existing_pour.ingredient = ingredient
        existing_pour.seconds = pour[:seconds].to_i
        existing_pour.save! if existing_pour.changed?
      end
    end
    drink.save!
    flash[:success] = drink.name + " updated."
    redirect_to drinks_path
  end

  def destroy
    drink = Drink.find(params[:id])
    drink.destroy
    flash[:info] = "Drink deleted."
    redirect_to :back
  end

end
