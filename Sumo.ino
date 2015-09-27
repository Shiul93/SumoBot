#include <SharpIR.h>

#define IRF A0
#define IRL A1
#define IRR A2

#define ML 10
#define MR 11

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
  
  sumo();
  
}

void printDistance(){
  int d1 = sF.distance();
  int d2 = sR.distance();
  int d3 = sL.distance();
  Serial.print("F ="+String(d1));
  Serial.print("   R ="+String(d2));
  Serial.println("   L ="+String(d3));
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n");
  delay(100);
}

void sumo(){
  int dF = sF.distance();
  int dR = sR.distance();
  int dL = sL.distance();

  if ((dF<dL)&&(dF<dL)){
    front();
  }
  else if (dL<dR){
    left();
  }else{
    right();
  }
}

void front(){
  digitalWrite(MR,HIGH);
  digitalWrite(ML,HIGH);
}
void left(){
  digitalWrite(MR,LOW);
  digitalWrite(ML,HIGH);
}
void right(){
  digitalWrite(MR,HIGH);
  digitalWrite(ML,LOW);
}
