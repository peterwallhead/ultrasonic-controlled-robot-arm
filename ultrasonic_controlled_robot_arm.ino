//Signal inputs from Ping sensors.
int signalT=2; //Top
int signalB=3; //Bottom
int signalL=4; //Left
int signalR=5; //Right
int signalC=6; //Centre (unused)

//Relay channel outputs.
int relayC1 = 7; //Up
int relayC2 = 8; //Down
int relayC3 = 9; //Left
int relayC4 = 10; //Right

//Unused relay channel outputs, second relay board required.
int relayC5 = 11; //Arm moving forward 
int relayC6 = 12; //Arm moving backward

//Ping sensor distance variables.
int distance;
int distanceT;
int distanceB;
int distanceL;
int distanceR;
unsigned long pulseduration=0;

void setup() {
  // Set all used pin modes to output (initial Ping state and relay channels).
  int pp;
  for(pp=2; pp<=12; pp++) {
      pinMode(pp, OUTPUT);
  }
}

void measureDistance(int sensorPin)
{
  // Set pin as output so we can send a pulse.
  pinMode(sensorPin, OUTPUT);

  // Set output to LOW.
  digitalWrite(sensorPin, LOW);
  delayMicroseconds(5);
  
  // Now send the 5uS pulse out to activate Ping)))
  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(sensorPin, LOW);
  
  // Now we need to change the digital pin 
  // to input to read the incoming pulse.
  pinMode(sensorPin, INPUT);
  
  // Finally, measure the length of the incoming pulse.
  pulseduration=pulseIn(sensorPin, HIGH);
  
  // Divide the pulse length by half.
  pulseduration=pulseduration/2;
  
  // Now convert to centimetres. We're metric here people...
  distance = int(pulseduration/29);
  
  // Set distance variable based on which pin is currently being read.
  if(sensorPin == 2) {
    distanceT = distance;
  }
  
  if(sensorPin == 3) {
    distanceB = distance;
  }

  if(sensorPin == 4) {
    distanceL = distance;
  }
  
  if(sensorPin == 5) {
    distanceR = distance;
  }
}
void loop() {
  measureDistance(signalT);
  measureDistance(signalB);
  measureDistance(signalL);
  measureDistance(signalR);

  //Control vertical direction of arm.
  if((distanceT<15) && distanceT != distanceB) {
    digitalWrite(relayC1, HIGH); //Move arm up
  } else {
    digitalWrite(relayC1, LOW);
  }
  
  if((distanceB<15) && distanceB != distanceT) {
    digitalWrite(relayC2, HIGH); //Move arm down
  } else {
    digitalWrite(relayC2, LOW);
  }

  //Control horizontal rotation of arm.
  if((distanceL<15) && distanceL != distanceR) {
    digitalWrite(relayC3, HIGH); //Turn arm left
  } else {
    digitalWrite(relayC3, LOW);
  }

  if((distanceR<15) && distanceL != distanceR) {
    digitalWrite(relayC4, HIGH); //Turn arm right
  } else {
    digitalWrite(relayC4, LOW);
  }
  
  delay(100);
}
