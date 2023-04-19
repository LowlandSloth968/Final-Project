#include <PS2X_lib.h>

PS2X ps2x;

//REMINDER TO GO BACK AND CHANGE THE VARIABLES FOR ALL THE BUTTONS
//THE ONES THAT DESIGNATE THE DIRECTION OF THE MOTORS




int error = 0;
byte type = 0;
byte vibrate = 0;

#define lpma  //(left player motor)
#define lpmb
#define lcpma
#define lcpmb
#define rcpma
#define rcpmb
#define rpma
#define rpmb

#define ltma  //(left transit motor)
#define ltmb
#define lctma
#define lctmb
#define rctma
#define rctmb
#define rtma
#define rtmb

#define enA 2  // must be a PMW pin
#define in1 6
#define in2 7
#define button 4

#define led 50


int PotVal = 255;  //change this to change the speed of the motor contoller


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  pinMode(enA, OUTPUT);    // speed of motor A
  pinMode(in1, OUTPUT);    // direction of motor A
  pinMode(in2, OUTPUT);    // direction of motor A

  error = ps2x.config_gamepad(13, 10, 12, 11, false, false);  //GamePad(clock, command, attention, data, Pressures?, Rumble?)
/* proper
 * clock 13 white
 * attention 12 green
 * command 10 orange
 * data 11 yellow
 * 
 * makeshift
 * clock yellow
 * command blue
 * attention grey
 * data green
 * 
 * yellow to white
 * blue to orange
 * grey to green
 * green to yellow
 *  
 */



  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
  }
}

void loop() {


  analogWrite(enA, PotVal);

  if (error == 1) {
    return;
  } else {  //DualShock Controller

    ps2x.read_gamepad(false, 0);  //stops controller from vibrating

    if (ps2x.Button(PSB_START))  //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if (ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");


    if (ps2x.Button(PSB_PAD_UP)) {  //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);  //dont need analog values just plug it straight into movment
    }
    if (ps2x.Button(PSB_PAD_RIGHT)) {
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if (ps2x.Button(PSB_PAD_LEFT)) {
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if (ps2x.Button(PSB_PAD_DOWN)) {
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }


    //how hard you press the blue (X) button
  }

  

  if (ps2x.Button(PSB_L2))
    Serial.println("L2 pressed");

  if (ps2x.Button(PSB_R2))
    Serial.println("R2 pressed");


  if (ps2x.ButtonPressed(PSB_RED)) {
    Serial.println("O");
    digitalWrite(led, HIGH);
  }


  if (ps2x.ButtonPressed(PSB_PINK)) {  //will be TRUE if button was JUST released
    Serial.println("[]");
    digitalWrite(led, LOW);
  }


  

//---------------------PLAYER MOVEMENT (EVERYTHING)------------------------------------

//---------------------BUTTONS----------------------------
if (ps2x.ButtonPressed(PSB_GREEN)) { //UP
    Serial.println("A");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW); } 
  if (ps2x.ButtonReleased(PSB_GREEN)) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
if (ps2x.ButtonPressed(PSB_BLUE)) { //DOWN
    Serial.println("X");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH); }
  if (ps2x.ButtonReleased(PSB_BLUE)) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }



//--------------------D-PAD-------------------------------
if(ps2x.ButtonPressed(PSB_UP)) {//UP
  Serial.println("d pad up");
  digitalWrite()
}
  if(ps2x.ButtonReleased(PSB_UP)) { //DOWN

  }


//-------------------BUMPERS AND TRIGGERS-----------------






//-------------------LEFT STICK---------------------------





//-------------------RIGHT STICK--------------------------

if(ps2x.ButtonPressed())


//--------------------------------------------------------------------------------------------------


  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))  // print stick values if either is TRUE
  {
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY), DEC);  //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC);
  }

  delay(50);
}
