#define BLYNK_PRINT Serial

#include <DHT.h>                                  //DHT.hのライブラリを取り込む
#include <math.h>                                 //math.hのライブラリを取り込む
#include <WiFi.h>                                 //WiFi.hのライブラリを取り込む
#include <WiFiClient.h>                           //WiFiClient.hのライブラリを取り込む
#include <BlynkSimpleEsp32.h>                     //BlynkSimpleEsp32.hのライブラリを取り込む

const char* Blynk_auth = "xxxxxxxxx";             //Blynkに書いてある AUTH TOKEN
const char* WiFi_SSID = "Your_WiFi_SSID";         //接続先のWiFiのSSIDを入力する
const char* WiFi_PASSWORD = "Your_WiFi_PASSWORD"; //接続先のWiFiのパスワードを入力する

const int BUZZER_PIN = 25;                        //定数BUZZER_PINは整数型で16番ピンであると定義する
const int LED_BUILTIN = 27;                       //1定数LED_PINは27番ピンであると定義する

const uint8_t DHT_PIN = 16;                       //DHT11を使用した場合
const uint8_t DHT_TYPE = DHT11;                   //DHT11を使用した場合
//const uint8_t DHT_TYPE = DHT21;                 //DHT21, AM2301を使用した場合
//const uint8_t DHT_TYPE = DHT22;                 //DHT22, AM2302, AM2321を使用した場合

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

void TimerSensor() {                              //サブルーティンTimerSensorを定義する
  float Hum = dht.readHumidity();                 //Humはdhtの湿度を読み込んだ値
  float Temp = dht.readTemperature();             //Tempはdhtの温度を読み込んだ値
  if (isnan(Hum) || isnan(Temp)) {                //Hum,Tempの値がなかった場合、エラーを表示する
   Serial.println("Failed to read from DHT sensor!");
   return;
  }
  Blynk.virtualWrite(V0, Hum);                    //湿度をBlynkに送る
  Blynk.virtualWrite(V1, Temp);                   //温度をBlynkに送る
  
  if (Temp >= expf(3.737622-0.005*Hum)) {         //熱中症の警告領域を近似計算
   Blynk.notify("熱中症に注意して下さい");
   digitalWrite(BUZZER_PIN, HIGH);                //BUZZER_PINの電圧値をHIGHにしてLEDを点灯
   digitalWrite(LED_BUILTIN, HIGH);               //LED_BUILTINの電圧値をHIGHにしてLEDを点灯
  }
  delay(1000);                                    //1000ミリ秒待つ
  digitalWrite(BUZZER_PIN, LOW);                  //BUZZER_PINの電圧値をLOWにしてLEDを消灯
  digitalWrite(LED_BUILTIN, LOW);                 //LED_BUILTINの電圧値をLOWにしてLEDを消灯
  delay(1000);                                    //1000ミリ秒待つ
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);                    //BUZZER_PINを出力用として使うと定義する
  pinMode(LED_BUILTIN, OUTPUT);                   //LED_PINを出力用として使うと定義する
  Serial.begin(115200);                           //ボーレイト115200bpsでシリアル通信をする
  Blynk.begin(Blynk_auth,WiFi_SSID,WiFi_PASSWORD);//Blynk.begin処理を使う。内容はBlynkSimpleEsp32.hの中に書いてある
  dht.begin();                                    //dht.begin処理を使う。内容はDHT.hの中に書いてある
  timer.setInterval(1000L, TimerSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
