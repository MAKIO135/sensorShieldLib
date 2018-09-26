let pot1 = 0

addEventListener( 'load', e => {
    const socket = io()
    socket.on( 'data', data => {
        console.log( data )
        pot1 = data.pot1
    } )
} )

function setup() {
    createCanvas( 500, 500 )

    noStroke()
    fill( 255 )
}

function draw() {
    background( pot1 / 4 )
    
    let x = map( pot1, 0, 1023, 0, width )
    ellipse( x, height / 2, 100 )
}