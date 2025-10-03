/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author ??? (TODO: your name)
 * @brief This is the main function of a simple UNIX Shell. You may add
 * additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient and clear comments to your code
// Reference:
// https://www.geeksforgeeks.org/cpp/strtok-strtok_r-functions-c-examples/ //
// https://brennan.io/2015/01/16/write-a-shell-in-c/
// https://www.geeksforgeeks.org/linux-unix/shell-scripting-test-command
// https://www.geeksforgeeks.org/c/making-linux-shell-c/

#include <complex>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <fstream>
using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated
 * by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[]) {

  int argcount = 0;
  char *token = strtok(command, "   "); //first strtok gets the command

  args[argcount] = token; //arg[0] contains the command
  argcount++;

  //command = token;
  while (token != NULL) //keep going until we hit the end of the string, we only continue when tokens are left 
  { 
    token = strtok(NULL, "   ");
    if(token != NULL) //dont increment count if the next token is null
    {
      args[argcount] = token;
      argcount++; //keep track of the number of arguments generated
    }
  }
  args[argcount] = NULL; //null terminator
  return argcount;//remove one argument because arg[0] is the command
}

void check_operator(char *args[], int num_args){

  for (int i = 0; i < num_args; i++){
    if(strcmp(args[i],"<") == 0){ //input operator
      int fdIn = open(args[i+1], O_RDONLY); //grabs the file descriptor from the next index no (the file) and sets it as read only
      dup2(fdIn, STDIN_FILENO);
      close(fdIn);
  for (int i = 0; i < num_args - 2; ++i) { // removes the operator and text from the index
     args[i] = args[i];
    }
      cout << "Flag: <" << endl;
    }
    

    else if (strcmp(args[i],">") == 0){ //output operator
        int fdOut = open(args[i+1], O_WRONLY| O_CREAT|O_TRUNC, S_IRWXU); // grabs file descriptor from the next index no (the file) and sets it as create, write only, emmpty upon opening and execute/search 
        dup2(fdOut, STDOUT_FILENO);
        close(fdOut);
    for (int i = 0; i < num_args - 2; ++i) { // removes the operator and text from the index
         args[i] = args[i];
         }
        cout << "Flag: >" << endl;
        }
    }
  } 

// Holds previous history 
char* access_history(char *args[], int num_args)
{
  char *history = new char[MAX_LINE];
    for (int i = 0; i < num_args; i++)
    {
      history[i] = *args[i]; //copies args to history
    }
  return history;
} 

//TODO: Add additional functions if you need

/**
 * @brief The main function of a simple UNIX Shell. You may add additional
 * functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) 
{
  char command[MAX_LINE];       // the command that was entered
  char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
  int should_run = 1;           /* flag to determine when to exit program */
  char  history[MAX_LINE]; //this will store the last executed command
  char temp_command[MAX_LINE]; //this will preserve the command to put into the history after execution.
  // TODO: Add additional variables for the implementation
  while (should_run) {
    // TODO: Add your code for the implementation
    /**
     * After reading user input, the steps are:
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included &
     */
    if(argv[0])
    printf("osh>");
    fflush(stdout);

    cout << "Reading input" << endl;
    // Read the input command
  
    fgets(command, MAX_LINE, stdin);
    int length = strlen(command);
    if(command[length - 1] == '\n')
    command[length - 1] = NULL; //remove trailing linebreak from fget.
    strcpy(temp_command,command); //we need to save the command temporarly because the parsing function is distructive to the og command string
    cout << "Parsing input" << endl;
    // Parse the input command
    int num_args = parse_command(command, args);
    if (num_args == 0){
      continue;
    }
    
    cout << "Attempting execution" << endl;
    // Forking begins
    if(strcmp(args[0],"exit") == 0)
    {
      should_run = false;
      break;
    }

    else if(strcmp(args[0], "!!") == 0)
    { 
      if(strlen(history) != 0)
      { 
       strcpy(command,history);
       num_args = parse_command(command, args); //parse the new command from history
      }
      else
      {
        perror("No commands in history.");
      }
    }


    pid_t pid;

    pid = fork(); //Forking a child process

    if(pid < 0)
    {
     perror("Error, pid cannot be below 0"); //Error, pid should never be below 0
     exit(EXIT_FAILURE);
    }

     else if(pid == 0)
     {
      check_operator(args, num_args);
      //cout << "I am a child process" << endl; //Debut
      execvp(args[0], args); //Executes parsed arguments and is terminated by a null pointer
      perror("Error, This line should not be reached");
      exit(EXIT_FAILURE); //This line should not be reached
    }

    else if(pid > 0)
    { 
      char last = strlen(args[0] - 1); //Grab the last char of the command
      if (last != '&'){ //If the end of the command isnt an ampersand
      wait(NULL); //Wait for the child to finish
      }
     }
    strcpy(history,temp_command); //Save the last command
    //iteration++;
  }
  return 0;
}

