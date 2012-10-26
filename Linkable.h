/*
 * Linkable.h
 *
 *  Created on: 10/apr/2010
 *      Author: ciccio
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
