// This function will be called everytime some valid JSON data are received:
function onData (data) {
	// Do your own stuff here...
	console.log(data);

	// A bit of visual feedback:
	$('.feedback').stop().animate({opacity: 1}, 50, function(elt) {
	    $('.feedback').animate({opacity: 0}, 50);
	});
}

// Automatically get the WebSocket URI based on the HTTP server location (zero conf):
function getWebSocketURI () {
    var loc = window.location;
    return ((loc.protocol === 'https:') ? 'wss://' : 'ws://') + loc.hostname + (((loc.port != 80) && (loc.port != 443)) ? ':' + loc.port : '') + loc.pathname;
}

// Should work on most "modern" browsers:
var ws = new WebSocket(getWebSocketURI());
ws.onmessage = function (event) {
	try {
		onData(JSON.parse(event.data));
	} catch (e) {
		console.log('Error while processing serial data:', e);
	}
};
