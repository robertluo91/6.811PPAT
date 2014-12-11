
int sensorPin = A2;    // select the input pin for the potentiometer
int sensorPin1 = A3;
int sensorPin2 = A5;
int sensorThumb = 0;  // variable to store the value coming from the sensor
int sensorPinMidFinger = 0;
int sensorPinPinkyFinger = 0;
int sensorRead = 0;
int motorPin  = 11;
int minInit = 60;
int minThreshold = 79;
int maxValue = 0;

int minValue = 75;
int maxValuethumb = 0;
int maxValuemid = 0;
int maxValuepinky = 0;
double decay = 0.5;
String outputString = "";

void setup() {
  Serial.begin(9600); 
  pinMode(motorPin, OUTPUT); 
}

void loop() {
  // read the value from the sensor:
  sensorThumb = analogRead(sensorPin);
  sensorPinMidFinger = analogRead(sensorPin1);
  sensorPinPinkyFinger = analogRead(sensorPin2);
  outputString = String(sensorThumb) + " " + String(sensorPinMidFinger) + " " + String(sensorPinPinkyFinger);   
  Serial.println(outputString);
  // delay(100);
  if (sensorThumb <= minThreshold && sensorPinMidFinger <= minThreshold && sensorPinPinkyFinger <= minThreshold ){  //for resetting to the initial value after she drops or leaves the sensor  sensorPinPinkyFinger <= minThreshold
    maxValuethumb = minInit;
    maxValuemid = minInit;
    maxValuepinky = minInit;
  }
  else{
    if (sensorThumb > maxValuethumb){
      maxValuethumb = sensorThumb;
    }
    else if (sensorPinMidFinger > maxValuemid){
      maxValuemid = sensorPinMidFinger;
    }
    else if (sensorPinPinkyFinger> maxValuepinky){
      maxValuepinky = sensorPinPinkyFinger;
    }
    if ((maxValuethumb-minThreshold > 5) && sensorThumb< (maxValuethumb-minThreshold)*decay + minThreshold && ((maxValuemid-minThreshold > 5) || (maxValuepinky-minThreshold > 5))){ //|| (maxValuepinky-minThreshold > 30)
      digitalWrite(motorPin,  HIGH);
      delay(1000);
      digitalWrite(motorPin,  LOW);
      delay(1000);
      maxValuethumb = minInit;
      maxValuemid = minInit;
      maxValuepinky = minInit;
    }
    else if ((maxValuemid-minThreshold > 5) && sensorPinMidFinger< (maxValuemid-minThreshold)*decay + minThreshold && (maxValuethumb-minThreshold > 5) && (maxValuepinky-minThreshold > 5) && sensorPinPinkyFinger < (maxValuepinky-minThreshold)*decay + minThreshold){ // && (maxValuepinky-minThreshold > 30) && sensorPinPinkyFinger < (maxValuepinky-minThreshold)*decay + minThreshold &&
      digitalWrite(motorPin,  HIGH);
      delay(1000);
      digitalWrite(motorPin,  LOW);
      delay(1000);
      maxValuethumb = minInit;
      maxValuemid = minInit;
      maxValuepinky = minInit;
    }
  } 
  delay(100);
  digitalWrite(motorPin,  LOW);
  
}
