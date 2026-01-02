function setLED(state) {
  fetch(`/led/${state}`)
    .then(response => response.text())
    .then(message => {
      document.getElementById("status").textContent =
        "LED Status: " + message;
    })
    .catch(() => {
      document.getElementById("status").textContent =
        "Connection error";
    });
}
