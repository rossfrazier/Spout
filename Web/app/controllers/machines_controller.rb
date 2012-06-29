class MachinesController < ApplicationController
  def index
    @machine = $machine
    if @machine.running
      @label = "Deactivate the queue"
      @method = :delete
    else
      @label = "Activate the queue"
      @method = nil
    end
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

end