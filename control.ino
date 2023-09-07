#include "DHT.h"
#define DHTPIN1 2
#define DHTPIN2 3
#define DHTPIN3 4
#define DHTTYPE DHT11
#define LIGHTPIN 13
#define PUMPPIN 11
#define FOGPIN 9
/*
DHT dht(DHTPIN,DHTTYPE);
DHT dht1(DHTPIN2,DHTTYPE);
*/
DHT dht[]={{DHTPIN1,DHTTYPE},{DHTPIN2,DHTTYPE},{DHTPIN3,DHTTYPE}};
int LDR[]={A0,A1,A2};
int p[3];
float h[3];
float t[3];
String inp;
int f=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LIGHTPIN,OUTPUT);
  pinMode(FOGPIN,OUTPUT);
  pinMode(PUMPPIN,OUTPUT);
  digitalWrite(LIGHTPIN,HIGH);
  digitalWrite(FOGPIN,HIGH);
  digitalWrite(PUMPPIN,HIGH);
  for(auto& sensor :dht){
    sensor.begin();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //LDR  
  if(Serial.available()>0){    
    inp=Serial.readStringUntil('\n');
    if(inp=="active"){           
      return_data();      
    }
    if(inp=="light_on"){
      digitalWrite(LIGHTPIN,LOW);
    }else if(inp=="light_off"){
      digitalWrite(LIGHTPIN,HIGH);
    }
    if(inp=="pump_on"){
      digitalWrite(PUMPPIN,LOW);
    }else if(inp=="pump_off"){
      digitalWrite(PUMPPIN,HIGH);
    }
    if(inp=="fog_on"){
      digitalWrite(FOGPIN,LOW);
    }else if(inp=="fog_off"){
      digitalWrite(FOGPIN,HIGH);
    }
  } 
 
}
void return_data(){  
    for(int i=0;i<3;i++){
        p[i]=analogRead(LDR[i]);   
        h[i]=dht[i].readHumidity();
        t[i]=dht[i].readTemperature();
      }
      for(int i=0;i<3;i++){
        Serial.print(p[i]);
        Serial.print(" ");
      }
      for(int i=0;i<3;i++){
        Serial.print(h[i]);
        Serial.print(" ");
        Serial.print(t[i]);
        Serial.print(" ");
      }
      Serial.println();
      Serial.flush();                         
      //digitalWrite(13,LOW);   
      //f=0;
      
    
}
