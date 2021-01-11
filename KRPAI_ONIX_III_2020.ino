// Bismillah
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
 
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
#define jml_servo 18
#define del 250
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
//################ a1,a2,a3,b3,b2,b1,c1,c2,c3,d3,d2,d1,e1,e2,e3,f3,f2,f1 #############//
int servoPins[] = {45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28};
int ss[] = {130,80,60,120,145,65,145,75,45,75,76,50,150,40,70,110,149,75};

Servo servos[jml_servo];
int relay=5;
int led=3;
int led2=12;
int led3=13;
int garis=A1;
int flameakeh1=19;
int flameakeh2=18;
int flameakeh3=17;
int flameakeh4=16;
int flameakeh5=15;
int flametgh1=11;
int flametgh2=10;
int flameknn1=50;
int flameknn2=9;
int flamekri1=8;
int flamekri2=16;
float bacagaris=0;
int deley=270;
int line=0,logic_program=0,grs=0,nilaigaris=0,Scand=0,apiknn1=0,apiknn2=0,apikri1=0,apikri2=0,apitgh1=0,apitgh2=0,apiakeh1=0,apiakeh2=0,apiakeh3=0,apiakeh4=0,apiakeh5=0;
int sp = 10;
float kp = 1.18;
float ki = 0.67;
float kd = 0.15;
float Out,p,i,d,pid;
float error,errorx,sumerr;
float heading,x,y,z;
const int pingkiri_blk = 46;
const int pingkiri_tgh = 22;
const int pingkiri_dpn = 48;
const int pingdepan_kri = 49;
const int pingdepan_tgh = 52;
const int pingdepan_knn = 51;
const int pingkanan_dpn = 27;
const int pingkanan_tgh = 24;
const int pingkanan_blk = 25;
long durationkiri_blk,durationkiri_tgh,durationkiri_dpn,durationdepan_kri,durationdepan_tgh,durationdepan_knn,durationkanan_dpn,durationkanan_tgh,durationkanan_blk,uskri_blk,uskri_tgh,uskri_dpn,usdpn_kri,usdpn_tgh,usdpn_knn,usknn_dpn,usknn_tgh,usknn_blk;
long microsecondsToCentimeters(long microseconds){
  return floor (microseconds / 2 / 29);
}
void uskiri_blk(){
  pinMode(pingkiri_blk,OUTPUT);
  digitalWrite(pingkiri_blk,LOW);
  delayMicroseconds(2);
  digitalWrite(pingkiri_blk,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingkiri_blk,LOW);
  pinMode(pingkiri_blk,INPUT);
  durationkiri_blk = pulseIn(pingkiri_blk,HIGH);
  uskri_blk = microsecondsToCentimeters(durationkiri_blk);
}
void uskiri_tgh(){
  pinMode(pingkiri_tgh,OUTPUT);
  digitalWrite(pingkiri_tgh,LOW);
  delayMicroseconds(2);
  digitalWrite(pingkiri_tgh,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingkiri_tgh,LOW);
  pinMode(pingkiri_tgh,INPUT);
  durationkiri_tgh = pulseIn(pingkiri_tgh,HIGH);
  uskri_tgh = microsecondsToCentimeters(durationkiri_tgh);
  error = sp-uskri_tgh;
  p=error*kp;
  sumerr=error+errorx;
  i = ki*sumerr;
  d = error-errorx;
  errorx=error;
  Out = p+i+d;
  pid=Out;
  if(pid > 5) pid=-5;
  else if(pid < 5) pid=5;
}
void uskiri_dpn(){
  pinMode(pingkiri_dpn,OUTPUT);
  digitalWrite(pingkiri_dpn,LOW);
  delayMicroseconds(2);
  digitalWrite(pingkiri_dpn,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingkiri_dpn,LOW);
  pinMode(pingkiri_dpn,INPUT);
  durationkiri_dpn = pulseIn(pingkiri_dpn,HIGH);
  uskri_dpn = microsecondsToCentimeters(durationkiri_dpn);
}
void usdepan_kiri(){
  pinMode(pingdepan_kri,OUTPUT);
  digitalWrite(pingdepan_kri,LOW);
  delayMicroseconds(2);
  digitalWrite(pingdepan_kri,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingdepan_kri,LOW);
  pinMode(pingdepan_kri,INPUT);
  durationdepan_kri = pulseIn(pingdepan_kri,HIGH);
  usdpn_kri = microsecondsToCentimeters(durationdepan_kri);
}
void usdepan_tengah(){
  pinMode(pingdepan_tgh,OUTPUT);
  digitalWrite(pingdepan_tgh,LOW);
  delayMicroseconds(2);
  digitalWrite(pingdepan_tgh,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingdepan_tgh,LOW);
  pinMode(pingdepan_tgh,INPUT);
  durationdepan_tgh = pulseIn(pingdepan_tgh,HIGH);
  usdpn_tgh = microsecondsToCentimeters(durationdepan_tgh);
}
void usdepan_kanan(){
  pinMode(pingdepan_knn,OUTPUT);
  digitalWrite(pingdepan_knn,LOW);
  delayMicroseconds(2);
  digitalWrite(pingdepan_knn,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingdepan_knn,LOW);
  pinMode(pingdepan_knn,INPUT);
  durationdepan_knn = pulseIn(pingdepan_knn,HIGH);
  usdpn_knn = microsecondsToCentimeters(durationdepan_knn);
}
void uskanan_dpn(){
  pinMode(pingkanan_dpn,OUTPUT);
  digitalWrite(pingkanan_dpn,LOW);
  delayMicroseconds(2);
  digitalWrite(pingkanan_dpn,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingkanan_dpn,LOW);
  pinMode(pingkanan_dpn,INPUT);
  durationkanan_dpn = pulseIn(pingkanan_dpn,HIGH);
  usknn_dpn = microsecondsToCentimeters(durationkanan_dpn);
}
void uskanan_tgh(){
  pinMode(pingkanan_tgh,OUTPUT);
  digitalWrite(pingkanan_tgh,LOW);
  delayMicroseconds(2);
  digitalWrite(pingkanan_tgh,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingkanan_tgh,LOW);
  pinMode(pingkanan_tgh,INPUT);
  durationkanan_tgh = pulseIn(pingkanan_tgh,HIGH);
  usknn_tgh = microsecondsToCentimeters(durationkanan_tgh);
  error = sp-usknn_tgh;
  p=error*kp;
  sumerr=error+errorx;
  i = ki*sumerr;
  d = error-errorx;
  errorx=error;
  Out = p+i+d;
  pid=Out;
  if(pid > 5) pid=-5;
  else if(pid < 5) pid=5;
}
void uskanan_blk(){
  pinMode(pingkanan_blk,OUTPUT);
  digitalWrite(pingkanan_blk,LOW);
  delayMicroseconds(2);
  digitalWrite(pingkanan_blk,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingkanan_blk,LOW);
  pinMode(pingkanan_blk,INPUT);
  durationkanan_blk = pulseIn(pingkanan_blk,HIGH);
  usknn_blk = microsecondsToCentimeters(durationkanan_blk);
}
void scand(){
  uskiri_blk();
  uskiri_tgh();
  uskiri_dpn();
  usdepan_kiri();
  usdepan_tengah();
  usdepan_kanan();
  uskanan_dpn();
  uskanan_tgh();
  uskanan_blk();
}
void standBy(){
  for(int i=0; i<jml_servo; i++){
    servos[i].attach(servoPins[i]);
    servos[i].write(ss[i]);
  }
}
void setservo(int srv1, int srv2, int srv3, int srv4, int srv5, int srv6, int srv7, int srv8, int srv9, int srv10, int srv11, int srv12, int srv13, int srv14, int srv15, int srv16, int srv17, int srv18){
  int servo[]={srv1,srv2,srv3,srv4,srv5,srv6,srv7,srv8,srv9,srv10,srv11,srv12,srv13,srv14,srv15,srv16,srv17,srv18};
  for(int i=0; i<18; i++){
    servos[i].write(servo[i]);
  }
}
// Sesi 2
// maju untuk sesi 2
void majubiasasesi2(){
  //setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,   d3,      d2,        d1,      e1,       e2,       e3,       f3,       f2,    f1);
    setservo(ss[0]-15,ss[1]+20,ss[2]-10,ss[3]-10,ss[4]+10,ss[5],ss[6],ss[7]-5,ss[8]+10,ss[9]+10,ss[10]-20,ss[11]+15,ss[12]-15,ss[13]+20,ss[14]-10,ss[15]-10,ss[16]+5,ss[17]);
    delay(200);
    setservo(ss[0],ss[1]-5,ss[2]+10,ss[3]+10,ss[4]-25,ss[5]+15,ss[6]-15,ss[7]+20,ss[8]-10,ss[9]-10,ss[10]+5,ss[11],ss[12],ss[13]-5,ss[14]+10,ss[15]+10,ss[16]-20,ss[17]+15);
    delay(200);
}
// maju untuk sesi 2
void majusesi2(){
  uskiri_tgh();
  // Data minus
  if(uskri_tgh>10){
  //setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,   d3,      d2,        d1,      e1,       e2,       e3,       f3,       f2,    f1);
    setservo(ss[0]-15,ss[1]+25,ss[2]-10,((ss[3]-10)+(pid)),ss[4]+10,ss[5],ss[6],ss[7]-5,ss[8]+10,((ss[9]+10)-(pid)),ss[10]-20,ss[11]+15,ss[12]-15,ss[13]+25,ss[14]-10,((ss[15]-10)+(pid)),ss[16]+5,ss[17]);
    delay(250);
    setservo(ss[0],ss[1]-5,ss[2]+10,((ss[3]+10)-(pid)),ss[4]-30,ss[5]+15,ss[6]-15,ss[7]+25,ss[8]-10,((ss[9]-10)+(pid)),ss[10]+5,ss[11],ss[12],ss[13]-5,ss[14]+10,((ss[15]+10)-(pid)),ss[16]-25,ss[17]+15);
    delay(250);
  }
  // Data plus
  else if(uskri_tgh<10){
    //setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,   d3,      d2,        d1,      e1,       e2,       e3,       f3,       f2,    f1);
    setservo(ss[0]-15,ss[1]+25,ss[2]-15-pid,ss[3]-10,ss[4]+10,ss[5],ss[6],ss[7]-5,ss[8]+15+pid,ss[9]+10,ss[10]-25,ss[11]+15,ss[12]-15,ss[13]+25,ss[14]-15-pid,ss[15]-10,ss[16]+5,ss[17]);
    delay(250);
    setservo(ss[0],ss[1]-5,ss[2]+15+pid,ss[3]+10,ss[4]-30,ss[5]+15,ss[6]-15,ss[7]+25,ss[8]-15-pid,ss[9]-10,ss[10]+5,ss[11],ss[12],ss[13]-5,ss[14]+15+pid,ss[15]+10,ss[16]-25,ss[17]+15);
    delay(250);
  }
  else{
    //setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,   d3,      d2,        d1,      e1,       e2,       e3,       f3,       f2,    f1);
    setservo(ss[0]-15,ss[1]+25,ss[2]-15,ss[3]-10,ss[4]+10,ss[5],ss[6],ss[7]-5,ss[8]+10,ss[9]+10,ss[10]-20,ss[11]+15,ss[12]-15,ss[13]+25,ss[14]-15,ss[15]-15,ss[16]+5,ss[17]);
    delay(250);
    setservo(ss[0],ss[1]-5,ss[2]+10,ss[3]+10,ss[4]-30,ss[5]+15,ss[6]-15,ss[7]+25,ss[8]-10,ss[9]-10,ss[10]+5,ss[11],ss[12],ss[13]-5,ss[14]+10,ss[15]+10,ss[16]-25,ss[17]+15);
    delay(250);
  }
}
// SESI 1
void majubiasa(){
  //setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,   d3,      d2,        d1,      e1,       e2,       e3,       f3,       f2,    f1);
    setservo(ss[0]-20,ss[1]+10,ss[2]-15,ss[3]-10,ss[4],ss[5],ss[6],ss[7],ss[8]+10,ss[9]+10,ss[10]-10,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]-15,ss[15]-10,ss[16],ss[17]);
    delay(250);
    setservo(ss[0],ss[1],ss[2]+10,ss[3]+10,ss[4]-10,ss[5]+10,ss[6]-20,ss[7]+10,ss[8]-10,ss[9]-10,ss[10],ss[11],ss[12],ss[13],ss[14]+10,ss[15]+10,ss[16]-10,ss[17]+10);
    delay(250);
}
void maju(){
  uskanan_tgh();
  // Data minus
  if(usknn_tgh>10){
    setservo(ss[0]-20,ss[1]+15,((ss[2]-10)+(pid)),ss[3]-10,ss[4],ss[5],ss[6],ss[7],((ss[8]+10)-(pid)),ss[9]+10,ss[10]-15,ss[11]+10,ss[12]-10,ss[13]+10,((ss[14]-10)+(pid)),ss[15]-10,ss[16],ss[17]);
    delay(deley);
    setservo(ss[0],ss[1],((ss[2]+10)-(pid)),ss[3]+10,ss[4]-15,ss[5]+10,ss[6]-20,ss[7]+15,((ss[8]-10)+(pid)),ss[9]-10,ss[10],ss[11],ss[12],ss[13],((ss[14]+10)-(pid)),ss[15]+10,ss[16]-10,ss[17]+10);
    delay(deley);
  }
  else if(usknn_tgh<10){setservo(ss[0]-20,ss[1]+15,ss[2]-10,ss[3]-15-pid,ss[4],ss[5],ss[6],ss[7],ss[8]+10,ss[9]+10+pid,ss[10]-15,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]-10,ss[15]-10-pid,ss[16],ss[17]);
    delay(deley);
    setservo(ss[0],ss[1],ss[2]+10,ss[3]+15+pid,ss[4]-15,ss[5]+10,ss[6]-20,ss[7]+15,ss[8]-10,ss[9]-10-pid,ss[10],ss[11],ss[12],ss[13],ss[14]+10,ss[15]+10+10,ss[16]-10,ss[17]+10);
    delay(deley);    
  }
  else{
    setservo(ss[0]-20,ss[1]+15,ss[2]-15,ss[3]-10,ss[4],ss[5],ss[6],ss[7],ss[8]+10,ss[9]+10,ss[10]-15,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]-15,ss[15]-10,ss[16],ss[17]);
    delay(deley);
    setservo(ss[0],ss[1],ss[2]+10,ss[3]+10,ss[4]-15,ss[5]+10,ss[6]-20,ss[7]+15,ss[8]-10,ss[9]-10,ss[10],ss[11],ss[12],ss[13],ss[14]+10,ss[15]+10,ss[16]-10,ss[17]+10);
    delay(deley);
  }
}

