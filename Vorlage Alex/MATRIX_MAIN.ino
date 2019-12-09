//by Alexander Stark (COde Bot)
//12.07.2019
//3. Lehrjahr Bruderer AG Lackiererei


#include <Wire.h>
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *MotorKugelweiche = AFMS.getStepper(200, 2);
//Disclaimer: Dieses Pogramm ist so geschrieben, dass auch nicht sehr erfahrene Leute es verstehen und anpasen können.

//******************************PRE COMPILER VARIABLES ********************************************//
#define DEBUG 
#define VALUES_ARRAY_SIZE 5
#define GAMESTATE_INDEX 7
#define LIVES_INDEX 8
#define COMMAND_INDEX 9
#define I2C_TX_BUFFER_SIZE 10
//******************************PRE COMPILER VARIABLES ********************************************//

//******************************OUTPUT VARIABLES ********************************************//
const int R1 = 38;      //LED-Startbutton
const int R2 = 39;      //48V-Freigabe
const int R3 = 40;      //Katapultfreigabe
const int R4 = 41;      //Spule Katapult hinten (zuerst)
const int R5 = 42;      //Spule Katapult vorne (1 Sekunde verzögert)
const int R6 = 43;      //Spule hinten Lackiererei (zuerst)
const int R7 = 44;      //Spule vorne Lackiererei (1 Sekunde Zeitverzögert)
const int R8 = 45;      //SlingShotLeft
const int R9 = 46;      //SlingShotRight
//******************************OUTPUT VARIABLES ********************************************//


//******************************INPUT VARIABLES ********************************************//
const int EingangKatapult = 2;
const int EingangTargets = 3;
const int EingangLackiererei = 18;
const int EingangSchlagturm = 19;
const int EingangKugelweiche = 17;
const int Start = 28;
const int InputSlingShotLeft = 16;
const int InputSlingShotRight = 15;
//******************************INPUT VARIABLES ********************************************//

//******************************ENUM DECLARATION ********************************************//
//Gamestate Enum
enum GameState {
  unknown,
  Waiting,
  Initialize,
  Run,
  Finish
};

enum StepperState {
  Stepper_unknown,
  Stepper_Idle,
  Stepper_IncrementStepsLeft,
  Stepper_IncrementStepsRight,
  Stepper_IncrementStepsHomingLeft,
  Stepper_IncrementStepsHomingRight
};

enum CatapultState{
  Catapult_unknown,
  Catapult_Initializing,
  Catapult_Idle,
  Catapult_WaitForFiring,
  Catapult_Firing,
  Catapult_Waiting
};

enum BallFeederState{
  BallFeeder_unknown,
  BallFeeder_Initializing,
  BallFeeder_Idle,
  BallFeeder_StoppBalls,
  BallFeeder_BallFeeding,
  BallFeeder_PrepareNextBall
};

enum DebounceState{
  DebounceState_Idle,
  DebounceState_WaitTime,
  DebounceState_CheckState
};

enum SlingShotState{
  SlingShot_Idle,
  SlingShot_WaitTime,
  SlingShot_Pause
};

enum MatrixSenderState{
  MatrixSenderState_Initialize,
  MatrixSenderState_Idle,
  MatrixSenderState_SendCommandtoMatrix1,
  MatrixSenderState_SendCommandtoMatrix2
};

enum MatrixCommand{
  Command_Unknown = 48, // 0
  Command_ClearMatrix = 49, // 1
  Command_ShowStartGame = 50, // 2
  Command_SendPoints= 51, // 3
  Command_SendLives= 52, // 4
  Command_SendGameState= 53, // 5
  Command_ShowMatrixRainfall= 54, // 6
  Command_ShowString= 55 // 7
};

//******************************ENUM DECLARATION ********************************************//


//******************************GLOBAL GAME VARIABLES DECLARATION ********************************************//
int lives;
int oldlives;
bool sendlivesrequest;
long points;
long oldpoints;
bool sendpointsrequest;
int Kugeln;
int KugelnImSpiel;
volatile GameState gamestate;
volatile GameState oldgamestate;
bool sendgamestaterequest;
bool sendstringrequest;
bool enablewaitingstaterequest;
bool changewakeupmessage;
bool sendlastmessage;
bool sendgameover;

