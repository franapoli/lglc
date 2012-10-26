/*
 * Nodeset.h
 *
 *  Created on: 01/apr/2010
 *      Author: ciccio
 */

#ifndef NODESET_H_
#define NODESET_H_

#include "Node.h"
#include <vector>
#include "Edgeset.h"

using namespace std;

class Nodeset: public Linkable, public std::vector<Node> {
	friend class Edgeset;
	friend class Graph;
	friend class AdjMatrix;
	friend Edgeset & leaf::link(Linkable & l1, Linkable & l2);

public:
	Nodeset();
	Nodeset(Node &);
	Nodeset(const Nodeset &);
	virtual ~Nodeset();
	void addNode(Node &);
	void addNodes(Nodeset &);
	void addNewNode(string label);
	Edgeset& link(Nodeset &);
	std::ostream & operator>>(std::ostream &);
	virtual Edgeset &getEdges(void) {
		return *new Edgeset();
	}
	bool has(string name);
	bool has(unsigned id);
	Node &findNode(unsigned id);
	//operator class Graph();
	virtual Linkable &clone() {
		Nodeset &ns = *new Nodeset;
		ns = *this;
		return ns;
	}
	//vector<Node>	_nodes;
	void updateIds() {
		Nodeset::iterator i;
		for (i = begin(); i != end(); i++)
			i->updateIds();
	}
	void setAttribute(unsigned, std::string s1, std::string s2);

	Nodeset& getOutputs(void) {
		return *this;
	}
	Nodeset& getInputs(void) {
		return *this;
	}
	Nodeset& getNodes(void) {
		return *this;
	}
	void setInputs(Nodeset &);
	void setOutputs(Nodeset &);

private:
	Nodeset& getSources(void) {
		return *this;
	}
	Nodeset& getSinks(void) {
		return *this;
	}
};

#endif /* NODESET_H_ */
