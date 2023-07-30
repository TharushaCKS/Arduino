// C++ code
//
int Val = 0;
int PIRVal = 0;

const uint8_t Data_1 = 9;
const uint8_t Data_2 = 10;
const uint8_t Data_3 = 11;
const uint8_t Data_4 = 12;

int PIR_Sensor =2;

//global

uint8_t led_state = LOW;
  
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);
  //Data Out
  pinMode(Data_1, OUTPUT);
  pinMode(Data_2, OUTPUT);
  pinMode(Data_3, OUTPUT);
  pinMode(Data_4, OUTPUT);
  
  //input from PIR
  pinMode(PIR_Sensor,INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR_Sensor), Toggle_Distance, CHANGE);
}

void loop()
{
  delay(100); 
}

void Toggle_Distance()
{
  PIRVal = digitalRead(PIR_Sensor);
  
  //motion sensor 
  if (PIRVal > 0) {
  	Serial.println("Motion Detected");
  	digitalWrite(Data_1, HIGH); //Motion Sensor Led ON
  } else {
    digitalWrite(Data_1, LOW);//Motion Sensor Led OFF
  }
  
  //Distance D_OUT
  Val = 0.01723 * readUltrasonicDistance(4,5);
  Serial.println(Val);
  
  if (Val > 180)
  {
    digitalWrite(Data_2, HIGH);
  }if(Val > 250){
    digitalWrite(Data_3, HIGH);
  }if(Val > 275){
    digitalWrite(Data_4, HIGH);
  }
  
  delay(5000);
  digitalWrite(Data_2, LOW);
  digitalWrite(Data_3, LOW);
  digitalWrite(Data_4, LOW);
}


