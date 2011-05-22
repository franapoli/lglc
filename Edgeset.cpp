/*
 * Edgeset.cpp
 *
 *  Created on: 08/apr/2010
 *      Author: ciccio
 */

#include "Edgeset.h"
#include "Nodeset.h"
#include <fstream> //debug

Edgeset::Edgeset() {
	// TODO Auto-generated constructor stub

}

Edgeset::Edgeset(Nodeset & ns1, Nodeset & ns2)
{
	Nodeset::iterator i;
	Nodeset::iterator j;


	for(i=ns1.begin();
			i!=ns1.end(); i++)
		for(j=ns2.begin();
				j!=ns2.end(); j++)
			AddEdge(i->getId(), j->getId());
}

Edgeset::~Edgeset() {
	// TODO Auto-generated destructor stub
}

/*Edge &Edgeset::AddEdge(Node & n1, Node & n2)
{
	Edge *e = new Edge(n1, n2);
	push_back(*e);
	return *e;
}*/

Edge &Edgeset::AddEdge(unsigned int id1, unsigned int id2)
{
	Edge *e = new Edge(id1, id2);
	if(!has(id1, id2) )
		push_back(*e);
	return *e;
}

void Edgeset::AddEdges(Edgeset & es)
{
	Edgeset::iterator i;
	for(i=es.begin(); i!=es.end(); i++)
			AddEdge(i->getSrcNodeId(), i->getDstNodeId());
}

/*Nodeset & Edgeset::GetOutNodes(Node & node)
{
Nodeset *innodes = new Nodeset;

	Edgeset::iterator i;
	for(i=begin(); i !=end(); i++)
		if(i->getSrcNode().getId() == node.getId())
			innodes->AddNode(i->getDstNode());

	return *innodes;
}*/

/*Nodeset & Edgeset::GetInNodes(Node & node)
{
Nodeset *innodes = new Nodeset;

	Edgeset::iterator i;
	for(i=begin(); i !=end(); i++)
		if(i->getDstNode().getName() == node.getName())
			innodes->AddNode(i->getSrcNode());

	return *innodes;
}*/


ostream & Edgeset::operator>>(std::ostream &str){
	Edgeset::iterator i;
	str << "   ES {" << endl;
	if(empty()) {
		str << "      <empty>" << endl << "      }"<<endl;
		return str;
	}
		for(i=begin();  i!=end()-1; i++) {
			cout << "      ";
			*i >> str << endl;
		}
		cout << "      ";
		*i >> str << endl << "      }" << endl;
		return str;

}



bool Edgeset::has(unsigned iid, unsigned jid){
	Edgeset::iterator i;
	for(i=begin(); i!=end(); i++)
		if( (i->getSrcNodeId() == iid) &&
				(i->getDstNodeId() == jid))
			return true;
	return false;
}



