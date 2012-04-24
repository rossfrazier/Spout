module Chomper

def self.next
	Order.pending.order('updated_at DESC').first
end

def self.chomp!
	machine = Machine.first
	@@machine_ip = machine.ip_address
	return false if machine.chomping

	Thread.new do
		machine.update_attributes(:chomping=>true)
		while machine.chomping do
			if order = Order.next
				order.update_attributes(:completed=>order.request_sent?)
			else
				machine.update_attributes(:chomping=>false)
			end
		end
	end
end

private

def request_sent?
	self.send_request
end

def send_request
	uri = URI.parse('http://'+@@machine_ip+'/spout')
	params = Hash.new
	self.pours.each do |pour|
		pour.bottle
		params['p'+pour.bottle.to_s] = pour.seconds
	end

	response = Net::HTTP.post_form(uri, params)
	return response.code == 200
end

end