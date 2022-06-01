#include <Wire.h> 
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <U8x8lib.h>
#include <virtuabotixRTC.h>
// RS485 setup with ESp32
#define RE 2  // Connect RE terminal with 32 of ESP
#define DE 3    // Connect DE terminal with 33 of ESP 
#define led1 5   
//05 03 00 02 00 01 24 4E  
        
const byte ModReadBuffer[] = {0x01, 0x03, 0x00, 0x30, 0x00, 0x01, 0x84, 0x05}; //48
const byte ModReadBufferh[] = {0x01, 0x03, 0x00, 0x32, 0x00, 0x01, 0x25, 0xC5}; //50
const byte ModReadBufferi[] = {0x01, 0x03, 0x00, 0x2D, 0x00, 0x01, 0x14, 0x03}; //45
const byte ModReadBufferj[] = {0x01, 0x03, 0x02, 0x0B, 0x00, 0x01, 0xF4, 0x70}; //523
const byte ModReadBufferk[] = {0x01, 0x03, 0x02, 0x0C, 0x00, 0x01, 0x45, 0xB1}; //524
//const byte ModReadBufferj[] = {0x01, 0x03, 0x00, 0x30, 0x00, 0x01, 0x84, 0x05}; //48--523
//const byte ModReadBufferk[] = {0x01, 0x03, 0x00, 0x32, 0x00, 0x01, 0x25, 0xC5}; //50--524
//const byte ModReadBufferj[] = {0x01, 0x03, 0x02, 0x0B, 0x00, 0x01, 0xF4, 0x70}; //523
//const byte ModReadBufferk[] = {0x01, 0x03, 0x02, 0x0C, 0x00, 0x01, 0x45, 0xB1}; //524

//01 03 02 0B 00 02 B4 71 :4523
//01 03 1B 59 00 01 52 FD :7001
//01 03 1B 5A 00 01 A2 FD :7002
//01 03 1B 5B 00 01 F3 3D :7003
//01 03 1B 5C 00 01 42 FC :7004
float inta,intb,intc,intd,intea,intf,intg,inth,inti,intt,intsub,intpre,inttn ;
uint16_t ib,ic,id,ie,ig,ih,ii,ij,ik,il,im,in,io,ip,iq,ir,is,it ;
byte i;

//const byte ModReadBuffer[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
virtuabotixRTC myRTC(4, 6, 7); //(14, 12, 13) If you change the wiring change the pins here also
//  Serial.print(myRTC.year);  Serial.print(myRTC.month);(myRTC.hours); (myRTC.dayofmonth); 
byte BufferValue[8];
//SoftwareSerial mod(9, 8); // RX=26(uno 9) , TX =27(uno 10)
//SoftwareSerial mod(0, 1);
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
File myFile;

void setup() {
    pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW);
    u8x8.begin();
  Serial.begin(19200, SERIAL_8E1);
  
     SD.begin(10);     
    if (!SD.begin(10)) {
      for(int y = 0; y < 200; y++) {  //132
         digitalWrite(led1, HIGH);
         delay(500);
         digitalWrite(led1, LOW);
         delay(500);}
 //       digitalWrite(led1, HIGH);
    while (1);
    }
//  myRTC.setDS1302Time(15, 29, 21, 3, 18, 5, 2022);
    digitalWrite(led1, LOW);
    delay(1000);
    myRTC.updateTime();
    ModbusDatas();
    digitalWrite(led1, LOW);
}


void loop() {
//    myRTC.updateTime();
// delay(500);
  /*  char text;
     u8x8.setFont(u8x8_font_8x13B_1x2_f);
  u8x8.setCursor(0,2); //................
  sprintf(time_output, "%02d:%02d:%02d", myRTC.hours, myRTC.minutes, myRTC.seconds);
//    sprintf(time_output, "%02d/%02d/%02d", myRTC.dayofmonth, myRTC.month, myRTC.year);
  u8x8.print(time_output);
//  sprintf(time_output, "%02d:%02d:%02d", myRTC.hours, myRTC.minutes, myRTC.seconds);
  delay(10000);
    text = char(myRTC.minutes); */
//if (text == '15') { 
//  if (myRTC.minutes = 15) { 
  u8x8.clearDisplay();
    ModbusData();  //10 times
//   delay(15000);
    delay(3596000);
/*if (myRTC.hours = 5) { 
    ModbusData();  //10 times
    delay(3600000);}
if (myRTC.hours = 9) { 
    ModbusData();  //10 times
    delay(3600000);}
if (myRTC.hours = 13) { 
    ModbusData();  //10 times
    delay(3600000);}
if (myRTC.hours = 17) { 
    ModbusData();  //10 times
    delay(3600000);}
if (myRTC.hours = 21) { 
    ModbusData();  //10 times
    delay(3600000);}  */
  digitalWrite(led1, LOW);}              
