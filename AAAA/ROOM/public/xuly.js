var socket = io("http://localhost:3000");

socket.on("server-send-rooms", function(data){
  $("#dsRoom").html("");
  data.map(function(r){
    $("#dsRoom").append("<h4 class='room'>" + r + "</h4>");
  });
});

socket.on("server-send-room-socket", function(data){
  $("#roomHienTai").html(data);
});

socket.on("server-send", function(data){
  $("#right").append("<div>" + data + "</div>");
  aler('hello');
  alert('data:',data);
});
socket.on("send-data", function(data){
  $("#jsonob").append("<div>" + data + "</div>");
  document.getElementById("jsonob").innerHTML = myJSON;
});

$(document).ready(function(){
  $("#btnTaoRoom").click(function(){
    socket.emit("tao-room", $("#txtRoom").val());
  });

  $("#btnChat").click(function(){
    socket.emit("user-chat", $("#txtMessage").val());
  });
});

