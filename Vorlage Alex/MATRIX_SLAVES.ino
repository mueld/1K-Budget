// TimerOne - Version: Latest 
#include <TimerOne.h>

#include <Wire.h>
#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD419.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
//https://www.velleman.eu/downloads/29/vma419_a4v02.pdf

/***************************PRECOMPILER DEFINITIONS**********************************************/
//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

#define DEBUG
//#define BOARD2
#define BOARD3
#define VALUES_ARRAY_SIZE 5
#define GAMESTATE_INDEX 7
#define LIVES_INDEX 8
#define COMMAND_INDEX 9
#define I2C_RX_BUFFER_SIZE 10
/***************************PRECOMPILER DEFINITIONS**********************************************/
/***************************LOOKUP TABLE DEFINITIONS**********************************************/
int hearttable[14] = {11,12,10,13,10,14,11,15,10,14,10,13,11,12};
DMD419 dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

  bool refreshstate;
/***************************LOOKUP TABLE DEFINITIONS**********************************************/
void SendDebugMessage(const String& message){
  #ifdef DEBUG
  Serial.println(message);
  #endif
}

/***************************ENUM DEFINITIONS**********************************************/
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

enum CommandInterpreterState{
  CommandInterpreter_Idle,
  CommandInterpreter_ExecuteCommand,
  CommandInterpreter_ShowPointsAndLives,
  CommandInterpreter_ReloadLastCommand
};


enum GameState {
  Game_unknown,
  Game_Waiting,
  Game_Initialize,
  Game_Run,
  Game_Finish
};
/***************************ENUM DEFINITIONS**********************************************/

/***************************CLASS DEFINITIONS**********************************************/
/***************************GLOBAL VARIABLES DEFINITIONS**********************************************/
char rxbuffer[I2C_RX_BUFFER_SIZE];
int rxindex;
#ifdef BOARD2
String textToScroll="RER PINBALL - AMER MELVYN MICHA RAPHAEL DAVID BRIAN              ";
String text2ToScroll="OMMEN AN DER BERUFSMESSE WEINFELDEN                                    ";
#endif
#ifdef BOARD3
String textToScroll="BRUDERER PINBALL - AMER MELVYN MICHA RAPHAEL DAVID BRIAN              ";
String text2ToScroll="WILLKOMMEN AN DER BERUFSMESSE WEINFELDEN                               ";
#endif

/***************************GLOBAL VARIABLES DEFINITIONS**********************************************/
void drawText( String dispString ) {
  dmd.clearScreen( true );
  char newString[256];
  int sLength = dispString.length();
  dispString.toCharArray( newString, sLength+1 );
  dmd.drawMarquee( newString , sLength , ( 32*DISPLAYS_ACROSS )-1 ,0);
  
  long start=millis();
  long timer=start;
  long timer2=start;
  boolean ret=false;
  int i = 0;
  while( i<375 ){
    if ( ( timer+40 ) < millis() )
    {
      ret=dmd.stepMarquee( -1 , 0 );
      timer=millis();
      i++;
      //Serial.println(i);
    }
    
  }
  dmd.clearScreen( true );
}

class CommandInterpreter{
  private :
  long points = 0;
  long oldpoints = 0;
  int lives = 0;
  int oldlives = 0;
  bool refreshpoints;
  GameState gamestate;
  GameState oldgamestate;
  long lastcommandtimestamp = 0;;
  CommandInterpreterState state = CommandInterpreter_Idle;
  
   char nextcommand_values[VALUES_ARRAY_SIZE];
  MatrixCommand nextcommand;

  char activecommand_values[VALUES_ARRAY_SIZE];
  MatrixCommand activecommand;
  char lastpointcommand_values[I2C_RX_BUFFER_SIZE];


  int i;
  int k;
  int j;
  
  void drawLives(bool ignoreoldlives){
    
    if(lives<=0){
      return;
    }

    if(oldlives !=lives || ignoreoldlives){
      
    SendDebugMessage("Draw Lives");
      for(k=0;k<lives;k++){
       for(j=0;j<7;j++){
          dmd.drawLine(((k*8)+1+j),hearttable[j*2],((k*8)+1+j),hearttable[(j*2)+1],GRAPHICS_NORMAL);
       }
      }
   
     for(k=0;k<(4-lives)*8;k++){
       for(j=10;j<16;j++){
         dmd.writePixel( 31-k, j, GRAPHICS_NORMAL, 0 );
        }

       }
    }
    oldlives =lives; 
  }
  
  void ShiftCommand(){
    for(i=0;i<VALUES_ARRAY_SIZE;i++)
    {
      activecommand_values[i]= nextcommand_values[i];
    }
    activecommand = nextcommand;
  }
  
