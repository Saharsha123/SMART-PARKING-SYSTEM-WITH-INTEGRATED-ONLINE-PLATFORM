// Importing necessary Firebase modules from CDN
import { initializeApp } from "https://www.gstatic.com/firebasejs/11.9.1/firebase-app.js";
import { getDatabase, ref, onValue } from "https://www.gstatic.com/firebasejs/11.9.1/firebase-database.js";

// Firebase project configuration object
const firebaseConfig = {
  //Copy the firebase configurations and paste here
};

// Initialize the Firebase app with config
const app = initializeApp(firebaseConfig);

// Get a reference to the Firebase Realtime Database
const db = getDatabase(app);

// Function to update and display the current date and time every second
function updateClock() {
  const now = new Date();
  document.getElementById('clock').textContent = `⏱️ Last Updated: ${now.toLocaleString()}`;
}
setInterval(updateClock, 1000); // Call updateClock every second
updateClock(); // Initial call to set clock immediately

// Function to update the available slot count display
function updateAvailability(slots, id) {
  const available = slots.filter(s => !s.occupied).length; // Count non-occupied slots
  document.getElementById(id).textContent = `🟢 Available Slots: ${available} / ${slots.length}`;
}

// Function to render each slot as a card on the webpage
function renderSlots(slots, type, parentId) {
  const grid = document.getElementById(parentId);
  grid.innerHTML = ''; // Clear previous content

  slots.forEach((slot) => {
    const card = document.createElement('div');
    card.className = `slot-card ${slot.occupied ? 'occupied' : 'available'}`; // Add class based on status

    // Slot content: vehicle emoji, ID, and availability status
    card.innerHTML = `
      <h3>${type === "bike" ? '🚲' : '🚗'} ${slot.id}</h3>
      <div class="status ${slot.occupied ? 'occupied' : 'available'}">
        ${slot.occupied ? '🔴 Occupied' : '🟢 Available'}
      </div>
    `;

    grid.appendChild(card); // Add card to the grid
  });

  // Update the availability count below the grid
  updateAvailability(slots, `${type}-available`);
}

// Function to fetch real-time slot data from Firebase and render it
function fetchAndRenderSlots(type) {
  const path = `ultrasonic/${type}`; // Database path: ultrasonic/bike or ultrasonic/car
  const dbRef = ref(db, path); // Create reference to that path

  // Listen for value changes in Firebase
  onValue(dbRef, (snapshot) => {
    const data = snapshot.val(); // Get snapshot data

    if (data) {
      // Convert data object into array of slot objects with ID and occupancy status
      const slots = Object.entries(data).map(([id, values]) => ({
        id: id,
        occupied: values.objectDetected
      }));

      // Render slots on UI and update the clock
      renderSlots(slots, type, `${type}-slots`);
      updateClock(); // Optional: ensure latest update timestamp
    }
  });
}

// Call the fetch function for both types of slots
fetchAndRenderSlots("bike");
fetchAndRenderSlots("car");

// When the page finishes loading, hide the loading screen
window.addEventListener('load', () => {
  const loader = document.getElementById('loader-screen');
  loader.classList.add('hidden'); // Add hidden class to fade out or remove loader
});
