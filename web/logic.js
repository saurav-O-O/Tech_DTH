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

// 🔹 your actual data path
const sensorRef = ref(db, "sensor/staticTest");

onValue(sensorRef, (snapshot) => {
  const data = snapshot.val();

  if (data) {
    document.getElementById("temp").textContent = `${data.temperature}°`;
    document.getElementById("humidity").textContent = `${data.humidity}%`;
    document.getElementById("lastUpdate").textContent = data.lastUpdate;
  }
});
