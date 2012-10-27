/*
 * Copyright (c) 2012 Francesco Napolitano.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/gpl.html
 * 
 * Contributors:
 *     Francesco Napolitano - initial API and implementation
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