//}
void ModbusData() {
  float inta,intb,intc,intd,intea,intf,intg,inth,inti,intt,intsub,intpre,inttn =0;
  uint16_t ib,ic,id,ie,ig,ih,ii,ij,ik,il,im,in,io,ip,iq,ir,is,it =0;
     digitalWrite(led1, HIGH);
   myRTC.updateTime();
   delay(800);
//     u8x8.clearDisplay();
  char time_output[30];
  char time_outputa{30};
  char text_output[20];
//  byte i;  //========================================================48=============1
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBuffer,sizeof(ModReadBuffer))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
 /*         uint16_t ib = BufferValue[3];
          uint16_t ic = BufferValue[4];
   inta = (ib*256 + ic) ;
      u8x8.setFont(u8x8_font_8x13B_1x2_f);
     u8x8.setCursor(6,4);
  u8x8.print((ib*256 + ic)); //48*/  
   }
  }   //============================================================================
       delay(1800);
//  byte i;  //=======================================================50=============2
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBufferh,sizeof(ModReadBufferh))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
          uint16_t id = BufferValue[3];
          uint16_t ie = BufferValue[4];
             intb = (id*256 + ie)/100.0f ;
                u8x8.setFont(u8x8_font_8x13B_1x2_f);
               u8x8.setCursor(11,0);
  u8x8.print((id*256 + ie)/100.0f); //50
   }
  }   //============================================================================
       delay(1800);
//  byte i;  //======================================================45===========3
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBufferi,sizeof(ModReadBufferi))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
          uint16_t ig = BufferValue[3];
          uint16_t ih = BufferValue[4];
             intc = (ig*256 + ih)/100.0f ;
             u8x8.setFont(u8x8_font_8x13B_1x2_f);
             u8x8.setCursor(11,2); //
             u8x8.print((ig*256 + ih)/100.0f);   //45
   }
  }   //============================================================================ 
       delay(1800);
//  byte i;  //================================================================523==4
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBufferj,sizeof(ModReadBufferj))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
          uint16_t ii = BufferValue[3];
          uint16_t ij = BufferValue[4];
             intd = (ii*256 + ij)/10.0f ;
               u8x8.setFont(u8x8_font_8x13B_1x2_f);
               u8x8.setCursor(11,4);  //
               u8x8.print((ii*256 + ij)/10.0f); //523 h 

   }
  }   //============================================================================
  delay(1800);  
//  byte i;  //===========================================523============524====5
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBufferk,sizeof(ModReadBufferk))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
          uint16_t ik = BufferValue[3];
          uint16_t il = BufferValue[4];

             intea = (ik*256 + il) ;
             u8x8.setCursor(0,4);  // 
             u8x8.print(ik*256 + il); //523 l ?(0)?
   }
  }   //============================================================================
    delay(1800);  
//  byte i;  //=================================================524=========524====0
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBufferk,sizeof(ModReadBufferk))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
         uint16_t ib = BufferValue[3];
          uint16_t ic = BufferValue[4];
   inta = (ib*256 + ic) ;
      u8x8.setFont(u8x8_font_8x13B_1x2_f);
     u8x8.setCursor(6,4);
  u8x8.print((ib*256 + ic)); //524*/  

           intpre = (intt) ;  //ok
           inttn = (((ib*256 + ic)*65536)) ;
//           inttn = ((((ib*256 + ic)*65536))/10.0f) ;
           intt = (inttn + intea) ;
           intsub = (intt -intpre) ;  //ok

           u8x8.setCursor(0,0);  //
           u8x8.print(intsub); //523 l (inttn)(inta)intsub
           u8x8.setFont(u8x8_font_8x13B_1x2_f);
//               u8x8.print(intea); //523 l 
                u8x8.setCursor(0,6);  //
           u8x8.print(intt); //524 h (intea)(intt)          
//           u8x8.print(intsub); //524 h   */
   }
  }   //============================================================================
  delay(1800);

 SD.begin(10);
 delay(100);   
  myFile = SD.open("test.txt", FILE_WRITE);
   delay(100); 
  // if the file opened okay, write to it:
