// Function to fetch LDR value from ESP32
function fetchLDRValue() {
    fetch('/ldr_value')
        .then(response => response.text())
        .then(data => {
            // Display the LDR value on the webpage
            document.getElementById('ldrValue').innerText = data;
        })
        .catch(error => {
            console.error('Error fetching LDR value:', error);
        });
}

// Automatically fetch LDR value every 2 seconds
setInterval(fetchLDRValue, 2000);
