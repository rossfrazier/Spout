class MachinesController < ApplicationController
  def update
    machine = Machine.find(params[:id])
    machine.update_attributes(:active=>params[:machine][:active], :ip_address=>params[:machine][:ip_address])
    flash[:info] = "Machine status updated."
    redirect_to :back
  end
end