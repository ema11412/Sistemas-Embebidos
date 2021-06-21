//Soket
const socket = io("ws://localhost:8080");

update();

socket.on("message", (img) => {
  const a = JSON.parse(img);
  updateNew(a);
});

function getSate() {
  socket.emit("message", "foto");
}

function updateNew(a) {
  try {
    alert("Nueva foto capturada");
    fetch("http://localhost:8080/dates")
      .then((response) => response.json())
      .then((data) => {
        const x = data;
        document.getElementById("i1").innerText = x[0];
        document.getElementById("i2").innerText = x[1];
        document.getElementById("i3").innerText = x[2];
        document.getElementById("i4").innerText = x[3];
        document.getElementById("i5").innerText = x[4];
        document.getElementById("i6").innerText = x[5];
      });
    document.getElementById("img1").src = a[0];
    document.getElementById("img2").src = a[1];
    document.getElementById("img3").src = a[2];
    document.getElementById("img4").src = a[3];
    document.getElementById("img5").src = a[4];
    document.getElementById("img6").src = a[5];

    //console.log(data)
  } catch (err) {
    console.error(err);
  }
}

function update() {
  fetch("http://localhost:8080/array")
    .then((response) => response.json())
    .then((data) => {
      const a = data;
      document.getElementById("img1").src = a[0];
      document.getElementById("img2").src = a[1];
      document.getElementById("img3").src = a[2];
      document.getElementById("img4").src = a[3];
      document.getElementById("img5").src = a[4];
      document.getElementById("img6").src = a[5];
    });
  fetch("http://localhost:8080/dates")
    .then((response) => response.json())
    .then((data) => {
      const x = data;
      document.getElementById("i1").innerText = x[0];
      document.getElementById("i2").innerText = x[1];
      document.getElementById("i3").innerText = x[2];
      document.getElementById("i4").innerText = x[3];
      document.getElementById("i5").innerText = x[4];
      document.getElementById("i6").innerText = x[5];
    });
}

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

let imgs = document.getElementsByClassName("content-image");
let banner = document.getElementsByClassName("cosafea");

console.log(banner);

// for (let i in 6) {
//   tmp = document.banner[i];
//   img = document.imgs[i];
//   modalImg = document.getElementById("img01");
//   console.log(modalImg);
//   tmp.onclick = function () {
//     modal.style.display = "block";
//     modalImg.src = img.src;
//   };
// }

update();

modalImg = document.getElementById("img01");
modal = document.getElementById("myModal");

tmp1 = document.getElementById("imgx1");
img1 = document.getElementById("img1");
console.log(modalImg);
tmp1.onclick = function () {
  modal.style.display = "block";
  modalImg.src = img1.src;
};

tmp2 = document.getElementById("imgx2");
img2 = document.getElementById("img2");
console.log(modalImg);
tmp2.onclick = function () {
  modal.style.display = "block";
  modalImg.src = img2.src;
};

tmp3 = document.getElementById("imgx3");
img3 = document.getElementById("img3");
console.log(modalImg);
tmp3.onclick = function () {
  modal.style.display = "block";
  modalImg.src = img3.src;
};

tmp4 = document.getElementById("imgx4");
img4 = document.getElementById("img4");
console.log(modalImg);
tmp4.onclick = function () {
  modal.style.display = "block";
  modalImg.src = img4.src;
};

tmp5 = document.getElementById("imgx5");
img5 = document.getElementById("img5");
console.log(modalImg);
tmp5.onclick = function () {
  modal.style.display = "block";
  modalImg.src = img5.src;
};

tmp6 = document.getElementById("imgx6");
img6 = document.getElementById("img6");
console.log(modalImg);
tmp6.onclick = function () {
  modal.style.display = "block";
  modalImg.src = img6.src;
};
// Get the <span> element that closes the modal
let span = document.getElementsByClassName("close")[0];

// When the user clicks on <span> (x), close the modal
span.onclick = function () {
  modal.style.display = "none";
};
