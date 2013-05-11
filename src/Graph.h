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
