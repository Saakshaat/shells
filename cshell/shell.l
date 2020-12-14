%{

#include <string.h>
#include "y.tab.h"

%}

/*Tokens*/
%%

\n 	{
		return NEWLINE;
	}    

[ \t] 	{
		/* Discard spaces and tabs */
     	}	

">" 	{
		return GREAT;
	}

">>" 	{
		return GREATGREAT;
	}

"<"     {
        return LESS;
    }

"&" 	{
		return AMPERSAND;
	}

">&"    {
        return GREATAMPERSAND;
    }

">>&"    {
        return GREATGREATAMPERSAND;
    }

"|"     {
        return PIPE;
    }

"*"     {
        return ASTERISK;
    }

[^ \t\n][^ \t\n]*  {
		yylval.string_val = strdup(yytext);
		return WORD;
	}

.	{
		return NOTOKEN;
	}

%%
	
