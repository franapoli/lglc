/*
 * Graph.cpp
 *
 *  Created on: 08/apr/2010
 *      Author: ciccio
 */

#include "Graph.h"
#include "AdjMatrix.h"


Graph::Graph() {
	// TODO Auto-generated constructor stub

}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

Graph::Graph(Nodeset &n, Edgeset&e){
_E.AddEdges(e);
_V.AddNodes(n);
}

void Graph::MergeWith(Graph & graph)
{
}


void Graph::FindNode(string string)
{
}



void Graph::Destroy(void)
{
}


AdjMatrix &Graph::Visit(void)
{
Node i;
Nodeset::iterator j;
Nodeset stack;

Nodeset *ns;

unsigned maxid=0;
Nodeset::iterator ni;
for(ni=_V.begin();ni!=_V.end();ni++)
	if(ni->getId() > maxid)
		maxid=ni->getId();

AdjMatrix &adjmat = *new AdjMatrix(maxid+1, maxid+1);

stack.AddNodes(GetSources());
//cout <<endl << "Visiting " << getName() << endl;
unsigned ij=0;

while(!stack.empty()){
	i=stack.back();
	//i >> cout << endl;
	stack.pop_back();

	_V.findNode(i.getId()).Visit();
	ns=&GetOutNodes(i);
	//i >> cout;
	//cout << " ha figli:" << endl;
	//*ns >> cout;

	for(j=ns->begin(); j!=ns->end(); j++, ij++) {
		if(!j->isVisited()) {
			stack.AddNode(*j);
		}
			adjmat.Set(i.getId(), j->getId());
			//cout << "Added (" << i.getId() << ", " << j->getId() << ")"<<endl;
	}

}
//adjmat >> cout;
return(adjmat);
//cout << "dot made... all done!" << endl;

}

ostream& Graph::operator>>(std::ostream &str){
	str << "Graph(" << _name << ")" << endl << "{" << endl;
		_V >> (str);
		_E >> (str);
		str << "}"<< endl;
		return str;
}


void Graph::SetInputs(Nodeset &in)
{
	Nodeset::iterator i;

	for (i=_V.begin(); i!=_V.end(); ++i)
		if(in.has(i->getId())){
			i->setIsinput(true);
			i->setInConnector(in.findNode(i->getId()).getInConnector());
		}
		else i->setIsinput(false);
}


void Graph::SetOutputs(Nodeset &o)
{
	Nodeset::iterator i;

	for (i=_V.begin(); i!=_V.end(); ++i)
		if(o.has(i->getId())) {
			i->setIsoutput(true);
			i->setOutConnector(o.findNode(i->getId()).getOutConnector());
		}
		else i->setIsoutput(false);
}


Nodeset& Graph::GetInputs(void)
{
	Nodeset *ns = new Nodeset;
	Nodeset::iterator i;

	for (i=_V.begin(); i!=_V.end(); ++i){
		if(i->getIsinput())
			ns->AddNode(*i);
	}

	return *ns;
}

Nodeset& Graph::GetOutputs(void)
{
	Nodeset *ns = new Nodeset;
	Nodeset::iterator i;

	for (i=_V.begin(); i!=_V.end(); ++i){
		if(i->getIsoutput())
			ns->AddNode(*i);
	}

	return *ns;
}

Nodeset& Graph::GetSinks(void)
{
	Nodeset &ns = (*new Nodeset());
	Nodeset::iterator i;

	for (i=_V.begin(); i!=_V.end(); ++i){
		if(i->isSink())
			ns.push_back(*i);
	}
	return ns;
}




Nodeset &Graph::GetOutNodes(Node &n){
	Nodeset &ns = *new Nodeset;
	Edgeset::iterator i;

	for(i=_E.begin(); i!=_E.end(); i++)
		if(i->getSrcNodeId()==n.getId())
			ns.push_back(_V.findNode(i->getDstNodeId()));
	return ns;
}



Nodeset& Graph::GetSources(void)
{
	Nodeset &ns = (*new Nodeset());
	Nodeset::iterator i;

	for (i=_V.begin(); i!=_V.end(); ++i){
		if(i->isSource())
			ns.push_back(*i);
	}
	return ns;
}

Graph::operator Nodeset(){

cerr << "unimplemented";
}

void Graph::AddNode(Node &n){
	_V.AddNode(n);
}


void Graph::AddEdges(Edgeset &e)
{
	Node *n1, *n2;
	Edgeset::iterator i;
	Edge *ne;

	for(i = e.begin(); i<e.end(); i++) {
		n1 = &_V.findNode(i->getSrcNodeId());
		n2 = &_V.findNode(i->getDstNodeId());
		ne=&_E.AddEdge(n1->getId(), n2->getId());
		n1->_issink=false;
		n2->_issource=false;
	}
}


void Graph::UpdateIds()
{
Nodeset::iterator i;
Edgeset::iterator e;
unsigned id;

for(i=_V.begin(); i!=_V.end(); i++){
	id = Node::newId();

	for(e=_E.begin(); e!=_E.end(); e++){
		if(e->getSrcNodeId() == i->getId())
			e->setSrcNodeId(id);
		if(e->getDstNodeId() == i->getId())
			e->setDstNodeId(id);
	}
i->setId(id);
}
}

void Graph::SetAttribute(std::string s1, std::string s2)
{
	Linkable::SetAttribute(s1,s2);
	Nodeset::iterator i;
	for(i=_V.begin(); i!=_V.end(); i++)
		i->SetAttribute(s1, s2);
}
