const screen = document.querySelector('.screen');


function buttonClick(value) {
    if (!value.classList.contains('calc-btn')) return;

    
    var symbol = value.innerHTML;

    switch (symbol){
        case '←':
            symbol = '<';
            break;
        case '÷':
            symbol = '/';
            break;
        case '×':
            symbol = 'x';
            break;
        case '−':
            symbol = '-';
            break;
    }
    

    var message = onButtonClick(symbol);
    //document.querySelector('.screen').innerHTML = message;
}

function printScreen(msg) {
    document.querySelector('.screen').innerHTML = msg;
}

function init() {
    const btns = document.querySelectorAll('.calc-btn');
    btns.forEach((btn) => {
        btn.addEventListener('click', function(event) { buttonClick(event.target); })
    });
}