class OrdersController < ApplicationController
  def index
  	@orders = Order.all
  end

  def create
  	order = current_user.orders.create(:drink=>drink)
  end

  def update
  end

  def destroy
  end

end
