/*
 * Graph.h
 *
 *  Created on: 08/apr/2010
 *      Author: ciccio
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Nodeset.h"
#include "Edgeset.h"
#include "AdjMatrix.h"

class Graph: public Linkable {

public:
	Graph();
	Graph(Nodeset &, Edgeset&);
	virtual ~Graph();
	void mergeWith(Graph &);
	void destroy(void);
	Nodeset& getOutputs(void);
	Nodeset& getInputs(void);
	AdjMatrix& visit(void);
	ostream& operator>>(std::ostream &);
	Edgeset& getEdges(void) {
		return _E;
	}
	Edgeset& addEdges(Edgeset &e, bool copyid = false);
	void addNodes(Nodeset &e) {
		_V.addNodes(e);
	}
	Nodeset& getNodes(void) {
		return _V;
	}
	void setInputs(Nodeset &);
	void setOutputs(Nodeset &);
	Nodeset& getSources(void);
	Nodeset& getSinks(void);
	virtual operator Nodeset();
	void addNode(Node &);
	Node& findNode(unsigned id) {
		return _V.findNode(id);
	}
	Nodeset& getOutNodes(Node &);
	virtual Linkable &clone() {
		Graph &g = *new Graph;
		g = *this;
		return g;
	}
	void updateIds();
	void setAttribute(std::string s1, std::string s2);
	void setAttribute(unsigned n, std::string s1, std::string s2) {
		_V.setAttribute(n, s1, s2);
	}
	void toDot(std::string fname);
	Edge* findEdge(unsigned id1, unsigned id2);
	Edgeset& getEdgesRooted(Linkable&);
	void resetVisited(void);

private:
	Edgeset _E;
	Nodeset _V;
};

#endif /* GRAPH_H_ */
