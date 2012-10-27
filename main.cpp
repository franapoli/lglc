#include "Graph.h"
#include "Environment.h"
#include "Frame.h"
#include "CallStack.h"
#include "Function.h"
#include "lglc.yy.hh"
#include "AdjMatrix.h"

//#define DEBUG
#define YYDEBUG 1
extern int yydebug;

FILE *fid = 0;

Environment &symboltable = *new Environment;
Frame *f = new Frame;
CallStack cs;
const char *protname;
AdjMatrix *adjmat;

const char *helptext =
		"\
Usage: lglc [options] file\n\
Options:\n\
  -o: output file name\n";

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

	while ((c = getopt(argc, argv, "hvo:")) != -1)
		switch (c) {
		case 'v':
			sprintf(text, "%s Version %d.%d\n", "Leaf Graph Language Compiler",
					0, 1);
			say(text, false);
			break;
		case 'h':
			fprintf(stdout, "%s", helptext);
			return 0;
			break;
		case 'o':
			sprintf(ofile, "%s", optarg);
			break;
		case '?':
			if (optopt == 'o') {
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

