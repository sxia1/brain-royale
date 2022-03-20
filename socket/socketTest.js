const SOCKET_URL = 'ws://localhost:8000';
const socket = new WebSocket(SOCKET_URL);

socket.addEventListener('open', function (event) {
    var newEvent = {type: 'connected', data: 'Howdy'};
    socket.send(JSON.stringify(newEvent));
});

socket.addEventListener('message', function (event) {
    console.log('Message from server ', JSON.parse(event.data));
});

var sendSomething = function(data) {
    var newEvent = {type: 'connected', data: data};
    socket.send(JSON.stringify(newEvent));
}