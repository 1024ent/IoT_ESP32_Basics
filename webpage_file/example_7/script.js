const slider = document.getElementById('brightnessSlider');
const valueDisplay = document.getElementById('brightnessValue');

slider.addEventListener('input', () => {
    const brightness = slider.value;
    valueDisplay.textContent = brightness;

    // Send brightness value to ESP32
    fetch(`/set_brightness?value=${brightness}`);
});
