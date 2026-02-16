📘 Case Study: Real-Time IoT Environmental Monitor
1. The Goal

The objective was to build a low-latency monitoring system that bridges the gap between physical environment data and a web-based user interface. The project demonstrates the ability to handle hardware-to-cloud data synchronization and automated software deployment.
2. Architecture & Workflow

The system follows a three-tier architecture:

    Edge Layer (Hardware): An ESP8266 microcontroller reads data from a DHT11 sensor. It uses non-blocking logic to maintain stability.

    Cloud Layer (Middleware): Firebase Realtime Database acts as the data broker. The ESP8266 pushes updates every 5 seconds, and the database automatically broadcasts these changes.

    Application Layer (Frontend): A web dashboard built with ES6 modules listens for database changes and updates the DOM in real-time without page refreshes.

3. Hardware & Software Specifications
Component	Details
Microcontroller	

ESP8266 (NodeMCU) 
Sensor	

DHT11 (Temperature & Humidity) 
Communication	

WiFi (802.11 b/g/n) 
Database	

Firebase Realtime Database (RTDB) 
Frontend	HTML5, CSS3 (Orbitron UI), JavaScript (Firebase SDK)
CI/CD	GitHub Actions (Auto-deploy to Pages)
🛠️ How to Run the Project
Firmware (ESP12E/ESP_code.ino)

    Dependencies: Install ESP8266WiFi, Firebase_ESP_Client, and DHT libraries via the Arduino Library Manager.

    Configuration: Update the WIFI_SSID, WIFI_PASSWORD, FIREBASE_HOST, and FIREBASE_SECRET constants with your specific credentials.

    Wiring: Connect the DHT11 Data pin to GPIO2 (D4) on your ESP8266.

    Upload: Use the Arduino IDE to flash the code to your board at a baud rate of 115200.

Web UI (web/dashboard.html)

    Deployment: The project is configured for GitHub Pages. Simply push your code to the main branch, and GitHub Actions will host the site automatically.

    Logic: The logic.js file handles the Firebase connection. Ensure the firebaseConfig object matches your Firebase project settings.

    Access: Open the URL provided by GitHub Pages (e.g., https://username.github.io/Tech_DTH/).

🚀 Future Improvements

To scale this project for a professional portfolio, the following enhancements are planned:

    Security Migration: Move from Firebase Legacy Tokens to Service Account authentication for improved security.

    Data Visualization: Integrate Chart.js on the dashboard to show 24-hour temperature trends instead of just live values.

    Battery Optimization: Implement Deep Sleep mode on the ESP8266 to allow the device to run for months on a single LiPo battery.
