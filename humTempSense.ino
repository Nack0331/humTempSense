/*****************************************************************************
 *  温度・湿度モニター
 * 
 * センサーから取得した温度・湿度を2ライン液晶ディスプレイに表示する
 * 
 * 
 * 稼働デバイス
 * - Arduino Uno
 * 
 * モジュール類
 * - センサー: DHT11 相当品
 * - 液晶ディスプレイ: 1602A LCD 相当品
 * 
 * 使用ライブラリー
 * - I2C LCD 制御: LiquidCrystal_I2C
 *                 https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/
 *                 https://github.com/johnrickman/LiquidCrystal_I2C.git
 * - センサー制御: DHT sensor library
 *                 https://www.arduino.cc/reference/en/libraries/dht-sensor-library/
 *                 https://github.com/adafruit/DHT-sensor-library
 * 
 * 備考
 * - 各モジュールの接続等は Fritzing デザイン図を参照のこと
 *****************************************************************************/

#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// センサーのデータはデジタルピン12から入力する
#define DHT_PIN 12

// LCDタイプ
#define LCD_TYPE 0x3f
// LCD 1行あたりの文字数
#define LCD_CHAR_COUNT 16
// LCD 行数
#define LCD_LINE_COUNT 2

// センサーを接続するピンの番号, 使用するセンサーモジュールの種類を指定する
DHT dht(DHT_PIN, DHT11);

// 使用するLCDのアドレス, 1行あたりの文字数(列数), 行数を指定する
LiquidCrystal_I2C lcd(LCD_TYPE, LCD_CHAR_COUNT, LCD_LINE_COUNT);

/*********************************************************
 * initSensor
 * - センサーを初期化する
 *********************************************************/
void initSensor()
{
  // センサー使用開始
  dht.begin();
}

/*********************************************************
 * initLCD
 * - LCDを初期化する
 *********************************************************/
void initLCD()
{
  // デバイス初期化
  lcd.init();
  // バックライト: ON
  lcd.backlight();
}

/*********************************************************
 * readSenseValue
 * - センサーから値を取得・返却する
 * - 引数
 * - - tmpValue: 温度値返却用
 * - - humValue: 湿度値返却用
 * - 戻り値
 * - - true: 処理成功
 * - - false: 処理失敗
 *********************************************************/
bool readSenseValue(float *tmpValue, float *humValue)
{
  // センサーから温度を取得
  *tmpValue = dht.readTemperature();

  // センサーから湿度を取得
  *humValue = dht.readHumidity();

  // 戻り値: 2つの値が適切に取得できたかどうか
  // いずれか一方, または両方の値取得に失敗した場合は false
  return ((!isnan(*tmpValue)) && (!isnan(*humValue)));
}

/*********************************************************
 * showLCD
 * - LCDの各行に指定された表示する
 * - 引数
 * - - line1Value: 1行目用文字列
 * - - line2Value: 2行目用文字列
 *********************************************************/
void showLCD(String line1Value, String line2Value)
{
  // 現在の表示を一旦クリア
  lcd.clear();

  // 1行目: 表示位置オフセット
  lcd.setCursor(0, 0);
  // 値表示
  lcd.print(line1Value);

  // 2行目: 表示位置オフセット
  lcd.setCursor(0, 1);
  // 値表示
  lcd.print(line2Value);
}

/*********************************************************
 * showValue
 * - センサーから取得した値をLCDに表示する
 * - 引数
 * - - tmpValue: 温度値
 * - - humValue: 湿度値
 *********************************************************/
void showSenseValue(float tmpValue, float humValue)
{
  // 取得した温度・湿度を文字列に変換し, 付加情報を添えてLCDに表示
  showLCD("Tmp: " + String(tmpValue, 1) + " C", "Hum: " + String(humValue, 1) + " %");
}

/*********************************************************
 * setup
 *********************************************************/
void setup()
{
  // センサーモジュール初期化
  initSensor();

  // LCD初期化
  initLCD();

  // LCDに起動時メッセージを表示する
  showLCD("Device started!", "Please for wait.");
}

/*********************************************************
 * loop
 *********************************************************/
void loop()
{
  // センサーの応答速度 (最速2秒) を考慮し, 毎回3秒のディレイを行う
  delay(3000);

  // 適切な値が取得できなかった場合は処理中断
  float tmpVl = 0.0;
  float humVl = 0.0;
  if (!readSenseValue(&tmpVl, &humVl))
  {
    return;
  }

  // 取得した値をLCDに表示
  showSenseValue(tmpVl, humVl);
}