void maju2(){
  uskiri_tgh();
  // Data minus
  if(uskri_tgh>10){
    //setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,   d3,      d2,        d1,      e1,       e2,       e3,       f3,       f2,    f1);
    setservo(ss[0]-20,ss[1]+10,ss[2]-10,((ss[3]-10)+(pid)),ss[4],ss[5],ss[6],ss[7],ss[8]+10,((ss[9]+10)-(pid)),ss[10]-10,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]-10,((ss[15]-10)+(pid)),ss[16],ss[17]);
    delay(deley);
    setservo(ss[0],ss[1],ss[2]+10,((ss[3]+10)-(pid)),ss[4]-15,ss[5]+10,ss[6]-20,ss[7]+10,ss[8]-10,((ss[9]-10)+(pid)),ss[10],ss[11],ss[12],ss[13],ss[14]+10,((ss[15]+10)-(pid)),ss[16]-10,ss[17]+10);
    delay(deley);
  }
  else if(uskri_tgh<10){
    //setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,   d3,      d2,        d1,      e1,       e2,       e3,       f3,       f2,    f1);
    setservo(ss[0]-20,ss[1]+10,ss[2]-15-pid,ss[3]-10,ss[4],ss[5],ss[6],ss[7],ss[8]+15+pid,ss[9]+10,ss[10]-10,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]-15-pid,ss[15]-10,ss[16],ss[17]);
    delay(deley);
    setservo(ss[0],ss[1],ss[2]+15+pid,ss[3]+10,ss[4]-15,ss[5]+10,ss[6]-20,ss[7]+10,ss[8]-15-pid,ss[9]-10,ss[10],ss[11],ss[12],ss[13],ss[14]+15+pid,ss[15]+10,ss[16]-10,ss[17]+10);
    delay(deley);    
  }
  else{
  //setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,   d3,      d2,        d1,      e1,       e2,       e3,       f3,       f2,    f1);
    setservo(ss[0]-20,ss[1]+10,ss[2]-15,ss[3]-10,ss[4],ss[5],ss[6],ss[7],ss[8]+10,ss[9]+10,ss[10]-10,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]-15,ss[15]-10,ss[16],ss[17]);
    delay(deley);
    setservo(ss[0],ss[1],ss[2]+10,ss[3]+10,ss[4]-15,ss[5]+10,ss[6]-20,ss[7]+10,ss[8]-10,ss[9]-10,ss[10],ss[11],ss[12],ss[13],ss[14]+10,ss[15]+10,ss[16]-10,ss[17]+10);
    delay(deley);
  }
}
int logicbelok=0;
void belokkanan(){
  if(logicbelok==1){
    //setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,   d3,      d2,        d1,      e1,       e2,       e3,       f3,       f2,    f1);
    setservo(ss[0]-15,ss[1]+20,ss[2]-15,ss[3]-3,ss[4]+10,ss[5],ss[6],ss[7]-5,ss[8]+15,ss[9]+3,ss[10]-20,ss[11]+15,ss[12]-15,ss[13]+20,ss[14]-15,ss[15]-3,ss[16]+5,ss[17]);
    delay(280);
    setservo(ss[0],ss[1]-5,ss[2]+15,ss[3]+3,ss[4]-25,ss[5]+15,ss[6]-15,ss[7]+20,ss[8]-15,ss[9]-3,ss[10]+5,ss[11],ss[12],ss[13]-5,ss[14]+15,ss[15]+3,ss[16]-20,ss[17]+15);
    delay(280);
  }
  else{
    setservo(ss[0]-20,ss[1]+10,ss[2]-15,ss[3]-3,ss[4],ss[5],ss[6],ss[7],ss[8]+15,ss[9]+3,ss[10]-10,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]-15,ss[15]-3,ss[16],ss[17]);
    delay(280);
    setservo(ss[0],ss[1],ss[2]+15,ss[3]+3,ss[4]-15,ss[5]+10,ss[6]-20,ss[7]+10,ss[8]-15,ss[9]-3,ss[10],ss[11],ss[12],ss[13],ss[14]+15,ss[15]+3,ss[16]-10,ss[17]+10);
    delay(280);
  }
}
void belokkiri(){
//setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,     d3,     d2,       d1,       e1,       e2,       e3,       f3,      f2,    f1);
  setservo(ss[0]-20,ss[1]+10,ss[2]-3,ss[3]-15,ss[4],ss[5],ss[6],ss[7],ss[8]+3,ss[9]+15,ss[10]-10,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]-3,ss[15]-15,ss[16],ss[17]);
  delay(280);
  setservo(ss[0],ss[1],ss[2]+3,ss[3]+15,ss[4]-10,ss[5]+10,ss[6]-20,ss[7]+10,ss[8]-3,ss[9]-15,ss[10],ss[11],ss[12],ss[13],ss[14]+3,ss[15]+15,ss[16]-10,ss[17]+10);
  delay(280);
}
void putarkanan(){
//setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,     d3,     d2,       d1,       e1,       e2,       e3,       f3,      f2,    f1);
  setservo(ss[0]-20,ss[1]+10,ss[2]-15,ss[3],ss[4],ss[5],ss[6],ss[7],ss[8],ss[9]-15,ss[10]-10,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]-15,ss[15],ss[16],ss[17]);
  delay(280);
  setservo(ss[0],ss[1],ss[2],ss[3]-15,ss[4]-10,ss[5]+10,ss[6]-20,ss[7]+10,ss[8]-15,ss[9],ss[10],ss[11],ss[12],ss[13],ss[14],ss[15]-15,ss[16]-10,ss[17]+10);
  delay(280);
}
void putarkiri(){
//setservo(a1,      a2,       a3,      b3,     b2,   b1,   c1,   c2,   c3,     d3,     d2,       d1,       e1,       e2,       e3,       f3,      f2,    f1);
  setservo(ss[0]-20,ss[1]+10,ss[2]+15,ss[3],ss[4],ss[5],ss[6],ss[7],ss[8],ss[9]+15,ss[10]-10,ss[11]+10,ss[12]-10,ss[13]+10,ss[14]+15,ss[15],ss[16],ss[17]);
  delay(280);
  setservo(ss[0],ss[1],ss[2],ss[3]+15,ss[4]-10,ss[5]+10,ss[6]-20,ss[7]+10,ss[8]+15,ss[9],ss[10],ss[11],ss[12],ss[13],ss[14],ss[15]+15,ss[16]-10,ss[17]+10);
  delay(280);
}
void scand_kanan(){
  scand();
  //if(usdpn_kri>15 && usdpn_tgh>15 && usdpn_knn>15 && usknn_tgh<=10){
    //maju();
  //}
  if(usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10 && usknn_dpn<=10){
    maju();
  }
  if(usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10 && usknn_dpn<=15 && usknn_tgh<=10){
    maju();
  }
  if(usknn_dpn>10 && usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10){
    belokkanan();
  }
  if(usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10 && usknn_blk>15){
    belokkanan();
  }
  if(usdpn_tgh<15 && usdpn_knn<15 && usknn_dpn<=15 && usknn_tgh<=10){
    putarkiri(); 
  }
  if(usdpn_knn<=15 && usknn_dpn<=11 && usknn_tgh<=15 && usknn_blk<=10){
    putarkiri();
  }
  if(usdpn_knn<=15 && usknn_dpn<=15 && usknn_tgh<=20){
    putarkiri();
  }
  if(usdpn_tgh<=15 && usdpn_knn<=15 && usknn_tgh<20 && usknn_blk<=15){
    putarkiri();
  }
  if(usdpn_tgh<=15 && usdpn_kri<=15){
    belokkanan();
  }
  if(usknn_dpn<15 && usknn_tgh>15 && usknn_blk<15){
    putarkiri();
  }
  if((usdpn_tgh<=15 && usdpn_knn<=15) || (usdpn_tgh>15 && usdpn_knn<=10)){
    putarkiri();
  }
}
void scand_kiri(){
  scand();
  if(usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10 && uskri_tgh<=15){
    majusesi2();
  }
  if(usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10 && uskri_dpn<=15){
    majusesi2();
  }
  if(usdpn_kri>15 && usdpn_tgh>15 && usdpn_knn>15 && uskri_dpn<=15 && uskri_tgh<=10){
    majusesi2();
  }
  if(uskri_dpn>10 && uskri_tgh>15 && usdpn_kri>10 && usdpn_tgh>15){
    belokkiri();
  }
  if(usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10 && uskri_blk>15){
    belokkiri();
  }
  if(usdpn_tgh<15 && usdpn_knn<15 && uskri_dpn<=15 && uskri_tgh<=10){
    putarkanan(); 
  }
  if(usdpn_kri<=15 && uskri_dpn<=11 && uskri_tgh<=15 && uskri_blk<=10){
    putarkanan();
  }
  if(usdpn_kri<=15 && uskri_dpn<=15 && uskri_tgh<=20){
    putarkanan();
  }
  if(usdpn_kri<=15 && usdpn_tgh<=15){
    putarkanan();
  }
  if(usdpn_tgh<=15 && usdpn_kri<=15 && uskri_tgh<20 && uskri_blk<=15){
    putarkanan();
  }
  if((usdpn_tgh<=15 && usdpn_kri<=15) || (usdpn_tgh>15 && usdpn_kri<=10)){
    putarkanan();
  }
  if(uskri_dpn>15 && uskri_tgh>10){
    belokkiri();
  }
}
void scand_kiri2(){
  scand();
  if(usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10 && uskri_tgh<=15){
    maju2();
  }
  if(usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10 && uskri_dpn<=15){
    maju2();
  }
  if(usdpn_kri>15 && usdpn_tgh>15 && usdpn_knn>15 && uskri_dpn<=15 && uskri_tgh<=10){
    maju2();
  }
  if(uskri_dpn>10 && uskri_tgh>15 && usdpn_kri>10 && usdpn_tgh>15){
    belokkiri();
  }
  if(usdpn_kri>10 && usdpn_tgh>10 && usdpn_knn>10 && uskri_blk>15){
    belokkiri();
  }
  if(usdpn_tgh<15 && usdpn_knn<15 && uskri_dpn<=15 && uskri_tgh<=10){
    putarkanan(); 
  }
  if(usdpn_kri<=15 && uskri_dpn<=11 && uskri_tgh<=15 && uskri_blk<=10){
    putarkanan();
  }
  if(usdpn_kri<=15 && uskri_dpn<=15 && uskri_tgh<=20){
    putarkanan();
  }
  if(usdpn_kri<=15 && usdpn_tgh<=15){
    putarkanan();
  }
  if(usdpn_tgh<=15 && usdpn_kri<=15 && uskri_tgh<20 && uskri_blk<=15){
    putarkanan();
  }
  if((usdpn_tgh<=15 && usdpn_kri<=15) || (usdpn_tgh>15 && usdpn_kri<=10)){
    putarkanan();
  }
}
void masukruang(int a,int b,int c,int d,int e){
    for(int i=0; i<a; i++){
      majubiasa();
    }
    for(int i=0; i<b; i++){
      putarkanan();
    }
    digitalWrite(relay,LOW);
    delay(300);
    digitalWrite(relay,HIGH);
    for(int i=0; i<c; i++){
      putarkiri();
    }
    digitalWrite(relay,LOW);
    delay(300);
    digitalWrite(relay,HIGH);
    for(int i=0; i<d; i++){
      putarkiri();
    }
    for(int i=0; i<e; i++){
      majubiasa();
    }
}
void masukruang2(int a,int b,int c,int d,int e){
  digitalWrite(led,HIGH);
  delay(1000);
  digitalWrite(led,LOW);
  for(int i=0; i<a; i++){
    majubiasa();
  }
  for(int i=0; i<b; i++){
    putarkanan();
  }
  for(int i=0; i<c; i++){
    majubiasa();
  }
  digitalWrite(relay,LOW);
  delay(2000);
  digitalWrite(relay,HIGH);
  for(int i=0; i<d; i++){
    putarkiri();
  }
  for(int i=0; i<e; i++){
    majubiasa();
  }
}

