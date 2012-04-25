class Machine < ActiveRecord::Base
  def self.bottles
    return 5
  end

  def reset_chomper!
  	self.update_attributes(:chomping=>false)
  end
end