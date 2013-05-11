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

