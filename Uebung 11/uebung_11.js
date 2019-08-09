'use strict';

let canvas, scene, camera, renderer, avantar;
let avatar, left_hand, right_hand, left_foot, right_foot, baum;
let richtung = 0;
let winkel = 60;


function rand(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}


// Zeichnen der Szene
function definitionScene() {
    scene = new THREE.Scene();

    // Definition der Kamera
    camera = new THREE.PerspectiveCamera(winkel, 1, 1.0, 300);
    //camera = new THREE.OrthographicCamera(-100, 100, 100, -100, 1.0, 300.0);
    console.info("Kamera FOV: " + camera.fov);
    //camera.position.x = 50;
    //camera.position.y = 50;
    //camera.position.z = 200;
    camera.lookAt(new THREE.Vector3(0, 0, -100));
    camera.up = new THREE.Vector3(0.0, 1.0, 0.0);

    // Definition der Geometry
    // Avatar als Mesh-Objekt (Kegel)
    let geometry = new THREE.ConeGeometry(8, 15, 32);
    let material = new THREE.MeshBasicMaterial({ color: "rgb(255, 0, 0)" });
    avatar = new THREE.Mesh(geometry, material);

    // Kopf als Kugel zum Avatar hinzufuegen
    let head_geometry = new THREE.SphereGeometry(5, 32, 32);
    let head_material = new THREE.MeshBasicMaterial({ color: "rgb(255, 255, 0)" });
    let head = new THREE.Mesh(head_geometry, head_material);
    head.position.set(0, 8, 0);
    avatar.add(head);

    // Zwei Haende als gestauchte Kugeln zum Avatar hinzufuegen
    let hand = new THREE.SphereGeometry(3);
    hand.scale(1, 0.7, 1);
    let hand_material = new THREE.MeshBasicMaterial({ color: "rgb(0, 255, 0)"});
    left_hand = new THREE.Mesh(hand, hand_material);
    left_hand.position.set(-7, 0, 0);
    avatar.add(left_hand);
    right_hand = new THREE.Mesh(hand, hand_material);
    right_hand.position.set(7, 0, 0);
    avatar.add(right_hand);

    // Zwei Fuesse als gestauchte Kugeln zum Avatar hinzufuegen
    let foot_material = new THREE.MeshBasicMaterial({ color: "rgb(255, 255, 0)" });
    let foot = new THREE.SphereGeometry(3);
    left_foot = new THREE.Mesh(foot, foot_material);
    foot.scale(0.7, 1, 1);
    left_foot.position.set(-3, -10, 0);
    avatar.add(left_foot);
    right_foot = new THREE.Mesh(foot, foot_material);
    right_foot.position.set(3, -10, 0);
    avatar.add(right_foot);

    // Avatar ausrichten und zur Szene hinzufuegen
    avatar.position.x = 30;
    avatar.add(camera);
    scene.add(avatar);

    // 5 Baeume zur Szene hinzufügen
    baum = new THREE.Object3D();
    let stamm_geometry = new THREE.CylinderGeometry(3, 5, 30, 32);
    let stamm_material = new THREE.MeshBasicMaterial({ color: "rgb(128, 64, 64)" });
    let stamm = new THREE.Mesh(stamm_geometry, stamm_material);
    let krone_geometry = new THREE.SphereGeometry(15, 32, 32);
    let krone_material = new THREE.MeshBasicMaterial({ color: "rgb(0, 128, 0)" });
    let krone = new THREE.Mesh(krone_geometry, krone_material);
    krone.position.y = 20;
    baum.add(stamm);
    baum.add(krone);
    baum.position.set(-20, 0, 50);
    scene.add(baum);

    baum = baum.clone();
    baum.position.set(10, 0, 0);
    scene.add(baum);

    baum = baum.clone();
    baum.position.set(-25, 0, 100);
    scene.add(baum);

    baum = baum.clone();
    baum.position.set(20, 0, 20);
    scene.add(baum);

    baum = baum.clone();
    baum.position.set(50, 0, 60);
    scene.add(baum);

    // Renderer erzeugen
    renderer = new THREE.WebGLRenderer({ canvas: canvas, antialias: true });
    renderer.setSize(window.innerHeight, window.innerHeight);
    renderer.setClearColor("rgb(0, 0, 0)", 1);
    renderer.render(scene, camera);
}


function animate() {
    requestAnimationFrame(animate);
    switch (richtung) {
        case 1:
            avatar.translateX(-1);
            break;
        case 2:
            avatar.translateZ(-1);
            break;
        case 3:
            avatar.translateX(1);
            break;
        case 4:
            avatar.translateZ(1);
            break;
        default:
            break;
    }
    camera.fov = winkel;
    camera.updateProjectionMatrix();
    renderer.render(scene, camera);
}


function click_down(event) {
    event = event || window.event;
    let code = event.keyCode;
    if (code == 37) {
        richtung = 1;
    } else if (code == 38) {
        richtung = 2;
    } else if (code == 39) {
        richtung = 3;
    } else if (code == 40) {
        richtung = 4;
    } else if (code == 171) {
        if (winkel >= 10) winkel--;
    } else if (code == 173) {
        if (winkel <= 165) winkel++;
    }
};


function click_up(event) {
    event = event || window.event;
    let code = event.keyCode;
    if (code == 37) {
        richtung = 0;
    } else if (code == 38) {
        richtung = 0;
    } else if (code == 39) {
        richtung = 0;
    } else if (code == 40) {
        richtung = 0;
    }
};


// Ausfuehren der WebGL-Anwendung, wird durch den onLoad-Event von der Webseite aufgerufen
function runWebGLApp() {
    canvas = document.getElementById("canvas-element-id");
    definitionScene();
    document.addEventListener("keydown", click_down);
    document.addEventListener("keyup", click_up);
    animate();
}
