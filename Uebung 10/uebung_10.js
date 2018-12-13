'use strict';

let canvas, clock, scene, camera, renderer;

// Zeichnen der Szene
function definitionScene() {
    scene = new THREE.Scene();
    // Definition der Kamera
    camera = new THREE.PerspectiveCamera(60, 0.5 * window.innerWidth / window.innerHeight, 1.0, 1600);
    camera.position.z = 100;
    camera.lookAt(scene.position);
    // Definition der Geometry
    //Avantar als Mesh-Objekt (Kegel)


    //Kopf als Kugel zum Avantar hinzufuegen


    //zwei Haende als gestauchte Kugeln zum Avantar hinzufuegen 


    //zwei Fuesse als gestauchte Kugeln zum Avantar hinzufuegen


    //Koordinatensystem hinzufügen
    let axis = new THREE.AxisHelper(50);
    scene.add(axis);

    //Hilfsobjekt erzeugen, Avantar hinzufuegen und Objekt zur Szene hinzufuegen


    //Renderer erzeugen
    renderer = new THREE.WebGLRenderer({ canvas: canvas, antialias: true });
    renderer.setSize(window.innerHeight, window.innerHeight);
    renderer.setClearColor("rgb(0, 0, 0)", 1); //Hintergrundfarbe
    renderer.render(scene, camera);
}

function animate() {
    requestAnimationFrame(animate);
    // Funktion zum Bewegen
    // Funktion zum Drehen
    renderer.render(scene, camera);
}

function key_down(event) {
    event = event || window.event;
    let code = event.keyCode;
    if (code == 37) {

    } else if (code == 38) {

    } else if (code == 39) {

    } else if (code == 40) {

    }
};

function key_up(event) {
    event = event || window.event;
    let code = event.keyCode;
    if (code == 37) {

    } else if (code == 38) {

    } else if (code == 39) {

    } else if (code == 40) {

    }
};

// Ausfuehren der WebGL-Anwendung, wird durch den onLoad-Event von der Webseite aufgerufen 
function runWebGLApp() {
    canvas = document.getElementById("canvas-element-id");
    definitionScene();
    clock = new THREE.Clock(true);
    document.addEventListener("keydown", key_down);
    document.addEventListener("keyup", key_up);
    animate();   
}
