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

#include "Nodeset.h"
#include "Node.h"

Nodeset::Nodeset() {
}

Nodeset::~Nodeset() {
// TODO Auto-generated destructor stub
}

void Nodeset::addNodes(Nodeset & ns) {
	Nodeset::iterator i;
	for (i = ns.begin(); i != ns.end(); i++)
		if (!has(i->getId()))
			push_back(*i);
}

void Nodeset::addNode(Node &n) {
	push_back(n);
}

Nodeset::Nodeset(Node & node) {
	addNode(node);
}

Nodeset::Nodeset(const Nodeset & ns) {
	addNodes(const_cast<Nodeset &>(ns).getNodes());
}

void Nodeset::addNewNode(string label) {
}

Edgeset &Nodeset::link(Nodeset &nodeset) {
	Edgeset *n;
	n = new Edgeset(*this, nodeset);
	return *n;
}

std::ostream& Nodeset::operator>>(std::ostream &str) {
	Nodeset::iterator i;
	str << "   NS {" << endl;
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

bool Nodeset::has(string name) {
	Nodeset::iterator i;
	for (i = begin(); i != end(); i++)
		if (i->getName() == name)
			return true;
	return false;
}

bool Nodeset::has(unsigned id) {
	Nodeset::iterator i;
	for (i = begin(); i != end(); i++)
		if (i->getId() == id)
			return true;
	return false;
}

Node &Nodeset::findNode(unsigned id) {
	Nodeset::iterator i;
	for (i = begin(); i != end(); i++)
		if (i->getId() == id)
			return *i;

	throw 10;
}

#include "Graph.h"
/*Nodeset::operator Graph()
 {
 Graph *g = new Graph;
 g->_V = *this;
 g->SetInputs(*this);
 g->SetOutputs(*this);
 g->setName(this->_name);
 }
 */

void Nodeset::setInputs(Nodeset &in) {
	Nodeset::iterator i;

	for (i = begin(); i != end(); ++i) {
		if (in.has(i->getId()))
			i->setIsinput(true);
		else
			i->setIsinput(false);
	}

}

void Nodeset::setOutputs(Nodeset &o) {
	Nodeset::iterator i;

	for (i = begin(); i != end(); ++i) {
		if (o.has(i->getId()))
			i->setIsoutput(true);
		else
			i->setIsoutput(false);
	}

}

void Nodeset::setAttribute(unsigned id, std::string s1, std::string s2) {
	Nodeset::iterator i;

	for (i = begin(); i != end(); ++i) {
		if (i->getId() == id)
			i->setAttribute(s1, s2);
	}

	Linkable::setAttribute(s1, s2);
}

