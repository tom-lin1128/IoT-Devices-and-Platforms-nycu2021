#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <math.h>

Adafruit_MPU6050 mpu;
float distance = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  //Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
   // Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
 // Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
 // Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
   // Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    //Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    //Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    //Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  //Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    //Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    //Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    //Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    //Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  //Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    //Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    //Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    //Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    //Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    //Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    //Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    //Serial.println("5 Hz");
    break;
  }

  //Serial.println("");
  delay(100);

}

void loop() {
  /* Print out the values */
  /*
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");*/
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /*float aa = sqrt(pow(a.acceleration.x,2)+pow(a.acceleration.y,2)+pow(a.acceleration.z - 9.64,2));
  Serial.print("acceleration :");
  Serial.println(aa);*/

  /*float xs = a.acceleration.x * 0.5 * 0.25;
  float ys = a.acceleration.y * 0.5 * 0.25;
  float zs = (a.acceleration.z - 9.2) * 0.5 * 0.25;
  distance += sqrt(pow(xs,2)+pow(ys,2)+pow(zs,2));
  Serial.println("distance angle");
  //Serial.print("distance :");
  Serial.print(distance);

  float Ax = g.gyro.x*0.5;
  float Ay = g.gyro.y*0.5;
  float Az = g.gyro.z*0.5;
  float Angle = sqrt(pow(Ax,2)+pow(Ay,2)+pow(Az,2));
  //Serial.print("Rotation angle: ");
  Serial.print(" ");
  Serial.println(Angle);*/
  float roll = atan2(-g.gyro.y,g.gyro.z)/M_PI*180;
  float pitch = atan2(g.gyro.x,sqrt(pow(g.gyro.y,2)+pow(g.gyro.z,2)))/M_PI*180;
  Serial.println("roll pitch");
  //Serial.print("roll : ");
  Serial.print(roll);
  //Serial.print("pitch : ");
  Serial.print(" ");
  Serial.println(pitch);
  //Serial.println();
  /*
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");*/
  delay(500);
}
