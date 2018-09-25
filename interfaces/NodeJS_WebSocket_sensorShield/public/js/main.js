const socket = io()
let pot1 = 0

socket.on( 'data', data => {
    console.log( data )
    pot1 = data.pot1
} )

function setup() {
    createCanvas( 500, 500 )
}

function draw() {
    background( pot1 / 4 )
}