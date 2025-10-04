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

void check_operator(char *args[], int num_args, int check[]){

  for (int i = 0; i < num_args; i++){ //loop through our list of aguments to look for an operator
    if(strcmp(args[i],"<") == 0){ //input operator
     int fdIn = open(args[i+1], O_RDONLY); //grabs the file descriptor from the next index no (the file) and sets it as read only
     args[i] = NULL; //set the operator index as NULL, we dont want it interfering with execution
     check[0] = fdIn; //our array to check if we're using a redirection, the first index [0] represents input and if it isnt set to -1, we'll call dup2 in main
    }
    
    else if (strcmp(args[i],">") == 0){ //output operator
       int fdOut = open(args[i+1], O_WRONLY| O_CREAT|O_TRUNC, S_IRWXU); // grabs file descriptor from the next index no (the file) and sets it as create, write only, emmpty upon opening and execute/search 
       args[i] = NULL; //set the operator index as NULL, we dont want it interfering with execution
       check[1] = fdOut;//our array to check if we're using a redirection, the second index [1] represents output and if it isnt set to -1, we'll call dup2 in main
      }
    }
  }

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
  int checkOperator[] = {-1,-1}; //checks and stores for file desc ints, the first index represents an input file desc, and the second an output file desc
  // TODO: Add additional variables for the implementation
  while (should_run) {
    if(argv[0])
    printf("osh>");
    fflush(stdout);

    cout << "Reading input" << endl;
    // Read the input command
  
    fgets(command, MAX_LINE, stdin);
    int length = strlen(command);
    if(command[length - 1] == '\n') //to deal with newline affecting our parsing
    command[length - 1] = NULL; //remove trailing linebreak from fget.
    strcpy(temp_command,command); //we need to save the command temporarly because the parsing function is distructive to the og command string


    cout << "Parsing input" << endl;
    // Parse the input command
    int num_args = parse_command(command, args);
    if (num_args == 0){ //handles a lack of arguments
      continue;
    }
    
    cout << "Attempting execution" << endl;
    // Forking begins
    if(strcmp(command,"exit") == 0) //if "exit" is our input, terminate
    {
      should_run = false;
      break;
    }

    else if(strcmp(command, "!!") == 0)
    { 
      if(strlen(history) != 0) //if history doesnt exist
      { 
       strcpy(command,history); ///copy our command to our history char array
       cout << history << endl;
       strcpy(temp_command,history); //ensures that history can handle repeated !!
       num_args = parse_command(command, args); //parse the new command from history
       
      }
      else
      {
        perror("No command history found.");
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
     // cout << "I am a child process" << endl; //Debut
      check_operator(args, num_args, checkOperator); //checks for operators

      if(checkOperator[1] != -1){ //if our output check index isnt default, that means checkOperator found an operator
        dup2(checkOperator[1], STDOUT_FILENO); //redirect the output to the file using the filedesc int stored in our array
        close(checkOperator[1]); //close the file
      }
      else if(checkOperator[0] != -1){ //if our input check index isnt default, that means checkOperator found an operator
       dup2(checkOperator[0], STDIN_FILENO); //redirect the output to the file using the filedesc int stored in our array
       close(checkOperator[0]); //close the file
      }

      execvp(args[0], args); //Executes parsed arguments and is terminated by a null pointer
      perror("Command not found");
      exit(1);
    }

    else if(pid > 0)
    { 
   //   cout << "I am a parent process" << endl;
      char *command = args[num_args - 1]; //Grab the last word of the input
      int comLen = strlen(command); //Grab the character length of the word
      char last = command[comLen - 1]; //Check the last character of our last arg

      if ( last == '&'){ //If the end of the arg is an ampersand
         command[comLen - 1] = NULL; //remove the ampersand, change it to NULL to prevent unexpected behavior
         args[num_args - 1] = command; //add our newly adjusted arg back into the last index
         execvp(args[0], args); //execute 
      }
      else{
         wait(NULL); //Wait for the child to finish
      }
     }
    strcpy(history,temp_command); //Save the last command
  }
  return 0;
}

