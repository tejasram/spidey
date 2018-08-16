#include <Servo.h>
#include <IRremote.h>

const int RECV_PIN = 6;
const int ledPin =  13; 
unsigned int state = 0;
bool still_zero = true;
IRrecv irrecv(RECV_PIN);
decode_results results;
int state_diff = 0;

Servo servos[12];
int servo_states[12] = { 0 };
int desired_states[12] = { 0 };
int pos = 0;
/*
 * All Servos are put in an array.
 * servos[0:3] are the base servos of each leg
 * servos[4:7] are the thigh servos of each leg
 * servos[8:11] are the leg servos of each leg
 */

        /*
        if(still_zero){
          still_zero = false;
          for(int i=0;i<12;i++){
            servos[i].write(0);
            servo_states[i] = 0;
          }
          delay(100);
          for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
            for(int i=0;i<12;i++){
              servos[i].write(pos);
              servo_states[i] = pos;
            }
            delay(15);                       // waits 15ms for the servo to reach the position
          }
        }
        for(int i=0;i<8;i++){
            servos[i].write(90);
            servo_states[i] = 90;
        }
        for(int i=8;i<12;i++){
          servos[i].write(45);
          servo_states[i] = 45;
        }
        */
        
void setup() {

  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  
  servos[0].attach(23);  
  servos[1].attach(22);
  servos[2].attach(21);
  servos[3].attach(20);
  servos[4].attach(19); 
  servos[5].attach(18); 
  servos[6].attach(17); 
  servos[7].attach(16);
  servos[8].attach(15);
  servos[9].attach(14);
  servos[10].attach(3);
  servos[11].attach(4);
  
  int temp_states[12] = { 90,90,90,90,45,45,45,45,0,0,0,0 };
  for(int i=0;i<12;i++){
    desired_states[i] = temp_states[i];
    while(servo_states[i] != desired_states[i]){
      state_diff = servo_states[i]-desired_states[i];
      state_diff < 0 ? servo_states[i]++ : servo_states[i]--;
      servos[i].write(servo_states[i]);
    }
  }
  delay(1500);
  state = 0;
  
}

void loop() {
  switch(state){
      case 0:      //Still stand
      {
        int temp_states1[12] = { 90,90,90,90,45,45,45,45,0,0,0,0 };
        for(int i=0;i<12;i++){
          desired_states[i] = temp_states1[i];
          while(servo_states[i] != desired_states[i]){
            state_diff = servo_states[i]-desired_states[i];
            state_diff < 0 ? servo_states[i]++ : servo_states[i]--;
            servos[i].write(servo_states[i]);
          }      
        }
        delay(100);
        break;
      }
      case 1:      //sit
      {
        still_zero = true;
        int temp_states2[12] = { 90,90,90,90,45,45,45,45,50,50,50,50 };
        for(int i=0;i<12;i++){
          desired_states[i] = temp_states2[i];
          while(servo_states[i] != desired_states[i]){
            state_diff = servo_states[i]-desired_states[i];
            state_diff < 0 ? servo_states[i]++ : servo_states[i]--;
            servos[i].write(servo_states[i]);
          }
        }
        delay(100);
        break;
      }
      case 2:      //Still stand
        still_zero = true;
        break;
      case 3:      //Still stand
        still_zero = true;
        break;
      case 4:      //Still stand
        still_zero = true;
        break;
      case 5:      //Still stand
        still_zero = true;
        break;
      case 6:      //Still stand
        still_zero = true;
        break;
      case 7:      //Still stand
        still_zero = true;
        break;
      case 8:      //Still stand
        still_zero = true;
        break;
      case 9:      //Still stand
        still_zero = true;
        break;
      default:      //Still stand
        still_zero = true;

  }
        
  if (irrecv.decode(&results)) {
    switch(results.value){
      case 0xFFA857:      //W
        state = 1;
        break;
      case 0xFF8877:      //B
        state = 2;
        break;
      case 0xFFD827:      //G
        state = 3;
        break;
      case 0xFF9867:      //R
        state = 0;
        break;
      case 0xFF906F:      //B+
        state = 4;
        break;
      case 0xFFB847:      //B-
        state = 5;
        break;
      case 0xFFB24D:      //Flash
        state = 6;
        break;
      case 0xFF00FF:      //Strobe
        state = 7;
        break;
      case 0xFF58A7:      //Fade
        state = 8;
        break;
      case 0xFF30CF:      //Smooth
        state = 9;
        break;
      default: 
        Serial.print(" unknown button   ");
        Serial.println(results.value, HEX);
        break;
    }
  
    //Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }

/*
  digitalWrite(ledPin, HIGH);
  base1.write(0);  
  base2.write(0);
  base3.write(0);
  base4.write(0);
  thigh1.write(0);
  thigh2.write(0);
  thigh3.write(0);
  thigh4.write(0);
  leg1.write(0);
  leg2.write(0);
  leg3.write(0);
  leg4.write(0);
  delay(100);
  base1.write(50);  
  base2.write(50);
  base3.write(50);
  base4.write(50);
  thigh1.write(100);
  thigh2.write(100);
  thigh3.write(100);
  thigh4.write(100);
  leg1.write(50);
  leg2.write(50);
  leg3.write(50);
  leg4.write(50);
  delay(100);
  digitalWrite(ledPin, LOW);

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  */
}

