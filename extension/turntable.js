var customEvent = document.createEvent('Event');
customEvent.initEvent('myCustomEvent', true, true)

var data_gatherer = document.getElementById('data_gatherer');
var data_receiver = document.getElementById('data_receiver');


var tt = { socket: null, roomid: null };

// Find the right object.
var request_re = / Preparing message /i, x = null;
for (x in turntable) {
   if (typeof turntable[x] === "function") {
      turntable[x].toString = Function.prototype.toString;
      if (request_re.test(turntable[x].toString())) {
         tt.socket = turntable[x];
         break;
      }
   }
}


data_receiver.addEventListener('myReceiverEvent', function () {
   var eventData = document.getElementById('data_receiver').innerText;
   var data = JSON.parse(eventData);

   // Get the roomid.
   for (var i in turntable) {
      if (turntable[i] && turntable[i].roomId) {
         tt.roomid = turntable[i].roomId;
         break;
      }
   }

   tt.socket({"api":"room.speak","roomid":tt.roomid,"text":data});
});


function message(data) {
   data_gatherer.innerText = JSON.stringify(data);
   data_gatherer.dispatchEvent(customEvent);
}

turntable.addEventListener('message', message);
