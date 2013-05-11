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
#include "AdjMatrix.h"
#include "Linkable.h"
#include <limits>

Graph::Graph() {
	// TODO Auto-generated constructor stub

}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

Graph::Graph(Nodeset &n, Edgeset&e) {
	_E.addEdges(e);
	_V.addNodes(n);
}

void Graph::mergeWith(Graph & graph) {
}

void Graph::destroy(void) {
}

void Graph::toDot(std::string fname) {
	FILE *fid;
	fid = fopen((string(fname)).c_str(), "w");
	if (!fid) {
		fprintf(stderr, "%s", "Error opening output file.\n");
		throw 1;
	}
	string attr_string = "";
	std::map<std::string, std::string>::iterator mapit;
	std::map<std::string, std::string> attribs;

	fprintf(fid, "digraph G {\n");
	fprintf(fid, "node [shape=box, style=rounded];\n");
	fprintf(fid, "rankdir=LR;\n");
	Nodeset::iterator i, j;

	for (i = _V.begin(); i != _V.end(); ++i) {
		attr_string = "[ label = ";
		attr_string += i->getName();

		attribs = i->GetAttributes();

		for (mapit = attribs.begin(); mapit != attribs.end(); mapit++) {
			attr_string += ", ";
			attr_string += (mapit->first).c_str();
			attr_string += " = ";
			attr_string += (mapit->second).c_str();
		}
		attr_string += "] ";

		fprintf(fid, "%d %s;\n", i->getId(), attr_string.c_str());
		//fprintf(fid, "%d [ label = \"%s\", color = \"%s\" ];\n", i->getId(), i->getName().c_str(), i->GetAttribute("color").c_str());

	}

	// Sorting edges by id in O(n^2). This is good enough
	// for small graphs.
	Edgeset::iterator e;
	unsigned minid, lastminid;
	lastminid = 0;
	Edgeset::iterator minedge;
	while (true) {
		minid = std::numeric_limits<unsigned>::max();
		for (e = _E.begin(); e != _E.end(); e++)
			if (e->getId() < minid && e->getId() > lastminid) {
				minid = e->getId();
				minedge = e;
			}
		if (minid == std::numeric_limits<unsigned>::max())
			break;
		lastminid = minid;
		fprintf(fid, "%d->%d [id=%u];\n", minedge->getSrcNodeId(),
				minedge->getDstNodeId(), minedge->getId());
	}

	fprintf(fid, "}\n");
	fclose(fid);
}

Edge *Graph::findEdge(unsigned id1, unsigned id2) {
	Edgeset::iterator i;

	for (i = _E.begin(); i != _E.end(); i++)
		if (i->getSrcNodeId() == id1 && i->getDstNodeId() == id2)
			return &*i;

	return 0;
}

AdjMatrix &Graph::visit(void) {
	Node i;
	Nodeset::iterator j;
	Nodeset stack;

	Nodeset *ns;

	unsigned maxid = 0;
	Nodeset::iterator ni;
	for (ni = _V.begin(); ni != _V.end(); ni++)
		if (ni->getId() > maxid)
			maxid = ni->getId();

	AdjMatrix &adjmat = *new AdjMatrix(maxid + 1, maxid + 1);

	stack.addNodes(getSources());
//cout <<endl << "Visiting " << getName() << endl;
	unsigned ij = 0;

	while (!stack.empty()) {
		i = stack.back();
		//i >> cout << endl;
		stack.pop_back();

		_V.findNode(i.getId()).visit();
		ns = &getOutNodes(i);
		//i >> cout;
		//cout << " ha figli:" << endl;
		//*ns >> cout;

		for (j = ns->begin(); j != ns->end(); j++, ij++) {
			if (!j->isVisited()) {
				stack.addNode(*j);
			}
			adjmat.set(i.getId(), j->getId());
			//cout << "Added (" << i.getId() << ", " << j->getId() << ")"<<endl;
		}

	}
//adjmat >> cout;
	return (adjmat);
//cout << "dot made... all done!" << endl;

}

ostream& Graph::operator>>(std::ostream &str) {
	str << "Graph(" << _name << ")" << endl << "{" << endl;
	_V >> (str);
	_E >> (str);
	str << "}" << endl;
	return str;
}

void Graph::setInputs(Nodeset &in) {
	Nodeset::iterator i;

	for (i = _V.begin(); i != _V.end(); ++i)
		if (in.has(i->getId())) {
			i->setIsinput(true);
			i->setInConnector(in.findNode(i->getId()).getInConnector());
		} else
			i->setIsinput(false);
}

