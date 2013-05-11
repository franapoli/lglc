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

#ifndef LINKABLE_H_
#define LINKABLE_H_

#include <iostream> //for debug
#include <fstream>
#include <string>
#include <vector>
#include <map>

enum LINK_TYPE {
	LINK_DIRECTED, LINK_UNDIRECTED
};

class Node;
class Nodeset;
class Edgeset;

class Linkable {
	friend class Byname;

public:
	Linkable();
	virtual ~Linkable();
	virtual Nodeset& getOutputs(void)=0;
	virtual Nodeset& getInputs(void)=0;
	virtual Nodeset& getNodes(void)=0;
	virtual void setInputs(Nodeset &)=0;
	virtual void setOutputs(Nodeset &)=0;
	virtual Nodeset& getSources(void)=0;
	virtual Nodeset& getSinks(void)=0;
	virtual std::ostream & operator>>(std::ostream &)=0;
	virtual Edgeset & getEdges(void)=0;
	virtual Linkable & clone()=0;
	virtual void updateIds()=0;
	virtual void setAttribute(std::string s1, std::string s2) {
		_attributes[s1] = s2;
	}
	virtual void setAttribute(unsigned, std::string s1, std::string s2)=0;
	std::string getName() const {
		return _name;
	}
	void setName(std::string _name);
	std::string getAttribute(std::string s) {
		return _attributes[s];
	}
	std::map<std::string, std::string> GetAttributes() {
		return _attributes;
	}
	void switchEdgeIdOrder(Edgeset &, Edgeset &);

protected:
	std::string _name;
	std::map<std::string, std::string> _attributes;

private:
	static std::vector<Linkable *> _linkables;
	Linkable *has(std::string s);
};

namespace leaf {
Edgeset& link(Linkable&, Linkable&);
Edgeset& ulink(Linkable&, Linkable&);
Nodeset& merge(Linkable&, Linkable&);
}

#endif /* LINKABLE_H_ */
