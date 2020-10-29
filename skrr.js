

function showHide()
{
    if(!document.getElementById) return;
    var heading1 = document.getElementById("heading1");
    var heading2 = document.getElementById("heading2");
    heading1.style.visibility=(showheading1) ? "visible" : "hidden";
    heading2.style.visibility=(showheading2) ? "visible" : "hidden";
}

function increment()
           {
               let counter =0;
               counter++;
               document.querySelector("#result").innerHTML = counter;
           }