void Graph::setOutputs(Nodeset &o) {
	Nodeset::iterator i;

	for (i = _V.begin(); i != _V.end(); ++i)
		if (o.has(i->getId())) {
			i->setIsoutput(true);
			i->setOutConnector(o.findNode(i->getId()).getOutConnector());
		} else
			i->setIsoutput(false);
}

Nodeset& Graph::getInputs(void) {
	Nodeset *ns = new Nodeset;
	Nodeset::iterator i;

	for (i = _V.begin(); i != _V.end(); ++i) {
		if (i->getIsinput())
			ns->addNode(*i);
	}

	return *ns;
}

Nodeset& Graph::getOutputs(void) {
	Nodeset *ns = new Nodeset;
	Nodeset::iterator i;

	for (i = _V.begin(); i != _V.end(); ++i) {
		if (i->getIsoutput())
			ns->addNode(*i);
	}

	return *ns;
}

Nodeset& Graph::getSinks(void) {
	Nodeset &ns = (*new Nodeset());
	Nodeset::iterator i;

	for (i = _V.begin(); i != _V.end(); ++i) {
		if (i->isSink())
			ns.push_back(*i);
	}
	return ns;
}

Nodeset &Graph::getOutNodes(Node &n) {
	Nodeset &ns = *new Nodeset;
	Edgeset::iterator i;

	for (i = _E.begin(); i != _E.end(); i++)
		if (i->getSrcNodeId() == n.getId())
			ns.push_back(_V.findNode(i->getDstNodeId()));
	return ns;
}

Nodeset& Graph::getSources(void) {
	Nodeset &ns = (*new Nodeset());
	Nodeset::iterator i;

	for (i = _V.begin(); i != _V.end(); ++i) {
		if (i->isSource())
			ns.push_back(*i);
	}
	return ns;
}

Graph::operator Nodeset() {

	cerr << "this was never tested! (Graph::operator Nodeset)";
	return _V;
}

void Graph::addNode(Node &n) {
	_V.addNode(n);
}

Edgeset &Graph::addEdges(Edgeset &e, bool copyid) {
	Node *n1, *n2;
	Edgeset::iterator i;
	Edgeset &newedges = *new Edgeset();

	for (i = e.begin(); i < e.end(); i++) {
		n1 = &_V.findNode(i->getSrcNodeId());
		n2 = &_V.findNode(i->getDstNodeId());
		if (copyid)
			newedges.push_back(
					_E.addEdge(n1->getId(), n2->getId(), i->getId()));
		else
			newedges.push_back(_E.addEdge(n1->getId(), n2->getId()));

		n1->_issink = false;
		n2->_issource = false;
	}

	return newedges;
}

void Graph::updateIds() {
	Nodeset::iterator i;
	Edgeset::iterator e;
	unsigned id;

	for (i = _V.begin(); i != _V.end(); i++) {
		id = Node::newId();

		for (e = _E.begin(); e != _E.end(); e++) {
			if (e->getSrcNodeId() == i->getId())
				e->setSrcNodeId(id);
			if (e->getDstNodeId() == i->getId())
				e->setDstNodeId(id);
		}
		i->setId(id);
	}
}

void Graph::setAttribute(std::string s1, std::string s2) {
	Linkable::setAttribute(s1, s2);
	Nodeset::iterator i;
	for (i = _V.begin(); i != _V.end(); i++)
		i->setAttribute(s1, s2);
}

void Graph::resetVisited(void) {
	Nodeset::iterator i;
	for (i = _V.begin(); i != _V.end(); i++)
		i->_visited = false;
}

/* Gets all edges in the subtree rooted in Node n. This is required
 * to update edge ids while building the graph in Frame (ACT_FORK).
 * This is partly copy-pasted from Visit (which is now unused).
 */
Edgeset& Graph::getEdgesRooted(Linkable& n) {
	Node i;
	Nodeset::iterator j;
	Nodeset stack;
	Edgeset &es = *new Edgeset;
	unsigned edgeid;
	Nodeset *ns;

	resetVisited();

	stack.addNodes(n.getNodes());
	unsigned ij = 0;

	while (!stack.empty()) {
		i = stack.back();
		stack.pop_back();

		i.visit();
		ns = &getOutNodes(i);

		for (j = ns->begin(); j != ns->end(); j++, ij++) {
			if (!j->isVisited())
				stack.addNode(*j);
			edgeid = findEdge(i.getId(), j->getId())->getId();
			es.addEdge(i.getId(), j->getId(), edgeid);
		}

	}

	resetVisited();
	return es;
}
