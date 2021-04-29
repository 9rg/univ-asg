#include "Arduino.h"
#include"avr/io.h"

//////////////////////接続ピンの定義/////////////////////////
#define L1_pin A0 //距離センサ
#define L2_pin A1
#define L3_pin A2
#define P1_pin A3 //フォトセンサ
#define P2_pin A4
#define P3_pin A5
#define Buzzer_DA2 7 //ブザー
#define M2_Vref 10 //PWM モータ１
#define M2_IN1   4
#define M2_IN2   5
#define M1_Vref  3  //PWM モータ２
#define M1_IN1   8
#define M1_IN2   9
////////////////////////////////////////////////////////////


///////////////////センサ取得値の初期化/////////////////////
int L1_val = 0; 
int L2_val = 0;
int L3_val = 0;
int P1_val = 0;
int P2_val = 0;
int P3_val = 0;
int x;
////////////////////////////////////////////////////////////


//////////////////////////間隔の設定/////////////////////////
int WAIT_SENSOR = 5;
int WAIT_SENSOR2 = 100;
int WAIT_BUZZER1 = 50;
int WAIT_BUZZER2 = 500;
int WAIT_SHUNJItime = 500; //瞬時停止 
int WAIT_Atime = 1600; //瞬時停止の走行
int WAIT_TURNA = 800; //方向転換、目標に対して角度つける秒数
int WAIT_TURNB = 200; //方向転換でバックする秒数
int WAIT_TURNC = 200; //隣まで進む秒数
int WAIT_TURND = 1000; //最後の方向修正
//////////////////////////////////////////////////////////////


//////////////////////関数のプロトタイプ宣言//////////////////
int sensorAvg( int val,float pin);
void getSensor();
void immidiStop();
void correctDir();
void findIt();
void turningA();
void turningB();
void turningC();
//////////////////////////////////////////////////////////////


////////////////////////////各初期設定////////////////////////
void setup() {
  Serial.begin(9600); //モニタのセットアップ
  pinMode(L1_pin,INPUT); //センサの初期設定
  pinMode(L2_pin,INPUT);
  pinMode(L3_pin,INPUT);
  pinMode(P1_pin,INPUT);
  pinMode(P2_pin,INPUT);
  pinMode(P3_pin,INPUT);
  pinMode(Buzzer_DA2,OUTPUT); //ブザーの初期設定
  pinMode(M1_Vref,OUTPUT); //モータの初期設定
  pinMode(M1_IN1,OUTPUT);
  pinMode(M1_IN2,OUTPUT);
  pinMode(M2_IN1,OUTPUT);
  pinMode(M2_IN2,OUTPUT);
  pinMode(M2_Vref,OUTPUT);
}////////////////////////////////////////////////////////////


////////////////////////////メインコード/////////////////////
void loop() {
  ADCSRA|=0b00000100;
  getSensor();  

  //メイン
  if(P2_val>=200 || P1_val>=200 || P3_val>=200){ //前方黒：走行不可能時
   if(L2_val>400 || L1_val>400 || L3_val>400){ //前方に目標物があるとき
      findIt(); //目標発見処理
      turningC();
      //turningB();
    }
    else{ //前方に目標物がないとき(ステージ端に来た時)
      correctDir(); //方向修正処理
    }
  }else{  //前方白：走行可能時
    if(L2_val>400 || L3_val>400 || L1_val>400){
      //減速
      digitalWrite(M1_IN1,HIGH);
      digitalWrite(M1_IN2,LOW);
      digitalWrite(M2_IN1,HIGH);
      digitalWrite(M2_IN2,LOW);
      analogWrite(M1_Vref,60);
      analogWrite(M2_Vref,60);
      delay(100);
    }else{//通常
      digitalWrite(M1_IN1,HIGH);
      digitalWrite(M1_IN2,LOW);
      digitalWrite(M2_IN1,HIGH);
      digitalWrite(M2_IN2,LOW);
      analogWrite(M1_Vref,100);
      analogWrite(M2_Vref,100);
      delay(100);
    }
    }
    /* 第２案
      if(L2_val<100){ //前方に目標物がないとき
        correctDir();
      }else{  //目標物があるとき
      findIt();  //
      turningA();
      }*/
  }/////////////////////////////////////////////////////////////



///////////////////メインコード内使用関数///////////////////////////////
int sensorAvg(int val,float pin){ ////////センサ平均値取得関数
  int sum=0;
  for(int i=0;i<10;i++){
  val = analogRead(pin);
  sum = sum + val;
  delay(WAIT_SENSOR);
  }
  return sum/10;
}/////////////////////////////////////////////////////////////

