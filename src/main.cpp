/* 
   The MIT License (MIT)

   Copyright (c) 2012-2013 Francesco Napolitano, franapoli@gmail.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/
#include "Graph.h"
#include "Environment.h"
#include "Frame.h"
#include "CallStack.h"
#include "Function.h"
#include "lglc.yy.hh"
#include "AdjMatrix.h"
#include <stdlib.h> //atoi

//#define DEBUG
#define YYDEBUG 1
extern int yydebug;

FILE *fid = 0;

Environment &symboltable = *new Environment;
Frame *f = new Frame;
CallStack cs;
const char *protname;
AdjMatrix *adjmat;
unsigned erroroffset=0;

const char *helptext ="\
Usage: lglc [options] file\n\
Options:\n\
  -h: show this help\n\
  -o: specify output file name\n\
  -v: print version information\n\
  -l: error line number offset\n\n\
";

void say(const char *string, bool iserr = true) {
	char outs[100] = "\0";
	strcat(outs, "lglc: ");
	if (iserr)
		strcat(outs, "error: ");
	strcat(outs, string);
	if (iserr)
		fprintf(stderr, "%s", outs);
	else
		fprintf(stdout, "%s", outs);
}

int main(int argc, char *argv[]) {
	char ofile[100] = "\0";
	int c;
	char text[100];

	opterr = 0;

	while ((c = getopt(argc, argv, "hvol:")) != -1)
		switch (c) {
		case 'v':
			sprintf(text, "%s Version %d.%d\n", "Leaf Graph Language Compiler",
					0, 1);
			say(text, false);
			return 0;
			break;
		case 'h':
			fprintf(stdout, "%s", helptext);
			return 0;
			break;
		case 'o':
			sprintf(ofile, "%s", optarg);
			break;
		case 'l':
		  yylineno += atoi(optarg);
		  break;
		case '?':
			if (optopt == 'o' || optopt == 'l') {
				sprintf(text, "option -%c requires an argument.\n", optopt);
				say(text, false);
				return 0;
			} else if (isprint(optopt)) {
				sprintf(text, "unknown option `-%c'.\n", optopt);
				say(text);
			} else {
				sprintf(text, "unknown option character `\\x%x'.\n", optopt);
				say(text);
			}
			return 1;
		}

	if (argc - optind > 1) {
		say("too many arguments \n");
		return 1;
	} else if (argc - optind < 1) {
		say("no input files \n");
		return 1;
	}

	if (ofile[0] == '\0') {
		strcat(ofile, argv[optind]);
		strcat(ofile, ".dot");
	}
	fid = fopen(argv[optind], "r");
	if (!fid) {
		sprintf(text, "Error opening file: %s\n", argv[optind]);
		say(text);
		return 1;
	}

	protname = argv[optind];
	Graph *res;
	f->setEnv(symboltable);
	yydebug = 0;
	f->setStream(fid);
	cs.push(*f);

	try {
		res = (Graph *) &(cs.Run());
	} catch (int) {
		return (1);
	}

	res->toDot(ofile);
	return 0;
}

