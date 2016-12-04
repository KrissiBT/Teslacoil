$( document ).ready(function() {
  console.log("redt");
});
var myVar = setInterval(seeState, 500);

function seeState() {
  jQuery.get('stat.txt', function(data) {
   if (data == "1") {
     $("#pic").attr("src","on.png");
   }
   else {
      $("#pic").attr("src","off.png");
   }
   console.log(data);
});
}


$("#takki").click(function() {
  $.get("changeState.php");
  console.log("boop");
});
