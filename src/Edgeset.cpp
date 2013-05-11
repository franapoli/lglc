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


#include "Edgeset.h"
#include "Nodeset.h"
#include <fstream> //debug
Edgeset::Edgeset() {
	// TODO Auto-generated constructor stub

}

Edgeset::Edgeset(Nodeset & ns1, Nodeset & ns2) {
	Nodeset::iterator i;
	Nodeset::iterator j;

	for (i = ns1.begin(); i != ns1.end(); i++)
		for (j = ns2.begin(); j != ns2.end(); j++)
			addEdge(i->getId(), j->getId());
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

Edge &Edgeset::addEdge(unsigned int id1, unsigned int id2) {
	Edge *e = new Edge(id1, id2);
	if (!has(id1, id2))
		push_back(*e);
	return *e;
}

Edge &Edgeset::addEdge(unsigned int id1, unsigned int id2, unsigned id) {
	Edge *e = new Edge(id1, id2, id);
	if (!has(id1, id2))
		push_back(*e);
	return *e;
}

void Edgeset::addEdges(Edgeset & es, bool copyid) {
	Edgeset::iterator i;
	for (i = es.begin(); i != es.end(); i++)
		if (copyid)
			addEdge(i->getSrcNodeId(), i->getDstNodeId(), i->getId());
		else
			addEdge(i->getSrcNodeId(), i->getDstNodeId());
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

ostream & Edgeset::operator>>(std::ostream &str) {
	Edgeset::iterator i;
	str << "   ES {" << endl;
	if (empty()) {
		str << "      <empty>" << endl << "      }" << endl;
		return str;
	}
	for (i = begin(); i != end() - 1; i++) {
		cout << "      ";
		*i >> str << endl;
	}
	cout << "      ";
	*i >> str << endl << "      }" << endl;
	return str;

}

bool Edgeset::has(unsigned iid, unsigned jid) {
	Edgeset::iterator i;
	for (i = begin(); i != end(); i++)
		if ((i->getSrcNodeId() == iid) && (i->getDstNodeId() == jid))
			return true;
	return false;
}

