
const socket = io('ws://localhost:8080');

socket.on('message', text => {

    const el = document.createElement('li');
    el.innerHTML = text;
    document.querySelector('ul').appendChild(el)

});


document.getElementById('b1').onclick = () => {

    const text = '0000';
    socket.emit('message', text)
    
}

document.getElementById('b2').onclick = () => {

    const text = '0001';
    socket.emit('message', text)
    
}

document.getElementById('b3').onclick = () => {

    const text = '0010';
    socket.emit('message', text)
    
}

document.getElementById('b4').onclick = () => {

    const text = '0011';
    socket.emit('message', text)
    
}

document.getElementById('b5').onclick = () => {

    const text = '0100';
    socket.emit('message', text)
    
}
document.getElementById('b6').onclick = () => {

    const text = '0101';
    socket.emit('message', text)
    
}
document.getElementById('b7').onclick = () => {

    const text = '0110';
    socket.emit('message', text)
    
}
document.getElementById('b8').onclick = () => {

    const text = '0111';
    socket.emit('message', text)
    
}
document.getElementById('b9').onclick = () => {

    const text = '1000';
    socket.emit('message', text)
    
}
document.getElementById('b10').onclick = () => {

    const text = '1001';
    socket.emit('message', text)
    
}
document.getElementById('b11').onclick = () => {

    const text = '1010';
    socket.emit('message', text)
    
}
document.getElementById('b12').onclick = () => {

    const text = '1011';
    socket.emit('message', text)
    
}
document.getElementById('b13').onclick = () => {

    const text = '1100';
    socket.emit('message', text)
    
}
document.getElementById('b14').onclick = () => {

    const text = '1101';
    socket.emit('message', text)
    
}
document.getElementById('b15').onclick = () => {

    const text = '1110';
    socket.emit('message', text)
    
}
document.getElementById('b16').onclick = () => {

    const text = '1111';
    socket.emit('message', text)
    
}
