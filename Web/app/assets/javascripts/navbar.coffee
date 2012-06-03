jQuery ->
	$(document).ready ->
		activeController = $('#main-navbar').data('active');
		$('#main-navbar li#'+activeController).addClass('active');