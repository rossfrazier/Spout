class MachinesController < ApplicationController
  before_filter :assign_machine

  def assign_machine
    @machine = $machine
  end
  
  def index
  end

  def create
    @machine.start
    flash[:success] = "Drink order queue now active."
    redirect_to :back
  end

  def destroy
    @machine.stop
    flash[:error] = "Drink order queue now deactivated."
    redirect_to :back
  end

  def update
    @machine.ip_address = params[:ip_address]
    flash[:success] = "Spout web connection address updated to "+$machine.uri.to_s
    respond_to do |format|
      format.html {redirect_to :back}
      format.json {render :nothing=>true}
    end
  end

end