# Stop-and-Wait Protocol on ESP32 🚦

This project demonstrates the **Stop-and-Wait Automatic Repeat Request (ARQ) protocol** implemented on two ESP32 boards using **Wi-Fi (UDP)**.  
The sender transmits data frames one by one, and the receiver responds with acknowledgments (ACK). If no ACK is received within a timeout, the sender retransmits the frame.

---

## 🔹 Features
- Frame transmission with sequence numbers (`DATA-0`, `DATA-1`)
- Receiver sends back ACKs (`ACK-0`, `ACK-1`)
- Timeout + retransmission for reliability
- LED indication on receiver side for successful reception
- Runs over UDP between two ESP32 boards

---

## 🛠️ Hardware Requirements
- 2 × ESP32 boards
- Wi-Fi network
- 1 × LED + resistor (for receiver)

---

## 📡 Connection Diagram
- **Sender ESP32**: Just connects to Wi-Fi, no LED needed.  
- **Receiver ESP32**: Connect an LED to GPIO 5 (or any digital pin with resistor).

---
