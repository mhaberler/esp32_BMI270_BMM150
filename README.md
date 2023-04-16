# Platformio demo project the [Arduino_BMI270_BMM150](https://github.com/arduino-libraries/Arduino_BMI270_BMM150) IMU driver

works with ESP-WROVER-KIT V4.1 and M5Stack (M5Unified)
Plots data using the [Teleplot VScode extension](https://marketplace.visualstudio.com/items?itemName=alexnesnes.teleplot)

## example teleplot output

<img src="Bildschirmfoto 2023-04-16 um 14.44.08.png"/>

### ESP-WROVER-KIT V4.1  notes

I2C bus 0 (Wire) is on IO12 and IO22
[jumper the 4 JTAG pins as described here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-wrover-kit.html)
