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

  cout << "Parsed Command:" << token << endl;
  args[argcount] = token; //arg[0] contains the command
  argcount++;

  //command = token;
  while (token != NULL) //keep going until we hit the end of the string
  { // we only continue when tokens are left 
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

// Holds previous history {NOT TESTED}
char* access_history(char *args[], int num_args)
{
  char *history = new char[MAX_LINE];
  if (history[0] == NULL)
  {
    for (int i = 0; i < num_args; i++)
    {
      history[i] = *args[i];
    }
    cout << history[0] << endl;
    cout << args[0] << endl;
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
  int iteration = 0;            // Used for history function
  vector<string> history;
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
    cout << "saving command to history" << endl;
   
    
    cout << "Parsing input" << endl;
    // Parse the input command
    int num_args = parse_command(command, args);
    if(strcmp(args[0],"\n") != 0) //dont save blank commands in history
    {
      history.push_back(command);
    }
    cout << "Attempting execution" << endl;
    // Forking begins

    //Checking for !! {NOT TESTED}
    if(strcmp(args[0], "!!") == 0)
    {
      if(iteration != 0)
      { //making sure we dont try to access history on the first execution
      //   char *history = new char[MAX_LINE];
      //   history = access_history(args, num_args);
      //     for (int i = 0; i < num_args; i++){
      //       args[i] = &history[i];
      // 
        cout << "reading history: " <<endl;
        for(int i = 0; i < history.size();i++)
        {
          cout << history[i] <<endl;
        }
      }
      else
      {
        perror("History does not exist");
        exit(EXIT_FAILURE);
      }
    }
    pid_t pid;

    pid = fork(); //Forking a child process

    if(pid < 0){
     perror("Error, pid cannot be below 0"); //Error, pid should never be below 0
     exit(EXIT_FAILURE);
    }

     else if(pid == 0){
      //cout << "I am a child process" << endl; //Debut
      execvp(args[0], args); //Executes parsed arguments and is terminated by a null pointer
      perror("Error, This line should not be reached");
      exit(EXIT_FAILURE); //This line should not be reached
    }

    else if(pid > 0){ 
      char last = strlen(args[0] - 1); //Grab the last char of the command
      //Ampersand check {NOT TESTED}
      if (last != '&'){ //If the end of the command isnt an ampersand
      wait(NULL); //Wait for the child to finish
      }
      //cout << "I am a parent process" << endl; //Debug
      }
    cout << "Iteration: " << iteration << endl;
    iteration++;
    //return 0;
  }
}

