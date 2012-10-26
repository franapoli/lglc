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

vector<Linkable *> Linkable::_linkables;

Linkable::Linkable() {
	// TODO Auto-generated constructor stub
}

Linkable::~Linkable() {
	// TODO Auto-generated destructor stub
}

void Linkable::setName(std::string _name) {
	this->_name = _name;
	_linkables.push_back(this);
}

void Linkable::switchEdgeIdOrder(Edgeset& e1, Edgeset& e2) {
	/*Make so that all ids in l1 will come after ids in l2. This is need
	 * to allow subtrees containing "->" to have edges with higher ids than
	 * the tree root.
	 * Reusing ids would be a good idea, but at the moment it is not necessary, so
	 * ids from e1 will just be shifted after e2.
	 * I'll just take care of preserving order in e2.
	 */

	Edgeset::iterator i;
	unsigned maxid = 0;

	for (i = e2.begin(); i != e2.end(); i++)
		if (i->getId() > maxid)
			maxid = i->getId();
	;

	unsigned minid = -1;
	for (i = e1.begin(); i != e1.end(); i++)
		if (i->getId() < minid)
			minid = i->getId();
	;

	if (minid > maxid)
		//nothing to be done
		return;

	unsigned diff;
	diff = maxid - minid + 1; //the +1 is probably not needed, but quite unharmful

	Edgeset &mye = getEdges();
	for (i = mye.begin(); i != mye.end(); i++)
		if (e1.has(i->getSrcNodeId(), i->getDstNodeId()))
			i->shiftId(diff);
	;
}

Linkable *Linkable::has(std::string s) {
	std::vector<Linkable *>::iterator i = _linkables.begin();

	for (; i != _linkables.end(); i++)
		if ((*i)->getName() == s)
			return *i;

	return 0;
}

namespace leaf {
Edgeset & link(Linkable & l1, Linkable & l2) {
	Nodeset &l1o = l1.getNodes();
	Nodeset &l2i = l2.getNodes();
	map<std::string, Nodeset> dbi;
	map<std::string, Nodeset> dbo;
	Nodeset::iterator i;
	map<std::string, Nodeset>::iterator dbiter;
	map<std::string, Nodeset>::iterator found;
	Edgeset *E = new Edgeset;
	bool foundin = false;
	bool foundout = false;
	std::string s;

	//cout << "Linking" << endl;

	for (i = l1o.begin(); i != l1o.end(); i++) {
		s = i->getOutConnector();
		if (i->getOutConnector() != "") {
			//cout << "Found out-connector:" << s << endl;
			foundout = true;
			dbo[i->getOutConnector()].addNode(*i);
		}
	}

	for (i = l2i.begin(); i != l2i.end(); i++) {
		s = i->getInConnector();
		if (i->getInConnector() != "") {
			//cout << "Found in-connector:" << s << endl;
			foundin = true;
			dbi[i->getInConnector()].addNode(*i);
		}
	}

	if (foundin || foundout) {
		for (dbiter = dbo.begin(); dbiter != dbo.end(); dbiter++) {
			found = dbi.find(dbiter->first);
			if (found != dbi.end())
				E->AddEdges(*new Edgeset(dbiter->second, found->second));
		}
	}

	else
		E->AddEdges(*new Edgeset(l1.getOutputs(), l2.getInputs()));

	return *E;
}

Edgeset& ulink(Linkable & l1, Linkable & l2) {
	Edgeset& e1 = (*new Edgeset(l1.getOutputs(), l2.getInputs()));
	Edgeset& e2 = (*new Edgeset(l2.getOutputs(), l1.getInputs()));

	e1.AddEdges(e2);
	e2.~Edgeset();

	return e1;
}

Nodeset& merge(Linkable& l1, Linkable& l2) {
	Nodeset& n1 = (*new Nodeset(l1.getNodes()));

	n1.addNodes(l2.getNodes());
	return n1;
}

}

