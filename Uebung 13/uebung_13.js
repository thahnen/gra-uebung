'use strict';

let canvas, scene, camera, renderer;
let p1, p2, pointGeometry;


function setPixel(x, y, fall) {
    let pixel;
    if (fall == 1) {
        pixel = [x, y];
    } else if (fall == 2) {
        pixel = [y, x];
    } else if (fall == 3) {
        pixel = [x, -y];
    } else {
        pixel = [y, -x];
    }

    pointGeometry.vertices.push(new THREE.Vector3(
        pixel[0],
        pixel[1],
        0
    ));
}

function bresenham(x0, y0, x1, y1, fall) {
    let dx = x1-x0;
    let dy = y1-y0;
    let d = 2*dy - dx;
    let incrE = 2*dy;
    let incrNE = 2 * (dy-dx);
    let x = x0;
    let y = y0;
    
    setPixel(x0, y0, fall);

    while (x < x1) {
        if (d <= 0) {
            d += incrE;
            x++;
        } else {
            d += incrNE;
            x++;
            y++;
        }
        setPixel(x, y, fall);
    }
}

function line(p1, p2) {
    if (p1.x > p2.x) {
        let temp = p2;
        p2 = p1;
        p1 = temp;
    }

    let dx = p2.x - p1.x;
    let dy = p2.y - p1.y;

    if (Math.abs(dx) < Math.abs(dy) && dy > 0) {
        //Fall 2: 45 - 90 Grad
        bresenham(p1.y, p1.x, p2.y, p2.x, 2);
    } else if (Math.abs(dx) > Math.abs(dy) && dy < 0) {
        //Fall 3: 315 - 360 Grad
        bresenham(p1.x, -p1.y, p2.x, -p2.y, 3);
    } else if (Math.abs(dx) < Math.abs(dy) && dy < 0) {
        //Fall 4: 270 - 315 Grad
        bresenham(-p1.y, p1.x, -p2.y, p2.x, 4);
    } else {
        bresenham(p1.x, p1.y, p2.x, p2.y, 1);
    }
}


// Zeichnen der Szene
function definitionScene() {
    scene = new THREE.Scene();

    // Definition der Kamera
    camera = new THREE.OrthographicCamera(-window.innerHeight / 2, window.innerHeight / 2, window.innerHeight / 2, -window.innerHeight/2, 1.0, -1.0);
    
    //Koordinatensystem hinzufügen
    axis = new THREE.AxisHelper(window.innerHeight/2);
    scene.add(axis);
    
    //Punkte einlesen
    let input = prompt("Eingabe x1, y1, x2, y2:", " ");
    let partsOfStr = input.split(',');
    p1 = {
        x: parseInt(partsOfStr[0]),
        y: parseInt(partsOfStr[1])
    };
    
    p2 = {
        x: parseInt(partsOfStr[2]),
        y: parseInt(partsOfStr[3])
    };

    pointGeometry = new THREE.Geometry();
    let p = new THREE.Vector3(p1.x, p1.y, 0);
    pointGeometry.vertices.push(p);
    p = new THREE.Vector3(p2.x, p2.y, 0);
    pointGeometry.vertices.push(p);
    
    //Einfuegen des Aufrufs des Bresenham-Algorithmus
    line(p1, p2);
    let material = new THREE.PointsMaterial({ color: 0xFFFFFF });
    let pointarray = new THREE.Points(pointGeometry, material);
    scene.add(pointarray);

    //Renderer erzeugen
    renderer = new THREE.WebGLRenderer({ canvas: canvas, antialias: true });
    renderer.setSize(window.innerHeight, window.innerHeight);
    renderer.setClearColor("rgb(0, 0, 0)", 1);
    renderer.render(scene, camera);
}


// Ausfuehren der WebGL-Anwendung, wird durch den onLoad-Event von der Webseite aufgerufen 
function runWebGLApp() {
    canvas = document.getElementById("canvas-element-id");
    //Beschaffen des WebGL-Kontext
    definitionScene(); 
}