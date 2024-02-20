//#include <SoftwareSerial.h>
//#include <ArduinoExcel.h>

#define SAMPLE_RATE 30
#define BAUD_RATE 9600
#define EOGL A0
#define EOGR A5

int sensor_valueL = 0;
float signalL = 0.0;

void setup()
{
	Serial.begin(BAUD_RATE);
}

void loop()
{
	static unsigned long past = 0;
	unsigned long present = micros();
	unsigned long interval = present - past;
	past = present;

	static long timer = 0;
	timer -= interval;

	if(timer < 0){
		timer += 1000000 / SAMPLE_RATE;

		sensor_valueL = analogRead(EOGL);
		signalL = EOGFilter(sensor_valueL);
		Serial.println(signalL);
    //Serial.print(",");
    
    //float sensor_valueR = analogRead(EOGR);
		//float signalR = EOGFilter(sensor_valueR);
		//Serial.println(signalR);

    }

    //alert
}

float EOGFilter(float input)
{
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.02977423*z1 - 0.04296318*z2;
    output = 0.09797471*x + 0.19594942*z1 + 0.09797471*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.08383952*z1 - 0.46067709*z2;
    output = 1.00000000*x + 2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.92167271*z1 - 0.92347975*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.96758891*z1 - 0.96933514*z2;
    output = 1.00000000*x + -2.00000000*z1 + 1.00000000*z2;
    z2 = z1;
    z1 = x;
  }

  return output;
}