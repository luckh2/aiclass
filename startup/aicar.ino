#include <AFMotor.h>

AF_DCMotor Rback_motor(4);   
AF_DCMotor Lback_motor(1);
float RLRatio = 1.0;

int maxSpeed = 80;//最大速度
char getstr;//串口数据
int IntervalTime;//测距时间
int trig = 9;//sero1保留端口
int echo = 10;//sero2保留端口
int control=1;//0:人工控制;1:自动控制

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);    
  Rback_motor.setSpeed(0);
  Rback_motor.run(RELEASE);
  Lback_motor.setSpeed(0);
  Lback_motor.run(RELEASE);
  delay(2000);

  //超声波测距
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
}

void loop() {
  getstr = Serial.read();
  driver();
  if(control==1){
      ultrasonicCar();
  }
}

void forward() {
  Rback_motor.run(BACKWARD);
  Lback_motor.run(BACKWARD);
  Rback_motor.setSpeed(maxSpeed*RLRatio);
  Lback_motor.setSpeed(maxSpeed);
}

void backward() {
  Rback_motor.run(FORWARD);
  Lback_motor.run(FORWARD);
  Rback_motor.setSpeed(maxSpeed*RLRatio);
  Lback_motor.setSpeed(maxSpeed);
}

void stopcar() {
  Rback_motor.setSpeed(0);
  Lback_motor.setSpeed(0);
  Rback_motor.run(RELEASE);
  Lback_motor.run(RELEASE);
}

void left(){
  Rback_motor.run(FORWARD);
  Lback_motor.run(BACKWARD);
  Rback_motor.setSpeed(maxSpeed*RLRatio);
  Lback_motor.setSpeed(maxSpeed);
}


void right(){
  Rback_motor.run(BACKWARD);
  Lback_motor.run(FORWARD);
  Rback_motor.setSpeed(maxSpeed*RLRatio);
  Lback_motor.setSpeed(maxSpeed);
}

void driver() {
  if ((getstr == '<')&&(RLRatio>0.1)) {
    RLRatio -= 0.1;
    Serial.println(RLRatio);
  }  
  if (getstr == '>') {
    RLRatio += 0.1;
    Serial.println(RLRatio);
  }  
  if (getstr == '5') {
    Serial.println("stopcar");
    stopcar();
    control=0;
  }
  if (getstr == '1') {
    Serial.println("forward");
    forward();
    control=0;
  }
  if (getstr == '2') {
    Serial.println("backward");
    backward();
    control=0;
  }
  if (getstr == '3') {
    Serial.println("right");
    right();
    control=0;
  }
  if (getstr == '4') {
    Serial.println("left");
    left();
    control=0;
  }
  if (getstr=='6'){
    control=1;
    Serial.println("Auto Control On");
  }
  if(getstr=='7'){
    control=0;
    Serial.println("Auto Control Off");
  }
  if(getstr=='8'){
    float s;
    s = getdistance();
    Serial.println(s);
  }  
}  

float getdistance() {
  digitalWrite(trig, 1);
  delayMicroseconds(15);
  digitalWrite(trig, 0);
  IntervalTime = pulseIn(echo, HIGH);
  return IntervalTime / 58.00;
}

void ultrasonicCar() {
  float s = 0;
  s = getdistance();
  ultrasonicCar(s);
}

void ultrasonicCar(float s) {
  if ((s < 40)&&(s>0)){//40cm以内
    randomright();
  }else{
    forward();
  }
}
void randomright(){
  Rback_motor.run(BACKWARD);
  Lback_motor.run(FORWARD);
  Rback_motor.setSpeed(maxSpeed*RLRatio);
  Lback_motor.setSpeed(maxSpeed);
  long n = random(50,1000);//随机转向 0.05 - 1秒
  delay(n);
  Rback_motor.setSpeed(0);
  Lback_motor.setSpeed(0);
}
