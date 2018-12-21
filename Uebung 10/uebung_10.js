'use strict';

let canvas, clock, scene, camera, renderer;
let Avatar, left_hand, right_hand, left_foot, right_foot;
let is_moving_left, is_moving_forward, is_moving_right, is_moving_back;
let direction = 0;

// Zeichnen der Szene
function definitionScene() {
    scene = new THREE.Scene();
    
    // Definition der Kamera
    camera = new THREE.PerspectiveCamera(60, 0.5 * window.innerWidth / window.innerHeight, 1.0, 1600);
    camera.position.z = 100;
    camera.lookAt(scene.position);
    
    // Definition der Geometry
    // Avantar als Mesh-Objekt (Kegel)
    let geometry = new THREE.ConeGeometry(8, 15, 32);
    let material = new THREE.MeshBasicMaterial({ color: "rgb(255, 0, 0)" });
    Avatar = new THREE.Mesh(geometry, material);

    // Kopf als Kugel zum Avantar hinzufuegen
    let head_geometry = new THREE.SphereGeometry(5, 32, 32);
    let head_material = new THREE.MeshBasicMaterial({ color: "rgb(255, 255, 0)" });
    let head = new THREE.Mesh(head_geometry, head_material);
    head.position.set(0, 8, 0);
    Avatar.add(head);

    // zwei Haende als gestauchte Kugeln zum Avantar hinzufuegen
    let hand = new THREE.SphereGeometry(3);
    hand.scale(1, 0.7, 1);
    let hand_material = new THREE.MeshBasicMaterial({ color: "rgb(0, 255, 0)"});
    left_hand = new THREE.Mesh(hand, hand_material);
    left_hand.position.set(-7, 0, 0);
    Avatar.add(left_hand);
    right_hand = new THREE.Mesh(hand, hand_material);
    right_hand.position.set(7, 0, 0);
    Avatar.add(right_hand);

    // zwei Fuesse als gestauchte Kugeln zum Avantar hinzufuegen
    let foot_material = new THREE.MeshBasicMaterial({ color: "rgb(255, 255, 0)" });
    let foot = new THREE.SphereGeometry(3);
    left_foot = new THREE.Mesh(foot, foot_material);
    foot.scale(0.7, 1, 1);
    left_foot.position.set(-3, -10, 0);
    Avatar.add(left_foot);
    right_foot = new THREE.Mesh(foot, foot_material);
    right_foot.position.set(3, -10, 0);
    Avatar.add(right_foot);

    // Koordinatensystem hinzufügen
    let axis = new THREE.AxisHelper(50);
    scene.add(axis);

    // Avantar zur Szene hinzufuegen
    scene.add(Avatar);

    // Renderer erzeugen
    renderer = new THREE.WebGLRenderer({ canvas: canvas, antialias: true });
    renderer.setSize(window.innerHeight, window.innerHeight);
    renderer.setClearColor("rgb(0, 0, 0)", 1); //Hintergrundfarbe
    renderer.render(scene, camera);
}

function animate() {
    requestAnimationFrame(animate);
    // Funktion zum Bewegen
    walk();
    // Funktion zum Drehen
    turn();
    renderer.render(scene, camera);
}

function isWalking() {
    if (is_moving_left) return true;
    if (is_moving_forward) return true;
    if (is_moving_right) return true;
    if (is_moving_back) return true;
    return false;
}

function walk() {
    if (!isWalking()) return;
    let position = Math.sin(clock.getElapsedTime() * 5) * 4;
    left_hand.position.z = -position;
    right_hand.position.z = position;
    left_foot.position.z = position;
    right_foot.position.z = -position;
}

function turn() {
    if (is_moving_forward) direction = 0;
    if (is_moving_back) direction = Math.PI;
    if (is_moving_right) direction = -Math.PI / 2;
    if (is_moving_left) direction = Math.PI / 2;
    Avatar.rotation.y = direction;
}

function key_down(event) {
    event = event || window.event;
    var code = event.keyCode;
    if (code == 37) {
        // Pfeil nach links
        Avatar.translateZ(-1);
        is_moving_left = true;
    } else if (code == 38) {
        // Pfeil nach unten
        Avatar.translateZ(-1);
        is_moving_forward = true;
    } else if (code == 39) {
        // Pfeil nach rechts
        Avatar.translateZ(-1);
        is_moving_right = true;
    } else if (code == 40) {
        // Pfeil nach oben
        Avatar.translateZ(-1);
        is_moving_back = true;
    }
};

function key_up(event) {
    event = event || window.event;
    var code = event.keyCode;
    if (code == 37) {
        is_moving_left = false;
    } else if (code == 38) {
        is_moving_forward = false;
    } else if (code == 39) {
        is_moving_right = false;
    } else if (code == 40) {
        is_moving_back = false;
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
