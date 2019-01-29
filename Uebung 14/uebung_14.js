'use strict';

let sonne_rot = 0;
let merkur_rot = 0;
let venus_rot = 0;
let erde_rot = 0;
let mond_rot = 0;
let mars_rot = 0;
let reference_system_2;
let camera, renderer, scene;
let ursprung, sonne, merkur, venus, erde, mond, mars, jupiter, saturn, uranus, neptun, pluto;
let hilfsobjekt, geometry, material, sphere;


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

    // Ursprung (um den sich alles dreht)
    ursprung = new THREE.Object3D(0, 0, 0);

    // Sonne
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(10, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("sunmap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(0, 0, 0)
    sonne = new THREE.Object3D();
    sonne.add(hilfsobjekt);
    scene.add(sonne);

    // Merkur
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(5, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("mercurymap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(20, 0, 0)
    merkur = new THREE.Object3D();
    merkur.add(hilfsobjekt);
    sonne.add(merkur);

    // Venus
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(5, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("venusmap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(40, 0, 0)
    venus = new THREE.Object3D();
    venus.add(hilfsobjekt);
    sonne.add(venus);

    // Erde
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(5, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("earthmap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(60, 0, 0)
    erde = new THREE.Object3D();
    erde.add(hilfsobjekt);

    // Mond
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(1, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("moonmap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(67.5, 0, 0)
    mond = new THREE.Object3D();
    mond.add(hilfsobjekt);
    erde.add(mond);
    sonne.add(erde);

    // Mars
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(5, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("marsmap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(80, 0, 0)
    mars = new THREE.Object3D();
    mars.add(hilfsobjekt);
    sonne.add(mars);

    // Jupiter
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(5, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("jupitermap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(100, 0, 0)
    jupiter = new THREE.Object3D();
    jupiter.add(hilfsobjekt);
    sonne.add(jupiter);

    // Saturn
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(5, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("saturnmap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(120, 0, 0)
    saturn = new THREE.Object3D();
    saturn.add(hilfsobjekt);
    sonne.add(saturn);

    // Uranus
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(5, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("uranusmap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(140, 0, 0)
    uranus = new THREE.Object3D();
    uranus.add(hilfsobjekt);
    sonne.add(uranus);

    // Neptun
    hilfsobjekt = new THREE.Object3D();
    geometry = new THREE.SphereGeometry(5, 20, 20);
    material = new THREE.MeshLambertMaterial({ map: THREE.ImageUtils.loadTexture("neptunemap.jpg") });
    sphere = new THREE.Mesh(geometry, material);
    hilfsobjekt.add(sphere);
    hilfsobjekt.position.set(140, 0, 0)
    neptun = new THREE.Object3D();
    neptun.add(hilfsobjekt);
    sonne.add(neptun);

    // Sonne hinzufuegen
    scene.add(sonne);

    //Licht
    let light = new THREE.PointLight(0xffffff, 1, 10000);
    light.position.set(0, 0, 0);
    scene.add(light);
    let ambientlight = new THREE.AmbientLight(0x404040);

    //Szene
    scene.add(ambientlight);
}


function click_down(event) {
    event = event || window.event;
    let code = event.keyCode;
    if (code == 77) {
        // m -> Sicht des Mondes
        console.log("Mond-Sicht");
    } else if (code == 83) {
        // s -> Sicht der Sonne
        console.log("Sonnen-Sicht");
    } else if (code == 69) {
        // e -> Sicht der Erde
        console.log("Erden-Sicht");
    } else if (code == 72) {
        // h -> Sicht aus dem Himmel (?)
        console.log("Himmels-Sicht");
    } else if (code == 84) {
        // t -> Sicht ueber der Sonne
        console.log("Uebersicht");
    }
};


defineScene();
renderLoop();


// Rendering
function renderLoop() {
    document.addEventListener("keydown", click_down);

    sonne_rot += 0.01;

    sonne.rotation.y = sonne_rot;
    merkur.rotation.y = sonne_rot;
    venus.rotation.y = sonne_rot;
    erde.rotation.y = sonne_rot;
    //mond.rotation.y = sonne_rot;
    mars.rotation.y = sonne_rot;
    jupiter.rotation.y = sonne_rot;
    saturn.rotation.y = sonne_rot;

    renderer.render(scene, camera);
    requestAnimationFrame(renderLoop);
}