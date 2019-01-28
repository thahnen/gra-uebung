'use strict';

let roty = 0;
let reference_system_2;
let camera, renderer, scene;


// Zeichnen der Szene
function defineScene() {
    scene = new THREE.Scene();

    // Definition einer perspektivischen Kamera
    camera = new THREE.PerspectiveCamera(30, window.innerWidth / window.innerHeight, 0.01, 600);
    camera.focalLength = 3;
    camera.position.z = 170;
    scene.rotation.x = 1.2;
    scene.rotation.y = 0.0;
    camera.lookAt(scene.position);

    //Definition des Renderers
    renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.autoClear = true;
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setClearColor("rgb(100%, 100%, 100%)", 1);
    document.body.appendChild(renderer.domElement);

    // Bezugssystem erste Kugel
    let reference_system_1 = new THREE.Object3D();
    let geometry = new THREE.SphereGeometry(0.8, 20, 20);
    let material = new THREE.MeshLambertMaterial({ color: "rgb(100%, 0%, 0%)" });
    let sphere = new THREE.Mesh(geometry, material);
    reference_system_1.add(sphere);
    reference_system_1.position.set(30, 0, 0);

    // Bezugssystem im Koordinatenursprung
    reference_system_2 = new THREE.Object3D();
    reference_system_2.add(reference_system_1);

    //Licht
    let light = new THREE.PointLight(0xffffff, 1, 10000);
    light.position.set(0, 0, 0);
    scene.add(light);
    let ambientlight = new THREE.AmbientLight(0x404040);

    //Szene
    scene.add(reference_system_2);
    scene.add(ambientlight);
}


defineScene();
renderLoop();


// Rendering
function renderLoop() {
    roty = roty + 0.01;
    reference_system_2.rotation.y = roty ;
    renderer.render(scene, camera);
    requestAnimationFrame(renderLoop);
}