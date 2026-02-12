# 🚗 Smart Parking System with Integrated Online Platform
An IoT-based Smart Parking System built using ESP32, Ultrasonic Sensors, Firebase Realtime Database, and a Web Application to provide real-time parking space monitoring, reservation, and online interaction.

📌 **Project Overview**
With rapid urbanization and increasing vehicle density, parking management has become a significant challenge in modern cities, often leading to traffic congestion, fuel wastage, driver frustration, and increased carbon emissions. This project proposes an IoT-based Smart Parking Solution that improves the efficiency of parking systems through real-time monitoring and digital interaction.
The system detects parking space occupancy using sensors and updates the availability status to a cloud database instantly. A web interface displays live parking information, allowing users to check free and occupied slots remotely. Additionally, the platform supports features like slot reservation and online interaction, making the parking process more convenient, time-saving, and environmentally friendly.

🧠 **System Architecture**
| Layer                 | Components Used                         | Function                                                |
| --------------------- | --------------------------------------- | ------------------------------------------------------- |
| **Hardware Layer**    | Ultrasonic Sensors (HC-SR04), ESP32     | Detects vehicle presence and sends occupancy data       |
| **Cloud Layer**       | Firebase Realtime Database              | Stores and synchronizes parking data in real time       |
| **Application Layer** | HTML, CSS, JavaScript, Firebase Web SDK | Displays live slot status and supports user interaction |

## 🛠️ Technologies Used
### 🔌 Hardware
* **ESP32 Microcontroller** – Processes sensor data and sends parking status to the cloud over Wi-Fi.
* **HC-SR04 Ultrasonic Sensors** – Detect vehicle presence in each parking slot.
* **Breadboard** – Used for circuit prototyping and component connections.
* **Jumper Wires** – Connect sensors, ESP32, and power supply.
### 💻 Software
* **Arduino IDE (ESP32 Programming)** – Used to write, compile, and upload code to the ESP32.
* **Firebase Realtime Database** – Stores and synchronizes parking slot data in real time.
* **HTML5** – Structures the web interface for displaying parking status.
* **CSS3** – Styles the web application layout and design.
* **JavaScript (ES Modules)** – Handles dynamic updates and user interactions.
* **Firebase Web SDK (v11)** – Connects the web app to Firebase for live data updates.

⚙️ **Features**
✅ Real-time parking slot detection
✅ Separate monitoring for bike and car parking spaces
✅ Firebase cloud integration for instant data sync
✅ Live parking availability updates on web interface
✅ Low-latency data transmission via Wi-Fi
✅ Scalable architecture (can add more slots easily)
✅ Energy-efficient operation using ESP32

## 🏗️ Hardware Specifications
| Component         | Specification     |
| ----------------- | ----------------- |
| Ultrasonic Sensor | HC-SR04           |
| Detection Range   | 2 cm – 4 m        |
| Accuracy          | ±3 mm             |
| ESP32 Processor   | Dual-core 32-bit  |
| Memory            | 520 KB SRAM       |
| Connectivity      | Wi-Fi + Bluetooth |
| Update Frequency  | ~1–2 seconds      |

## 🔌 Hardware Setup
**Connect Ultrasonic Sensor (HC-SR04) to ESP32:**
* VCC → 5V
* GND → GND
* Trig → ESP32 GPIO pin
* Echo → ESP32 GPIO pin
Repeat the same connections for all parking slots in both Bike and Car sections. For refernce check the circuit diagram that is attached.
* Connect ESP32 to the computer.
* Upload the ESP32 code using Arduino IDE.

## 🔥 Firebase Setup
1. Go to: [https://firebase.google.com](https://firebase.google.com)
2. Create a new project.
3. Enable **Realtime Database**.
4. Set database rules to **test mode** (for development).
5. Copy the following credentials:
   * API Key
   * Database URL
   * Authentication credentials

**Update in project files:**
* Add Firebase credentials in the ESP32 code.
* Add Firebase configuration in `app.js`.

## 🚀 How to Run the Project
### Step 1: Upload ESP32 Code
* Install the **ESP32 board package** in Arduino IDE.
* Install the required libraries:
  * `WiFi.h`
  * `Firebase_ESP_Client`
* Connect ESP32 to the system.
* Upload the code to ESP32.

### Step 2: Run the Web Application
* Place project files in a local server (e.g., Live Server in VS Code).
* Open `index.html` in the browser.
* Select vehicle type (Bike / Car).
* View real-time parking slot status.
  
## 📊 Firebase Data Structure
```
ultrasonic
 ├── bike
 │    ├── B1
 │    │    ├── distance: 40
 │    │    └── objectDetected: false
 │    ├── B2
 │
 ├── car
 │    ├── C1
 │    │    ├── distance: 12
 │    │    └── objectDetected: true
```

## 📈 Results
* Accurate real-time parking detection
* Stable Wi-Fi communication
* Minimal latency (~2 seconds)
* Successful cloud synchronization
* Scalable for larger parking areas

**Sample Serial Monitor Output:**
```
Bike Sensor B1: Distance = 39 cm, Object detected = False
Car Sensor C4: Distance = 16 cm, Object detected = False
All sensor data sent to Firebase successfully
```

## 👨‍💻 Authors
Mayur Kiran Kumar | Rutikaa M | Saharsha | Samartha K B: **RV College of Engineering**, Department of Computer Science

## 📜 License
This project is developed for academic and educational purposes.
⭐ If you found this project helpful, consider giving it a star!
