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

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdio.h>
#include <vector>
#include <assert.h>

extern const char *protname;
extern FILE *yyin;
extern int yyparse();

typedef enum ACTION_TYPE {
	ACT_NODE,
	ACT_COMMA,
	ACT_ARROW,
	ACT_PARENTHESIS,
	ACT_MERGE,
	ACT_FORK,
	ACT_DIAGRAM,
	ACT_GRAPHNAME,
	ACT_REFERENCE,
	ACT_CHAINASFORKSON,
	ACT_CONNECTOR,
	ACT_ATTRIBUTE,
	ACT_FUNCTDEF,
	ACT_GROUP
} ACTION_TYPE;

enum ACTION_FLAG {
	ACT_FLAG_NO, ACT_FLAG_HASH
};

extern class Graph *g;
extern class Environment &symboltable;
extern class Frame *f;
extern class CallStack cs;

#endif /* GLOBALS_H_ */
