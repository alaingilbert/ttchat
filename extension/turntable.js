var customEvent = document.createEvent('Event');
customEvent.initEvent('myCustomEvent', true, true)

var data_gatherer = document.getElementById('data_gatherer');
var data_receiver = document.getElementById('data_receiver');


data_receiver.addEventListener('myReceiverEvent', function () {
   var eventData = document.getElementById('data_receiver').innerText;
   var data = JSON.parse(eventData);

   // Find the right object.
   var request_re = / Preparing message /i, x = null, rq = null;
   for (x in turntable) {
      if (typeof turntable[x] === "function") {
         turntable[x].toString = Function.prototype.toString;
         if (request_re.test(turntable[x].toString())) {
            rq = turntable[x];
            break;
         }
      }
   }
   // Get the roomid.
   for (var i in turntable) { if (turntable[i].roomId) { var rid = turntable[i].roomId; break; } }

   rq({"api":"room.speak","roomid":rid,"text":data});
});


function message(data) {
   data_gatherer.innerText = JSON.stringify(data);
   data_gatherer.dispatchEvent(customEvent);
}

turntable.addEventListener('message', message);
