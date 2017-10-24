const int LED_BUILTIN = 27;              // LED_BUILTINを27番ピンに定義する
const int LIGHT_PIN = 25;                // ライトセンサーのピン番号は25番と定義する

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);          // LED_BUILTINのピンモードは出力用に定義する
  pinMode(LIGHT_PIN, INPUT);             // LIGHT_PINのピンモードは入力用に定義する
  Serial.begin(115200);                  // シリアルコンソール通信速度を115200bps
}

void loop() {
  int LIGHT_VAL = analogRead(LIGHT_PIN); // LIGHT_VALの値は、Light_Pinのアナログ値である
  Serial.println(LIGHT_VAL);             // LIGHT_VALをモニタに出力する
  if(LIGHT_VAL<700) {                    // LIGHT_VALが700未満であると次の文を実行する
  digitalWrite(LED_BUILTIN, HIGH);       // LED_BUILTINの電圧値をHIGHにしてLEDを点灯
    }
  delay(1000);                           // 1000ミリ秒待つ
  digitalWrite(LED_BUILTIN, LOW);        // LED_BUILTINの電圧値をLOWにしてLEDを消灯
  delay(1000);                           // 1000ミリ秒待つ
}
