#include <Arduino.h>                          //Arduino.hのライブラリを取り込む
#include <WiFi.h>                             //WiFi.hのライブラリを取り込む
#include <WiFiClientSecure.h>                 //WiFiClientSecure.hのライブラリを取り込む
#include <Wire.h>
#include <Digital_Light_TSL2561.h>

const char* LINE_Token = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";//発行されたLINEのトークンを入力する
const char* LINE_Message = "手紙が来ました";  //投稿するLINEメッセージを入力する
const char* WiFi_SSID = "Your_WiFi_SSD";      //ご自分のルーターの SSID
const char* WiFi_PASSWORD = "Your_WiFI_PASSWORD";//ご自分のルーターのパスワード

const int LIGHT_SDA = 26;                     // I2C通信の際のSDAを26番ピンに割り当てる
const int LIGHT_SCL = 25;                     // I2C通信の際のSCLを25番ピンに割り当てる

boolean rerset_flag = false;

void sendLineNotify() {                       //サブルーティンsendLineNotifyを定義する
  const char* host = "notify-api.line.me";    //hostはnotify-api.line.meであると定義する

  WiFi.begin(WiFi_SSID, WiFi_PASSWORD);       //先に示されたSSIDとパスワードでWiFi接続を試みる
  Serial.print("\nWiFi Connecting");          //WiFi Connectingとメッセージを出す
  while(WiFi.status() != WL_CONNECTED) {      //WiFi接続が完了するまで待つ
    Serial.print('.');
    delay(500);
  }
  delay(1500);                                //1500msec待つ
  
  Serial.print("\nWiFi Connected\n");
  Serial.print("Local-IPv4 address: ");
  Serial.println(WiFi.localIP());             //ローカルIPv4を表示する

  WiFiClientSecure client;

  if (!client.connect(host,443)) {            //LineのAPIサーバに接続を試みる
    Serial.println("Connection failed");      //失敗したらこのルーティンから抜ける
    WiFi.disconnect();                        //WiFiから切断する
    return;
  }
  Serial.println("Connected");

  String query = String("message=") + F(LINE_Message) ;//POSTするメッセージを作成する
  String request = String("POST /api/notify HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" +
               "Authorization: Bearer " + LINE_Token + "\r\n" +
               "Content-Length: " + String(query.length()) + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
                query + "\r\n";
  client.print(request);                      //リクエストを送信する
 
  while (client.connected()) {                //受信終了まで待つ
    String line = client.readStringUntil('\n');
    if (line == "\r") {break;}
  }
  
  String line = client.readStringUntil('\n');
  Serial.println(line);
  WiFi.disconnect();                         //WiFiから切断する
}

void setup() {                               //setup - Arduinoを起動した際に最初に呼ばれる処理
Wire.begin(LIGHT_SDA, LIGHT_SCL);          // 2つのピンを使ってTSL2561とる
TSL2561.init();                            // TSL2561を初期化する
  Serial.begin(115200);                      // シリアルコンソール通信速度を115200bps
}

void loop() {                             //loop - setup処理後、loopの中の処理を電源が切れるまで繰り返す
  int HALL_VAL = hallRead();                 //HALL_VALの値は内蔵のホールセンサの値である
  int LIGHT_VAL = TSL2561.readVisibleLux();
  
while(LIGHT_VAL<100 ) {                     //LIGHT_VALが100を超えるとドアが開いたと判断する
  HALL_VAL = hallRead();
  LIGHT_VAL = TSL2561.readVisibleLux();
if(HALL_VAL>=100 && rerset_flag == true) {  //HALL_VALが100を超えるとメールが来たと判断する
    sendLineNotify();
    rerset_flag = false;
    }
    delay(1000);                            //1000msec待つ
}
  Serial.println("Door Open");
  rerset_flag = true;
  delay(1000);                              //1000msec待つ
}
