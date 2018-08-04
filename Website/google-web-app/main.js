/**
 * Listens for the app launching then creates the window
 *
 * @see http://developer.chrome.com/apps/app.window.html
 */

chrome.app.runtime.onLaunched.addListener(function() {


	chrome.app.window.create('index.html', {
		id: 'main',
		bounds: { width: 620, height: 500 }
	});


	if(chrome.runtime.lastError) {
		// Something went wrong
		console.log("Whoops.. " + chrome.runtime.lastError.message);
		// Maybe explain that to the user too?
	} else {
		// No errors, you can use entry
	}

});