void kompas(){
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  //Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  //Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  //Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
 
  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  x = event.magnetic.x;
  y = event.magnetic.y;
  z = event.magnetic.z;
  
  heading = atan2(event.magnetic.y, event.magnetic.x);
  heading = heading * 57.29577951;
  heading = heading + 180;
  /*
  Serial.print("Heading : ");
  Serial.print(heading);
  if(heading>1 && heading<50) {
    Serial.print("Arah : ");
    Serial.println("Timur");
  }
  else if(heading>=50 && heading<130){
    Serial.print("Arah : ");
    Serial.println("Selatan");
  }
  else if(heading>=130 && heading<200){
    Serial.print("Arah : ");
    Serial.println("Barat");
  }
  else if(heading>=200 && heading<360){
    Serial.print("Arah : ");
    Serial.println("Utara");
  }*/
 // delay(500);
  
}
int compas=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(relay,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);
  digitalWrite(relay,HIGH);
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  standBy();
}
int kunci=0;
void loop() {
  // put your main code here, to run repeatedly:
  // Sesi 1 
  //majubiasasesi2();
  line=analogRead(garis);
  apikri1=digitalRead(flamekri1);
  apikri2=digitalRead(flamekri2);
  apiknn1=digitalRead(flameknn1);
  apiknn2=digitalRead(flameknn2);
  apitgh1=digitalRead(flametgh1);
  apitgh2=digitalRead(flametgh2);
  apiakeh1=digitalRead(flameakeh1);
  apiakeh2=digitalRead(flameakeh2);
  apiakeh3=digitalRead(flameakeh3);
  apiakeh4=digitalRead(flameakeh4);
  apiakeh5=digitalRead(flameakeh5);
  bacagaris=line;
  kompas();scand();
  /*Serial.print("Garis : ");
  Serial.print(bacagaris);
  Serial.print(" Heading : ");
  Serial.println(heading);
  delay(500);
  if((heading>=130 && heading<=200) && (x>=4.00 && x<=9.00) && (y>=-6.00 && y<=0.00) && (z>=51.00 && z<=58.00)){
    digitalWrite(led,HIGH);
  }
  else digitalWrite(led,LOW);
  /*
   * Sesi 1 FIKSSS!!!
   */
  if(Scand==1 && compas==1){
      if(heading>80 && heading<100){
          for(int i=0; i<4; i++){majubiasa();}
          masukruang(8,12,3,16,2);
          Scand=1;compas=0;
      }
      else putarkiri();
   }
  else if(compas==1){
    if((heading>100 && heading<=180) && usknn_dpn<30){
      standBy();
      delay(500);
      compas=1;Scand=1;logicbelok=1;
    } else scand_kanan();
  }
  // Jalan pulang ke home
  else if(compas==0 && Scand==1){
    if((heading>80 && heading<=102) && usknn_dpn>=50){
      for(int i=0; i<12; i++){majubiasa();}
      for(int i=0; i<8; i++){putarkiri();}
      for(int i=0; i<2; i++){majubiasa();}
      standBy();
      delay(20000);
    } else scand_kanan();
  }
  else{
    if(bacagaris>500 ||(Scand==0 && compas==0)){
      scand_kanan();
      digitalWrite(relay,HIGH);
      digitalWrite(led,LOW);
    }
    if(bacagaris<500 && (heading>100 && heading<=200) && usknn_dpn>30){
      masukruang(8,5,3,14,7);
      compas=1;
      logicbelok=1;
    }
    if(bacagaris<=500 && (heading>30 && heading<=130)){
      logicbelok=1;
      masukruang(7,4,5,9,8);
    }
    if(bacagaris<=500 && (heading>350 || heading<=30)){
      masukruang(7,9,4,15,7);
      logicbelok=0;
    }
  }
  /*
   * Sesi 2
   * PR tinggal jalan keluar dari room 4 ke room 2 kembali ke home
   *
   //if(heading>350 || heading<50)=Timur
   //if(heading>=50 && heading<130)=Selatan
   //if(heading>=130 && heading<200)=Barat;
   //if(heading>=200 && heading<360)=Utara;
    if(kunci==1){
        if(heading>30 && heading<90){
          for(int i=0; i<5; i++){majubiasa();}
          for(int i=0; i<6; i++){belokkiri();}
          for(int i=0; i<7; i++){majubiasa();}
          compas=1;kunci=0;Scand=0;
        }
        else scand_kiri();
    }
    else if(Scand==1 && compas==1){
      // masuk ruang 4
      if(heading>85 && heading<100){
        for(int i=0; i<4; i++){majubiasa();}
        masukruang(8,10,3,17,2);
        Scand=0;compas=1;
      }
      else{
        putarkiri();
      }
    }
    else if(Scand==1){
      // keluar dari ruang 1 menuju ruang 3
      if(bacagaris<=400 && (heading>350 || heading<=50)){
         standBy();delay(500);
         for(int i=0; i<6; i++){majubiasa();}
         for(int i=0; i<10; i++){putarkanan();}
         Scand=0;compas=0;logic_program=1;
      }
      // otw masuk ruang 4
      if(usknn_tgh<20 && (heading>120 && heading<250)){
        standBy();delay(500);
        for(int i=0; i<4; i++){majubiasa();}
        Scand=1;compas=1;
      }
      else scand_kanan();
    }
    else if(compas==1){
      // masuk ruang 2
      if(bacagaris<=400 && (heading>350 || heading<=50)){
          masukruang(7,6,3,14,3);
          standBy();
          delay(5000);
      }
      // keluar daru ruang 4
      if(bacagaris<=400 && (heading>150 && heading<=350)){
        //masukruang(7,8,3,15,4);
        for(int i=0; i<=5; i++){majubiasa();}
        for(int i=0; i<8; i++){putarkanan();}
        kunci=1;
        //compas=0;Scand=0;
      }
      // maju lurus di perempatan untuk menuju ruang 4
      else if(usknn_dpn>30 && (heading>120 && heading<250)){
        for(int i=0; i<14; i++){majubiasa();}
        Scand=1;compas=0;
      }
      else scand_kanan();
    }
    else{
      if(Scand==0 && compas==0){
        // Barat masuk ruang 1
        if(bacagaris<=400 && ((heading>120 && heading<=250) && uskri_dpn<40)){
          standBy();delay(500);
          masukruang(7,6,3,14,3);
          Scand=1;compas=0;
        }
        // Selatan masuk ruang 3
        else if(bacagaris<=400 && (heading>30 && heading<=120)){
          standBy();delay(500);
          masukruang(7,5,3,11,3); 
          compas=1;Scand=0;
          logicbelok=1;
        }
        else{
          if(logic_program==0){
            scand_kiri();
          }
          else if(logic_program==1){
            scand_kiri2();
          }
        }
      }// Scand 0 && compas 0
    }  
  
  
  /*
    Sudut room 2 72
    Sudut room 3 104
    Sudut room 1 165 
   *//*
   // SESI 3
   //if(heading>350 || heading<50)=Timur
   //if(heading>=50 && heading<130)=Selatan
   //if(heading>=130 && heading<200)=Barat;
   //if(heading>=200 && heading<360)=Utara; 
    if(heading<50 && uskri_tgh>30){
      for(int i=0; i<3; i++){putarkanan();}
       for(int i=0; i<16; i++){majubiasa();}
       compas=1;
    }
    else if(compas==1){
      if((heading>70 && heading<110) && ((apitgh1==LOW || apitgh2==LOW) || (apitgh1==LOW && apitgh2==LOW))){
          digitalWrite(led,HIGH);delay(500);digitalWrite(led,LOW);
          //for(int i=0; i<2; i++){putarkanan();}
          for(int i=0; i<7; i++){majubiasa();}
          for(int i=0; i<=3; i++){
              digitalWrite(led2,HIGH);delay(50);
              digitalWrite(led2,LOW);delay(50);
            }
            digitalWrite(led2,HIGH);
            standBy();
            digitalWrite(relay,LOW);
            delay(1000);
            digitalWrite(relay,HIGH);
            digitalWrite(led2,LOW);
            for(int i=0; i<12; i++){putarkiri();}
            for(int i=0; i<4; i++){majubiasa();}
            logicbelok=1;
       }
       else if((heading>350 || heading<70) && ((apitgh1==LOW || apitgh2==LOW) || (apitgh1==LOW && apitgh2==LOW))){
          digitalWrite(led,HIGH);delay(500);digitalWrite(led,LOW);
          //for(int i=0; i<3; i++){putarkanan();}
          for(int i=0; i<7; i++){majubiasa();}
          //for(int i=0; i<3; i++){putarkiri();}
          standBy();
          for(int i=0; i<=3; i++){
            digitalWrite(led2,HIGH);delay(50);
            digitalWrite(led2,LOW);delay(50);
          }
          digitalWrite(led2,HIGH);
          digitalWrite(relay,LOW);
          delay(1000);
          digitalWrite(relay,HIGH);
          digitalWrite(led2,LOW);
          for(int i=0; i<11; i++){putarkiri();}
          for(int i=0; i<10; i++){majubiasa();}
          logicbelok=0;
       }
       else if((heading>130 && heading<175) && bacagaris<400){
          for(int i=0; i<6; i++){majubiasa();}
          if((apitgh1==LOW || apitgh2==LOW) || (apitgh1==LOW && apitgh2==LOW)){
            for(int i=0; i<=3; i++){
               digitalWrite(led2,HIGH);delay(50);
               digitalWrite(led2,LOW);delay(50);
             }
            digitalWrite(led2,HIGH);
            standBy();
            digitalWrite(relay,LOW);
            delay(2000);
            digitalWrite(relay,HIGH);
            digitalWrite(led2,LOW);
            for(int i=0; i<7; i++){putarkiri();}
            for(int i=0; i<3; i++){majubiasa();}
          }
        }
       else {
        digitalWrite(relay,HIGH);
        digitalWrite(led,LOW);
        scand_kanan(); 
       }
    }
    else{
      scand_kiri();
    }*/
}
