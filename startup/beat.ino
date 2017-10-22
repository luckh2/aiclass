/* Learning the beats
   created 17 Sept 2017
   by luckh2
 */

const int ledPin = 13; // Onboard led
const int knockSensor = A0; // Sound sensor is connected to analog pin 0
const float threshold = 79.8; //hyper-parameter, threshold value to decide whether a beat comes in
const int led2 = 8; //flag led
const int led3 =7; //beat led

int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light

void setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
  pinMode(led2, OUTPUT); // declare the ledPin as as OUTPUT
  pinMode(led3, OUTPUT); // declare the ledPin as as OUTPUT  
  Serial.begin(9600); // use the serial port
}
int i=0;
unsigned long time;
unsigned long t[3]={0}; // record 3 time positions
int pointer = 0; //time array pointer
int beat =0; //the beat
int i1,i2=0; //beat interval
void loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);
  time=millis();
  
  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    t[pointer++] = time;
    if (pointer>2) pointer =0;
    if ((t[0]>0)&&(t[1]>0)&&(t[2]>0)){
       i1 = t[(pointer+1)%3]-t[pointer];
       i2 = t[(pointer+2)%3]-t[(pointer+1)%3];
      }
    // toggle the status of the ledPin:
    ledState = !ledState;
    // update the LED pin itself:
    digitalWrite(ledPin, ledState);
    // send the time interval to the computer, followed by newline
    Serial.print(i1);Serial.print("-");
    Serial.print(i2);Serial.println("");
    if((abs(i1-i2)<50)&&(abs(i1-i2)>0))
    {
      digitalWrite(led2, !digitalRead(led2)); //switch flag led
      beat = (i1+i2)/2;
      Serial.print("The beat:");
      Serial.println(beat);
    }
    
    i++;
    if(i>3) { //count to 3
      Serial.println("");
      i=0;
      digitalWrite(led2, !digitalRead(led2)); //switch flag led
    }
  }
  if((beat>200)&&(beat<2000)){
    digitalWrite(led3, !digitalRead(led3)); //switch beat led
    digitalWrite(led2,HIGH);
    if(beat>800) delay(beat/2);
    else delay(beat);
    }else
  delay(50);  // delay 0.05s
}

