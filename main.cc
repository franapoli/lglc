
#include "Graph.h"
#include "Environment.h"
#include "Frame.h"
#include "CallStack.h"
#include "Function.h"
#include "lex.yy.hh"

//#define DEBUG
#define YYDEBUG 1
extern int yydebug;

FILE *fid=0;

Environment &symboltable = *new Environment;
Frame *f=new Frame;
CallStack cs;
const char *protname;


int main(int ARGC, char *ARGV[])
{
	Graph *res;
	f->setEnv(symboltable);

  yydebug=0;

  if(ARGC<2){
	  fprintf(stderr, "No protocol to parse\n");
	  return 1;
  }

  fid=fopen(ARGV[1], "r");
  protname = ARGV[1];

  if(!fid){
	  fprintf(stderr, "Error opening protocol file: %s\n", ARGV[1]);
	  return 1;
  }

  f->setStream(fid);
  cs.push(*f);

  try { res=(Graph *)&(cs.Run()); }
  catch(int)
	  {
	  //fprintf(stderr, "Syntax Error: sorry, I'm a prototype compiler and don't know how to help you further :-(.\n");
	  return(1);
	  }

	res->Visit();
	fprintf(stdout, "Protocol correctly parsed.\n");
	return 0;
}