long catapulttimestamp = 0;
long lackierereitimestamp = 0;
long waitfinishgame = 0;

//Konstanten
const int MAX_KUGELN_IM_SPIEL = 3;
const int MAX_LIVES = 3;

int oldKatapultInterrupt;
int oldTargetsInterrupt;
int oldLackierereiInterrupt;
int oldSchlagturmInterrupt;

int KatapultInterrupt;
int TargetsInterrupt;
int LackierereiInterrupt;
int SchlagturmInterrupt;
//******************************GLOBAL GAME VARIABLES DECLARATION ********************************************//

void SendDebugMessage(const String& message){
  #ifdef DEBUG
  Serial.println(message);
  #endif
}

class MatrixSender
{
  private:
  MatrixSenderState state = MatrixSenderState_Initialize;
  bool sendtomatrix2;
  bool refreshpoints;
  char sendbuffer1[I2C_TX_BUFFER_SIZE];   
  char sendbuffer2[I2C_TX_BUFFER_SIZE];
  GameState internalstate;
  long number1 = 0;
  long number2 = 0;
  long oldnumber2 = 0;
  long delayforsendingnumber = 0;
  int i = 0;
  int ii = 0;
  
  void StreamStringToArray(const String& matrix2,const String& matrix1){

    // Prepare the character array (the buffer) 
    char char_arr_matrix2[VALUES_ARRAY_SIZE+1];
      // Prepare the character array (the buffer) 
    char char_arr_matrix1[VALUES_ARRAY_SIZE+1];
    
    // Copy it over 
    matrix2.toCharArray(char_arr_matrix2, VALUES_ARRAY_SIZE+1);
    // Copy it over 
    matrix1.toCharArray(char_arr_matrix1, VALUES_ARRAY_SIZE+1);
    
    for(ii=0;ii<VALUES_ARRAY_SIZE;ii++){
      sendbuffer1[ii] = char_arr_matrix1[ii];
      sendbuffer2[ii] = char_arr_matrix2[ii];
    }
    sendbuffer1[GAMESTATE_INDEX] = internalstate;
    sendbuffer2[GAMESTATE_INDEX] = internalstate;
    sendbuffer1[LIVES_INDEX] = lives;
    sendbuffer2[LIVES_INDEX] = lives;
    sendbuffer1[COMMAND_INDEX] = Command_ShowString;
    sendbuffer2[COMMAND_INDEX] = Command_ShowString;
  }

 void StreamNumberToArray(long number,MatrixCommand command){

     //Convert to String
    sprintf(sendbuffer1, "% 5lu", number);  
    //Convert to String
    sprintf(sendbuffer2, "% 5lu", number); 
    //itoa(number2,sendbuffer2,10);
    sendbuffer1[GAMESTATE_INDEX] = internalstate;
    sendbuffer2[GAMESTATE_INDEX] = internalstate;
    sendbuffer1[LIVES_INDEX] = lives;
    sendbuffer2[LIVES_INDEX] = lives;
    sendbuffer1[COMMAND_INDEX] = command;
    sendbuffer2[COMMAND_INDEX] = command;
  }
  
  void StreamPointsToArray(long number,MatrixCommand command){

    number2 = points / 100000;             //teilt Punktzahl in einzelne Zahlen auf für die Anzeigen
    number1 = points - (number2 * 100000);
  
    if(number1==0 && points==100000){
    
      sendbuffer1[0] = '0';
      sendbuffer1[1] = '0';
      sendbuffer1[2] = '0';
      sendbuffer1[3] = '0';
      sendbuffer1[4] = '0';
    }
    else{ 
      if( points>100000)
      {
        sprintf(sendbuffer1, "%05lu", number1); 
      }else
      {
        if(number1<10000){
          sprintf(sendbuffer1, "% 5lu", number1); 
        }else{
          sprintf(sendbuffer1, "%5lu", number1); 
        }
        
      }
    }
    //Convert to String
    sprintf(sendbuffer2, "% 5lu", number2); 
    
    //itoa(number2,sendbuffer2,10);
    sendbuffer1[GAMESTATE_INDEX] = internalstate;
    sendbuffer2[GAMESTATE_INDEX] = internalstate;
    sendbuffer1[LIVES_INDEX] = lives;
    sendbuffer2[LIVES_INDEX] = lives;
    sendbuffer1[COMMAND_INDEX] = command;
    sendbuffer2[COMMAND_INDEX] = command;
  }
  
