
const socket = io('ws://localhost:8080');

socket.on('message', text => {

    const el = document.createElement('li');
    el.innerHTML = text;
    document.querySelector('ul').appendChild(el)

});


document.getElementById('b1').onclick = () => {

    const text = '/../cam/imgN.jpg';
    socket.emit('message', text)
    
}
