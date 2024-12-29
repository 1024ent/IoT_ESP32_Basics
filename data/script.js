// Function to update the brightness based on the slider value
function updateBrightness() {
    var slider = document.getElementById('brightnessSlider');
    var value = slider.value;
    document.getElementById('brightnessValue').innerText = value;

    // Send the value to ESP32 via a GET request
    fetch('/set_brightness?value=' + value);
}