  void SendDebugBufferContents(){
    #ifdef DEBUG
    
    SendDebugMessage("Buffer 1 : ");
    for(i=0;i<I2C_TX_BUFFER_SIZE;i++){
      Serial.print(sendbuffer1[i]);
    }
    SendDebugMessage("");
      
    SendDebugMessage("Buffer 2 : ");
    for(i=0;i<I2C_TX_BUFFER_SIZE;i++){
      Serial.print(sendbuffer2[i]);
    }
    SendDebugMessage("");
    
    #endif
  }

  public:
  bool SendPoints(long number){
    if(state==MatrixSenderState_Idle && ((millis()-delayforsendingnumber)>2000)){
      
      StreamPointsToArray(number,Command_SendPoints);
      state = MatrixSenderState_SendCommandtoMatrix1;
      if(refreshpoints){
          sendtomatrix2 = true;
          refreshpoints = false;
      }else{
          sendtomatrix2 = false;
      }
    
      return true;
    }
    return false;
  }
  
  bool SendState(long number,GameState newstate){
    if(state==MatrixSenderState_Idle){
      internalstate = newstate;
      StreamPointsToArray(number,Command_SendPoints);
      state = MatrixSenderState_SendCommandtoMatrix1;
       sendtomatrix2 = true;
      return true;
    }
    return false;
  }
  
   bool SendLives(int lives){
    if(state==MatrixSenderState_Idle){
      
      StreamNumberToArray(lives,Command_SendLives);
      state = MatrixSenderState_SendCommandtoMatrix2;
      return true;
    }
    return false;
  }
  
   bool SendString(const String& matrix2,const String& matrix1){
    if(state==MatrixSenderState_Idle){
      delayforsendingnumber = millis();
      StreamStringToArray(matrix2,matrix1);
      state = MatrixSenderState_SendCommandtoMatrix1;
      sendtomatrix2 = true;
      refreshpoints = true;
      return true;
    }
    return false;
  }
  
  void ExecuteStateMachine() 
  {
    switch(state){
      
      case MatrixSenderState_Initialize:
      
          Wire.begin();             //startet die Bilbliothek für die Kommunikation über I2C

           
           state = MatrixSenderState_Idle;
           break;
      
      case MatrixSenderState_Idle:

        break;

      case MatrixSenderState_SendCommandtoMatrix1:
        
        Wire.beginTransmission(2);       //begin der Übertragung der Daten an Gerät 2
        Wire.write(sendbuffer1,I2C_TX_BUFFER_SIZE);         //sendet Inhalt des char arrays buf2
        Wire.endTransmission();          //beendet die Übertragung

         
        if(number2!=oldnumber2 || sendtomatrix2){
            state = MatrixSenderState_SendCommandtoMatrix2;
        }
        else{
          state = MatrixSenderState_Idle;
        }
        oldnumber2 = number2;
        
  
        break;
      case MatrixSenderState_SendCommandtoMatrix2:


        
        Wire.beginTransmission(3);       //begin der Übertragung der Daten an Gerät 3
        Wire.write(sendbuffer2,I2C_TX_BUFFER_SIZE);         //sendet Inhalt des char arrays buf3 
        Wire.endTransmission();          //beendet due Übertragung
        
        state = MatrixSenderState_Idle;
        
        SendDebugBufferContents();
        
        break;

    }
  
  }
};


