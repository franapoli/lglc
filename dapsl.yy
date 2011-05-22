%{
#include <stdio.h>
#include "globals.h"
#include "nodes.h"
#include "Linkable.h"
#include "Frame.h"
#define YYDEBUG 1
#define YYSTYPE Linkable*
//#define YYPARSE_PARAM scanner
//#define YYLEX_PARAM   scanner

  inline	int yyerror(const char *s) {/*fprintf (stderr, "%s\n", s);*/ return 1;}
  void say(const char *s);
  int yylex(void);

%}
     

/*%union {
   node *    nodet;  
   nodering  nodeset;
   char symbol;
 }

%type <nodet> chain 
%type <nodeset> tree fork_lchild fork_rchild merge_lchild merge_rchild diagram
%token <symbol> '-' '<'  ';' NUM '\n' '\\' '/' '>' '='*/

%token TOK_ID
%token TOK_LARROW "<-"
%token TOK_LARROW_HASH "}-"
%token TOK_RARROW "->"
%token TOK_RARROW_HASH "-{"
%token NUM
%token BOGUS

%left '/' '>'  ';'  TOK_ID NUM '\n' '<' '=' '\\' '|'  '(' ')' '{' '}' '[' ']'
%left "<-" "->" '-' "|-" "-|" "-{" "}-"
%left ',' 
%left '@' '^' 
     
%%

diagram_list:
			|diagram_list diagram
			;

diagram: graphname forktree	';' 		{	$$ = f->doAction(ACT_DIAGRAM, $2, 0, 0, 0);	}
		|forktree	';' 				{	$$ = f->doAction(ACT_DIAGRAM, $1, 0, 0, 0);	}
        |graphname mergetree	';'    	{	$$ = f->doAction(ACT_DIAGRAM, $2, 0, 0, 0);	}
        |mergetree	';'    				{	$$ = f->doAction(ACT_DIAGRAM, $1, 0, 0, 0);	}        
        |graphname nodeline	';' 		{	$$ = f->doAction(ACT_DIAGRAM, $2, 0, 0, 0);	}
        |nodeline	';' 				{	$$ = f->doAction(ACT_DIAGRAM, $1, 0, 0, 0);	}
        |funcdef;
        ;

funcdef: TOK_ID '(' paramlist ')' '{' { f->doAction(ACT_FUNCTDEF, (Linkable *)1, 0, 0, 0);}
				diagram_list '}'	{ f->doAction(ACT_FUNCTDEF, (Linkable *)0, 0, 0, 0);}
	;

node: TOK_ID 		{	$$ = f->doAction(ACT_NODE, $1, 0, 0, 0);						}
     |attrib_node	{	$$ = f->doAction(ACT_NODE, $1, 0, 0, 0);						}
     |'@' TOK_ID 				{	$$ = f->doAction(ACT_REFERENCE, $2, 0, 0, 0);					}
     ;
     

fork_rchain:	'\\' nodeline 		{	$$ = $2	} ;

fork_lchain: 	'/' nodeline  		{	$$ = f->doAction(ACT_CHAINASFORKSON, $2, 0, 0, 0);	} ;

merge_lchain: 	nodeline '\\' 		{	$$ = $1	} ;

merge_rchain: 	nodeline '/' 		{	$$ = $1	} ;

           
nodeline: node 					
		  |connector node 		{	$$ = f->doAction(ACT_NODE, $2, $1, 0, (Linkable *)1);			}
		  | TOK_ID connector 		{	$$ = f->doAction(ACT_NODE, $1, $2, 0, (Linkable *)2);			}
		  |nodeline ',' nodeline  	{	$$ = f->doAction(ACT_COMMA, $1, $3, 0, 0);						}
//		  |'(' 						{	  	 f->doAction(ACT_PARENTHESIS, (Linkable *)1, 0, 0, 0);	}
//			  nodeline  ')' 		{	$$ = f->doAction(ACT_PARENTHESIS, (Linkable *)-1, 0, $3, 0);	}
		  |'{'  nodeline  '}' 		{	$$ = f->doAction(ACT_GROUP, $2, 0, 0, 0);	}
		  | nodeline "->" nodeline 	{	$$ = f->doAction(ACT_ARROW, $1, $3, 0, 0);						}
		  | nodeline "<-" nodeline 	{	$$ = f->doAction(ACT_ARROW, $3, $1, 0, (Linkable *)1);			}
		  | nodeline TOK_RARROW_HASH nodeline 	{	$$ = f->doAction(ACT_ARROW, $1, $3, (Linkable *)2, 0);						}
		  | nodeline TOK_LARROW_HASH nodeline 	{	$$ = f->doAction(ACT_ARROW, $3, $1, (Linkable *)2, (Linkable *)1);			}
		  | nodeline '-' nodeline 	{	$$ = f->doAction(ACT_ARROW, $3, $1, (Linkable *)1, 0);			}
		  ;
      
	        
