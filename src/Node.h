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

#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>
#include "Linkable.h"

using namespace std;

class Node: public Linkable {
	friend class Edge;
	friend class Graph;
public:
	Node();
	Node(string name);
	virtual ~Node();

	bool isVisited(void) {
		return _visited;
	}

	void visit(void);
	bool isSink() const {
		return _issink;
	}

	bool isSource() const {
		return _issource;
	}

	unsigned getId() {
		return _id;
	}

	ostream& operator>>(std::ostream &);
	Edgeset &getEdges(void);
	string getInConnector() const {
		return _inconnector;
	}

	string getOutConnector() const {
		return _outconnector;
	}

	void setInConnector(string _inconn) {
		_inconnector = _inconn;
	}

	void setOutConnector(string _outconn) {
		_outconnector = _outconn;
	}

	bool getIsinput() const {
		return _isinput;
	}

	bool getIsoutput() const {
		return _isoutput;
	}

	void setIsinput(bool _isinput) {
		this->_isinput = _isinput;
	}

	void setIsoutput(bool _isoutput) {
		this->_isoutput = _isoutput;
	}
	virtual Linkable &clone() {
		Node &n = *new Node;
		n = *this;
		return n;
	}

	unsigned static newId() {
		return _lastid++;
	}

	void setId(unsigned i) {
		_id = i;
	}
	void updateIds() {
		setId(newId());
	}
	void setAttribute(std::string s1, std::string s2) {
		_attributes[s1] = s2;
	}

private:
	void setAttribute(unsigned, std::string s1, std::string s2) {
		_attributes[s1] = s2;
	}
	;
	inline Nodeset& getOutputs(void);
	inline Nodeset& getInputs(void);
	inline Nodeset& getNodes(void);
	inline void setInputs(Nodeset &);
	inline void setOutputs(Nodeset &);
	inline Nodeset& getSources(void);
	inline Nodeset& getSinks(void);

	bool _visited;
	unsigned _id;
	static unsigned _lastid;
	bool _issink;
	bool _issource;
	bool _isinput;
	bool _isoutput;
	std::string _inconnector;
	std::string _outconnector;

};

#endif /* NODE_H_ */