class RaisingEdge
{
  private:
  DebounceState state = DebounceState_Idle;
  bool oldtriggerstate = false;
  long activetime = 0;
  int debouncetimeout = 2;


  public:
  
  void Setup(int debouncetime){
     debouncetimeout = debouncetime;
  }
  
  bool GetRaisingEdge(const bool trigger) 
  {
   bool result = false;
    switch(state){
      case DebounceState_Idle:
         if(trigger==true && oldtriggerstate==false){
           activetime = millis();
           state = DebounceState_WaitTime;
         }
        break;

      case DebounceState_WaitTime:
         if((millis()-activetime)>debouncetimeout){
           state = DebounceState_CheckState;
         }
        break;
      case DebounceState_CheckState:
         if(trigger==true){
           result = true;
         }
         state = DebounceState_Idle;
        break;
    }
    oldtriggerstate = trigger;
    return result;
  }
};


class FallingEdge
{
  private:
  DebounceState state = DebounceState_Idle;
  bool oldtriggerstate = false;
  long activetime = 0;
  int debouncetimeout = 2;
  
   
  public:
  void Setup(int debouncetime){
     debouncetimeout = debouncetime;
  }
  
  bool GetFallingEdge(const bool trigger) 
  {
    bool result = false;
    switch(state){
      case DebounceState_Idle:
         if(trigger==false && oldtriggerstate==true){
           activetime = millis();
           state = DebounceState_WaitTime;
         }
        break;

      case DebounceState_WaitTime:
         if((millis()-activetime)>debouncetimeout){
           state = DebounceState_CheckState;
         }
        break;
      case DebounceState_CheckState:
         if(trigger==false){
           result = true;
         }
         state = DebounceState_Idle;
        break;
    }
    oldtriggerstate = trigger;
    return result;
  }
};

class SlingShot
{
  private:
  SlingShotState state = SlingShot_Idle;
  long activetime = 0;
  int spule = 0;
  int trigger =0;
  FallingEdge edgetrigger;
  
  public:
  void Setup(int eingangsnummer,int spulenummer){
  spule = spulenummer;
  trigger = eingangsnummer;
  edgetrigger.Setup(10);
  }
  
  void ExecuteStateMachine() 
  {
   
    switch(state){
      case SlingShot_Idle:
         //edgetrigger
         //if(digitalRead(trigger) == LOW)
         if(edgetrigger.GetFallingEdge(digitalRead(trigger))){
           activetime = millis();
           digitalWrite(spule, HIGH);    //Spule einschalten
           SendDebugMessage("Slingshot Spule wurde eingeschalten"); 
           state = SlingShot_WaitTime;
         }
        break;

      case SlingShot_WaitTime:
         if((millis()-activetime)>100){
            digitalWrite(spule, LOW);    //Spule ausschalten
            activetime = millis();
            state = SlingShot_Pause;
         }
        break;
      case  SlingShot_Pause :
       if((millis()-activetime)>400){
           digitalWrite(spule, LOW); 
           state = SlingShot_Idle;
         }
         break;
    }
  }
};


class StepperMotor
{
  private: 
  StepperState stepperstate = Stepper_Idle;
  long actualms = 0;
  int timedelay = 0;
  int steps = 0;
  const int stepstotarget = 600;

  
  public:
  void ExecuteStateMachine(){
    switch(stepperstate) 
    {
    case Stepper_Idle :
        
        break;
      case Stepper_IncrementStepsLeft:
        if(steps<stepstotarget){
          MotorKugelweiche->onestep(BACKWARD,DOUBLE);
          steps++;
        }else{
          steps = 0;
          SendDebugMessage("Stepper bewegt sich nach Links");
          stepperstate = Stepper_IncrementStepsHomingLeft;
          actualms = millis();

        }
        
        break;
      case Stepper_IncrementStepsRight:
           if(steps<stepstotarget){
               MotorKugelweiche->onestep(FORWARD,DOUBLE);
               steps++;
            }else{
               steps = 0;
               SendDebugMessage("Stepper bewegt sich nach Rechts");
               stepperstate = Stepper_IncrementStepsHomingRight;
               actualms = millis();

           }
         break;
      case Stepper_IncrementStepsHomingLeft:
           if((millis()-actualms)>1000) 
           {
             if(steps<stepstotarget){
              MotorKugelweiche->onestep(FORWARD,DOUBLE);
              steps++;
             }else{
             steps = 0;
             SendDebugMessage("Stepper bewegt sich von links nach Home");
             stepperstate = Stepper_Idle;
             }

           }
         break;
      case Stepper_IncrementStepsHomingRight:
           if((millis()-actualms)>1000) 
           {
             if(steps<stepstotarget){
                MotorKugelweiche->onestep(BACKWARD,DOUBLE);
                steps++;
             }else{
               steps = 0;
               SendDebugMessage("Stepper bewegt sich von rechts nach Home");
               stepperstate = Stepper_Idle;
             }

           }
         break;

    }
    
  }

