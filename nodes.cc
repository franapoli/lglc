/*
 * nodes.c
 *
 *  Created on: 13/feb/2010
 *      Author: ciccio
 */

#include "nodes.h"
#include <assert.h>
#include <malloc.h>
#include <stdlib.h> // system()
#include <string.h> // strncmp()
#include <stdio.h>

int lastid=0;
NODECHAIN *allnodes;




MAT *newmat(int n, int m)
{
int i,j;
MAT *adjmat;
adjmat=(char ***)malloc(sizeof(MAT));
(*adjmat)=(char **)malloc(sizeof(char *)*n);

for(i=0;i<n;i++)	{
	(*adjmat)[i]=(char *)malloc(sizeof(char)*m);
	for(j=0;j<m;j++)
		(*adjmat)[i][j]=0;
	}
return adjmat;
}

void initnode(NODE *n)
{
	assert(n);
	n->id=lastid++;
	n->outedges=newnodechain();
	n->inedges=newnodechain();
	n->numvisits=0;
	n->label[0]=0;
	n->is_what=0; // 0 for leaf, 1 for fork, 2 for merge
}

void initnodechain(NODECHAIN *nc)
{
	assert(nc);
	nc->head=0;
	nc->tail=0;
	nc->leftarroperand=nc;
}

NODE * newnode(void)
{
	if(!allnodes)
		allnodes=newnodechain();

	NODE *n = (NODE *)malloc(sizeof(NODE));
	assert(n);
	initnode(n);
	addnodetochain(allnodes, n, TO_CHAIN_TAIL);
	return n;
}

NODECHAIN * newnodechain(void)
{
	NODECHAIN *nc = (NODECHAIN *)malloc(sizeof(NODE));
	assert(nc);
	initnodechain(nc);
	return nc;
}



/*node * newinnode(node *src)
{
	node *n = malloc(sizeof(node));
	assert(n);
	initnode(n);

	src->innodes = addtonodechain(src->innodes, n);

	return n;
}*/

NODE * attachtonewnode(NODE *src)
{
	assert(src);

	NODE *n = (NODE *)malloc(sizeof(NODE));
	assert(n);
	initnode(n);

	addnodetochain(src->outedges, n, 1);
	addnodetochain(n->inedges, src, 1);

	return n;
}


void linknodes(NODE *src, NODE *dst)
{
#ifdef DEBUG
	printf("Linking %s to %s\n", src->label, dst->label);
#endif

	addnodetochain(src->outedges, dst, TO_CHAIN_TAIL);
	addnodetochain(dst->inedges, src, TO_CHAIN_TAIL);
}

void mergesubtrees(NODE *src, NODE *dst1, NODE *dst2)
{
	NODECHAIN *nsrc, *ndst1, *ndst2;

	nsrc=newnodechain();
	ndst1=newnodechain();
	ndst2=newnodechain();
	addnodetochain(nsrc, src, TO_CHAIN_HEAD);

	if(src->is_what == dst1->is_what || dst1->is_what==NODE_TYPE_LEAF)
		addnodetochain(ndst1, dst1, TO_CHAIN_HEAD);
	else
		getleaves(dst1, ndst1);

	if(src->is_what == dst2->is_what || dst2->is_what==NODE_TYPE_LEAF)
		addnodetochain(ndst2, dst2, TO_CHAIN_HEAD);
	else
		getleaves(dst2, ndst2);

	if(src->is_what == NODE_TYPE_FORK) {
		linkchains(nsrc, ndst1);
		linkchains(nsrc, ndst2);
	}
	else {
		linkchains(ndst1, nsrc);
		linkchains(ndst2, nsrc);
	}
}





char hasinedges(NODE *n)
{
assert(n);
assert(n->inedges);

return !!(n->inedges->head);
}

void addnodetochain(NODECHAIN *nc, NODE *n, char where)
{
	assert(nc);

	if(where==TO_CHAIN_HEAD)	{
		NODERING *nr = (NODERING *)malloc(sizeof(NODERING));
		nr->actualnode=n;
		nr->nextring=nc->head;
		if(nc->tail == 0)
			nc->tail=nr;
		nc->head=nr;
	}


	else	{

		if(!nc->head){
			addnodetochain(nc, n, TO_CHAIN_HEAD);
			return;
		}
		NODERING *nr = (NODERING *)malloc(sizeof(NODERING));
		nr->actualnode=n;
		nc->tail->nextring=nr;
		if(nc->head == 0)
			nc->head=nr;
		nc->tail=nr;
	}
}


void addnoderingtochain(NODECHAIN *nc, NODERING *nr, char where)
{
	assert(nc);

	if(where==TO_CHAIN_HEAD)	{
		nr->nextring=nc->head;
		if(nc->tail == 0)
			nc->tail=nr;
		nc->head=nr;
	}


	else	{

		if(!nc->head){
			addnoderingtochain(nc, nr, TO_CHAIN_HEAD);
			return;
		}
		nc->tail->nextring=nr;
		if(nc->head == 0)
			nc->head=nr;
		nc->tail=nr;
	}
}




NODE *popnodefromchain(NODECHAIN *chain)
{
assert(chain);

	if(!chain->head)
		return 0;

	NODERING *oldhead = chain->head;
	NODE *popped = oldhead->actualnode;

	if(chain->head == chain->tail) {
		chain->head=0;
		chain->tail=0;
	}
	else
		chain->head = chain->head->nextring;

	free(oldhead);
	return popped;
}


