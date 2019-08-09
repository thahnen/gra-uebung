'use strict';

let canvas, scene, renderer, camera;
let directionalLight, blackbox, spotLight, ambientlight;
let angle = 0;
let start = false;
let bright = false;
let dark = false;


// Zeichnen der Szene
function drawScene() {
    scene = new THREE.Scene();

    // Definition einer perspektivischen Kamera
    camera = new THREE.PerspectiveCamera(50, window.innerWidth / window.innerHeight, 0.01, 600);
    camera.focalLength = 3;
    camera.position.z = 120;
    camera.position.y = 13;
    camera.lookAt(new THREE.Vector3(0, 0, 0));

    // Definition des Renderers
    renderer = new THREE.WebGLRenderer({ canvas: canvas, antialias: true });
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.autoClear = true;
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.setClearColor("rgb(0%, 0%, 0%)", 1);
    renderer.shadowMap.enabled = true;

    // Boden
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

    let geometry_ground = new THREE.ParametricBufferGeometry(getSurfacePoint, 200, 200);
    let material_ground = new THREE.MeshLambertMaterial({ color: "rgb(200, 130, 0)" });
    let ground = new THREE.Mesh(geometry_ground, material_ground);
    ground.position.y = -25;
    ground.castShadow = true;
    ground.receiveShadow = true;
    scene.add(ground);

    // Wasser
    let geometry_water = new THREE.PlaneGeometry(2000, 2000, 32);
    let material_water = new THREE.MeshPhongMaterial({ color: 0x0080FF, side: THREE.DoubleSide });
    geometry_water.computeVertexNormals();
    let water = new THREE.Mesh(geometry_water, material_water);
    water.rotation.x = -1.57;
    water.position.y = -22;
    water.receiveShadow = true;
    scene.add( water );

    // Himmel
    let geometry_sky = new THREE.PlaneGeometry(2000, 2000, 32);
    let material_sky = new THREE.MeshLambertMaterial({ color: 0x81F7F3, side: THREE.DoubleSide });
    let sky = new THREE.Mesh(geometry_sky, material_sky);
    scene.add(sky);

    // Nebel
    scene.fog = new THREE.Fog(scene.background, 1, 500);

    // Leuchtturm
    let subdivision = 32;

    let geometry_lighthouse = new THREE.CylinderGeometry(3, 5, 20, subdivision);
    let material_lighthouse = new THREE.MeshLambertMaterial({ color: "rgb(255, 0, 0)" });
    let lighthouse = new THREE.Mesh(geometry_lighthouse, material_lighthouse);

    let geometry_lightarea = new THREE.CylinderGeometry(3, 3, 2, subdivision);
    let material_lightarea = new THREE.MeshLambertMaterial({ color: "rgb(255, 255, 255)", });
    material_lightarea.emissive = new THREE.Color(1, 1, 0);
    let lightarea = new THREE.Mesh(geometry_lightarea, material_lightarea);
    lightarea.position.y = 11;
    lighthouse.add(lightarea);

    let geometry_cone = new THREE.ConeGeometry(3.5, 5, subdivision);
    let material_cone = new THREE.MeshLambertMaterial({ color: "rgb(255, 0, 0)" });
    let cone = new THREE.Mesh(geometry_cone, material_cone);
    cone.position.y = 14.5;
    lighthouse.add(cone);

    lighthouse.position.x = 15;
    lighthouse.position.y = -5;
    lighthouse.position.z = 15;
    lighthouse.castShadow = true;
    lighthouse.receiveShadow = true;
    scene.add(lighthouse);

    // Haus & Dach
    let geometry_house = new THREE.BoxGeometry(20, 8, 4);
    let material_house = new THREE.MeshLambertMaterial({ color: 0xFE642E });
    let house = new THREE.Mesh(geometry_house, material_house);

    let vertices = [
        new THREE.Vector3(0.0, 8.0, 0.0),
        new THREE.Vector3(-10, 4.0, 2),
        new THREE.Vector3(10, 4.0, 2),
        new THREE.Vector3(10, 4.0, -2),
        new THREE.Vector3(-10, 4.0, -2)
    ];
    let geometry_roof = new THREE.Geometry();
    geometry_roof.vertices = vertices;

    let faces = [
        new THREE.Face3(0, 1, 2),
        new THREE.Face3(0, 2, 3),
        new THREE.Face3(0, 3, 4),
        new THREE.Face3(0, 4, 1)
    ];
    geometry_roof.faces = faces;

    let material_roof = new THREE.MeshLambertMaterial({ color: 0xB40404 });
    let roof = new THREE.Mesh(geometry_roof, material_roof);
    house.add(roof);

    house.castShadow = true;
    house.receiveShadow = true;
    house.position.y = -7;

    scene.add(house);

    // Ambientes Licht
    ambientlight = new THREE.AmbientLight("rgb(255, 0, 0)", 0.1);
    scene.add(ambientlight);

    // Gerichtete Lichtquelle (Sonnenlicht)
    directionalLight = new THREE.DirectionalLight(0xffffff, 0.2);
    directionalLight.position.z = 200;
    directionalLight.position.x = 100;
    directionalLight.position.y = 50;
    directionalLight.castShadow = true;
    scene.add(directionalLight);

    //let helper = new THREE.DirectionalLightHelper(directionalLight, 5);
    //scene.add(helper);

    // Hilfsobjekt
    blackbox = new THREE.Object3D();
    blackbox.position.x = lighthouse.position.x;
    blackbox.position.z = lighthouse.position.z;
    blackbox.position.y = lighthouse.position.y + 5;

    // Scheinwerfer
    spotLight = new THREE.SpotLight(0xffffff, 1);
    spotLight.position.x = 0;
    spotLight.position.z = 0;
    spotLight.position.y = 10;
    spotLight.target.position.x = 10;
    spotLight.target.position.z =10;
    spotLight.target.position.y = 0;
    spotLight.target.updateMatrixWorld();
    spotLight.angle = 0.2;
    spotLight.penumbra = 0.05;
    spotLight.decay = 2;
    spotLight.distance = 200;
    spotLight.castShadow = true;
    spotLight.shadow.mapSize.width = 1024;
    spotLight.shadow.mapSize.height = 1024;
    spotLight.castShadow = true;
    blackbox.add(spotLight.target);

    //let spotLightHelper = new THREE.SpotLightHelper(spotLight);
    //scene.add(spotLightHelper);

    blackbox.add(spotLight);
    scene.add(blackbox);

    renderer.render(scene, camera);
}


function animate() {
    requestAnimationFrame(animate);

    if (start == true) {
        angle = angle + 0.01;
        if (angle > 359) { angle = 0; }
        blackbox.rotateOnAxis(new THREE.Vector3(0, 1, 0), angle * Math.PI/180.0);
    }

    if (dark == true && directionalLight.intensity > 0) {
        directionalLight.intensity = directionalLight.intensity - 0.01;
    } else if (bright == true && directionalLight.intensity + ambientlight.intensity < 1.0) {
        directionalLight.intensity = directionalLight.intensity + 0.01;
    }

    renderer.render(scene, camera);
}


function click_down(event) {
    event = event || window.event;
    let code = event.keyCode;
    if (code == 38) {
        bright = true;
    } else if (code == 40) {
        dark = true;
    } else if (code == 171) {
        start = true;
    }
};


function click_up(event) {
    event = event || window.event;
    let code = event.keyCode;
    if (code == 38) {
        bright = false;
    } else if (code == 40) {
        dark = false;
    } else if (code == 171) {
        start = false;
    }
};


function runWebGLApp() {
    canvas = document.getElementById("canvas-element-id");
    drawScene();
    document.addEventListener("keydown", click_down);
    document.addEventListener("keyup", click_up);
    animate();
}
