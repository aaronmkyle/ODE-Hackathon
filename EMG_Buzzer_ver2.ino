
  #define SENSITIVITY_BUTTON_PIN 7            //pin for button that selects sesitivity
  #define NUM_LED 6                           //number of LEDs in LED bar

  byte ledPins[] = {8, 9, 10, 11, 12, 13};    //pins for LEDs in LED bar
  int speakerPin = 3;                             //Digital pin for output speaker
  
  //EMG saturation values (when EMG reaches this value the gripper will be fully opened/closed)
  int sensitivities[] = {200, 350, 520, 680, 840, 1000};
  int lastSensitivitiesIndex = 2;             //set initial sensitivity index
  
  int emgSaturationValue = 0;                 //selected sensitivity/EMG saturation value
  int analogReadings;                         //measured value for EMG
  byte ledbarHeight = 0;                      //temporary variable for led bar height
  int vol = 0;                               //integer value for vol based on EMG value
  int thisPitch = 0;                         //integer value for tone based on EMG value
  //float toneVol = 0.0;                        //floating point value corresponding to the 
  
  unsigned long debouncerTimer = 0;           //timer for button debouncer         
  //int gripperStateButtonValue = 0;            //temporary variable that stores state of button 
  int userReleasedButton = 1;                 //flag that is used to avoid multiple button events when user holds button
  
  //-----------------------------------------------------------------------------------
  //   Setup servo, inputs and outputs
  // ----------------------------------------------------------------------------------
  void setup(){

    Serial.begin(9600);
                           
    pinMode(SENSITIVITY_BUTTON_PIN, INPUT); 
    pinMode(speakerPin,OUTPUT); 
    digitalWrite(speakerPin,LOW);                          
    
    //initialize all LED pins to output
    for(int i = 0; i < NUM_LED; i++){ 
      pinMode(ledPins[i], OUTPUT);
    }
    
    //get current sensitivity
    emgSaturationValue = sensitivities[lastSensitivitiesIndex];
  }

  //-----------------------------------------------------------------------------------
  //   Main loop
  //
  //   - Checks state of sesitivity button
  //   - Checks state of default-gripper-state button
  //   - Measure EMG
  //   - Shows EMG strength on LED bar
  //   - Sets angle of servo based on EMG strength and current mode (open/closed)
  // ----------------------------------------------------------------------------------
  void loop()
  {
   
        //-----------------------  Switch sensitivity ------------------------------------
    
        //check if button is pressed (HIGH)
        if (digitalRead(SENSITIVITY_BUTTON_PIN))
        { 
            //turn off all the LEDs in LED bar
            for(int j = 0; j < NUM_LED; j++)
            {  
              digitalWrite(ledPins[j], LOW);
            }
          
            //increment sensitivity index
            lastSensitivitiesIndex++;
            if(lastSensitivitiesIndex==NUM_LED)
            {
              lastSensitivitiesIndex = 0;
            }
          
            //get current sensitivity value
            emgSaturationValue = sensitivities[lastSensitivitiesIndex]; 
            
            //light up LED at lastSensitivitiesIndex position for visual feedback
            digitalWrite(ledPins[lastSensitivitiesIndex], HIGH);
           
            //wait user to release button
            while (digitalRead(SENSITIVITY_BUTTON_PIN)) 
            {  
              delay(10);
            }       
            //whait a bit more so that LED light feedback is always visible
            delay(100);        
        }
     
        //-----------------------------  Measure EMG -----------------------------------------------
    
        analogReadings = analogRead(A0);//read EMG value from analog input A0
        
        //---------------------- Show EMG strength on LED ------------------------------------------
        
        //turn OFF all LEDs on LED bar
        for(int j = 0; j < NUM_LED; j++)
        {  
          digitalWrite(ledPins[j], LOW);
        }
         
        //calculate what LEDs should be turned ON on the LED bar
        analogReadings= constrain(analogReadings, 30, emgSaturationValue);
        ledbarHeight = map(analogReadings, 30, emgSaturationValue, 0, NUM_LED);
        thisPitch = map(analogReadings,30, emgSaturationValue, 300, 3500);
        vol = map(analogReadings,30, emgSaturationValue, 0, 255);


        // analogReadings= constrain(analogReadings, 30, 1023);
        // ledbarHeight = map(analogReadings, 30, 1023, 0, NUM_LED);
        //thisPitch = map(analogReadings,30,1023,100,10000);
        
        if (analogReadings < 60){
          digitalWrite(speakerPin,LOW);
        }

        if (analogReadings > 60){
        //tone(speakerPin, thisPitch,100);
        //delay(1);  // delay in between reads for stability
        analogWrite(speakerPin,vol);
        }
        
        //turn ON LEDs on the LED bar
       for(int k = 0; k < ledbarHeight; k++)
        {
          digitalWrite(ledPins[k], HIGH);

 
        }
   

//Stream the data from the EMG and force sensor acquisition, added by AMK, 2/8/22

        Serial.print(analogReadings);    //Voltage from EMG
        Serial.print(" ");
        Serial.println(vol);

}
