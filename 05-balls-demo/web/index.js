import loadWasm from "./wasm-loader.js";
const canvas = document.getElementById('ball-canvas');
const context = canvas.getContext('2d');

let frameCount = 0;
let lastFpsUpdate = performance.now();

const instance = await loadWasm({
    platform_draw_ball: drawBall
});

const { init, draw, update, add_balls, get_ball_count } = instance.exports;

const clearCanvas = () => {
    context.fillStyle = '#2C3E50';
    context.fillRect(0, 0, canvas.clientWidth, canvas.clientHeight);
}

const setBallCount = () => {
    document.getElementById('ball_count').innerText = get_ball_count();
}

const updateFpsDisplay = () => {
    const fpsDisplay = document.getElementById('fps_display');
    const now = performance.now();
    const deltaTime = now - lastFpsUpdate;

    if (deltaTime >= 1000) {
        const fps = (frameCount / deltaTime) * 1000;
        fpsDisplay.textContent = `FPS: ${fps.toFixed(2)}`;
        frameCount = 0;
        lastFpsUpdate = now;
    }
};

function drawBall(ballPtr) {
    const wasmMemoryBuffer = instance.exports.memory.buffer;
    const dataView = new DataView(wasmMemoryBuffer);

    const x_offset = 0;
    const y_offset = 4;
    const radius_offset = 8;
    const red_offset = 20;
    const green_offset = 24;
    const blue_offset = 28;

    const x = dataView.getFloat32(ballPtr + x_offset, true);
    const y = dataView.getFloat32(ballPtr + y_offset, true);
    const radius = dataView.getFloat32(ballPtr + radius_offset, true);
    const r = dataView.getInt32(ballPtr + red_offset, true);
    const g = dataView.getInt32(ballPtr + green_offset, true);
    const b = dataView.getInt32(ballPtr + blue_offset, true);

    context.fillStyle = `rgba(${r},${g},${b})`;
    context.beginPath();
    context.arc(x, y, radius, 0, 2 * Math.PI);
    context.fill();
}

canvas.addEventListener('click', e => {
    const rect = canvas.getBoundingClientRect();
    const scaleX = canvas.width / rect.width;
    const scaleY = canvas.height / rect.height;
    const x = (e.clientX - rect.left) * scaleX;
    const y = (e.clientY - rect.top) * scaleY;

    add_balls(x, y);
});

const gameLoop = () => {
    clearCanvas();
    setBallCount();
    frameCount++;
    updateFpsDisplay();
    draw();
    update();

    requestAnimationFrame(gameLoop);
};

init(Date.now(), canvas.clientWidth, canvas.clientHeight);
requestAnimationFrame(gameLoop);

