//Soket 
const socket = io('ws://localhost:8080');



socket.on('message', door => {
    switch(door){
        case '1000':
            mydiv11.classList.toggle("onflashDoorOpen");
            break;
        case '0100':
            mydiv8.classList.toggle("onflashDoorOpen");
            break;
        case '0010':
            mydiv9.classList.toggle("onflashDoorOpen");
            break;
        case '0001':
            mydiv10.classList.toggle("onflashDoorOpen");
            break;
    }


});




/***********************************************NavBar**************************************************/
(function($) { // Begin jQuery
    $(function() { // DOM ready
      // If a link has a dropdown, add sub menu toggle.
      $('nav ul li a:not(:only-child)').click(function(e) {
        $(this).siblings('.nav-dropdown').toggle();
        // Close one dropdown when selecting another
        $('.nav-dropdown').not($(this).siblings()).hide();
        e.stopPropagation();
      });
      // Clicking away from dropdown will remove the dropdown class
      $('html').click(function() {
        $('.nav-dropdown').hide();
      });
      // Toggle open and close nav styles on click
      $('#nav-toggle').click(function() {
        $('nav ul').slideToggle();
      });
      // Hamburger to X toggle
      $('#nav-toggle').on('click', function() {
        this.classList.toggle('active');
      });
    }); // end DOM ready
  })(jQuery); // end jQuery
  
/************************************************************************************************************** */
/*vars for logic control*/
c1= 0;c2= 0;c3= 0;c4= 0; c5 = 0; c7 =0;





/****************************************************Lights*******************************************************/
/*Turn on and off light 1*/
var mydiv1 = document.getElementById("flash1"),
	myButton1 = document.getElementById("btn1");
    myButton1.onclick = function lol() {
	"use strict";
    mydiv1.classList.toggle("onflash");
    c1++;
    if(c1%2 !=0 && c2%2 !=0 && c3%2 !=0 && c4%2 !=0 && c5%2 !=0 ){
        mydiv7.classList.toggle("onflashmain");

        c7++;
    }
    if((c1%2 ==0 || c2%2 ==0 || c3%2 ==0 || c4%2 ==0 || c5%2 ==0 ) && c7%2!=0){
        mydiv7.classList.toggle("onflashmain");
        c7++;
    }
};

/*Turn on and off light 2*/
var mydiv2 = document.getElementById("flash2"),
	myButton2 = document.getElementById("btn2");
myButton2.onclick = function lol() {
	"use strict";
    mydiv2.classList.toggle("onflash");
    c2++;
    if(c1%2 !=0 && c2%2 !=0 && c3%2 !=0 && c4%2 !=0 && c5%2 !=0 ){
        mydiv7.classList.toggle("onflashmain");
        c7++;
    }
    if((c1%2 ==0 || c2%2 ==0 || c3%2 ==0 || c4%2 ==0 || c5%2 ==0 ) && c7%2!=0){
        mydiv7.classList.toggle("onflashmain");
        c7++;
    }
};

/*Turn on and off light 3*/
var mydiv3 = document.getElementById("flash3"),
	myButton3 = document.getElementById("btn3");
myButton3.onclick = function lol() {
	"use strict";
    mydiv3.classList.toggle("onflash");
    c3++;
    if(c1%2 !=0 && c2%2 !=0 && c3%2 !=0 && c4%2 !=0 && c5%2 !=0 ){
        mydiv7.classList.toggle("onflashmain");
        c7++;
    }
    if((c1%2 ==0 || c2%2 ==0 || c3%2 ==0 || c4%2 ==0 || c5%2 ==0 ) && c7%2!=0){
        mydiv7.classList.toggle("onflashmain");
        c7++;
    }
};

/*Turn on and off light 4*/
var mydiv4 = document.getElementById("flash4"),
	myButton4 = document.getElementById("btn4");
myButton4.onclick = function lol() {
	"use strict";
    mydiv4.classList.toggle("onflash");
    c4++;
    if(c1%2 !=0 && c2%2 !=0 && c3%2 !=0 && c4%2 !=0 && c5%2 !=0 ){
        mydiv7.classList.toggle("onflashmain");
        c7++;
    }
    if((c1%2 ==0 || c2%2 ==0 || c3%2 ==0 || c4%2 ==0 || c5%2 ==0 ) && c7%2!=0){
        mydiv7.classList.toggle("onflashmain");
        c7++;
    }
};

/*Turn on and off light 5*/
var mydiv5 = document.getElementById("flash5"),
	myButton5 = document.getElementById("btn5");
myButton5.onclick = function lol() {
	"use strict";
    mydiv5.classList.toggle("onflash");
    c5++;
    if(c1%2 !=0 && c2%2 !=0 && c3%2 !=0 && c4%2 !=0 && c5%2 !=0 ){
        mydiv7.classList.toggle("onflashmain");
        c7++;
    }
    if((c1%2 ==0 || c2%2 ==0 || c3%2 ==0 || c4%2 ==0 || c5%2 ==0 ) && c7%2!=0){
        mydiv7.classList.toggle("onflashmain");
        c7++;
    }
};




/*Turn on and off main light*/
var mydiv7 = document.getElementById("mainflash"),
	myButton7 = document.getElementById("mainbtn");
myButton7.onclick = function lol() {
    "use strict";
    if(c7%2==0){
        if(c1%2==0){
            mydiv1.classList.toggle("onflash");
            c1++;
        }
        if(c2%2==0){
            mydiv2.classList.toggle("onflash");
            c2++;
        }
        if(c3%2==0){
            mydiv3.classList.toggle("onflash");
            c3++;
        }
        if(c4%2==0){
            mydiv4.classList.toggle("onflash");
            c4++;
        }
        if(c5%2==0){
            mydiv5.classList.toggle("onflash");
            c5++;
        }
        mydiv7.classList.toggle("onflashmain");
    }
    else{
        if(c1%2!=0){
            mydiv1.classList.toggle("onflash");
            c1++;
        }
        if(c2%2!=0){
            mydiv2.classList.toggle("onflash");
            c2++;
        }
        if(c3%2!=0){
            mydiv3.classList.toggle("onflash");
            c3++;
        }
        if(c4%2!=0){
            mydiv4.classList.toggle("onflash");
            c4++;
        }
        if(c5%2!=0){
            mydiv5.classList.toggle("onflash");
            c5++;
        }
        mydiv7.classList.toggle("onflashmain");
    }
    c7++;
};

/*****************************************************Doors***************************************************/

/*Turn on and off light Door 1*/
var mydiv11 = document.getElementById("flashD1");


var mydiv8 = document.getElementById("flashD2");

/*Turn on and off light Door 3*/
var mydiv9 = document.getElementById("flashD3");

/*Turn on and off light Door 4*/
var mydiv10 = document.getElementById("flashD4");


$('.button').click(function(){
    var buttonId = $(this).attr('id');
    $('#modal-container').removeAttr('class').addClass(buttonId);
    $('body').addClass('modal-active');
    
  })
  
  $('#modal-container').click(function(){
    $(this).addClass('out');
    $('body').removeClass('modal-active');
  });

//Send message to socket, lux
$(".btn").click((element) => {
    let thisBtn = element.target;
    let message = {
        message: $(thisBtn).attr("id")
    };
    socket.emit('message', message);
})


$(".mainbtn").click((element) => {
    let thisBtn = element.target;
    let message = {
        message: $(thisBtn).attr("id")
    };
    socket.emit('message', message);
})

function imagen(){
    socket.emit('message', 'foto');
}