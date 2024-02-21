
int sensorPin = A0;   // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int vThresh1 = 100;
int vThresh2 = 200;


#define RedPin  8
#define BluePin  10
#define GreenPin  12

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  pinMode(RedPin,OUTPUT);
  pinMode(GreenPin,OUTPUT);
  pinMode(BluePin,OUTPUT);
  digitalWrite(RedPin,LOW);
  digitalWrite(BluePin,LOW);
  digitalWrite(GreenPin,LOW);

}

void loop() {
  // read the value from the sensor:
    sensorValue = analogRead(sensorPin);
 
    if (sensorValue > vThresh2){
      digitalWrite(BluePin,HIGH);
      digitalWrite(RedPin,LOW);
      digitalWrite(GreenPin,LOW);
    }

    if (sensorValue < vThresh1){
      digitalWrite(BluePin,LOW);
      digitalWrite(RedPin,HIGH);
      digitalWrite(GreenPin,LOW);
    }

    if (sensorValue > vThresh1 && sensorValue < vThresh2) {
      digitalWrite(BluePin,LOW);
      digitalWrite(RedPin,LOW);
      digitalWrite(GreenPin,HIGH);
    }
    
    delay(50);
    Serial.println(sensorValue);
}