  StepperState ActiveState()
  {
    return stepperstate;
  }

  void MoveLeft(int settimedelay)
  {
    if(stepperstate==Stepper_Idle)
    {
      SendDebugMessage("Stepper bewegt sich nach Links");
    //  actualms = millis();
      timedelay = settimedelay;
      steps = 0;
      stepperstate = Stepper_IncrementStepsLeft;
      //MotorKugelweiche->step(600, BACKWARD, DOUBLE);   
    }
  }

   void MoveRight(int settimedelay)
  {
    if(stepperstate==Stepper_Idle)
    {
      SendDebugMessage("Stepper bewegt sich nach Rechts");
      timedelay = settimedelay;
      steps = 0;
   //   actualms = millis();
      stepperstate = Stepper_IncrementStepsRight;

     // MotorKugelweiche->step(600, FORWARD, DOUBLE); 
     
    }
  }
   
};

class BallFeeder{
  private : 
  BallFeederState ballfeederstate = BallFeeder_Initializing;
  long activetime = 0;
  int spulevorne = 0;
  int spulehinten = 0;
  
  public:

  void Setup(int spulenummervorne,int spulenummerhinten)
  {
    spulevorne = spulenummervorne;
    spulehinten = spulenummerhinten;
  }
  
  BallFeederState ActiveState(){
    return ballfeederstate;
  }
  
  bool GiveNewBall(){
    if(ballfeederstate == BallFeeder_Idle){
      //Spule öffnen
      ballfeederstate = BallFeeder_StoppBalls;
      digitalWrite(spulevorne, HIGH);    //Hintere Spule einschalten
      digitalWrite(spulehinten, LOW);    //Vordere Spule einschalten
      activetime = millis();
      return true;
    }
    return false;
  }
  
  void ExecuteStateMachine(){
    
    switch (ballfeederstate){
      
      case BallFeeder_Initializing :
          //Spulen stellung setzen
          //
          //   
          digitalWrite(spulevorne, LOW);    //Hintere Spule ausschalten
          digitalWrite(spulehinten, LOW);    //Vordere Spule ausschalten
          ballfeederstate = BallFeeder_Idle;
          break;
      case BallFeeder_Idle:
          break;
          
      case BallFeeder_StoppBalls:
          if((millis()-activetime)>500){
               //Vorder Spule bestromen
           //Hintere Spule stromfrei schalten
            digitalWrite(spulevorne, HIGH);    //Vorne Spule einschalten
            digitalWrite(spulehinten, HIGH);    //Vordere Spule ausschalten
            ballfeederstate = BallFeeder_BallFeeding;
            activetime = millis();
            }
          break;
      case BallFeeder_BallFeeding :
            
            if((millis()-activetime)>1000){
               //Vorder Spule bestromen
           //Hintere Spule stromfrei schalten
            digitalWrite(spulevorne, HIGH);    //Hintere Spule einschalten
            digitalWrite(spulehinten, LOW);    //Vordere Spule ausschalten
            ballfeederstate = BallFeeder_PrepareNextBall;
            activetime = millis();
            }
          
           break;
      
      case  BallFeeder_PrepareNextBall:
      
            if((millis()-activetime)>100){
              digitalWrite(spulevorne, LOW);    //Hintere Spule ausschalten
              digitalWrite(spulehinten, LOW);    //Vordere Spule ausschalten
              ballfeederstate = BallFeeder_Idle;
            }
        
           break;
    }
  
  }
  
};


