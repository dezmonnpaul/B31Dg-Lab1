/*---------Definitions and Global Variables----------------------------------------------------------*/
//Defining pins to the desired Input (In1,In2) and Outputs (SigA,SigB)
#define SigA 2 //Signal A
#define SigB 1 //Signal B
#define In1 4 //Switch 1
#define In2 5 //Switch 2

// Defning the initial counter value to determine the initial position of the waveform
#define INITIAL 0 


//Defining parameters a,b,c and d for which the values are obtained as shown.
int a = 1100; //us
int b = 100; //us
int c = 10;
int d = 6000; //us

//Creating a control variable to determine the behaviour depending on the state of Switch 2
int ctrl=  c;

//Defining a variable that has a value of 50us
int comm_del = 50; //us

//'Pulse_count' is a variable used as a counter of pulses which also 
//determines the start of a waveform when its value is 0
int pulse_count = 0;

//'inc' is a variable that holds the incremental delay that would be added to 'a' after every pulse
int inc = 0;

/*------------------------------------------------------------------------------------------------------*/

void setup() {
  //Seting up the Output and Input pins
  pinMode(SigA, OUTPUT);
  pinMode(SigB, OUTPUT);
  pinMode(In1, INPUT);
  pinMode(In2, INPUT);
}

//The loop function will be in a continous loop as the program runs
//Each iteration outputs a single pulse to either Signal A or Signal B as required
//pulse_count will be used to determine the output of each iteration
void loop() {
  //First checks if the current loop is at the initial position of the waveform
  if(pulse_count==INITIAL){
    //Determines the total number of pulses to output based on the state of Switch 2
    ctrl=c-3*(digitalRead(In2)); 

    //Determines if Switch 1 is LOW and outputs Signal B if it is
    if(!digitalRead(In1)){ 
    //Output Signal B as High for 50us
      digitalWrite(SigB, HIGH);
      delayMicroseconds(comm_del); 
      digitalWrite(SigB, LOW); 

      //Increment pulse_count by 1 to allow the output of Signal A
      pulse_count++; 
    }
    //If Switch 1 is HIGH, no there will be no output and 
    //pulse_count will remain as 0, thus disabling the output stream of pulses
  }

  //Determines if the waveform has started and 
  //if the number of pulses output has not exceeded the maximum
  else if (pulse_count>0 && pulse_count <ctrl+1) {
    //Output Signal A as high for a+inc ms
    digitalWrite(SigA,HIGH);
    delayMicroseconds(a+inc);
    digitalWrite(SigA,LOW); 

    //providing a delay of b ms before the next pulse
    delayMicroseconds(b);

    //incrementing the value of inc by 50us, and increasing the pusle counter 
    inc +=  comm_del;
    pulse_count++;
  }

  //Determines if the waveform has completed the cycle of pulses
  else { 
    delayMicroseconds(d); //Provides a delay of d ms

    //resets the values of inc and pulse_count
    inc=0; 
    pulse_count=0;
  }

}
/*---------------------------------------End of code--------------------------------------------*/