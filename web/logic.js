import { initializeApp } from "https://www.gstatic.com/firebasejs/10.12.2/firebase-app.js";
import { getDatabase, ref, onValue } from "https://www.gstatic.com/firebasejs/10.12.2/firebase-database.js";

const firebaseConfig = {
  apiKey: "AIzaSyBFMQ2qzmtvMs8qk6LkfMGNX9CTWEfShMM",
  authDomain: "ttx22p.firebaseapp.com",
  databaseURL: "https://ttx22p-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "ttx22p",
  storageBucket: "ttx22p.firebasestorage.app",
  messagingSenderId: "1028900135625",
  appId: "1:1028900135625:web:47d24439b37c684ab22318"
};

const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

const sensorRef = ref(db, "sensor/staticTest");
const statusEl = document.querySelector(".status");
const tempEl = document.getElementById("temp");
const humidityEl = document.getElementById("humidity");
const lastUpdateEl = document.getElementById("lastUpdate");

let lastUpdateValue = null;

onValue(sensorRef, (snapshot) => {
  const data = snapshot.val();

  if (data) {
    tempEl.textContent = `${data.temperature}°`;
    humidityEl.textContent = `${data.humidity}%`;
    lastUpdateEl.textContent = data.lastUpdate;

    // store current lastUpdate value
    lastUpdateValue = data.lastUpdate;
    statusEl.textContent = "LIVE";
    statusEl.style.opacity = 0.7;
  }
});

// check after 10 seconds if lastUpdate changed
setInterval(() => {
  if (!lastUpdateValue) return; // no data yet

  // get latest snapshot once
  import("https://www.gstatic.com/firebasejs/10.12.2/firebase-database.js").then(({ getDatabase, ref, get }) => {
    const db = getDatabase();
    const sensorRef = ref(db, "sensor/staticTest");
    get(sensorRef).then((snapshot) => {
      const data = snapshot.val();
      if (!data || data.lastUpdate === lastUpdateValue) {
        // no change → offline
        statusEl.textContent = "OFFLINE";
        statusEl.style.opacity = 0.5;
        tempEl.textContent = "--°";
        humidityEl.textContent = "--%";
        lastUpdateEl.textContent = "--";
      } else {
        // changed → still live
        lastUpdateValue = data.lastUpdate;
        statusEl.textContent = "LIVE";
        statusEl.style.opacity = 0.7;
      }
    });
  });
}, 10000); // 10 sec