class Catapult{
  private : 
  CatapultState catapultstate = Catapult_Initializing;
  CatapultState oldstate = Catapult_Initializing;
  long activetime = 0;

  
  public:
  CatapultState ActiveState(){
    return catapultstate;
  }
  
  bool FireBall(){
    if(catapultstate == Catapult_Idle){
      //Spule öffnen
      catapultstate = Catapult_WaitForFiring;
      activetime  = millis();
      return true;
    }
    return false;
  }
  
  void ExecuteStateMachine(){
    
    switch (catapultstate){
      
      case Catapult_Initializing :
          //Spulen stellung setzen
          digitalWrite(R3, LOW);    //Relais für Katapult wird ausgeschalten
          catapultstate = Catapult_Idle;
          break;
      case Catapult_Idle:
          break;
      case Catapult_WaitForFiring :
            if((millis()-activetime)>2000){
               digitalWrite(R3, HIGH);
               catapultstate = Catapult_Firing;
               activetime = millis();
            }
            break;
      case Catapult_Firing :
            
            if((millis()-activetime)>200){
               digitalWrite(R3, LOW); 
               catapultstate = Catapult_Waiting;
               activetime = millis();
            }
          
           break;
      case Catapult_Waiting :
           if((millis()-activetime)>1000){
               catapultstate = Catapult_Idle;
            }
          
           break;
         

    }
      if(oldstate!=catapultstate){
                  SendDebugMessage("Katapult State Wechsel : ");
                  Serial.println(catapultstate);
           }

           oldstate = catapultstate;
  
  }
  
};

/****************************INSTANCE DECLARATION************************************************************/
RaisingEdge rEdgeWaitingState;
RaisingEdge rNoPointsAfterTime;
FallingEdge fEdgeKugelweiche;
FallingEdge fEdgeLackiererei;
FallingEdge fEdgeTargets;
FallingEdge fEdgeSchlagturm;
FallingEdge fEdgeKatapult;

StepperMotor stepper1;
BallFeeder ballfeeder1;
BallFeeder ballfeederLackiererei;
Catapult catapult1;
SlingShot SlingShotLeft;
SlingShot SlingShotRight;
MatrixSender matrixSender1;
/*******************************INSTANCE DECLARATION*********************************************************/


void setup()  {

  

  Serial.begin( 9600);

  
  pinMode(R1, OUTPUT);      //legt fest, dass die Pins als Ausgang dienen
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(R9, OUTPUT);
  
  SendDebugMessage("Ausgänge wurde initialisiert");
  
  pinMode(EingangKatapult, INPUT_PULLUP);                             //legt die Pins als Eingänge fest
  pinMode(EingangTargets, INPUT_PULLUP);                              //
  pinMode(EingangLackiererei, INPUT_PULLUP);
  pinMode(EingangSchlagturm, INPUT_PULLUP);
  pinMode(EingangKugelweiche, INPUT_PULLUP);
  pinMode(Start, INPUT_PULLUP);
  pinMode(InputSlingShotLeft, INPUT_PULLUP);
  pinMode(InputSlingShotRight, INPUT_PULLUP);
  
  SendDebugMessage("Eingänge wurde initialisiert");


  gamestate = Waiting;

  AFMS.begin();                       //beginnt Kommunikation mit Motorentreiber

  MotorKugelweiche->setSpeed(500);    //muss noch richtig eingestellt werden
  digitalWrite(R1, HIGH);    //schaltet LED des Startschalters ein
  
  SendDebugMessage("Schrittmotor wurde initialisiert");

  ballfeeder1.Setup(R4,R5);
  ballfeederLackiererei.Setup(R6,R7);
  SlingShotLeft.Setup(InputSlingShotLeft,R8);
  SlingShotRight.Setup(InputSlingShotRight,R9);
  fEdgeKugelweiche.Setup(300);
  rEdgeWaitingState.Setup(2000);
  rNoPointsAfterTime.Setup(15000);
  SendDebugMessage("Klassen wurden initialisiert");
  
  //Justin Special!!
  delay(6000);
  
  matrixSender1.SendString("LETS ","PLAY?");
  }




