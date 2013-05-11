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
