/*****************************************************************************
 * 
 * Arduino: 温湿度計測・通知モジュール
 * 
 * ---------------------------------------------------------------------------
 * 機能 
 *   センサーで温度・湿度を計測
 *   計測は3秒間隔で実施
 *   センサーはDHT11を使用
 *   センサーはPin8に接続
 *   前回計測値に対し一定量以上の変化があった場合はシリアル通信で計測値を送信
 *   シリアル通信のボーレートは9600
 *     書式1. 湿度: "H," + 計測値 + [\n]
 *     書式2. 温度: "T," + 計測値 + [\n] 
******************************************************************************/

#include "DHT.h"

#define DATA_PIN 8
#define BAUDRATE 9600
#define VL_HUM "H,"
#define VL_TMP "T,"

DHT dht(DATA_PIN, DHT11);
float lastHumidity = 0.0;
float lastTemperature = 0.0;

void setup() {
  // シリアル通信, センサー動作開始
  Serial.begin(BAUDRATE);
  dht.begin();
}

void loop() {
  // 一定時間 (3秒) ごとに処理を行う
  delay(3000);

  // 温湿度を計測
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // 適切な値が取得できなかった場合は処理中断
  if (isnanf(h) || isnanf(t)) {
    return;
  }

  // 湿度
  // 前回の計測値から一定以上の変化があった場合はシリアル通信で通知
  if (abs(lastHumidity - h) > 1.0) {
    // 前回計測値を保持
    lastHumidity = h;

    // シリアルコマンド送信
    Serial.print(VL_HUM);
    Serial.print(h);
    Serial.print('\n');
  }

  // 温度
  // 前回の計測値から一定以上の変化があった場合はシリアル通信で通知
  if (abs(lastTemperature - t) > 1.0) {
    // 前回計測値を保持
    lastTemperature = t;

    // シリアルコマンド送信
    Serial.print(VL_TMP);
    Serial.print(t);
    Serial.print('\n');
  }
}