if (myFile) {
//  myFile.print(inta);
//       myRTC.updateTime();
/*    sprintf(time_output, "%02d/%02d/%02d/%02d", myRTC.dayofmonth, myRTC.month, myRTC.year);
        delay(800);
    myFile.print(time_output);
    myFile.print(",");  //fix for two
    sprintf(time_outputa, "%02d:%02d:%02d", myRTC.hours, myRTC.minutes, myRTC.seconds);
    delay(800);
    myFile.print(time_outputa);*/
    sprintf(time_output, "%02d/%02d/%02d", myRTC.month, myRTC.dayofmonth, myRTC.hours);
    myFile.print(time_output);
    myFile.print(",");  //fix for two
//    sprintf(time_output, "%02d:%02d:%02d", myRTC.hours, myRTC.minutes, myRTC.seconds);
//    myFile.print(time_output);
//    myFile.print(",");  //fix for two
      myFile.print(intb);
          myFile.print(",");  //fix for two
      myFile.print(intc);  //48
          myFile.print(",");  //fix for two
      myFile.print(intd);  //50  
          myFile.print(",");  //fix for two
      myFile.print(intea);    //523  //45
          myFile.print(",");  //fix for two
      myFile.print(inta);     //524  //523
          myFile.print(",");  //fix for two
      myFile.print(intt);     //total of power comsumption
          myFile.print(",");  //fix for two
      myFile.print(intsub);      //total
          myFile.println(",");  //fix for two
    delay(500);
    myFile.close();
    //Serial.println("done.");
 
}
//         myRTC.updateTime();

      delay(800);
  u8x8.setFont(u8x8_font_8x13B_1x2_f);
  u8x8.setCursor(0,2); //................
  sprintf(time_output, "%02d:%02d:%02d", myRTC.hours, myRTC.minutes, myRTC.seconds);
  u8x8.print(time_output);
//   u8x8.setFont(u8x8_font_8x13B_1x2_f);
        digitalWrite(led1, LOW);
}

void ModbusDatas() {
     digitalWrite(led1, HIGH);
   myRTC.updateTime();
   delay(800);
//     u8x8.clearDisplay();
  char time_output[30];
  char time_outputa{30};
  char text_output[20];
//  byte i;  //========================================================48=============1
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBuffer,sizeof(ModReadBuffer))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
          uint16_t ib = BufferValue[3];
          uint16_t ic = BufferValue[4];
   inta = (ib*256 + ic)/100.0f ;
      u8x8.setFont(u8x8_font_8x13B_1x2_f);
     u8x8.setCursor(11,0);
  u8x8.print((ib*256 + ic)/100.0f); //48  
   }
  }   //============================================================================
       delay(1800);
//  byte i;  //=======================================================50=============2
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBufferh,sizeof(ModReadBufferh))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
          uint16_t id = BufferValue[3];
          uint16_t ie = BufferValue[4];
             intb = (id*256 + ie)/100.0f ;
                u8x8.setFont(u8x8_font_8x13B_1x2_f);
               u8x8.setCursor(11,2);
  u8x8.print((id*256 + ie)/100.0f); //50
   }
  }   //============================================================================
       delay(1800);
//  byte i;  //======================================================45===========3
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBufferi,sizeof(ModReadBufferi))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
          uint16_t ig = BufferValue[3];
          uint16_t ih = BufferValue[4];
             intc = (ig*256 + ih)/10.0f ;
                u8x8.setFont(u8x8_font_8x13B_1x2_f);
               u8x8.setCursor(11,4); //
  u8x8.print((ig*256 + ih)/100.0f);   //45
   }
  }   //============================================================================ 
       delay(1800);
//  byte i;  //================================================================523==4
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBufferj,sizeof(ModReadBufferj))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
          uint16_t ii = BufferValue[3];
          uint16_t ij = BufferValue[4];
             intd = (ii*256 + ij)/10.0f ;
               u8x8.setFont(u8x8_font_8x13B_1x2_f);
               u8x8.setCursor(0,4);  //
               u8x8.print((ii*256 + ij)/10.0f); //523 h 

   }
  }   //============================================================================
  delay(1800);  
//  byte i;  //===============================================================524====5
  digitalWrite(DE,HIGH);  //HIGH
  digitalWrite(RE,HIGH);  //HIGH
//  delay(2000);
  if(Serial.write(ModReadBufferk,sizeof(ModReadBufferk))==8){
    digitalWrite(DE,LOW);  //LIW
    digitalWrite(RE,LOW);  //LOW
//    delay(2000);
    for(i=0;i<8;i++){
//          for(i=0;i<4;i++){
    //Serial.print(mod.read(),HEX);
    BufferValue[i] = Serial.read();
    }
    if(BufferValue[1]!=255 && BufferValue[2]!=255 && BufferValue[2]!=255){
          uint16_t ik = BufferValue[3];
          uint16_t il = BufferValue[4];
/*             intpre = intt ;
           intt = ((((ik*256 + il)*65536)+(ii*256 + ij))/10.0f);
           intsub =intt - intpre ;
           u8x8.setCursor(0,6);  //
           u8x8.print(intt); //524 h 
           u8x8.setCursor(0,0);  //
           u8x8.print(intsub); //524 h   */
   }
  }   //============================================================================
//  delay(1800);
      delay(800);
  u8x8.setFont(u8x8_font_8x13B_1x2_f);
  u8x8.setCursor(0,2); //................
  sprintf(time_output, "%02d:%02d:%02d", myRTC.hours, myRTC.minutes, myRTC.seconds);
  u8x8.print(time_output);
//   u8x8.setFont(u8x8_font_8x13B_1x2_f);
        digitalWrite(led1, LOW);
}
