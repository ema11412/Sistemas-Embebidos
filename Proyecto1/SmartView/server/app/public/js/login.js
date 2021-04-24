window.onload = function(){

    document.getElementById("loginForm").onsubmit = function() {
      var username = document.getElementById("username").value;
      var password = document.getElementById("password").value;
  
      if (username === "Nero" &&
        password === "yep") {
        
        location.href = "/smart";
      } else {
        alert("Datos incorrectos");
        //location.href = "index1.html";
      }
      // to prevent submit
      return false;
    }
  }