void graphvisit(NODECHAIN *startnodes, char strategy)
{
#ifdef DEBUG
	printf("Visiting graph\n");
#endif

MAT* adjmat = newmat(lastid, lastid);

NODERING *currnode = startnodes->head;
while(currnode){
	NODERING *currson=currnode->actualnode->outedges->head;

	while(currson) {
		(*adjmat)[currnode->actualnode->id][currson->actualnode->id]=1;
		currson=currson->nextring;
	}

	currnode=currnode->nextring;
}

/*NODECHAIN *tobevisited = startnodes; // startnodes is going to be cleared!
NODE *currnode =0;
NODERING *nodei=0;

do
{
	currnode=popnodefromchain(tobevisited);
	if(!currnode)
		break;
	if(!currnode->numvisits) {
	visitnode(currnode);
	nodei = currnode->outedges->head;

	while(nodei){
		(*adjmat)[currnode->id][nodei->actualnode->id]=1;
		if(strategy == GRAPH_VISIT_BFS)
			addnodetochain(tobevisited, nodei->actualnode, TO_CHAIN_TAIL);
		else
			addnodetochain(tobevisited, nodei->actualnode, TO_CHAIN_HEAD);
		nodei = nodei->nextring;
	}}
} while(currnode);

deletenodechain(tobevisited);*/
dumpmat(*adjmat, lastid, lastid);

}



void visitnode(NODE *n)
{
	fflush(stdout);
	fprintf(stdout,"Visiting: %s\n", n->label);
	n->numvisits=1;
}

void dumpmat(MAT mat, int n, int m)
{
FILE *fid;
int i,j;
fid=fopen("temp.txt", "w");

for(i=0;i<n;i++)
	for(j=0;j<m;j++)
		if(j<m-1)
			fprintf(fid,"%d, ",mat[i][j]);
		else
			fprintf(fid,"%d\n",mat[i][j]);
adjmat2dot(mat,n,m);
system("dot temp.dot -Tpdf -o temp.pdf");
}

void adjmat2dot(MAT mat, int n, int m)
{
	FILE *fid;
	int i,j;
	fid=fopen("temp.dot", "w");

    fprintf(fid, "digraph G {\n");
    fprintf(fid, "node [shape=box, style=rounded];\n");
    fprintf(fid, "rankdir=LR;\n");

    for(i=0; i<n; i++){
    	fprintf(fid, "%d [ label = \"%s\" ];\n", i, getnode(allnodes,i)->label);
    }
    for (i = 0; i<n; i++){              // process ARCs
        for (j = 0; j<m; j++)
        	if(mat[i][j])
                fprintf(fid, "%d->%d;\n", i, j);
    }
    fprintf(fid, "}");
    fclose(fid);
}

NODE *getnode(NODECHAIN *nc, int id)
{
assert(nc);
NODERING *node_i=nc->head;
while(node_i){
	if(node_i->actualnode->id == id)
		return node_i->actualnode;
		node_i=node_i->nextring;
}
return 0;
}

NODE *findnode(NODECHAIN *nc, const char *label)
{
	assert(nc);
	NODERING *node_i=nc->head;
	while(node_i){
		if(!strcmp(node_i->actualnode->label, label))
			return node_i->actualnode;
			node_i=node_i->nextring;
	}
	return 0;

}


void getleaves(NODE *n, NODECHAIN *leaves)
{
NODERING *nodei=0;
NODECHAIN *tobevisited = newnodechain();
addnodetochain(tobevisited, n, TO_CHAIN_HEAD);
NODE *currnode;


char direction=0; //merge or fork depending on has inedges or not

if(n->outedges->head)
	direction=1;

while((currnode=popnodefromchain(tobevisited)))
{

	if(direction)
		nodei = currnode->outedges->head;
	else
		nodei = currnode->inedges->head;

	while(nodei){
		if(direction){
			if(!nodei->actualnode->outedges->head)
				addnodetochain(leaves, nodei->actualnode, TO_CHAIN_HEAD);}
		else{
			if(!nodei->actualnode->inedges->head)
				addnodetochain(leaves, nodei->actualnode, TO_CHAIN_HEAD);}


			addnodetochain(tobevisited, nodei->actualnode, TO_CHAIN_HEAD);
			nodei = nodei->nextring;
		}
}
if(!leaves->head)
	addnodetochain(leaves, n, TO_CHAIN_HEAD);

deletenodechain(tobevisited);
}

void deletenodechain(NODECHAIN *nc){}


void linkchains(NODECHAIN *nc1, NODECHAIN *nc2)
{
NODERING *nr_i, *nr_j;
nr_i=nc1->head;

if(!nc1->head || !nc2->head)
	return;

while(nr_i) {
	nr_j=nc2->head;

	while(nr_j) {
		linknodes(nr_i->actualnode, nr_j->actualnode);
		nr_j=nr_j->nextring;
	}

	nr_i=nr_i->nextring;
}


}


void linknodeleaves(NODE *n1, NODE *n2)
{
	NODECHAIN *nc1, *nc2;
	nc1=newnodechain();
	nc2=newnodechain();

	getleaves(n1, nc1);
	//getleaves(n2, nc2);
	addnodetochain(nc2, n2, TO_CHAIN_HEAD);

	linkchains(nc1, nc2);

	deletenodechain(nc1);
	deletenodechain(nc2);
}
