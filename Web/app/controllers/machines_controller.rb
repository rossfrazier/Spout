class MachinesController < ApplicationController
  def update
    machine = Machine.find(params[:id])
    machine.update_attributes(:active=>params[:machine][:active], :ip_address=>params[:machine][:ip_address])
    machine.reset_chomper!
    flash[:info] = "Machine status updated."
    redirect_to :back
  end

  def create
  	render :status => 200
  end
end