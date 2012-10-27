%{
#include "lglc.tab.hh"  /* Generated by bison. */
#define YY_NO_INPUT
#include <stdint.h>
extern FILE *fid;
%}
%s IN_COMMENT
%option yylineno

DIGIT    	[0-9]
ALPHA 	 	[a-zA-Z_]
TOKEN		[0-9a-zA-Z_.]

%%
<INITIAL>{
     "/*"              BEGIN(IN_COMMENT);
     }
     <IN_COMMENT>{ 
     "*/"      BEGIN(INITIAL);
     [^*\n]+   // eat comment in chunks
     "*"       // eat the lone star
     \n        yylineno++;
     }



"->"		return TOK_RARROW; 

"<-"		return TOK_LARROW;

"-{"		return TOK_RARROW_HASH; 

				
{TOKEN}+	{	yylval =   (uintptr_t) strdup(yytext);
				return TOK_ID;				}	

						
			

[ \t\n|]+    /* eat up whitespace */

.			return *yytext; 


%%
int yywrap()
{
return(1);
}
 
 