void loop() {

  ProcessChangeData();

  switch(gamestate) 
  {
    case Waiting :
        ExecuteWaiting();
        break;
    case Initialize :
        ExecuteInitialize();     
        break;
    case Run :
        ExecuteRun();
        break;
    case Finish :
        ExecuteFinish();
        break;
  }
  
  stepper1.ExecuteStateMachine();
  ballfeeder1.ExecuteStateMachine();
  catapult1.ExecuteStateMachine();
  ballfeederLackiererei.ExecuteStateMachine();
  SlingShotLeft.ExecuteStateMachine();
  SlingShotRight.ExecuteStateMachine();
  matrixSender1.ExecuteStateMachine();
  
  if(oldgamestate!=gamestate){
    // sendgamestaterequest = true;
     enablewaitingstaterequest = true;
   }
   if(sendgamestaterequest){
     sendgamestaterequest = !matrixSender1.SendState(points,gamestate);
     SendDebugMessage("State change sended");
     Serial.println(gamestate);
   }

 
   oldgamestate=gamestate;
   
   if(rEdgeWaitingState.GetRaisingEdge(gamestate==Waiting) && enablewaitingstaterequest){
     if(matrixSender1.SendString("LETS ","PLAY?")){
       enablewaitingstaterequest = false;
     }
   }
   
}



void ExecuteWaiting()
{
  if( digitalRead(Start) == LOW)
  {
     gamestate = Initialize;
     if(matrixSender1.SendString("GAME ","STARTS")){
     
      SendDebugMessage("Spiel wird initialisiert");
      digitalWrite(R1, LOW);     //schaltet LED des Startschalters aus   
       //Stepper Auf die Seite bewegen (Kugel auf SprungFeder rollen)
       stepper1.MoveRight(2000);
     }
  }

  
}


void ExecuteInitialize()
{
   lives = MAX_LIVES;
   //Trick to send the lives to the Slaves
   oldlives = 0;
   points = 0;
    //Trick to send the poin to the Slaves
   oldpoints = 1;
   KugelnImSpiel = 0;
   //48 V Einschalten
   digitalWrite(R2, HIGH);    //Schaltet 48V frei
  
  
    if(stepper1.ActiveState()==Stepper_Idle)
    {
      //    matrixSender1.SendString("GET  ","READY");
          gamestate = Run;
          matrixSender1.SendState(points,gamestate); 
          KugelnImSpiel = 1;
        
          SendDebugMessage("Spiel wurde gestartet, 1 Kugel im Spiel"); 
          
         
    }
}

void ExecuteRun()
{
  DetectBallLost();
  
  
  if(lives <= 0){
    
     if(matrixSender1.SendState(points,gamestate)){ 
      gamestate = Finish;
       SendDebugMessage("Spiel wurde beendet : GAME OVER");
       waitfinishgame = millis();
      
    }

  

   }
}

void ExecuteFinish()
{
   if((millis()-waitfinishgame)>2500){
        gamestate = Waiting;
  
       digitalWrite(R1, HIGH);    //schaltet LED des Startschalters ein
       digitalWrite(R2, LOW);     //Schaltet 48V aus
       SendDebugMessage("Status ist Waiting");
 
   }
}

