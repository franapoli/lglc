/*
 * Node.cpp
 *
 *  Created on: 01/apr/2010
 *      Author: ciccio
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

