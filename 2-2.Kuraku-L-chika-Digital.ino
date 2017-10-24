#include <Wire.h>                              // I2C通信ライブラリを読み込む
#include <Digital_Light_TSL2561.h>             // ライトセンサーIC(TSL2561)のライブラリを読み込む

const int LED_BUILTIN = 27;                   // LED_BUILTINを27番ピンに定義する
const int LIGHT_SDA = 26;                     // I2C通信の際のSDAを26番ピンに割り当てる
const int LIGHT_SCL = 25;                     // I2C通信の際のSCLを25番ピンに割り当てる

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);               // LED_BUILTINのピンモードは出力用に定義する
Wire.begin(LIGHT_SDA, LIGHT_SCL);           // 2つのピンを使ってTSL2561とる
TSL2561.init();                             // TSL2561を初期化する
  Serial.begin(115200);                       // シリアルコンソール通信速度を115200bps
}

void loop() {
int LIGHT_VAL = TSL2561.readVisibleLux();  // LIGHT_VALの値は、TSL2561.readVisibleLux()値である
  Serial.println(LIGHT_VAL);                 // LIGHT_VALをモニタに出力する
  if(LIGHT_VAL<100) {                        // LIGHT_VALが100未満であると次の文を実行する
  digitalWrite(LED_BUILTIN, HIGH);           // LED_BUILTINの電圧値をHIGHにしてLEDを点灯
    }
  delay(1000);                               // 1000ミリ秒待つ
  digitalWrite(LED_BUILTIN, LOW);            // LED_BUILTINの電圧値をLOWにしてLEDを消灯
  delay(1000);                               // 1000ミリ秒待つ
}