fork_lchild: fork_lchild  forkroot  '/' fork_rchild 		{	$$ = f->doAction(ACT_FORK, $1,$2,$4,0);	}
            |fork_lchild  forkroot_hash  '/' fork_rchild 	{	$$ = f->doAction(ACT_FORK, $1,$2,$4,(Linkable *) ACT_FLAG_HASH);	}
			|merge_lchild mergeroot  '/'  					{	$$ = f->doAction(ACT_MERGE, $1,$2,$1,0);	}
			|fork_lchain								
			;

fork_rchild: '\\' fork_lchild  forkroot fork_rchild 		{	$$ = f->doAction(ACT_FORK, $2,$3,$4, 0);	}
            |'\\' fork_lchild  forkroot_hash fork_rchild 	{	$$ = f->doAction(ACT_FORK, $2,$3,$4, (Linkable *) ACT_FLAG_HASH);	}
			|'\\'  mergeroot  merge_rchild   				{	$$ = f->doAction(ACT_MERGE, $3,$2,$3,0);	}
			|fork_rchain
			;

merge_lchild: fork_lchild  forkroot  '\\' 						{	$$ = f->doAction(ACT_FORK, $1,$2,$1,0);	}
            | fork_lchild  forkroot_hash  '\\' 					{	$$ = f->doAction(ACT_FORK, $1,$2,$1,(Linkable *) ACT_FLAG_HASH);	}
			|merge_lchild  mergeroot  merge_rchild '\\'  		{	$$ = f->doAction(ACT_MERGE, $1,$2,$3,0);	}
			|merge_lchild  mergeroot_hash  merge_rchild '\\'  	{	$$ = f->doAction(ACT_MERGE, $1,$2,$3,(Linkable *) ACT_FLAG_HASH);	}
			|merge_lchain     	        	      
	        ;


merge_rchild: '/'  forkroot  fork_rchild						{	$$ = f->doAction(ACT_FORK, $3,$2,$3,0);		}
			|merge_lchild '/'  mergeroot  merge_rchild   		{	$$ = f->doAction(ACT_MERGE, $1,$3,$4,0);	}
			|merge_lchild '/'  mergeroot_hash  merge_rchild   	{	$$ = f->doAction(ACT_MERGE, $1,$3,$4,(Linkable *) ACT_FLAG_HASH);	}
			|merge_rchain    
			;
	        	      
paramlist: TOK_ID
		|TOK_ID ',' paramlist
		;
	        
forktree:  fork_lchild  forkroot  fork_rchild 			{	$$ = f->doAction(ACT_FORK, $1,$2,$3, (Linkable *) ACT_FLAG_NO);		};
forktree:  fork_lchild  forkroot_hash  fork_rchild 		{	$$ = f->doAction(ACT_FORK, $1,$2,$3, (Linkable *) ACT_FLAG_HASH);	};

mergetree: merge_lchild  mergeroot  merge_rchild		{	$$ = f->doAction(ACT_MERGE, $1,$2,$3, (Linkable *) ACT_FLAG_NO);	};
mergetree: merge_lchild  mergeroot_hash  merge_rchild	{	$$ = f->doAction(ACT_MERGE, $1,$2,$3, (Linkable *) ACT_FLAG_HASH);	};

forkroot: nodeline '{' 			{	$$=$1;	};
forkroot_hash: nodeline '<'		{	$$=$1;	};

mergeroot: '}' nodeline 		{	$$=$2;	};
mergeroot_hash: '>' nodeline 	{	$$=$2;	};
		   
		   
connector: '^' TOK_ID '^'		{	$$ = f->doAction(ACT_CONNECTOR, $2,0,0,0);	}
           ;

graphname: TOK_ID ':'			{ $$ = f->doAction(ACT_GRAPHNAME, $1, 0, 0, 0);}
          |attrib_graph ':'	{ $$ = f->doAction(ACT_GRAPHNAME, $2, $1, 0, 0);}
          ;
          
attrib_node:  TOK_ID '[' attrib_list ']' {	$$ = $1;	}
         ;

attrib_graph:  TOK_ID '[' attrib_list ']'
		;

attrib_list: attrib 			 
		| attrib_list ',' attrib 
		;
attrib: TOK_ID '=' TOK_ID		{$$ = f->doAction(ACT_ATTRIBUTE, $1, $3, 0, 0)};
        | TOK_ID				{$$ = f->doAction(ACT_ATTRIBUTE, (Linkable*)"LEAF_FLAGS", $1, 0, 0)};
        ;
%%


void say(const char *s)
{
    printf("%s", s);
}


extern int main(int ARGC, char *ARGV[]);
