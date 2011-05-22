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
	LINK_DIRECTED,
	LINK_UNDIRECTED
};

class Node;
class Nodeset;
class Edgeset;


class Linkable {
	friend class Byname;

public:
								Linkable		();
	virtual 					~Linkable		();
	virtual		Nodeset& 		GetOutputs		(void)=0;
	virtual		Nodeset& 		GetInputs		(void)=0;
	virtual		Nodeset& 		GetNodes		(void)=0;
	virtual		void 			SetInputs		(Nodeset &)=0;
	virtual		void 			SetOutputs		(Nodeset &)=0;
	virtual		Nodeset& 		GetSources		(void)=0;
	virtual		Nodeset& 		GetSinks		(void)=0;
	virtual		std::ostream & 	operator>> 		(std::ostream &)=0;
	virtual		Edgeset &		GetEdges		(void)=0;
	virtual		Linkable &		Clone			()=0;
	virtual		void 			UpdateIds		()=0;
	virtual		void 			SetAttribute	(std::string s1, std::string s2) {_attributes[s1]=s2;}
	virtual		void 			SetAttribute	(unsigned, std::string s1, std::string s2)=0;
				std::string 	getName			() const {return _name;}
				void 			setName			(std::string _name);
				std::string 	GetAttribute	(std::string s) {return _attributes[s];}
				std::map<std::string, std::string>	GetAttributes() {return _attributes;}

protected:
	std::string			_name;
	std::map<std::string, std::string> _attributes;

private:
	static std::vector<Linkable *> _linkables;
	Linkable *_has(std::string s);
};

namespace leaf {
	Edgeset& link(Linkable&, Linkable&);
	Edgeset& ulink(Linkable&, Linkable&);
	Nodeset& merge(Linkable&, Linkable&);
}


#endif /* LINKABLE_H_ */
