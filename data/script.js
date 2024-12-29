document.getElementById('btnOn').addEventListener('click', () => sendRequest('on'));
document.getElementById('btnOff').addEventListener('click', () => sendRequest('off'));

function sendRequest(state) {
  fetch(`/led/${state}`)
    .then(response => response.text())
    .then(data => console.log(data))
    .catch(err => console.error('Error:', err));
}