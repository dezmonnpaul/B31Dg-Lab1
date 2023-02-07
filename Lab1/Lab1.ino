@@ -1,71 +0,0 @@
int SigA = 15;
int SigB = 21;
int In1 = 22;
int In2 = 23;



int a = 1.1*1000;
int b = 0.1*1000;
int c= 10;
int d = 6*1000;
int ctrl=c;

int start =0;
int inc =0;

bool Input1;
bool Input2;
bool enb=1;
//int interval = d+(a-1)*b+(c*a)+((c*0.5)*((2*a)+((c-1)*0.05*1000)));
void setup() {
  // put your setup code here, to run once:
  pinMode(SigA, OUTPUT);
  pinMode(SigB, OUTPUT);
  pinMode(In1, INPUT);
  pinMode(In2, INPUT);
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis =millis();
    if(start==0){
      Input1=!digitalRead(In1);
      ctrl=c-3*(digitalRead(In2));

      if(Input1){
      Serial.print("SignalB- High ");
      digitalWrite(SigB, HIGH);
      delay(0.05*1000);
      Serial.print(0.05*1000);
      Serial.print(" SignalB-LOW");
      Serial.print('\n');
      digitalWrite(SigB, LOW);
      start=start +1;}
    }
    else if (start>0 && start <ctrl+1 && Input1) {
      digitalWrite(SigA,HIGH);
      Serial.print(start);
      Serial.print(" :SignalA- High ");
      delay(a+inc);
      Serial.print(a+inc);
      Serial.print(" SignalA- LOW");
      Serial.print('\n');
      digitalWrite(SigA,LOW);
      inc = inc +(0.05*1000);
      Serial.print("Delay: ");
      Serial.print(b);
      Serial.print('\n');
      delay(b);
      start=start+1;
    }
    else if (Input1) {
      Serial.print("Delay: ");
      Serial.print(d);
      Serial.print('\n');
      delay(d);
      inc=0;
      start=0;
    }

}
