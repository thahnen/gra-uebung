'use strict';

let canvas, scene, renderer, camera;

// Zeichnen der Szene
function drawScene() {
    scene = new THREE.Scene();

    // Definition einer perspektivischen Kamera
    camera = new THREE.PerspectiveCamera(50, window.innerWidth / window.innerHeight, 0.01, 600);
    camera.focalLength = 3;
    camera.position.z = 120;
    camera.position.y = 13;
    camera.lookAt(new THREE.Vector3(0, 0, 0));

    //Definition des Renderers
    renderer = new THREE.WebGLRenderer({ canvas: canvas, antialias: true });
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.autoClear = true;
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setClearColor("rgb(0%, 0%, 0%)", 1);
    renderer.shadowMap.enabled = true;

    //Boden
    let nsControlPoints = [[
            new THREE.Vector4(-70, 0, -30, 1),
            new THREE.Vector4(-10, 0, -30, 1),
            new THREE.Vector4(10, 0, -30, 1),
            new THREE.Vector4(70, 0, -30, 1)
        ], [
            new THREE.Vector4(-70, 0, -10, 1),
            new THREE.Vector4(-10, 30, -10, 1),
            new THREE.Vector4(10, 30, -10, 1),
            new THREE.Vector4(70, 0, -10, 1)
        ], [
            new THREE.Vector4(-70, 0, 10, 1),
            new THREE.Vector4(-10, 30, 10, 1),
            new THREE.Vector4(10, 30, 10, 1),
            new THREE.Vector4(70, 0, 10, 1)
        ], [
            new THREE.Vector4(-70, 0, 30, 1),
            new THREE.Vector4(-10, 0, 30, 1),
            new THREE.Vector4(10, 0, 30, 1),
            new THREE.Vector4(70, 0, 30, 1)
    ]];

    let knots = [0, 0, 0, 0, 1, 1, 1, 1];
    let nurbsSurface = new THREE.NURBSSurface(3, 3, knots, knots, nsControlPoints);

    function getSurfacePoint(u, v, target) {
        return nurbsSurface.getPoint(u, v, target);
    }

    let geometry = new THREE.ParametricBufferGeometry(getSurfacePoint, 200, 200);
    let material = new THREE.MeshBasicMaterial({ color: "rgb(200, 130, 0)" });
    let ground = new THREE.Mesh(geometry, material);
    ground.position.y = -25;
    scene.add(ground);

    //Wasser
    geometry = new THREE.PlaneGeometry(2000, 2000, 32);
    material = new THREE.MeshBasicMaterial({ color: 0x0080FF, side: THREE.DoubleSide });
    geometry.computeVertexNormals();
    let water = new THREE.Mesh(geometry, material);
    water.rotation.x = -1.57;
    water.position.y = -22;
    scene.add( water );

    //Himmel
    geometry = new THREE.PlaneGeometry(2000, 2000, 32);
    material = new THREE.MeshBasicMaterial({ color: 0x81F7F3, side: THREE.DoubleSide });
    let sky = new THREE.Mesh(geometry, material);
    scene.add(sky);

    //Nebel
    scene.fog = new THREE.Fog(scene.background, 1, 500);

    //Leuchtturm
   
    //Haus und Dach
      
    //Ambientes Licht
   
    //Gerichtete Lichtquelle (Sonnenlicht)
   
    //Hilfsobjekt
 
    //Scheinwerfer
  
    renderer.render(scene, camera);
}


function animate() {
    requestAnimationFrame(animate);    
    renderer.render(scene, camera);
}


/*
function click_down(event) {
    event = event || window.event;
    let code = event.keyCode;
    if (code == 38) {
    } else if (code == 40) {
    } else if (code == 171) {
    }
};


function click_up(event) {
    event = event || window.event;
    let code = event.keyCode;
    if (code == 38) { 
    } else if (code == 40) {
    } else if (code == 171) {
    }
};
*/


function runWebGLApp() {
    canvas = document.getElementById("canvas-element-id");
    drawScene();
    //document.addEventListener("keydown", click_down);
    //document.addEventListener("keyup", click_up);
    animate();
}