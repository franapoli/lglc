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

#include "Node.h"
#include <iostream> // JUST FOR DEBUG
#include "Nodeset.h"

class Graph;
unsigned Node::_lastid = 0;

Node::Node() {
	_id = Node::_lastid++;
	_issink = true;
	_issource = true;
	_isinput = true;
	_isoutput = true;
	_outconnector = "";
	_inconnector = "";
	_visited = false;
	setAttribute("color", "black");
}

Node::Node(string name) {
	_id = Node::_lastid++;
	_issink = true;
	_issource = true;
	_isinput = true;
	_isoutput = true;
	_outconnector = "";
	_inconnector = "";
	_visited = false;
	setName(name);
	setAttribute("color", "black");
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

void Node::setInputs(Nodeset &n) {
	*this = n[0];
}
void Node::setOutputs(Nodeset &n) {
	*this = n[0];
}

Nodeset& Node::getSources(void) {
	return *(new Nodeset(*this));
}

Nodeset& Node::getSinks(void) {
	return *(new Nodeset(*this));
}

inline Nodeset& Node::getInputs(void) {
	return *(new Nodeset(*this));
}

inline Nodeset& Node::getOutputs(void) {
	return *(new Nodeset(*this));
}

void Node::visit(void) {
	//* this >> cout;
	_visited = true;
}

inline Nodeset& Node::getNodes(void) {
	return (*new Nodeset(*this));
}

ostream& Node::operator>>(std::ostream &str) {
	std::map<std::string, std::string>::iterator mapit;
	std::map<std::string, std::string> attribs;
	string attr_string;

	attribs = GetAttributes();
	for (mapit = attribs.begin(); mapit != attribs.end(); mapit++) {
		attr_string += ", ";
		attr_string += (mapit->first).c_str();
		attr_string += " = ";
		attr_string += (mapit->second).c_str();
	}

	str << "N(" << _id << ", ";
	str << "\"" << getName() << "\"";
	str << ", " << _inconnector;
	str << ", " << _outconnector;
	str << (_issink ? ", Snk" : "");
	str << (_issource ? ", Src" : "");
	str << (_isinput ? ", In" : "");
	str << (_isoutput ? ", Out" : "");
	//str << ", " << _attributes["color"];
	str << ", " << attr_string;
	str << ")";

	return str;
}

/* Design conflict?
 * Node has no edge, but we need a GetEdges on a generic Linkable
 */
Edgeset &Node::getEdges(void) {
	return *new Edgeset();
}

