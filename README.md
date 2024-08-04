# Haptic-Enhanced Arduino-Based Smart Navigation Cane

This project utilizes an Arduino-based system to assist visually impaired individuals with navigation. It combines ultrasonic sensors for obstacle detection and a GPS module for location tracking. Haptic feedback and auditory signals alert the user of nearby obstacles.

## Table of Contents

- [Installation](#installation)
- [Hardware Setup](#hardware-setup)
- [Code Overview](#code-overview)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/Haptic-Enhanced-Arduino-Based-Smart-Navigation-Cane.git
    cd Haptic-Enhanced-Arduino-Based-Smart-Navigation-Cane
    ```

2. Install the required libraries:

    - [SoftwareSerial](https://www.arduino.cc/en/Reference/softwareSerial)
    - [TinyGPS](http://arduiniana.org/libraries/tinygps/)

    You can install these libraries via the Arduino IDE Library Manager.

## Flowchart
![image](https://github.com/user-attachments/assets/2ab36c49-b728-46f1-9f8e-b014002ffc5f)


## Hardware Setup

1. **Components:**
    - Arduino Board
    - Ultrasonic Sensor (HC-SR04)
    - GPS Module
    - Buzzer
    - Vibration Motor

2. **Connections:**
    - **Ultrasonic Sensor:**
        - `Trig` to Arduino pin 7
        - `Echo` to Arduino pin 8
    - **GPS Module:**
        - `RX` to Arduino pin 0
        - `TX` to Arduino pin 1
    - **Buzzer:**
        - Positive to Arduino pin 2
        - Negative to Ground
    - **Vibration Motor:**
        - Positive to Arduino pin 3
        - Negative to Ground

## Code Overview

The main functionalities of the code are:

1. **Obstacle Detection:**
    - Uses an ultrasonic sensor to measure distance to obstacles.
    - Activates a buzzer and vibration motor if an obstacle is detected within 50 cm.

2. **GPS Tracking:**
    - Uses a GPS module to get the current location.
    - Prints GPS data to the Serial Monitor every 5 seconds.

## Usage

1. Upload the code to your Arduino board.
2. Open the Serial Monitor in the Arduino IDE to view the GPS data and distance measurements.
3. The buzzer and vibration motor will activate when an obstacle is detected within 50 cm.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

---

Please replace `https://github.com/yourusername/Haptic-Enhanced-Arduino-Based-Smart-Navigation-Cane.git` with your actual GitHub repository URL.
