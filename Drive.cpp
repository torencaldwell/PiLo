/*
  Drive.py
  
  A simple serial interface for giving drive control to raspberry pi
  
  created by: Toren Caldwell
  created on: 23 February 2018
*/

#include "simpletools.h"                      // Include simple tools
#include "fdserial.h"
#include "string.h"
#include "abdrive360.h"
#include <stdlib.h>

fdserial *pi;

void parseCommand(char* cmd);



int main()                                    // Main function
{
  pi = fdserial_open(31, 30, 0, 19200);       //Open a serial connection
  
  char cmd[15];                               //Stores the raw command string
  
  char c;                                     //stores characters from serial
  int i=0;                                    //counter
  while(true){
    c = fdserial_rxChar(pi);                  //Get a character from serial
    cmd[i] = c;                               //Put it into cmd
    i++;
    
    //End the string with a '\r' character
    if(c == '\r'){
      cmd[i] = '\0';                          //Terminate the string
      if(i>=6){
        //print(cmd);
        parseCommand(cmd);                      //Parse the command
      }     
      i = 0;
      //fdserial_rxFlush(pi);
    }  
  }      
}

  
char type[8];                 //Command type (GO or MOVE)
char leftString[5];           //Left wheel parameter  (string)
char rightString[5];          //Right Wheel parameter (string)  
  
void parseCommand(char* cmd){
  bool err = false;
  
  int left, right;
  
  int i=0;
  int j=0;
  
  //Get the command type
  while(cmd[i] != ':'){
    type[j] = cmd[i];
    j++;i++;
    if(j>4){
      err = true;
      break;
    }      
  }
  i++;
  type[j] = '\0';
  j=0;
  
  
  //Get the left parameter
  while(cmd[i] != ':'){
    leftString[j] = cmd[i];
    j++;i++;
    if(j>6){
      err = true;
      break;
    }      
  }    
  i++;
  leftString[j] = '\0';
  j=0;
  
  
  //Get the right parameter
  while(cmd[i] != '\r'){
    rightString[j] = cmd[i];
    j++;i++;
    if(j>6){
      err = true;
      break;
    }      
  }
  rightString[j] = '\0';
  
  if(!err){
    //Convert the wheel parameters to ints
    left = atoi(leftString);
    right = atoi(rightString);
  
    //Print the command to the terminal
    printf("%d, %d\n", left, right); 
   
     //Execute the command  
    if(strcmp(type, "GO") == 0){
      drive_speed(left, right);  
    }else if(strcmp(type, "MOVE") == 0){
      drive_goto(left, right);
    } 
  }    
}  
