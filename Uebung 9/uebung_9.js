'use strict';

// Liefern des WebGL-Kontext
function getGLContext(canvas) {
	let gl = gl || null;
    if (canvas == null) {
        alert("there is no canvas on this page");
        return;
    }
    let names = ["webgl", "experimental-webgl", "webkit-3d", "moz-webgl"];
    for (var i = 0; i < names.length; ++i) {
        try {
            gl = canvas.getContext(names[i]);
        } catch (e) { }
        if (gl) break;
    }
    if (gl == null) {
        alert("WebGL is not available");
    }
}

function rendering(canvas) {
    let renderer = new THREE.WebGLRenderer({ canvas: canvas, antialias: true });
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.autoClear = true;
    renderer.setSize(window.innerHeight, window.innerHeight);
    renderer.setClearColor("rgb(0, 0, 0)", 1);
    return renderer;
}

let canvas;
let scene, camera, renderer;

// Zeichnen der Szene
function definitionScene() { 
    // Definition der Kamera mit minx, maxx, maxy, miny, minz, maxz
    //camera = new THREE.OrthographicCamera();
    camera = new THREE.OrthographicCamera(-2.5, 2.5, 2.5, -2.5, -10, 10);

    // Definition der Geometry
    // Erzeugen eines Geometrie-Objektes
    let geometry = new THREE.Geometry();

    // Vertices als Array von THREE.Vector3-Objekten var vertices = []
    let vertices = [
    	new THREE.Vector3(0, 0.5, 0),
    	new THREE.Vector3(-1, -0.5, 1),
    	new THREE.Vector3(1, -0.5, 1),
    	new THREE.Vector3(1, 1.5, 1),
    	new THREE.Vector3(-1, 1.5, 1)
    ];
    for (var i = 0; i < vertices.length; i++) {
    	geometry.vertices.push(vertices[i]);
    }
    
    //Erzeugen der Faces als Array von THREE.Face3-Objekten
    let normal = THREE.Vector3(0, 1, 0);
    let faces = [
    	new THREE.Face3(0, 1, 2, normal, new THREE.Color(0xff0000), 0),
    	new THREE.Face3(0, 2, 3, normal, new THREE.Color(0x00ff00), 0),
    	new THREE.Face3(0, 3, 4, normal, new THREE.Color(0x0000ff), 0),
    	new THREE.Face3(0, 4, 1, normal, new THREE.Color(0xffff00), 0),
    	new THREE.Face3(1, 4, 2, normal, new THREE.Color(0xff00ff), 0),
    	new THREE.Face3(2, 4, 3, normal, new THREE.Color(0x00ffff), 0)
    ];
    for (var i = 0; i < faces.length; i++) {
    	geometry.faces.push(faces[i]);
    }

    //Definition des Materials
    //let material = new THREE.MeshBasicMaterial({vertexColors: THREE.VertexColors, side: THREE.DoubleSide});
    let materials = [
    	new THREE.MeshBasicMaterial({ vertexColors: THREE.VertexColors, side: THREE.DoubleSide }),
    	new THREE.MeshBasicMaterial({ color: 0x000000, wireframe: true, transparent: true })
    ]

    //Verbinden von Geometie und Material zu einem Mesh-Objekt
    //let pyramide = new THREE.Mesh(geometry, material);
    let pyramide = THREE.SceneUtils.createMultiMaterialObject(geometry, materials);

    //Hinzufuegen des Meshobjekts zur Szene
    scene = new THREE.Scene();
    scene.add(pyramide)

    let axis = new THREE.AxisHelper(50);
    scene.add(axis);
    renderer = rendering(canvas);
}


function renderloop() {
    requestAnimationFrame(renderloop);
    scene.rotation.x = scene.rotation.x + 0.005;
    scene.rotation.y = scene.rotation.y + 0.005;
    scene.rotation.z = scene.rotation.z + 0.005;
    renderer.render(scene, camera);
}


// Ausfuehren der WebGL-Anwendung, wird durch den onLoad-Event von der Webseite aufgerufen 
function runWebGLApp() {
    canvas = document.getElementById("canvas-element-id");
    //Beschaffen des WebGL-Kontext
    getGLContext(canvas);
    definitionScene();
    //Rendern der Szene
    renderloop();    
}