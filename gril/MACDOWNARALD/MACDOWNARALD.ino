
#include <Ultrasonick.h>
Ultrasonick ultrasonick(12, 13);


//gril 
#define B1955 3
#define B2 4
#define B3 5
boolean gril_state=false; //false-> open ture->close
boolean gril_on=false;
const int tmp=A2;
const int buz=40;
const int btn[2]={23,25};
const int motor[6]={42,44,46,48,4,5};
// light
const int light=4;
const int cds=A1;
//light control counter
int count=0;
int timer=0;




//void cook(unsigned char patty);
//unsigned char patty();
//void use_buz();
//void lightcontrol();
//void grilcontrol();
//void gril_open();
// void gril_close();


 
void setup() {
    pinMode(cds,INPUT);
  
  int i=0;
   pinMode(tmp,INPUT);
  pinMode(light,OUTPUT);

 for(i=0;i<2;i++){
   pinMode(btn[i],INPUT);
 }   
  pinMode(buz,OUTPUT);

  
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(btn[0])==HIGH)
  gril_on=true;
     grilcontrol();
    lightcontrol();
   delay(1000);
}


void use_buz(){
  
    Serial.println("buz on bzzzz");
  
  digitalWrite(buz,HIGH);
  delay(500);
  digitalWrite(buz,LOW);
  
}

void grilcontrol(){
gril_on=true;
if(gril_on==true){

for( ; ; ){
    Serial.println("wait btn1 click");
  
if(digitalRead(btn[1])==HIGH){
 if(gril_state==false)
{
  gril_state =true;
  gril_close();
  cook( patty());
  use_buz();
  gril_open();
  Serial.print("gril off");
  gril_on=false;
  
}
else{
gril_state=false;
gril_open();}

}
delay(100);
break;
}
 }
}

void cook(unsigned char patty){

    Serial.println("start cook");

  Serial.print(patty);
  if(patty&0x01){
    timer=30;
    
  }
  if(patty&0x02){
    timer=60;
  }
  if(patty==3){
    timer=100;
  }

    Serial.print("timer");
    Serial.println(timer);
  
  while(timer){
    Serial.print(timer);
    Serial.print("cook");
    timer--;
    delay(1000);
  }
}

 unsigned char patty(){

    Serial.println("patty");
  
  unsigned int distance = ultrasonick.distanceRead();

distance =B1955;
if(distance >=B1955){

    Serial.println("1955");
  
  return 1;
}
if(distance >=B2){
  return 2;
}
if(distance >=B3){
  return 3;
}

  
}
 


//int griltmp(){
//
//return digitalRead(tmp);
//
//}


void gril_open() {
  
    Serial.println("open");
  
MOTOR_ctrl(5);
PWM_ctrl(100);
delay(5000);
PWM_ctrl(0);  
}

 void gril_close(){

    Serial.println("close");
  
MOTOR_ctrl(10);
PWM_ctrl(100);
delay(5000);
PWM_ctrl(0);  
} 

  


void lightcontrol(){
Serial.println("light sensing...");


if(digitalRead(cds) > 0) 
  light_on();
 
else 
 light_off();
 
}


void light_on(){


if(count>10){

digitalWrite(light,HIGH);

Serial.println("light on");
}
count ++;

if(count>20){
   
  count=20;
}

}

void light_off(){

if(count<5){
digitalWrite(light,LOW);
Serial.print("light off");
}
count --;

if(count<0)
count =0;

}




void MOTOR_ctrl( unsigned char da){
  
  int i=0;
  for(i=0;i<4;i++)
  {
    if(da&0x08){
      digitalWrite(motor[i],HIGH);
    }
    else 
    digitalWrite(motor[i],LOW);

    da*=2;
    }
  }


 void PWM_ctrl(const unsigned char spe){
  analogWrite(motor[4],spe);
  analogWrite(motor[5],spe);
}

