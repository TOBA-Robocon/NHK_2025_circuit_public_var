#include "CAN.h"
#include "PS4Controller.h"

void setup() {
  if(!CAN.begin(1000E3)) //通信速度
  {
    while (1);
    //送信不可
  }
  volatile uint32_t* pREG_IER = (volatile uint32_t*)0x3ff6b010;
  *pREG_IER &= ~(uint8_t)0x10;

  PS4.begin(""); //←ESP32のBluetoothMACアドレスをぶち込んで
}

void loop() {
  CAN.beginPacket(0x00);//パケット1送信開始
  
  CAN.write(0x01);//ヘッダー1

  //LスティックYの送信
  if(PS4.LStickY() >= 0){
    CAN.write(PS4.LStickY());
  }
  else{
    CAN.write(0);
  }
  if(PS4.LStickY() <= 0){
    CAN.write(-PS4.LStickY());
  }
  else{
    CAN.write(0);
  }
  //LスティックYの送信ここまで

  //LスティックXの送信
  if(PS4.LStickX() >= 0){
    CAN.write(PS4.LStickX());
  }
  else{
    CAN.write(0);
  }
  if(PS4.LStickX() <= 0){
    CAN.write(-PS4.LStickX());
  }
  else{
    CAN.write(0);
  }
  //LスティックXの送信ここまで

  //RスティックYの送信
  if(PS4.RStickY() >= 0){
    CAN.write(PS4.RStickY());
  }
  else{
    CAN.write(0);
  }
  if(PS4.RStickY() <= 0){
    CAN.write(-PS4.RStickY());
  }
  else{
    CAN.write(0);
  }
  //RスティックYの送信ここまで

  //RスティックXの送信
  if(PS4.RStickX() >= 0){
    CAN.write(PS4.RStickX());
  }
  else{
    CAN.write(0);
  }
  CAN.endPacket();//パケット1送信完了

  CAN.beginPacket(0x00);//パケット2送信開始
  
  CAN.write(0x02);//ヘッダー2

  if(PS4.RStickX() <= 0){
    CAN.write(-PS4.RStickX());
  }
  else{
    CAN.write(0);
  }
  //RスティックXの送信ここまで

  CAN.write(PS4.Up());//十字↑
  CAN.write(PS4.Right());//十字→
  CAN.write(PS4.Down());//十字↓
  CAN.write(PS4.Left());//十字←
  CAN.write(PS4.Circle());//◯ボタン
  CAN.write(PS4.Cross());//☓ボタン

  CAN.endPacket();//パケット2送信完了

  CAN.beginPacket(0x00);//パケット3送信開始
  
  CAN.write(0x03);//ヘッダー3

  CAN.write(PS4.Triangle());//△ボタン
  CAN.write(PS4.Square());//□ボタン
  CAN.write(PS4.R1());//R1ボタン
  CAN.write(PS4.L1());//L1ボタン
  CAN.write(PS4.R2Value());//R2押し込み
  CAN.write(PS4.L2Value());//L2押し込み
  CAN.write(0x00);//偽物

  CAN.endPacket();//パケット3送信完了

  delay(30);

}
