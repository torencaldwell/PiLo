/*
  Drive.py
  
  A simple serial interface for giving drive control to raspberry pi
  
  created by: Toren Caldwell
  created on: 23 February 2018
*/

#include "simpletools.h"                      // Include simple tools
#include "fdserial.h"
#include "string.h"
#include "abdrive.h"
#include <stdlib.h>

fdserial *pi;

void parseCommand(char*);

int main()                                    // Main function
{
  pi = fdserial_open(1, 0, 0, 19200);         //Open a serial connection
  char cmd[15];                               //Stores the raw command string
  
  char c;                                     //stores characters from serial
  int i=0;                                    //counter
  while(1){
    c = fdserial_rxChar(pi);                  //Get a character from serial
    cmd[i] = c;                               //Put it into cmd
    i++;
    
    //End the string with a '\r' character
    if(c == '\r'){
      cmd[i] = '\0';                          //Terminate the string
      i = 0;
      parseCommand(cmd);                      //Parse the command 
      fdserial_rxFlush(pi);                   //Empty the rx buffer
    }  
  }      
}

  
char type[8];                 //Command type (GO or MOVE)
char leftString[5];           //Left wheel parameter  (string)
char rightString[5];          //Right Wheel parameter (string)  
  
void parseCommand(char* cmd){
  
  int left, right;
  
  int i=0;
  int j=0;
  
  //Get the command type
  while(cmd[i] != ':'){
    type[j] = cmd[i];
    j++;i++;
  }
  i++;
  type[j] = '\0';
  j=0;
  
  
  //Get the left parameter
  while(cmd[i] != ':'){
    leftString[j] = cmd[i];
    j++;i++;
  }    
  i++;
  leftString[j] = '\0';
  j=0;
  
  
  //Get the right parameter
  while(cmd[i] != '\r'){
    rightString[j] = cmd[i];
    j++;i++;
  }
  rightString[j] = '\0';
  
  
  //Convert the wheel parameters to ints
  left = atoi(leftString);
  right = atoi(rightString);

  //Print the command to the terminal
  printf("%d, %d\n", left, right); 
  
  //Execute the command  
  if(strcmp(type, "GO") == 0){
    drive_speed(left, right);  
  }else{
    drive_goto(left, right);
  }        
}  
