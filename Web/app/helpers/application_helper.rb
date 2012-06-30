module ApplicationHelper
  def machine_form_setup
    if @machine.running
      @label = "Deactivate the queue"
      @method = :delete
    else
      @label = "Activate the queue"
      @method = nil
    end
  end
end
