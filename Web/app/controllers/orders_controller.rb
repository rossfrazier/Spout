class OrdersController < ApplicationController
  def index
  	@pending_orders = Order.pending
    @completed_orders = Order.completed
  end

  def create
  	order = current_user.orders.create(:drink_id=>params[:drink])
    flash[:success] = "Drink ordered."
    redirect_to orders_path
  end

  def update
    order = Order.find(params[:id])
    order.update_attributes(:drink_id=>params[:drink])
    flash[:info] = "Order updated."
    redirect_to orders_path
  end

  def destroy
    order = Order.find(params[:id])
    order.destroy
    flash[:info] = "Order cancelled."
    redirect_to orders_path
  end

end