void DetectBallLost()
{
   
  if(fEdgeKugelweiche.GetFallingEdge(digitalRead(EingangKugelweiche)))
  {
    if(KugelnImSpiel<=1)
    {
      lives = lives  -1 ; 
      if(points<10000){
         if(lives>0){
           matrixSender1.SendString("NOOB ","!!!!!");
         }
         else{
           matrixSender1.SendString("GAME ","OVER!");
         }

      }
      else{
         if(points<20000){
         
          if(lives>0){
          matrixSender1.SendString("ROOKI","E!!!!");
         }
         else{
           matrixSender1.SendString("GAME ","OVER!");
         }
        }else
        {
          
           if(lives>0){
            matrixSender1.SendString("BALL ","LOST!");
         }
         else{
           matrixSender1.SendString("GAME ","OVER!");
         }
        }
      }
     
     SendDebugMessage("NOOB : lives verloren!");
      
      if(lives >0 ){
        stepper1.MoveRight(2000);
      }
    }
    else
    {
       matrixSender1.SendString("LUCKY ","PUNCH");
       SendDebugMessage("LUCKY PUNCH : Noch eine Kugel im Spiel!");
       KugelnImSpiel = KugelnImSpiel - 1;
       stepper1.MoveLeft(2000);
    }
  }

  
}



void ProcessChangeData()
{

    if(gamestate!=Run){
      return;
    }

    
    if(fEdgeLackiererei.GetFallingEdge(digitalRead(EingangLackiererei))){
       points = points + 500; 
      
      if(ballfeederLackiererei.GiveNewBall()) {
        SendDebugMessage("Lackiererei spielt neuen Ball");
        if((millis()-lackierereitimestamp)<15000){
          matrixSender1.SendString("GOOD","CATCH");

        }else{
           matrixSender1.SendString("PARTY","TIME!");
        }
        lackierereitimestamp = millis();
      }else
      {
        SendDebugMessage("Lackiererei Ball kann nicht gespielt werden! Ooopss");
      }
    }

    if(fEdgeTargets.GetFallingEdge(digitalRead(EingangTargets))){
      points = points + 100;
    }

    if(fEdgeSchlagturm.GetFallingEdge(digitalRead(EingangSchlagturm))){
        points = points + 300; 
      //  matrixSender1.SendString("JUST ","DO IT");
    }

    if(fEdgeKatapult.GetFallingEdge(digitalRead(EingangKatapult))){
     
      if(lives<MAX_LIVES){
        lives++;
      }
      if(KugelnImSpiel<MAX_KUGELN_IM_SPIEL){
        if(catapult1.ActiveState()==Catapult_Idle){
          if(ballfeeder1.GiveNewBall()) {
           if((millis()-catapulttimestamp)<15000){
              matrixSender1.SendString("CHEAT","ING??");

           }else{
              matrixSender1.SendString("POWER","PLAY!");
           }
           catapulttimestamp = millis();
           SendDebugMessage("Ball Feeder spielt neuen Ball");
           KugelnImSpiel = KugelnImSpiel + 1;
        }else
         {
           SendDebugMessage("Ball Feeder Katapult kann nicht gespielt werden! Ooopss");
         }
        }
      }
      if(catapult1.FireBall()) {
         points = points + 600;
         SendDebugMessage("Katapult wirft Ball");
      }else
      {
        SendDebugMessage("Katapult kann Ball nicht werfen! Ooopss");
      }
     
    }
    
    
    if(oldpoints!=points){
     sendpointsrequest = true;
    }
    if(sendpointsrequest){
     sendpointsrequest = !matrixSender1.SendPoints(points);
       SendDebugMessage("Punkte werden gesendet");
    }
    
    if(rNoPointsAfterTime.GetRaisingEdge(oldpoints==points)){
      if(changewakeupmessage){
      //   matrixSender1.SendString("COME ","ON!!!");
      }else{
      //   matrixSender1.SendString("WAKE ","UP!!!");
      }
      changewakeupmessage = !changewakeupmessage;
    }
    
    oldpoints=points;


   if(oldlives!=lives){
     sendlivesrequest = true;
      //senden();
   }
   if(sendlivesrequest){
   sendlivesrequest = !matrixSender1.SendPoints(points); 
   }

   oldlives=lives;

   
   oldKatapultInterrupt = KatapultInterrupt;
   oldTargetsInterrupt  = TargetsInterrupt;
   oldLackierereiInterrupt  = LackierereiInterrupt;
   oldSchlagturmInterrupt  = SchlagturmInterrupt;
}
  
