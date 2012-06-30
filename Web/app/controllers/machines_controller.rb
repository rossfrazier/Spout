class MachinesController < ApplicationController
  def index
    @machine = $machine
  end

  def create
    $machine.start
    flash[:success] = "Drink order queue now active."
    redirect_to :back
  end

  def destroy
    $machine.stop
    flash[:error] = "Drink order queue now deactivated."
    redirect_to :back
  end

  def update
    $machine.ip_address = params[:ip_address]
    flash[:success] = "Spout web connection address updated to "+$machine.uri.to_s
    redirect_to :back
  end

end