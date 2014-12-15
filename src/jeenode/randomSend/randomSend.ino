#include <Ports.h>
#include <RF12.h>

//*********************
#include <Wire.h>

Port redPort (1);
Port bluePort (2);
Port greenPort (3);

void setup () {
    //readPort();
    //Wire.begin(5);                // join i2c bus with address #4
    //Wire.onReceive(receiveEvent); // register event
  
    // initialize the serial port and the RF12 driver
    Serial.begin(57600);
    Serial.print("\n[pof66]");
    
    //****************************
    randomSeed(12);
    //****************************
    
    rf12_config();
    // set up easy transmissions every 5 seconds
    rf12_easyInit(1);
    // enable pull-up on LDR analog input 
    // ldr.mode2(INPUT);
    //ldr.digiWrite2(1);
}
//*****************************************
unsigned int ONTIME=20000;

unsigned long lastTimeRed=0;
unsigned long lastTimeGreen=0;
unsigned long lastTimeBlue=0;

int redRand=0;
int greenRand=0;
int blueRand=0;

int randToSend=0;

// Read PINs
int redPIN=0;
int greenPIN=0;
int bluePIN=0;

int firstRed=1;
int firstGreen=1;
int firstBlue=1;



//*****************************************

void loop () {
  
    int randToSend = random(1, 12);
    
    //readPort();
    
    // keep the easy tranmission mechanism going
    rf12_easyPoll();
    // convert analog 0..1023 readings to a 0..255 light level
    //byte value = 255 - ldr.anaRead() / 4;
    //sendToFamily();
    
    Serial.print("Random fuck is : ");
    Serial.println(randToSend);
    
    rf12_easySend(&randToSend, sizeof randToSend);

    delay(1000);
    
}




void sendToFamily(){
  
  //*RED   ****************************
  if(redPIN) {
        
        if(firstRed){
          redRand = random(1,5);
          firstRed=0;
          lastTimeRed = millis();
        }
        
        if( (millis()-lastTimeRed) > ONTIME ){
          redRand = random(1,5);
          lastTimeRed = millis();
        }
     randToSend = redRand;   
           
  }
  
    //*blue   ****************************
  if(bluePIN){
        
        if(firstBlue){
          blueRand = random(5,9);
          firstBlue=0;
          lastTimeBlue = millis();
        }
        
        if( (millis()-lastTimeBlue) > ONTIME ){
          blueRand = random(5,9);
          lastTimeBlue = millis();
        }
        randToSend = blueRand;
        
         
  }
  
    //*green   ****************************
  if(greenPIN){
        
        if(firstGreen){
          greenRand = random(10, 12);
          firstGreen=0;
          lastTimeGreen = millis();
        }
        
        if( (millis()-lastTimeGreen) > ONTIME ){
          greenRand = random(10,12);
          lastTimeGreen = millis();
        }
        randToSend = greenRand;
          
  }
  

  rf12_easySend(&randToSend, sizeof randToSend);
  Serial.println("Random is: ...");
  Serial.println(randToSend);
}

void readPort(){

  Serial.println(redPIN);
  Serial.println(bluePIN);
  Serial.println(greenPIN);
  
  redPIN = redPort.digiRead();
  bluePIN = bluePort.digiRead();
  greenPIN = greenPort.digiRead();
  
  Serial.println(redPIN);
  Serial.println(bluePIN);
  Serial.println(greenPIN);
  
}




