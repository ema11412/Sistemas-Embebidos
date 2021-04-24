
//const http = require('http').createServer(app);

//const io = require('socket.io')(http, {
 //   cors: { origin: "*" }
//});


const express = require("express");
const app = express();
const http = require("http").createServer(app);
const io = require("socket.io")(http);

const PORT = process.env.PORT || 8080;


app.use(express.static(__dirname));

app.get("/", (req, res) => {
  res.sendFile(__dirname + `/app/login.html`);
});

app.get("/login", (req, res) => {
    res.sendFile(__dirname + `/app/login.html`);
  });

app.get("/smart", (req, res) => {
    res.sendFile(__dirname + `/app/smartView.html`);
  });

  app.get("/test", (req, res) => {
    res.sendFile(__dirname + `/app/test.html`);
  });
  
doors = '0000'

f1=0;f2=0;f3=0,f4=0;f5=0;

f10=0;

io.on('connection', (socket) => {
    console.log('a user connected');

    socket.on('message', (message) =>     {
        
        tmp0 = message
        tmp = Object.values(message)[0]
        if(tmp0=='foto'){
            io.emit('message', `foto` );
        }
        if(typeof(tmp0) != "string"){

            switch (tmp) {
                case 'btn1':
                    if (f1 == 0){
                        io.emit('message', `Lo1` );  
                        f1=1;
                    }
                    else{
                        io.emit('message', `Lc1` );  
                        f1=0;
                    }
                  break;
                case 'btn2':
                    if (f2 == 0){
                        io.emit('message', `Lo2` );  
                        f2=1;
                    }
                    else{
                        io.emit('message', `Lc2` );  
                        f2=0;
                    }
                  break;
                case 'btn3':
                    if (f3 == 0){
                        io.emit('message', `Lo3` );  
                        f3=1;
                    }
                    else{
                        io.emit('message', `Lc3` );  
                        f3=0;
                    }
                  break;
                case 'btn4':
                    if (f4 == 0){
                        io.emit('message', `Lo4` );  
                        f4=1;
                    }
                    else{
                        io.emit('message', `Lc4` );  
                        f4=0;
                    }
                  break;
                case 'btn5':
                    if (f5 == 0){
                        io.emit('message', `Lo5` );  
                        f5=1;
                    }
                    else{
                        io.emit('message', `Lc5` );  
                        f5=0;
                    }
                  break;
    
                  case 'mainbtn':
                    if (f10 == 0){
                        io.emit('message', `Lo10` );  
                        f1=1;f2=1;f3=1;f4=1;f5=1;f10=1;
                    }
                    else{
                        io.emit('message', `Lc10` );  
                        f1=0;f2=0;f3=0;f4=0;f5=0;f10=0;
                    }
                  break;
    
                default:        
        }
        }else{

        state = xOr(doors,tmp0)

        switch(state){
            case '0000':
                /* nada */
                break;
            case '0001':
                io.emit('message', `0001` );  
                doors = tmp0;
                break;
            case '0010':
                io.emit('message', `0010` );
                doors = tmp0;  
                break;
            case '0011':
                io.emit('message', `0010` ); 
                io.emit('message', `0001` ); 
                doors = tmp0;
                break;
            case '0100':
                io.emit('message', `0100` ); 
                doors = tmp0; 
                break;
            case '0101':
                io.emit('message', `0100` ); 
                io.emit('message', `0001` ); 
                doors = tmp0;
                break;
            case '0110':
                io.emit('message', `0100` ); 
                io.emit('message', `0010` ); 
                doors = tmp0;
                break;
            case '0111':
                io.emit('message', `0001` );  
                io.emit('message', `0100` ); 
                io.emit('message', `0010` ); 
                doors = tmp0;
                break;
            case '1000':
                io.emit('message', `1000` );  
                doors = tmp0;
                break;
            case '1001':
                io.emit('message', `1000` );  
                io.emit('message', `0001` ); 
                doors = tmp0;
                break;
            case '1010':
                io.emit('message', `1000` );  
                io.emit('message', `0010` ); 
                doors = tmp0;
                break;
            case '1011':
                io.emit('message', `1000` );  
                io.emit('message', `0010` ); 
                io.emit('message', `0001` ); 
                doors = tmp0; 
                break;
            case '1100':
                io.emit('message', `1000` );  
                io.emit('message', `0100` );  
                doors = tmp0;
                break;
            case '1101':
                io.emit('message', `1000` );  
                io.emit('message', `0100` ); 
                io.emit('message', `0001` ); 
                doors = tmp0;
                break;
            case '1110':
                io.emit('message', `1000` );  
                io.emit('message', `0100` ); 
                io.emit('message', `0010` ); 
                doors = tmp0; 
                break;
            case '1111':
                io.emit('message', `1000` );  
                io.emit('message', `0100` ); 
                io.emit('message', `0010` ); 
                io.emit('message', `0001` ); 
                doors = tmp0;
                break;   
            
            default:
                
        }
        }
        
    });
});


//comparar el cambio de puertas
function xOr(input,key) {
    var c = '';
    while (key.length < input.length) {
         key += key;
    }
    for(var i=0; i<input.length; i++) {
        var value1 = input[i].charCodeAt(0);
        var value2 = key[i].charCodeAt(0);

        var xorValue = value1 ^ value2;

        c += xorValue;
    }
    return c;
}

http.listen(PORT, () => console.log('listening on http://localhost:8080') );

