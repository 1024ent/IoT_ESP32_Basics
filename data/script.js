const ldrValueDisplay = document.getElementById('ldrValue');
const recordedValuesList = document.getElementById('recordedValues');
let recordedValues = [];

function fetchLDRValue() {
    fetch('/ldr_value')
        .then(response => response.text())
        .then(data => {
            ldrValueDisplay.textContent = data;
            recordedValues.push(data);
            updateRecordedList();
        })
        .catch(err => console.error('Error fetching LDR value:', err));
}

function updateRecordedList() {
    recordedValuesList.innerHTML = '';
    recordedValues.forEach((val, index) => {
        const li = document.createElement('li');
        li.textContent = `${index + 1}: ${val}`;
        recordedValuesList.appendChild(li);
    });
}

function saveData() {
    if (recordedValues.length === 0) return;
    const blob = new Blob([recordedValues.join('\n')], { type: 'text/plain' });
    const url = URL.createObjectURL(blob);

    const a = document.createElement('a');
    a.href = url;
    a.download = 'ldr_values.txt';
    a.click();
    URL.revokeObjectURL(url);
}

function clearData() {
    recordedValues = [];
    updateRecordedList();
    ldrValueDisplay.textContent = '0';
}

// Event listeners
document.getElementById('getValueBtn').addEventListener('click', fetchLDRValue);
document.getElementById('saveBtn').addEventListener('click', saveData);
document.getElementById('clearBtn').addEventListener('click', clearData);

// Automatic update every 2 seconds
setInterval(fetchLDRValue, 2000);