  void InterpretCommand(const MatrixCommand& command){
    SendDebugMessage("Interpret new Command : ");
    Serial.println(command);
    
    switch(command){
      case  Command_Unknown :
        break;
      case Command_ClearMatrix :
        dmd.clearScreen( true );
        break;
      case Command_ShowStartGame:
        break;
      case Command_SendPoints:
       // dmd.clearScreen( true );
      
       //if(oldpoints != points){
         SendDebugMessage("DRAW NEW POINTS");
       
        #ifdef BOARD3
        //(x1,y1,values,size)
        //dmd.clearScreen( true );
        if(points>0){
           dmd.drawString(  3,  1, activecommand_values,VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
        }
        else{
           if(oldlives !=lives && lives == 3){
               dmd.drawString(  3,  1, "     ",VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
           }
 
        }
        #endif
        #ifdef BOARD2
        //(x1,y1,values,size)
        dmd.drawString(  1,  1, activecommand_values,VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
        #endif
        for(i=0;i<VALUES_ARRAY_SIZE;i++)
        {
          lastpointcommand_values[i]= activecommand_values[i];
        }
    //    }
        #ifdef BOARD3
        drawLives(true);
        #endif

        oldpoints = points;
        break;
      case Command_ShowMatrixRainfall:
        break;
      case Command_ShowString:
         SendDebugMessage("DRAW NEW STRING");

         dmd.clearScreen( true );
         #ifdef BOARD3
        //(x1,y1,values,size)
        dmd.drawString(  3,  1, activecommand_values,VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
        #endif
        #ifdef BOARD2
        //(x1,y1,values,size)
        dmd.drawString(  1,  1, activecommand_values,VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
        #endif
        #ifdef BOARD3
        drawLives(true);
        #endif
        refreshpoints = true;
        lastcommandtimestamp = millis();
        break;

        
    }
    
   
    
    state = CommandInterpreter_Idle;
  }
   
  public :
  
  CommandInterpreterState ActiveState(){
    return state;
  };

  long ActualPoints(){
    return points;
  }

  int ActualLives(){
    return lives;
  }
  
  void ExecuteStateMachine(){
    switch(state){
      case CommandInterpreter_Idle:
      
          /// critical section
          if(nextcommand != Command_Unknown){
            noInterrupts ();
            ShiftCommand();
            nextcommand = Command_Unknown;
            state = CommandInterpreter_ExecuteCommand;
            
            interrupts ();
            
          }
          
          //No new Commands -> Refresh Points in Case of Showing some other Contents
          if(gamestate==Game_Run){
            if((millis()-lastcommandtimestamp)>2000 && refreshpoints){
              refreshpoints = false;
              
                 #ifdef BOARD3
               //(x1,y1,values,size)
               if(points>0){
                dmd.drawString(  3,  1, lastpointcommand_values,VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
               }
                else{
                    dmd.drawString(  3,  1, "     ",VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
                }
                drawLives(true);
               #endif
               #ifdef BOARD2
               //(x1,y1,values,size)
                dmd.drawString(  1,  1, lastpointcommand_values,VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
               #endif
              
             
             
            }
          }
          else{
           // #ifdef BOARD3
             if(gamestate==Game_Finish){
               
                if((millis()-lastcommandtimestamp)>2000 && refreshpoints){
                refreshpoints = false;
                if(points>0){
                  dmd.drawString(  3,  1, lastpointcommand_values,VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
                 }
                else{
                    dmd.drawString(  3,  1, "     ",VALUES_ARRAY_SIZE , GRAPHICS_NORMAL );
                }
             //lives = 0;
             //drawLives(true);
               ;}
             }
           
           
        //   #endif
          }
           

          break;
      case CommandInterpreter_ExecuteCommand :
          InterpretCommand(activecommand);

          break;
      case CommandInterpreter_ReloadLastCommand :
          break;
    }

    if(oldgamestate != gamestate){ 
      
               if(gamestate==Game_Finish){
                 SendDebugMessage("Start Marquisee");
                drawText(text2ToScroll);
                }
     SendDebugMessage("New Game State processed : ");
    Serial.println(gamestate);
    }
    oldgamestate = gamestate;
  };
  
  bool AddNewCommand(char values[I2C_RX_BUFFER_SIZE],const MatrixCommand& command){

      
      for(i=0;i<VALUES_ARRAY_SIZE;i++){
        nextcommand_values[i] = values[i];
      }
      nextcommand = command;
      
      return true;


  };
  
  void OverridePointCount(char values[I2C_RX_BUFFER_SIZE],long newpoints){
    int kk;
    SendDebugMessage("New Points Count received : ");
    Serial.println(newpoints);
     for(kk=0;kk<VALUES_ARRAY_SIZE;kk++)
     {
          lastpointcommand_values[kk]= values[kk];
     }
    points = newpoints;
  }
  
  void OverrideLivesCount(int newlives){
    SendDebugMessage("New Lives Count received : ");
    Serial.println(newlives);
    lives = newlives;
  }
  
  void OverrideGameState(GameState newgamestate){
    SendDebugMessage("New Game State received : ");
    Serial.println(newgamestate);
    gamestate = newgamestate;
  }
};
/***************************CLASS DEFINITIONS**********************************************/

/***************************INSTANCE DEFINITIONS**********************************************/
CommandInterpreter commandInterpreter1;

/***************************INSTANCE DEFINITIONS**********************************************/



void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}


void setup() {
  
  #ifdef DEBUG
  Serial.begin( 9600);
  #endif
  
  #ifdef BOARD3
  int boardid = 3;         
  #endif
  
  #ifdef BOARD2
  int boardid = 2;  
  #endif
  SendDebugMessage("Start I2C Configuration");
  Wire.begin(boardid);
  
  Wire.onReceive(receiveI2CData);
  
  SendDebugMessage("End I2C Configuration");
 
  
  //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
  Timer1.initialize( 1000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
  Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

  //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)

  dmd.selectFont(System5x7);
  
  SendDebugMessage("Board : ");
  Serial.print(boardid);
  SendDebugMessage("Initialisierung Fertig ");

  drawText(textToScroll);
}

void loop() {

  commandInterpreter1.ExecuteStateMachine();
 
  //dmd.drawFilledBox(x1, y1, x2, y2, GRAPHICS_NORMAL );

}

void receiveI2CData() {
  
  
  rxindex = 0;
  long pointbuffer;
  int livesbuffer;
  int gamestatebuffer;
  int ii;
  int kk;
  
  //Read I2C Buffer
  while (Wire.available() && rxindex < sizeof(rxbuffer))  {
    
    rxbuffer[rxindex] = Wire.read();
    rxindex ++;
   
  }
  

  #ifdef DEBUG
   Serial.print("New Command received, Raw Data : ");
  for(ii=0;ii<sizeof(rxbuffer);ii++){
    Serial.print(rxbuffer[ii]);
  }
  Serial.println("");
  #endif
    
 
  switch(rxbuffer[COMMAND_INDEX]){
    case Command_ClearMatrix :
        commandInterpreter1.AddNewCommand(rxbuffer,Command_ClearMatrix);
        break;
     case Command_ShowString :
        refreshstate = true;
        commandInterpreter1.AddNewCommand(rxbuffer,Command_ShowString);
        break;
     case Command_ShowMatrixRainfall :
        commandInterpreter1.AddNewCommand(rxbuffer,Command_ShowMatrixRainfall);
        break;
    case Command_SendPoints :

        pointbuffer=0;
        if(rxbuffer[0] != ' '){
                 pointbuffer += (rxbuffer[0]- '0') * 10000; 
        }
        if(rxbuffer[1] != ' '){
            pointbuffer += (rxbuffer[1]- '0') * 1000;
        }
        if(rxbuffer[2] != ' '){
           pointbuffer += (rxbuffer[2]- '0') * 100;
        }
       if(rxbuffer[3] != ' '){
            pointbuffer += (rxbuffer[3]- '0') * 10;
        }
       if(rxbuffer[4] != ' '){
            pointbuffer += (rxbuffer[4]- '0');
        }

       
       
        

        //Activate new Point Count
        if(commandInterpreter1.ActiveState() == CommandInterpreter_Idle){

          #ifdef BOARD3
          if(pointbuffer>0 || commandInterpreter1.ActualLives()!=rxbuffer[LIVES_INDEX]){
              commandInterpreter1.AddNewCommand(rxbuffer,Command_SendPoints); 
          }
          #else
             if(commandInterpreter1.ActualPoints()!=pointbuffer || pointbuffer == 0){
                 commandInterpreter1.AddNewCommand(rxbuffer,Command_SendPoints); 
             }
          #endif
          if(commandInterpreter1.ActualPoints()!=pointbuffer || pointbuffer == 0){
           commandInterpreter1.OverridePointCount(rxbuffer,pointbuffer);
          }

          commandInterpreter1.OverrideGameState(rxbuffer[GAMESTATE_INDEX]);
          commandInterpreter1.OverrideLivesCount(rxbuffer[LIVES_INDEX]);
        }
        break;
    case Command_SendLives :
        livesbuffer=0;
          if(rxbuffer[3] != ' '){
            livesbuffer += (rxbuffer[3]- '0') * 10;
        }
       if(rxbuffer[4] != ' '){
            livesbuffer += (rxbuffer[4]- '0');
        }
        commandInterpreter1.OverrideLivesCount(livesbuffer);
        //Activate new Live Count
        if(commandInterpreter1.ActiveState() == CommandInterpreter_Idle){
          commandInterpreter1.AddNewCommand(rxbuffer,Command_SendLives); 
        }
        break;
    case Command_SendGameState :
        gamestatebuffer=0;
          if(rxbuffer[3] != ' '){
            gamestatebuffer += (rxbuffer[3]- '0') * 10;
        }
       if(rxbuffer[4] != ' '){
            gamestatebuffer += (rxbuffer[4]- '0');
        }
        commandInterpreter1.OverrideGameState(gamestatebuffer);
        break;
  } 


  }
