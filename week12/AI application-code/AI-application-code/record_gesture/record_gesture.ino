#include <Wire.h>
#include "MPU6050.h"

MPU6050 IMU;
//宣告一個MPU6050，叫作IMU
#define NUM_AXES 3
//總共加速度有3個方向ax,ay,az(三軸)
#define TRUNCATE_AT 20
//加速度值的合理範圍，過濾掉雜訊、不合理的值(spikes)
#define ACCEL_THRESHOLD 5
//完成一次動作的閥值，3軸加速度的絕對值總和超過5，就代表使用者開始在做動作
#define NUM_SAMPLES 30
//ax,ay,az各方向的測量值數目，每個方向存30筆資料
double baseline[NUM_AXES];
//同一瞬間的ax,ay,az的3軸資料
float features[NUM_SAMPLES * NUM_AXES];
//儲存全部3軸各30筆資料，共90筆資料(30*3=90)


void setup() {
  Serial.begin(115200);
  //請注意！鮑率是115200！！！
  while(!IMU.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
  delay(500);
  }
  //初始化MPU6050，讀取不到會印訊息
  recordBaseline();
  //成功初始化後，進行一次3軸加速度的數值讀取，作為3軸加速度的基準值
}


void imu_read(float *ax, float *ay, float *az) {
  Vector normAccel = IMU.readNormalizeAccel();
    
  *ax = normAccel.XAxis;
  *ay = normAccel.YAxis;
  *az = normAccel.ZAxis;
}//此函式負責讀取3軸加速度數值

void recordBaseline() {
    float ax, ay, az;
    for (int i = 0; i < 10; i++) {
        imu_read(&ax, &ay, &az);
        delay(100);
    }
    baseline[0] = ax;
    baseline[1] = ay;
    baseline[2] = az;
}//此函式負責讀取3軸加速度數值作為3軸加速度的基準值


bool motionDetected(float ax, float ay, float az) {
    return (abs(ax) + abs(ay) + abs(az)) > ACCEL_THRESHOLD;
}//3軸加速度的絕對值總和超過"ACCEL_THRESHOLD"(此處設定為5)
//就代表使用者完成一次動作


void recordIMU() {
    float ax, ay, az;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        imu_read(&ax, &ay, &az);
        ax = constrain(ax - baseline[0], -TRUNCATE_AT, TRUNCATE_AT);
        ay = constrain(ay - baseline[1], -TRUNCATE_AT, TRUNCATE_AT);
        az = constrain(az - baseline[2], -TRUNCATE_AT, TRUNCATE_AT);
        //判斷ax,ay,az的值，限制值在正負"TRUNCATE_AT"(此處設定為20)
        features[i * NUM_AXES + 0] = ax;
        features[i * NUM_AXES + 1] = ay;
        features[i * NUM_AXES + 2] = az;
        //將3軸加速度值依序存入陣列
        delay(30);
    }
}


void printFeatures() {
    const uint16_t numFeatures = sizeof(features) / sizeof(double);
    //計算"features"陣列的大小(也就是3軸加速度值的總數:90)
    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? ' ' : ',');
    }
    Serial.println(' ');//依序將值印出
}


void loop() {
    float ax, ay, az;
    //宣告3個變數儲存3軸加速度值
    imu_read(&ax, &ay, &az);
    //讀取＆存入3軸加速度值
    ax = constrain(ax - baseline[0], -TRUNCATE_AT, TRUNCATE_AT);
    ay = constrain(ay - baseline[1], -TRUNCATE_AT, TRUNCATE_AT);
    az = constrain(az - baseline[2], -TRUNCATE_AT, TRUNCATE_AT);
    //判斷ax,ay,az的值，限制值在正負"TRUNCATE_AT"(此處設定為20)
    if (!motionDetected(ax, ay, az)) {
        delay(10);
        return;
    }
    //確定是否成功感測到動作，沒有就重新偵測

    recordIMU();
    //讀取30次動作的3軸加速度值
    printFeatures();
    //印出30次動作的加速度值

    delay(2000);
} 
