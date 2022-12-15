const screen = document.querySelector('.screen');


function buttonClick(value) {
    if (value.hasAttribute('calc-btn') == null) return;

    var message = onButtonClick(value.innerHTML);
    document.querySelector('.screen').innerHTML = message;
}


function init() {
    document.querySelector('.calculator-buttons').addEventListener('click', function(event) {
        buttonClick(event.target);
    });
}