#ifndef COMMAND_H
#define COMMAND_H

// the smallest unit of a command
struct AtomicCommand {
	// total number of arguments
	int _numberOfAvailableArguments;
	// current number of arguments
	int _numberOfArguments;
	// string array of arguments
	char ** _arguments;
	
	AtomicCommand();

	// used to double the total number of arguments available
	// and reallocate memory for `_arguments` to double the current size
    void doubleAvailableSpace();
	// adds passed `argument` to the `_arguments` array
	// also checks if the total number of arguments is full, 
	// in which case calls `doubleAvailableSpace`
	void insertArgument( char * argument );
};

// compound command composed one or more AtomicCommands and 
struct Command {
	// total number of atomic commands
    int _numberOfAvailableAtomicCommands;
	// current number of atomic commands
    int _numberOfAtomicCommands;
	// array of AtomicCommand(s)
	AtomicCommand ** _atomicCommands;
	// file used for writing output
	char * _outFile;
	// file used for taking input
	char * _inputFile;
	// file used for logging errors
	char * _errFile;
	// optional background argument
	int _background;

	// CLI prompt 
	void prompt();

	// prints command table (debugging)
	void print();
	// command execution logic
	void execute();
	// clears terminal
	void clear();
	
	Command();

	// used to double the total number of atomic commands available
	// and reallocates memory for `_atomicCommands` to double the current size
    void doubleAvailableSpace();
	//adds passed `atomicCommand` to `_atomicCommands` array and
	// calls `doubleAvailableSpace` if the total number of commands is full
	void insertAtomicCommand( AtomicCommand * atomicCommand );

	// reference to the current Command
	static Command _currentCommand;
	// reference to current AtomicCommand being processed
	static AtomicCommand *_currentAtomicCommand;
};

#endif