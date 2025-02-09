# AWCPB3 Project

This project is an ESPHome configuration for monitoring air quality and displaying sensor data on an SSD1306 display. The configuration includes multiple pages to show different sensor readings and automatically dims the display if no button is pressed for 1 minute.

## Features
Sensors Used
1. **AHT20** (Temperature & Humidity) I2C (Address: 0x38)  
2.	**BMP280** (Temperature & Pressure) I2C (Address: 0x77)  
3.	**PMSX003** (Air Quality - PM1.0, PM2.5, PM10) UART (TX: GPIO5, RX: GPIO4)  
4.	**CO2 Sensor** (PWM-based)  
5.	**MQ2** (Gas Sensor - Smoke, LPG, CO, etc.).  
6.	**MQ135** (Air Quality - NH3, NOx, Benzene, etc.)  

others  

7. Buzzer (Alarm) Connected to GPIO2 for audio alerts.
8. Button GPIO0 (Boot button) for page change (single press) and wifi connect (double press)

Wiring Diagram

| Sensor/Module                  | Communication     | ESP8266 Pin            |
|--------------------------------|------------------|------------------------|
| AHT20 (Temp & Humidity)       | I2C              | SDA: GPIO14, SCL: GPIO12 |
| BMP280 (Temp & Pressure)      | I2C              | SDA: GPIO14, SCL: GPIO12 |
| PMSX003 (Air Quality)         | UART             | TX: GPIO5, RX: GPIO4    |
| CO2 Sensor                    | PWM              | GPIO13                  |
| MQ2 (Gas Sensor)              | Analog/Digital   | Analog or Digital Pin   |
| MQ135 (Air Quality Sensor)    | Analog/Digital   | Analog or Digital Pin   |
| OLED Display (SSD1306 128x64) | I2C              | SDA: GPIO14, SCL: GPIO12 |
| Buzzer                        | GPIO             | GPIO2                   |
| Button                    | GPIO             | GPIO0                   |

**TIP:** Adding sensor one by one to ensure they are working correctly and not prevent the ESP from booting up!

#### Automatic Dimming  
The display brightness is automatically dimmed if no button is pressed for 1 minute. 

#### On boot behaviour
By default, the system will boot, then attempt to connect to Wi-Fi. After connected, the system will sync time. If successful, the system will turn off Wi-Fi to save power. (You can disable this by modifying the YAML file.) You can press the button twice to reenable the Wi-Fi. 

### Setup Instructions

1. **Install ESPHome**: Follow the [ESPHome installation guide](https://esphome.io/guides/installing_esphome.html) to set up ESPHome on your system.
2. **Clone the Repository**: Clone this repository to your local machine.
   ```bash
   git clone https://github.com/yourusername/AWCPB3.git
   cd AWCPB3```
3. **Configure WiFi:**: Update the WiFi credentials in the AWCPB3.yaml file.  
    ```
    wifi:
        ssid: "YourSSID"
        password: "YourPassword"
    ```  
4. **Compile and Upload:** Compile and upload the configuration to your ESP device.
`esphome run AWCPB3.yaml`

### Code Snippets
Display Page Example
```
display:
  - platform: ssd1306_i2c
    model: "SSD1306 128x64"
    address: 0x3C
    id: my_display
    pages:
      - id: alarm_page
        lambda: |-
          it.printf(0, 0, id(open_sans), "ALARM");
          it.strftime(80, 0, id(open_sans), "%H:%M:%S", id(sntp_time).now());
          int air_problem = check_save_air(); 
          if(air_problem){
            it.printf(0, 13, id(open_sans), "Problem: %i", air_problem);
            if(air_problem == 3){
              it.printf(0, 26, id(open_sans), "LPG/Propane/H2/CO");
              it.printf(0, 39, id(open_sans), "CH4 detected");
            }
            if(air_problem == 4){            
              it.printf(0, 26, id(open_sans), "NH3/NOx/alcohol/Benze");
              it.printf(0, 39, id(open_sans), "Smoke detected");
            }
            if(air_problem == 2){
              it.printf(0, 26, id(open_sans), "Co2 is high");
              it.printf(0, 13, id(open_sans), "Co2: %.1f ppm", id(co2_sensor).state);
            }
            if(air_problem == 1){
              it.printf(0, 26, id(open_sans), "PM2.5 is high");
              it.printf(0, 13, id(open_sans), "PM2.5: %.1f µg/m³", id(pm_2_5).state);
            }
          }
          else{
            it.printf(0, 13, id(open_sans), "No Problem");
          }
```

License
This project is licensed under the MIT License.