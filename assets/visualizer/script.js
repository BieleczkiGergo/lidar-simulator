const canvas = document.getElementById("canvas");
const mapInput = document.getElementById("map");
const measureInput = document.getElementById("measure");
const pathInput = document.getElementById("path");

const leftInfo = document.getElementById("left-info");
const rightInfo = document.getElementById("right-info");

const ctx = canvas.getContext("2d");

// The canvas has a width of 800px and a height of 600px, and it's middle is at 400;300
const WIDTH = 800;
const HEIGHT = 600;
const CANVAS_LEFT = canvas.getBoundingClientRect().left;
const CANVAS_TOP = canvas.getBoundingClientRect().top;
let scale = 10;

let map = {
    "horizontal": [],
    "vertical": []

};
let measure = [];
let origin = [];
let pos = [];
let path = [];

function scaleX(x){
    return (WIDTH / 2) + (x * scale);

}

function scaleY(y){
    return (HEIGHT / 2) - (y * scale);

}

function drawLidar( scale = 10 ){

    // clear canvas before drawing anything: set it all to rgb(140, 140, 140)
    ctx.beginPath();
    ctx.fillStyle = "rgb(140, 140, 140)";
    ctx.fillRect(0, 0, WIDTH, HEIGHT);

    ctx.fillStyle = "#ff0000";
    
    // draw position
    const crossSize = 0.5;
    ctx.beginPath();
    ctx.strokeStyle = "green";
    ctx.moveTo((WIDTH / 2) + ((pos[0] - crossSize) * scale), (HEIGHT / 2) - ((pos[1] - crossSize) * scale));
    ctx.lineTo((WIDTH / 2) + ((pos[0] + crossSize) * scale), (HEIGHT / 2) - ((pos[1] + crossSize) * scale));
    ctx.moveTo((WIDTH / 2) + ((pos[0] - crossSize) * scale), (HEIGHT / 2) - ((pos[1] + crossSize) * scale));
    ctx.lineTo((WIDTH / 2) + ((pos[0] + crossSize) * scale), (HEIGHT / 2) - ((pos[1] - crossSize) * scale));
    ctx.stroke();
    

    // draw map
    ctx.strokeStyle = "#000000";

    map["horizontal"].forEach( barrier => {
        ctx.beginPath();
        ctx.moveTo( (WIDTH / 2) + (barrier.start * scale), (HEIGHT / 2) + (barrier.pos * scale) );
        ctx.lineTo( (WIDTH / 2) + (barrier.end * scale), (HEIGHT / 2) + (barrier.pos * scale) );
        ctx.stroke();

    });

    map["vertical"].forEach( barrier => {
        ctx.beginPath();
        ctx.moveTo( (WIDTH / 2) + (barrier.pos * scale), (HEIGHT / 2) - (barrier.start * scale) );
        ctx.lineTo( (WIDTH / 2) + (barrier.pos * scale), (HEIGHT / 2) - (barrier.end * scale) );
        ctx.stroke();

    });


    // draw measure
    measure.forEach( coords => {
        const x = coords[0];
        const y = coords[1];

        ctx.beginPath();
        ctx.arc((WIDTH / 2) + (x * scale), (HEIGHT / 2) - (y * scale), 1, 0, 2*Math.PI);
        ctx.fill();

    });


    // draw path
    ctx.beginPath();
    ctx.moveTo( scaleX( path[0][0] ), scaleY( path[0][1] ) );

    path.slice( 1 ).forEach(( [ x, y ] ) => {
        ctx.lineTo( scaleX(x), scaleY(y) );

    });
    ctx.stroke();

    ctx.strokeStyle = "#00ff00";
    path.forEach( ([x, y]) => {
        ctx.beginPath();
        ctx.moveTo( scaleX(x), scaleY(y + 0.5) );
        ctx.lineTo( scaleX(x), scaleY(y - 0.5) );
        ctx.moveTo( scaleX(x + 0.5), scaleY(y) );
        ctx.lineTo( scaleX(x - 0.5), scaleY(y) );
        ctx.stroke();

    });

}

mapInput.addEventListener("input", () => {
    let raw = mapInput.value.split("\n");
    let header = raw[0].split(" ");
    raw = raw.slice(1);

    let horizontal = parseInt( header[0] );

    parsed = raw.map( line => {
        values = line.split(" ").map( str => parseFloat(str) );
        return { "pos": values[0], "start": values[1], "end": values[2]}

    });

    map["horizontal"] = parsed.slice(0, horizontal);
    map["vertical"] = parsed.slice(horizontal);

    // console.log(map);

    drawLidar();

});

function toRad(deg){
    return deg * ( Math.PI / 180 );

}

measureInput.addEventListener("input", () => {
    let raw = measureInput.value.split("\n");
    const head = raw[0].split(" ");
    const start_deg = parseFloat( head[0] );
    const origin_x = parseFloat( head[1] );
    const origin_y = parseFloat( head[2] );

    measure = raw[1].split(" ")
        .map( val => parseFloat(val) )
        .map( (dist, i, arr) => {
            const angle_deg = (i*360/arr.length) + start_deg;
            const angle = toRad( angle_deg );

            let x = 0;
            let y = 0;
            if( angle_deg != 0 && angle_deg != 180 ){
                x = (Math.cos(angle) * dist) + origin_x;

            }
            if( angle_deg != 90 && angle_deg != 270 ){
                y = (Math.sin(angle) * dist) + origin_y;

            }

            return [x, y];

        }
    );

    pos = [origin_x, origin_y];

    //console.log(measure);
    drawLidar();

});

pathInput.addEventListener("input", () => {
    path = pathInput.value.split(" ")
    .map( positionStr => positionStr.split(";"))
    .map( ([x_str, y_str]) => [parseFloat(x_str), parseFloat(y_str)]);

    drawLidar();

});

canvas.addEventListener("click", e => {
    const click_x = ( (e.clientX - CANVAS_LEFT) - (WIDTH / 2) );
    const click_y = ( (e.clientY - CANVAS_TOP)  - (HEIGHT / 2) );

    leftInfo.innerText = `position: ${click_x}, ${click_y}`;
});
