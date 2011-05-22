/*
 * nodes.h
 *
 *  Created on: 13/feb/2010
 *      Author: ciccio
 */

#ifndef NODES_H_
#define NODES_H_
//typedef struct node;

#define TO_CHAIN_HEAD		1
#define TO_CHAIN_TAIL		0

#define GRAPH_VISIT_BFS 	0
#define GRAPH_VISIT_DFS 	1

#define NODE_TYPE_LEAF 	0
#define NODE_TYPE_FORK	1
#define NODE_TYPE_MERGE	2
#define NODE_TYPE_COMPLEXCHAIN	2

typedef char** MAT;

typedef struct s_node{
	int id;
	char label[20];
	struct s_nodechain *outedges;
	struct s_nodechain *inedges;
	int numvisits;
	char is_what;
} NODE;

typedef struct s_nodechain{
	struct s_nodering *head;
	struct s_nodering *tail;
	struct s_nodechain *leftarroperand;
} NODECHAIN;

typedef struct s_nodering{
	NODE *actualnode;
	struct s_nodering *nextring;
} NODERING;


void deletenodechain(NODECHAIN *n);
void graphvisit(NODECHAIN *startnodes, char strategy);
void initnode(NODE *n);
NODE * newnode(void);
NODE * attachtonewnode(NODE *src);
void addnodetochain(NODECHAIN *nc, NODE *n, char head);
void linknodes(NODE *src, NODE *dst);
void initnodechain(NODECHAIN *nc);
NODECHAIN * newnodechain(void);
void visitnode(NODE *n);
char hasinedges(NODE *n);
void dumpmat(MAT mat, int n, int m);
void adjmat2dot(MAT mat, int n, int m);
NODE *getnode(NODECHAIN *nc, int id);
NODE *findnode(NODECHAIN *nc, const char *label);
void getleaves(NODE *n, NODECHAIN *leaves);
void linknodeleaves(NODE *n1, NODE *n2);
void linkchains(NODECHAIN *nc1, NODECHAIN *nc2);
void clearchain(NODECHAIN **nc);

extern NODECHAIN *allnodes;

#endif /* NODES_H_ */

