//const http = require('http').createServer(app);

//const io = require('socket.io')(http, {
//   cors: { origin: "*" }
//});

const express = require("express");
const app = express();
const http = require("http").createServer(app);
const io = require("socket.io")(http);

var net = require('net');

var host = 'localhost';
var port = 8888;

var server = new net.createServer((socket) => {
  socket.on('data', (payload) => {
    console.log("payload", payload.toString('utf-8'));
    const ruta = payload.toString();
    const fs = require("fs");
    const data = fs.readFileSync("app/public/js/history.txt", "utf8");
    const a = JSON.parse(data);
    a.unshift(data);
    fs.writeFileSync("app/public/js/history.txt", JSON.stringify(a));

    const data2 = fs.readFileSync("app/public/js/dates.txt", "utf8");
    const dates = JSON.parse(data2);

    dates.unshift(getDateTimeFormat(new Date()));
    fs.writeFileSync("app/public/js/dates.txt", JSON.stringify(dates));

    io.emit("message", JSON.stringify(a));
    console.log('Request from', socket.remoteAddress, 'port', socket.remotePort);
    socket.write(`${ruta.toUpperCase()}\n`);
  });
  socket.on('end', () => {
    console.log('Closed', socket.remoteAddress, 'port', socket.remotePort);
  });
});

server.listen(8888);


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

app.get("/array", (req, res) => {
  const fs = require("fs");
  const data = fs.readFileSync("app/public/js/history.txt", "utf8");
  res.send(data);
});

app.get("/dates", (req, res) => {
  const fs = require("fs");
  const data = fs.readFileSync("app/public/js/dates.txt", "utf8");
  res.send(data);
});

io.on("connection", (socket) => {
  console.log("a user connected");

  socket.on("message", (message) => {
    const fs = require("fs");
    const data = fs.readFileSync("app/public/js/history.txt", "utf8");
    const a = JSON.parse(data);
    a.unshift(message);
    fs.writeFileSync("app/public/js/history.txt", JSON.stringify(a));

    const data2 = fs.readFileSync("app/public/js/dates.txt", "utf8");
    const dates = JSON.parse(data2);

    dates.unshift(getDateTimeFormat(new Date()));
    fs.writeFileSync("app/public/js/dates.txt", JSON.stringify(dates));

    io.emit("message", JSON.stringify(a));
  });
});

function getDateTimeFormat(pDate) {
  let day = pDate.getDate();
  let month = pDate.getMonth() + 1;
  let year = pDate.getFullYear();
  let hours = pDate.getHours();
  let minutes =
    pDate.getMinutes() > 9 ? pDate.getMinutes() : "0" + pDate.getMinutes();
  let dayTime = "";

  if (hours > 12) {
    hours = hours - 12;
    dayTime = "pm";
  } else {
    dayTime = "am";
  }

  return `${month}/${day}/${year} ${hours}:${minutes} ${dayTime}`;
}

http.listen(PORT, () => console.log("listening on http://localhost:8080"));
