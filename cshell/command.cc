#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#include "command.h"


AtomicCommand::AtomicCommand() {
  _numberOfAvailableArguments = 5;
  _numberOfArguments = 0;
  _arguments = (char ** ) malloc(_numberOfAvailableArguments * sizeof(char * ));
}

void AtomicCommand::doubleAvailableSpace() {
  _numberOfAvailableArguments *= 2;
  // rellocate double the current memory of `_arguments`
  _arguments = (char ** ) realloc(_arguments,
    _numberOfAvailableArguments * sizeof(char * ));
}

void AtomicCommand::insertArgument(char * argument) {
  if (_numberOfAvailableArguments == _numberOfArguments + 1) {
    doubleAvailableSpace();
  }

  _arguments[_numberOfArguments] = argument;

  _arguments[_numberOfArguments + 1] = NULL;

  _numberOfArguments++;
}


Command::Command() {
  _numberOfAvailableAtomicCommands = 1;

  _atomicCommands = (AtomicCommand ** )
  malloc(_numberOfAtomicCommands * sizeof(AtomicCommand * ));

  _numberOfAtomicCommands = 0;
  _outFile = 0;
  _inputFile = 0;
  _errFile = 0;
  _background = 0;
}

void Command::doubleAvailableSpace() {
    _numberOfAvailableAtomicCommands *= 2;
    // rellocate double the current memory of `_atomicCommands`
    _atomicCommands = (AtomicCommand **) realloc( _atomicCommands,
			 _numberOfAvailableAtomicCommands * sizeof( AtomicCommand * ) );
}

void Command::insertAtomicCommand(AtomicCommand *atomicCommand) {
    if(_numberOfAvailableAtomicCommands == _numberOfAtomicCommands) {
        doubleAvailableSpace();
    }

    _atomicCommands[_numberOfAtomicCommands] = atomicCommand;
    _numberOfAtomicCommands++;
}

// free all field and reset all counters
void Command::clear() {
  for (int i = 0; i < _numberOfAtomicCommands; i++) {
    for (int j = 0; j < _atomicCommands[i] -> _numberOfArguments; j++) {
      free(_atomicCommands[i] -> _arguments[j]); // free current argument for current AtomicCommand in routine
    }

    free(_atomicCommands[i] -> _arguments); // free arguments reference for current AtomicCommand in routine
    free(_atomicCommands[i]); // free reference to current AtomicCommand in routine
  }

  if (_outFile) {
    free(_outFile); // free reference to the output file
  }
  if (_inputFile) {
    free(_inputFile); // free reference to the input file
  }
  if (_errFile) {
    free(_errFile); // free reference to the error file
  }

  // reset counters
  _numberOfAtomicCommands = 0;
  _outFile = 0;
  _errFile = 0;
  _background = 0;
}

void Command::print() {
  printf("\n\n");
  printf("              COMMAND TABLE                \n");
  printf("\n");
  printf("  #   Atomic Commands\n");
  printf("  --- ----------------------------------------------------------\n");

  for (int i = 0; i < _numberOfAtomicCommands; i++) {
    printf("  %-3d ", i);
    for (int j = 0; j < _atomicCommands[i] -> _numberOfArguments; j++) {
      printf("\"%s\" \t", _atomicCommands[i] -> _arguments[j]);
    }
  }

  printf("\n\n");
  printf("  Output       Input        Error        Background\n");
  printf("  ------------ ------------ ------------ ------------\n");
  printf("  %-12s %-12s %-12s %-12s\n", _outFile ? _outFile : "default",
    _inputFile ? _inputFile : "default", _errFile ? _errFile : "default",
    _background ? "YES" : "NO");
  printf("\n\n");
}

void Command::prompt() {
  printf("cshell$ ");
  fflush(stdout);
}

void Command::execute() {
  // return control if there are no AtomicCommands to execute
  if (_numberOfAtomicCommands == 0) {
    prompt();
    return;
  }

  // print out Command Table
  print();  

  int status;

  for(int i = 0; i < _numberOfAtomicCommands; i++) {

      status = fork();

      if(status == 0) { // this is child process
        execvp(_atomicCommands[i]->_arguments[0], _atomicCommands[i]->_arguments);
        perror("Error in execvp");
        return;
      } else if (status < 0) { // error while forking
          perror("Error while forking");
          return;
      } else { // for the parent shell process
        if(!_background) {
            // wait for the child process to be executed
            waitpid(status, NULL, 0);
        }
      }
  }

  clear();

  prompt();
}

Command Command::_currentCommand;
AtomicCommand *Command::_currentAtomicCommand;

int yyparse(void);

int main() {
  Command cmd;
  
  // initializing the shell with a prompt
  cmd.prompt();
  yyparse();

  return 0;
}
