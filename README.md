🛰️ Tech_DTH: Real-Time IoT Dashboard

A sleek, full-stack IoT solution that bridges physical sensor data with a modern web interface. This project captures ambient temperature and humidity via an ESP8266 and streams it instantly to a Firebase Realtime Database for live visualization.

[ View Live Demo ] ---
💎 Features at a Glance

    ⚡ Real-Time Synchronization: Uses Firebase onValue listeners to update the UI instantly when sensor data changes.

    🛠️ Robust Firmware: Implements non-blocking millis() timers to ensure the ESP8266 remains responsive during data transmission.

    🎨 Sci-Fi Aesthetic: A "Cyberpunk" inspired dashboard featuring the Orbitron typeface and glowing UI elements.

    🤖 Automated Deployment: Integrated CI/CD pipeline via GitHub Actions that deploys updates to the web dashboard on every push.

🏗️ System Architecture
1. Edge Layer (Hardware)

    Microcontroller: ESP8266 (NodeMCU).

    Sensor: DHT11 (Temperature & Humidity).

    Logic: Reads data every 5 seconds and pushes to /sensor/staticTest.

2. Cloud Layer (Middleware)

    Provider: Firebase Realtime Database.

    Mechanism: Acts as a reactive data broker between the hardware and the frontend.

3. Application Layer (Web)

    Stack: Vanilla JS (ES6+), HTML5, CSS3.

    Library: Firebase Web SDK v10.12.2.

🚀 Quick Start
Hardware Setup

    Open ESP12E/ESP_code.ino in the Arduino IDE.

    Install the DHT and Firebase_ESP_Client libraries.

    Configure your credentials:
    C++

    #define WIFI_SSID "Your_SSID"
    #define WIFI_PASSWORD "Your_Password"
    #define FIREBASE_HOST "your-project.firebaseio.com"
    #define FIREBASE_SECRET "your_legacy_token"

Web Dashboard

The frontend is hosted automatically via GitHub Pages. To run locally:

    Navigate to the /web directory.

    Open dashboard.html in any modern browser.

    Ensure your firebaseConfig in logic.js is updated with your project keys.
