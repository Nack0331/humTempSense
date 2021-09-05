# humTempSense

## 概要

温度・湿度センサーから取得した値を2ラインLCDに表示するサンプルプログラムです。

# 稼働デバイス

- Arduino Uno

## モジュール類

- センサー: DHT11 相当品
- 液晶ディスプレイ: 1602A LCD 相当品

## 使用ライブラリー

- I2C LCD 制御: LiquidCrystal_I2C
  - https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/
  - https://github.com/johnrickman/LiquidCrystal_I2C.git
- センサー制御: DHT sensor library
  - https://www.arduino.cc/reference/en/libraries/dht-sensor-library/
  - https://github.com/adafruit/DHT-sensor-library
