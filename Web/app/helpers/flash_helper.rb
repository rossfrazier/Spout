module FlashHelper

def flash_message_helper
	output = String.new
	flash.each do |key,value|
		output+=generate_alert_box(key,value)
	end
	return output.html_safe
end

def generate_alert_box(key,value)
	case key
	when :error
		type = "alert-error"
	when :success
		type = "alert-success"
	when :info
		type = "alert-info"
	else
		type=""
	end

	output = '<div class="alert '+type+'"><a class="close" data-dismiss="alert">x</a>'+value+'</div>'
	return output
end

end