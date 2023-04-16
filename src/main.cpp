
#ifdef M5STACK
#include <M5Unified.h>
#endif
#include "Arduino_BMI270_BMM150.h"

BoschSensorClass myIMU(SENSOR_BUS);

extern void i2cScan(void);

void print_data() {
  // we can also read accelerometer / gyro data here!
  Serial.println("Got new data!");
}

void setup() {
#ifdef M5STACK
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  cfg.internal_imu = false; // default=true. use internal IMU.
  cfg.external_imu = false; // default=false. use Unit Accel & Gyro.
  cfg.led_brightness = 128; // default= 0. system LED brightness (0=off /
                            // 255=max) (※ not NeoPixel)
  M5.begin(cfg);
  // M5.Ex_I2C.begin();
#else
  Serial.begin(115200);
#endif

  /* Wait for the Serial Monitor */
  while (!Serial) {
    yield();
  }
  i2cScan();

  myIMU.debug(Serial);
  // myIMU.onInterrupt(print_data);
  myIMU.begin();

  Serial.print("Accelerometer sample rate = ");
  Serial.println(myIMU.accelerationSampleRate());
}

void loop() {
  // put your main code here, to run repeatedly:
  float x, y, z;

  if (myIMU.accelerationAvailable()) {
    myIMU.readAcceleration(x, y, z);

    Serial.print("accel: \t");
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    Serial.println();
  }

  if (myIMU.gyroscopeAvailable()) {

    myIMU.readGyroscope(x, y, z);

    Serial.print("gyro: \t");
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    Serial.println();
  }

  if (myIMU.magneticFieldAvailable()) {

    myIMU.readMagneticField(x, y, z);

    Serial.print("mag: \t");
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    Serial.println();
  }
  delay(500);
}
