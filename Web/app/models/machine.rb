class Machine < ActiveRecord::Base
  #kind of a singleton: a machine represents the machine's state (is it pouring?, is it broken?)

  def self.bottles
    return 5
  end

  def reset_chomper!
    self.update_attributes(:chomping=>false)
  end
end