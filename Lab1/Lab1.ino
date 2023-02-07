//Defining pins to the desired Input (In1,In2) and Outputs (SigA,SigB)
#define SigA 15 //Signal A
#define SigB 21 //Signal B
#define In1 22 //Switch 1
#define In2 23 //Switch 2

// Defning the initial counter value to determine the initial position of the waveform
#define INITIAL 0 //
const int time_multi = 1000;

//Defining parameters a,b,c and d for which the values are obtained as 1.1ms,0.1ms,10,6ms respectively.
int a = 1.1*time_multi; //ms
int b = 0.1*time_multi; //ms
int c = 10;
int d = 6*time_multi; //ms

//Creating a control variable to determine the behaviour depending on the state of Switch 2
int ctrl=  c;

//Defining a variable that has a value of 0.05ms(50us)
int comm_del = 0.05*time_multi;

//'start' is a variable used as a counter of pulses which alos determines the start of a waveform when its value is 0
int start = 0;

//'inc' is a variable that holds the incremental delay that would be added to 'a' after every pulse
int inc = 0;


//Creating a constant variable that can be used to increase the time multipler. This allows
// delays in microseconds to be delays in miliseconds if time_multi = 1000


void setup() {
  //Seting up the Output and Input pins
  pinMode(SigA, OUTPUT);
  pinMode(SigB, OUTPUT);
  pinMode(In1, INPUT);
  pinMode(In2, INPUT);

  Serial.begin(115200); //Setting up the serial monitor baud rate at 115200
}

void loop() {
  if(start==INITIAL){//First checks if the current loop is at the initial position of the waveform
    ctrl=c-3*(digitalRead(In2)); //Determines the total number of pulses to output based on the state of Switch 2


    if(!digitalRead(In1)){ //Determines if Switch 1 is LOW and outputs Signal B if it is
      Serial.print("SignalB- High ");
      digitalWrite(SigB, HIGH); //Output Signal B as High
      delay(comm_del); // Delays for 50us(pusle width of signal B)
      Serial.print(comm_del);
      Serial.print(" SignalB-LOW");
      Serial.print('\n');
      digitalWrite(SigB, LOW); //Output of Signal B is LOW
      start=start +1; //Increment start by 1 to allow the output of Signal A
    }
    //If Switch 1 is HIGH, no there will be no output and start will remain as 0, thus disabling the output stream of pulses
  }

  //Determines if the waveform has started and if the number of pulses output has not exceeded the maximum
  else if (start>0 && start <ctrl+1) {
    digitalWrite(SigA,HIGH); //Output Signal A as High
    Serial.print(start);
    Serial.print(" :SignalA- High ");
    delay(a+inc); //Delays the change in output for a+inc ms (pulse width)
    Serial.print(a+inc);
    Serial.print(" SignalA- LOW");
    Serial.print('\n');
    digitalWrite(SigA,LOW); //Output Signal A as LOW
    inc = inc + comm_del;//incrementing the value of inc by 50us, thus increaing the overall pulse width of the following pulse 
    Serial.print("Delay: ");
    Serial.print(b);
    Serial.print('\n');
    delay(b);// Delays the change in output for b ms
    start=start+1; //Increments start by 1 to signify a pulse has been output
  }
  //Determines if the waveform has completed the cycle of pulses
  else { 
    Serial.print("Delay: ");
    Serial.print(d); 
    Serial.print('\n');
    delay(d); //Provides a delay of d ms
    inc=0; //resets the values of inc and start
    start=0;
  }

}