////////////////////////////////////////センサ値取得関数
void getSensor(){
  L1_val = sensorAvg(L1_val,L1_pin);
  L2_val = sensorAvg(L2_val,L2_pin);
  L3_val = sensorAvg(L3_val,L3_pin);

  P1_val = analogRead(P1_pin);
  P2_val = analogRead(P2_pin);
  P3_val = analogRead(P3_pin);

  //シリアルモニタに出力
 /*Serial.print("\n""P_Sensor P=""\t");
  Serial.print(P1_val);
  Serial.print(",\t");
  Serial.print(P2_val);
  Serial.print(",\t");
  Serial.print(P3_val);
  Serial.print("\n""D_Sensor L=""\t");
  Serial.print(L1_val);
  Serial.print(",\t");
  Serial.print(L2_val);
  Serial.print(",\t");
  Serial.println(L3_val);*/
}/////////////////////////////////////////////////////

void immidiStop(){ /////////////////////瞬時停止処理関数
  digitalWrite(M1_IN1,LOW); // IN1設定
  digitalWrite(M1_IN2,LOW); // IN2設定
  digitalWrite(M2_IN1,LOW); // IN1設定
  digitalWrite(M2_IN2,LOW); // IN2設定
  analogWrite( M1_Vref, 0 ); //Vref端子設定（右）
  analogWrite( M2_Vref, 0 ); //Vref端子設定（左）
  delay(WAIT_SHUNJItime);
}/////////////////////////////////////////////////////////

void correctDir(){ /////////////////////方向修正処理
immidiStop();
  digitalWrite(M1_IN2,HIGH);
    digitalWrite(M2_IN2,HIGH);
    analogWrite( M1_Vref, 100 );
    analogWrite( M2_Vref, 100 );
    delay(2000);

  digitalWrite(M1_IN1,LOW);
  digitalWrite(M1_IN2,HIGH);
  digitalWrite(M2_IN1,HIGH);
  digitalWrite(M2_IN2,LOW);
  analogWrite( M1_Vref, 110 );
  analogWrite( M2_Vref, 110);
  delay(2500);
  immidiStop();
}////////////////////////////////////////////////////

void findIt(){ //////////////////////////発見処理関数
  immidiStop();
  for(int i=0;i<2;i++){
    for(int j=0;j<5;j++){
      digitalWrite(7,HIGH);
      delay(WAIT_BUZZER1);
      digitalWrite(7,LOW);
      delay(WAIT_BUZZER1);
    }
    digitalWrite(7,LOW);
    delay(WAIT_BUZZER2);
  }
  digitalWrite(7,HIGH);
  delay(WAIT_BUZZER1);
  digitalWrite(7,LOW);
}/////////////////////////////////////////////////



void turningB(){///////////////////////////方向転換処理関数B
  immidiStop();
  //バック
  while(1){
    getSensor();
    if(L2_val<450||L3_val<450){
      break;
    }else{
    digitalWrite(M1_IN2,HIGH);
    digitalWrite(M2_IN2,HIGH);
    analogWrite( M1_Vref, 100 );
    analogWrite( M2_Vref, 100 );
    delay(WAIT_TURNB);
    }
  }
  
  //角度つける
  immidiStop();
  digitalWrite(M2_IN1,HIGH);
  digitalWrite(M2_IN2,LOW);
  analogWrite( M2_Vref, 110 );
  digitalWrite(M1_IN1,LOW);//追加
  digitalWrite(M1_IN2,HIGH);
  analogWrite( M1_Vref,110);
  delay(WAIT_TURNA);
  /*digitalWrite(M1_IN1,LOW);
  digitalWrite(M1_IN2,HIGH);
  analogWrite( M1_Vref,110);*/

  
  
/* //隣まで前進
  digitalWrite(M1_IN1,HIGH);
  analogWrite( M1_Vref, 100 );
  delay(WAIT_TURNC);*/
  
  //円弧運動
  while(1){
    getSensor();
    //右フォトセンサが黒→break
    if(P3_val>=200){
     break;
    }else{
    //そうでない場合→円弧運動
     digitalWrite(M1_IN1,HIGH);
     digitalWrite(M1_IN2,LOW);
     analogWrite( M1_Vref, 100 );
     digitalWrite(M2_IN1,HIGH);
     digitalWrite(M2_IN2,LOW);
     analogWrite( M2_Vref, 25 );
     delay(50);
    }
  }
  //方向修正
  immidiStop();
  while(1){
    getSensor();
    if(P1_val<80){
      break;
    }else{
  digitalWrite(M1_IN1,LOW);
  digitalWrite(M1_IN2,LOW);
  digitalWrite(M2_IN1,HIGH);
  digitalWrite(M2_IN2,LOW);
  analogWrite( M1_Vref, 0 );
  analogWrite( M2_Vref, 110);
  delay(WAIT_TURND);
  }
  }
  immidiStop();
}///////////////////////////////////////////////////////



void turningC(){
  immidiStop();
  digitalWrite(M1_IN2,HIGH);
  digitalWrite(M2_IN2,HIGH);
  analogWrite( M1_Vref, 100 );
  analogWrite( M2_Vref, 100 );
  delay(2000);

  digitalWrite(M1_IN1,LOW);
  digitalWrite(M1_IN2,LOW);
  digitalWrite(M2_IN1,HIGH);
  digitalWrite(M2_IN2,LOW);
  analogWrite( M1_Vref, 0 );
  analogWrite( M2_Vref, 110);
  delay(WAIT_TURND);
}
