#include <Wire.h>

int datapin = 0;
int clockpin = 1;
int latchpin = 2;
int delayt =1;
int bz = 3; 
int dot = 4;
int delt = 20;

int upbtn = 7;
int downbtn = 6;
int setbtn = 5;


int hour = 0;
int minut = 0;
int second = 0;
int milisecond = 0;

int shour = 0;
int sminut = 1;

unsigned long previousMillis = 0;
const long interval = 3;
const long interval2 = 500;

int statebz=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(datapin,OUTPUT);
  pinMode(clockpin,OUTPUT);
  pinMode(latchpin,OUTPUT);
  pinMode(bz,OUTPUT);
  pinMode(dot,OUTPUT);
  pinMode(upbtn,INPUT);
  pinMode(downbtn,INPUT);
  pinMode(setbtn,INPUT);
  //Serial.begin(9600);
}
int menu=0;
int buz=0;
void loop() {
      menum();
      clockengine();
      singleupordown();
      setbutn();
      buzzer();
}


int upbt=0;
int downbt=0;
int upbtnp=0;
int downbtnp=0;
int uppressd = 0;
int downpressd = 0;
int varbtn = 25;
void singleupordown(){
  if(digitalRead(upbtn)==LOW){
    upbt++;  
  }else if(digitalRead(downbtn)==LOW){
    downbt++; 
  }else{
    upbt = 0;
    downbt = 0;
    varbtn = 25;
    }
    if(upbt-1 < varbtn && upbt==varbtn && upbt  !=0){
      varbtn+=25;
     uppressd = 1;
   }else if(downbt-1 < varbtn && downbt==varbtn && downbt !=0){
    varbtn+=25;
      downpressd = 1;
    }else{
       uppressd = 0;
       downpressd = 0;
       //varbtn = 0;
     }
     if(menu==0){
      if(uppressd==1){
          hour++;
        }
        if(downpressd==1){
          minut++;
        }
     }
     if(menu==1){
      if(uppressd==1){
          shour++;
        }
        if(downpressd==1){
          sminut++;
        }
     }
}
void clockengine(){
  milisecond++;
  if(milisecond >60){
    second++;
    milisecond=0;
    }
    if(second>59){
      minut++;
      second=0;
      }
      if(minut>59){
        hour++;
        minut=0;
        }
        if(hour>12){
            hour=0;
          }
}

int n=0;
void setbutn(){
  
    if(digitalRead(setbtn)==LOW){
        n++;
      }else{
          n=0;
        }
   if(n-1<10 && n==10){
      menu++;
    }
  if(n-1<30 && n==30 && statebz==1){
      digitalWrite(bz,LOW);
      shour=0;
      sminut=0;
    }
  
}
int count=0;
void buzzer(){
  
  if(hour==shour && minut == sminut && count<3 && second<5){
  buz=1;
  statebz=1;
        digitalWrite(bz,HIGH);
      count++;
    
  }else{
      statebz=0;
      count=0;
      digitalWrite(bz,LOW);
    }
      
}

void menum(){
        unsigned long currentMillis = millis();
       if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
         if(menu==0){// normal time 
        updateshift(cnumber(hour/10),cdigit(0),delayt);
        updateshift(cnumber(hour-((hour/10)*10)),cdigit(1),delayt);
        updateshift(cnumber(minut/10),cdigit(2),delayt);
        updateshift(cnumber(minut-((minut/10)*10)),cdigit(3),delayt);
        digitalWrite(dot,HIGH);
        
        
      }
      if(menu==1){  // alarm
        updateshift(cnumber(shour/10),cdigit(0),delayt);
        updateshift(cnumber(shour-((shour/10)*10)),cdigit(1),delayt);
        updateshift(cnumber(sminut/10),cdigit(2),delayt);
        updateshift(cnumber(sminut-((sminut/10)*10)),cdigit(3),delayt);
        digitalWrite(dot,LOW);
        
      }
      if(menu==2){
        menu=0;
      }
        }
    
  }
void updateshift(byte n, byte d,int del){
  
 digitalWrite(latchpin,LOW);
  //shiftOut(datapin,clockpin,LSBFIRST,leds);
  shiftOut(datapin, clockpin, MSBFIRST, n);
  shiftOut(datapin, clockpin, MSBFIRST, d);
  digitalWrite(latchpin,HIGH);
  delay(del);
}

byte cnumber(byte n){
  byte m;
  switch(n){
    case 0: m = 0b00000001; break;
    case 1: m = 0b11111001; break;
    case 2: m = 0b00010010; break;
    case 3: m = 0b00110000; break;
    case 4: m = 0b01101000; break;
    case 5: m = 0b00100100; break;
    case 6: m = 0b00000100; break;
    case 7: m = 0b11110001; break;
    case 8: m = 0b00000000; break;
    case 9: m = 0b01100000; break;
  }
  return m;
}

byte cdigit(byte n){
  byte m;
  switch(n){
    case 0: m = 0b00001000; break;
    case 1: m = 0b00000100; break;
    case 2: m = 0b00000010; break;
    case 3: m = 0b00000001; break;
  }
  return m;
}