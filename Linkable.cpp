/*è
 * Linkable.cpp
 *
 *  Created on: 10/apr/2010
 *      Author: ciccio
 */

#include "Linkable.h"
#include "Edgeset.h"
#include "Nodeset.h"
#include <map>
//#include <assert>

vector <Linkable *> Linkable::_linkables;

Linkable::Linkable() {
	// TODO Auto-generated constructor stub
}


Linkable::~Linkable() {
	// TODO Auto-generated destructor stub
}


void Linkable::setName(std::string _name)
{
	this->_name = _name;
	_linkables.push_back(this);
}


Linkable *Linkable::_has(std::string s) {
	std::vector<Linkable *>::iterator i=_linkables.begin();

	for(;i!=_linkables.end(); i++)
		if((*i)->getName()==s)
			return *i;

	return 0;
}


namespace leaf {
Edgeset & link(Linkable & l1, Linkable & l2)
{
	Nodeset &l1o = l1.GetNodes();
	Nodeset &l2i = l2.GetNodes();
	map<std::string, Nodeset > dbi;
	map<std::string, Nodeset > dbo;
	Nodeset::iterator i;
	map<std::string, Nodeset >::iterator dbiter;
	map<std::string, Nodeset >::iterator found;
	Edgeset *E = new Edgeset;
	bool foundin = false;
	bool foundout = false;
	std::string s;

	//cout << "Linking" << endl;


	for(i=l1o.begin(); i!=l1o.end(); i++){
		s = i->getOutConnector();
		if(i->getOutConnector()!="") {
		    //cout << "Found out-connector:" << s << endl;
			foundout = true;
			dbo[i->getOutConnector()].AddNode(*i);
		}
	}

	for(i=l2i.begin(); i!=l2i.end(); i++){
		s = i->getInConnector();
		if(i->getInConnector()!=""){
		    //cout << "Found in-connector:" << s << endl;
			foundin = true;
			dbi[i->getInConnector()].AddNode(*i);
		}
	}


	if(foundin || foundout){
	for(dbiter = dbo.begin(); dbiter != dbo.end(); dbiter++){
		found = dbi.find(dbiter->first);
		if(found!=dbi.end())
			E->AddEdges(*new Edgeset(dbiter->second, found->second));
	}
	}


	else E->AddEdges(*new Edgeset(l1.GetOutputs(), l2.GetInputs()));

	return *E;
}



Edgeset& ulink(Linkable & l1, Linkable & l2)
{
Edgeset& e1 = (*new Edgeset(l1.GetOutputs(), l2.GetInputs()));
Edgeset& e2 = (*new Edgeset(l2.GetOutputs(), l1.GetInputs()));

e1.AddEdges(e2);
e2.~Edgeset();

return e1;
}

Nodeset& merge(Linkable& l1, Linkable& l2)
{
Nodeset& n1 = (*new Nodeset(l1.GetNodes()));

n1.AddNodes(l2.GetNodes());
return n1;
}

}



