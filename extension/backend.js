var turntableTab = null;

var wsUri = "ws://localhost:1337";
var websocket = null;
var state = false;

chrome.browserAction.onClicked.addListener(function(tab) {
   if (state) { stopWebsocket(); }
   else       { initWebsocket(); }
});

chrome.extension.onConnect.addListener(function (port) {
   port.onMessage.addListener(function (data) {
      var params = JSON.parse(data);
      if (websocket) {
         if (params.command == 'speak') {
            websocket.send('<b>'+params.name + ':</b> ' + params.text);
         }
      }
   });
});


function onRequest(request, sender, callback) {
   switch (request.action) {
      case 'initWebsocket': initWebsocket();         break;
      case 'stopWebsocket': stopWebsocket();         break;
      case 'checkSocket':   callback(checkSocket()); break;
   }
}

function initWebsocket() {
   try {
      if (typeof MozWebSocket == 'function')
      WebSocket = MozWebSocket;
      websocket = new WebSocket(wsUri);
      websocket.onopen = function (evt) {
         chrome.browserAction.setIcon({ path: 'bullet_green.png' })
         state = true;
      };
      websocket.onclose = function (evt) {
         chrome.browserAction.setIcon({ path: 'bullet_red.png' })
         state = false;
      };
      websocket.onmessage = function (evt) {
         console.log( evt.data );
      };
      websocket.onerror = function (evt) {
         console.log('ERROR: ' + evt.data);
      };
   } catch (exception) {
      chrome.browserAction.setIcon({ path: 'bullet_red.png' })
      state = false;
      console.log('ERROR: ' + exception);
   }
}

function stopWebsocket() {
   if (websocket) {
      websocket.close();
      chrome.browserAction.setIcon({ path: 'bullet_red.png' })
      state = false;
   }
}

function checkSocket() {
   if ( websocket != null ) {
      var stateStr;
      switch (websocket.readyState) {
      case 0:  stateStr = "CONNECTING"; break;
      case 1:  stateStr = "OPEN";       break;
      case 2:  stateStr = "CLOSING";    break;
      case 3:  stateStr = "CLOSED";     break;
      default: stateStr = "UNKNOW";     break;
      }
      console.log("Websocket state = " + websocket.readyState + " ( " + stateStr + " )");
      return stateStr;
   } else {
      console.log("Websocket is null");
      return 'Websocket is null';
   }
}


function onRemoved(tabId) {
   if (turntableTab == tabId) {
      turntableTab = null;
   }
}


chrome.extension.onRequest.addListener(onRequest);
chrome.tabs.onRemoved.addListener(onRemoved);
