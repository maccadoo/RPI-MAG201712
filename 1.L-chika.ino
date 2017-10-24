const int LED_BUILTIN = 27;          // LED_BUILTINを27番ピンに定義する

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);      // LED_BUILTINのピンモードは出力用に定義する
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // LED_BUILTINの電圧値をHIGHにしてLEDを点灯
  delay(1000);                       // 1000ミリ秒待つ
  digitalWrite(LED_BUILTIN, LOW);    // LED_BUILTINの電圧値をLOWにしてLEDを消灯
  delay(1000);                       // 1000ミリ秒待つ
}
