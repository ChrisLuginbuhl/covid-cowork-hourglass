  /* March 24, 2020
   *  Chris Luginbuhl, Social Body Lab
   *  Using Adafruit absolute orientation sensor breakout board to ring a bell with a solenoid when the orientation changes.
   *  This is part of a work in progress. First prototype is an hourglass that rings the bell when turned over or some other signal arrives.
   */
    
    
    #include <Wire.h>
    #include <Adafruit_Sensor.h>
    #include <Adafruit_BNO055.h>
    #include <utility/imumaths.h>
      
    Adafruit_BNO055 bno = Adafruit_BNO055(55);

    float x, y, z = 0.0;
    unsigned long lastDing = 0;
    const int SOLENOID = 12;
     
    void setup(void) 
    {
      pinMode(SOLENOID, OUTPUT);
      digitalWrite(SOLENOID, LOW);
      
      Serial.begin(9600);
      Serial.println("Orientation Sensor Test"); Serial.println("");
      
      /* Initialise the sensor */
      if(!bno.begin())
      {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
      }
      
      delay(1000);
        
      bno.setExtCrystalUse(true);
    }
     
    void loop(void) 
    {
      /* Get a new sensor event */ 
      sensors_event_t event; 
      bno.getEvent(&event);
      if ((abs(x - event.orientation.x) + abs(y - event.orientation.y) + abs(z - event.orientation.z) > 5) && (millis() - lastDing > 1500))   {
        ding();
      }
      
      x = event.orientation.x;
      y = event.orientation.y;
      z = event.orientation.z; 
      
      /* Display the floating point data */
      Serial.print("X: ");
      Serial.print(event.orientation.x, 4);
      Serial.print("\tY: ");
      Serial.print(event.orientation.y, 4);
      Serial.print("\tZ: ");
      Serial.print(event.orientation.z, 4);
      Serial.println("");
      delay(100);
    }

    void ding() 
    {
        digitalWrite(SOLENOID, HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
        digitalWrite(SOLENOID, LOW);
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("Ding!");
        lastDing = millis();
    }
