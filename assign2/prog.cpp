
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
// https://www.geeksforgeeks.org/cpp/strtok-strtok_r-functions-c-examples/
#include <complex>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

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
  //
  // referenced
  // https://www.geeksforgeeks.org/cpp/strtok-strtok_r-functions-c-examples/
  //
  int argcount = 0;
  char *token = strtok(command, "   "); //first strtok gets the command
  cout << "Parsed Command:" << token << endl;
  args[argcount] = token; //arg[0] contains the command
  argcount++;
  //command = token;
  while (token != NULL) //keep going until we hit the end of the string
  { // we only continue while there is tokens left
    token = strtok(NULL, "   ");
    if(token != NULL) //dont increment timer and print token if the next token is null
    {
      cout << "Parsed ARG:" << token << endl;
      args[argcount] = token;
      argcount++; //keep track of the number of arguments generated
    }
  }
  cout << "There are: " << argcount << " Arguments"<< endl;
  args[argcount] = NULL; //null terminator
  return argcount;//remove one argument because arg[0] is the command
}

// TODO: Add additional functions if you need

/**
 * @brief The main function of a simple UNIX Shell. You may add additional
 * functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[]) {
  char command[MAX_LINE];       // the command that was entered
  char *args[MAX_LINE / 2 + 1]; // hold parsed out command line arguments
  int should_run = 1;           /* flag to determine when to exit program */

  // TODO: Add additional variables for the implementation.

  while (should_run) {
    printf("osh>");
    fflush(stdout);
    // Read the input command
    fgets(command, MAX_LINE, stdin);
    // Parse the input command
    int num_args = parse_command(command, args);
    
    // TODO: Add your code for the implementation
    /**
     * After reading user input, the steps are:
     * (1) fork a child process using fork()
     * (2) the child process will invoke execvp()
     * (3) parent will invoke wait() unless command included &
     */

    
  }
  return 0;
}
