class OrdersController < ApplicationController
  def index
  	@orders = Order.all
  end

  def create
    drink = Drink.find(params[:drink])
  	order = current_user.orders.create(:drink_id=>drink.id)
  end

  def update
  end

  def destroy
  end

end
