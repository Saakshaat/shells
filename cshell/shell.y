%token <string_val> WORD
%token NEWLINE GREAT GREATGREAT LESS AMPERSAND GREATAMPERSAND GREATGREATAMPERSAND PIPE ASTERISK NOTOKEN

%union {
		char   *string_val;
	}

%{

extern "C" int yylex();
#define yylex yylex
#include <stdio.h>
#include <stdlib.h>
#include "command.h"
void yyerror(const char *s) { fprintf(stderr, "%s\n", s); exit(1);}
%}

// Grammer File

%%
goal:
    command_list
    ;

command_list:
    command_list command_line
    |
    ;

command_line:
    pipe_list io_modifier_list background_optional NEWLINE {
        Command::_currentCommand.execute();
    }
    | NEWLINE {
		Command::_currentCommand.prompt();
	}
    | error NEWLINE{yyerrok;}
    ;

pipe_list:
    pipe_list PIPE cmd_and_args
    | cmd_and_args
    ;

cmd_and_args:
    command arg_list {
        Command::_currentCommand.insertAtomicCommand( Command::_currentAtomicCommand );
    }   
    ;   

command:
    WORD {
        Command::_currentAtomicCommand = new AtomicCommand();
        Command::_currentAtomicCommand->insertArgument( $1 );
    }   
    ;   

arg_list:
    arg_list argument
	|
    ;   

argument:
    WORD {
        printf("Argument: %s\n", $1);
    }   
    ;

io_modifier_list:
	io_modifier_list io_modifier
	|
	;

io_modifier:
	GREATGREAT WORD {
		Command::_currentCommand._outFile = $2; 
        }
    |   GREAT WORD {
        Command::_currentCommand._outFile = $2; 
    }   
    |   GREATGREATAMPERSAND WORD {
        Command::_currentCommand._outFile = $2; 
        Command::_currentCommand._errFile = $2; 
    }   
    |   GREATAMPERSAND WORD {
        Command::_currentCommand._outFile = $2; 
        Command::_currentCommand._errFile = $2; 
    }   
    |   LESS WORD {
        Command::_currentCommand._inputFile = $2;
    }   
    ;   

background_optional:
	AMPERSAND {
		Command::_currentCommand._background = 1;
	}
	|
	;
%%