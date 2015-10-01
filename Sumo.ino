#include <SharpIR.h>

#define IRF A0
#define IRL A1
#define IRR A2

#define MRR 10
#define MRF 11
#define MLR 5
#define MLF 6

#define turnT90  1850
#define turnT180 4060
#define turnT360 7770

#define model 1080

SharpIR sF(IRF, 25, 93, model);
SharpIR sR(IRR, 25, 93, model);
SharpIR sL(IRL, 25, 93, model);

int calDisF;
int calDisR;
int calDisL;


void setup(){
  
  Serial.begin(9600);
  pinMode (IRF, INPUT);
  pinMode (IRL, INPUT);
  pinMode (IRR, INPUT);

  calDisF = sF.distance();
  calDisR = sR.distance();
  calDisL = sL.distance();
  
}


void loop(){
 if (Serial.available()){
   turnSerial();
 }
 
  
}

void printDistance(){
  int d1 = sF.distance();
  int d2 = sR.distance();
  int d3 = sL.distance();
  Serial.print("F ="+String(d1));
  Serial.print("   R ="+String(d2));
  Serial.println("   L ="+String(d3));
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n");
  delay(1000);
}

void sumo(){
  int dF = sF.distance();
  int dR = sR.distance();
  int dL = sL.distance();

  if (((dF<dL)&&(dF<dL))||(dF<50)){
    front();
  }
  else if (dL<dR){
    left();
  }else{
    right();
  }
}

void front(){
  digitalWrite(MRR,LOW);
  digitalWrite(MLR,LOW);
  digitalWrite(MRF,HIGH);
  digitalWrite(MLF,HIGH);
  Serial.println("^");
  
}

void back(){
  digitalWrite(MRF,LOW);
  digitalWrite(MLF,LOW);
  digitalWrite(MRR,HIGH);
  digitalWrite(MLR,HIGH);
  Serial.println("V");
  
}

void right(){
  digitalWrite(MLR,LOW);
  digitalWrite(MRF,LOW);
  digitalWrite(MRR,HIGH);
  digitalWrite(MLF,HIGH);
  Serial.println("<");
}
void left(){
  digitalWrite(MRR,LOW);
  digitalWrite(MLF,LOW);
  digitalWrite(MLR,HIGH);
  digitalWrite(MRF,HIGH);
  Serial.println(">");
}
void stop(){
  digitalWrite(MRR,LOW);
  digitalWrite(MLF,LOW);
  digitalWrite(MLR,LOW);
  digitalWrite(MRF,LOW);
  Serial.println("+");
}
void rotate(int degrees,int direction){

  int rotationTime = map(degrees,0,360,0,turnT360);
  if (direction = 0){
    left(); 
  }else {
    right();
  }
  delay(rotationTime);
  stop();
}


void turnSerial(){
  int i=0;
  char commandbuffer[100];
  while( Serial.available() && i< 99) {
        commandbuffer[i++] = Serial.read();
     }
     commandbuffer[i++]='\0';

     
  int turnValue = int(commandbuffer);
  Serial.println((char*) commandbuffer);
  if (turnValue<0){
    rotate(abs(turnValue),0);
  }else{
    rotate(abs(turnValue),1);
  }
}












