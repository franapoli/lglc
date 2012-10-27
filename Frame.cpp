/*
 * Frame.cpp
 *
 *  Created on: 22/mag/2010
 *      Author: ciccio
 */

#include "globals.h"
#include "Frame.h"
#include "Linkable.h"
#include <stdio.h>
#include <stdlib.h> //itoa
#include <string>
#include <sstream>
#include "Graph.h"
#include "Nodeset.h"
#include "Environment.h"
#include <typeinfo>
#include <stdint.h>

using namespace std;

bool FRAME_DEBUG = 0;

Frame::Frame() {
	g = new Graph();
	// TODO Auto-generated constructor stub

}

Frame::~Frame() {
	// TODO Auto-generated destructor stub
}

Linkable* Frame::doAction(ACTION_TYPE type, Linkable * p1, Linkable * p2,
		Linkable * p3, Linkable * p4) {
	stringstream ss;
	Nodeset *ns;
	static string name = "global";
	Linkable *l;
	static Graph *gtemp = new Graph;
	static Nodeset *realins;
	static Nodeset *realouts;
	Graph *arrowgraph;
	static string connector = "";
	static vector<string> inconnectors;
	static vector<string> outconnectors;
	bool isold = false;
	static vector<pair<string, string> > attribs;
	static bool suspend_actions = false;
	static unsigned int groupid = 0;

	if (suspend_actions) {
		if ((uintptr_t) p1 == 0 && type == ACT_FUNCTDEF) {
			suspend_actions = false;
			if (FRAME_DEBUG)
				cout << "Re-enabling actions" << endl;
		} else
			return 0;
	}

	switch (type) {
	case ACT_ATTRIBUTE:
		pair<string, string> *attr;
		attr = new pair<string, string>((const char *) p1, (const char *) p2);
		attribs.push_back(*attr);
		return (Linkable *) attr;

	case ACT_FUNCTDEF:
		if ((uintptr_t) p1 == 1) {
			suspend_actions = true;
			if (FRAME_DEBUG)
				cout << "Suspending actions" << endl;
		}
		return p1;

	case ACT_CHAINASFORKSON:
		if (FRAME_DEBUG)
			cout << "Performing action CHAINASFORKSON" << endl;
		p1->setInputs(p1->getSources());
		if (FRAME_DEBUG)
			*p1 >> cout << endl;
		return p1;

	case ACT_REFERENCE:
		if (FRAME_DEBUG)
			cout << "Performing action REFERENCE" << endl;
		l = symboltable.getSymbol(name, (const char *) p1);
		//	*namesp >> cout;
		if (l) {
			if (FRAME_DEBUG)
				*l >> cout << endl;
			return l;
		} else
			cerr << "Reference not found: " << (const char *) p1 << endl;
		exit(1);

	case ACT_GRAPHNAME:
		name = (const char *) p1;
		symboltable.addNameSpace(name, *new NameSpace);
		if ((uintptr_t) p2)
			attribs.push_back(
					pair<string, string>(((pair<string, string>*) p2)->first,
							((pair<string, string>*) p2)->second));

		return p1;

	case ACT_GROUP: { //necessary
		Nodeset &nodes = p1->getNodes();
		Nodeset::iterator ni;

		for (ni = nodes.begin(); ni != nodes.end(); ni++) {
			std::stringstream out;
			out << groupid;
			gtemp->setAttribute(ni->getId(), "group", out.str());
		}

		groupid++;
		return p1;

	}

	case ACT_PARENTHESIS:
		/*quadopenpar+=(int)p2;
		 roundopenpar+=(int)p1;*/

		return p3;

	case ACT_CONNECTOR:
		if (FRAME_DEBUG)
			cout << "Performing action CONNECTOR" << endl;
		if (FRAME_DEBUG)
			cout << (const char *) p1 << endl;
		return (Linkable *) p1;

	case ACT_NODE:
		if (FRAME_DEBUG)
			cout << "Performing action NODE" << endl;
		ss << (char *) p1;

		l = symboltable.getSymbol(name, (const char *) p1);
		if (l) {
			isold = true;
			if (FRAME_DEBUG) {
				cout << "Found existing symbol:" << endl;
				*l >> cout << endl;
			}
			Linkable &l2 = l->clone();
			l2.updateIds();
			symboltable.addSymbol(name, ss.str(), &l2);
			gtemp->addNodes(l2.getNodes());
			gtemp->addEdges(l2.getEdges(), true);
			if (FRAME_DEBUG)
				cout << "Result:" << endl;
			if (FRAME_DEBUG)
				l2 >> cout << endl;
			l = &l2;
		}

		else {
			l = new Node(ss.str());
		}

		if (attribs.size() != 0) {
			vector<pair<string, string> >::iterator i;
			for (i = attribs.begin(); i != attribs.end(); ++i)
				l->setAttribute((*i).first, (*i).second);
			attribs.clear();
		}

		if ((uintptr_t) p4 == 1) {
			if (!realins)
				realins = new Nodeset;
			realins->addNode(*(Node *) l);
			inconnectors.push_back((const char *) p2);
		}
		if ((uintptr_t) p4 == 2) {
			if (!realouts)
				realouts = new Nodeset;
			realouts->addNode(*(Node *) l);
			outconnectors.push_back((const char *) p2);
		}

		if (l->getName() == ".")
			isold = true;

		if (!isold) {
			symboltable.addSymbol(name, ss.str(), (Node *) l);
			gtemp->addNode(*(Node *) l);
		}

		if (FRAME_DEBUG) {
			cout << "Result:" << endl;
			*(Node *) l >> cout << endl;
		}

		return l;

	case ACT_COMMA:
		if (FRAME_DEBUG) {
			cout << "Performing action COMMA" << endl;
			cout << "p1" << endl;
			*p1 >> cout << endl;
			cout << "p2" << endl;
			*p2 >> cout << endl;
		}

		ns = &leaf::merge(*p1, *p2);

		if (FRAME_DEBUG) {
			cout << "Result:" << endl;
			*ns >> cout;
		}
		return ns;

	case ACT_ARROW:
		if (FRAME_DEBUG) {
			cout << "Performing action ARROW" << endl;
			cout << "p1" << endl;
			*p1 >> cout << endl;
			cout << "p2" << endl;
			*p2 >> cout << endl;
		}

		arrowgraph = new Graph;

		arrowgraph->addNodes(p1->getNodes());
		arrowgraph->addNodes(p2->getNodes());
		arrowgraph->addEdges(p1->getEdges(), true);
		arrowgraph->addEdges(p2->getEdges(), true);

		arrowgraph->addEdges(leaf::link(*p1, *p2), true);

		if (!p4) {
			arrowgraph->setOutputs(p2->getOutputs());
			arrowgraph->setInputs(p1->getInputs());
		}

		else {
			arrowgraph->setInputs(p2->getOutputs());
			arrowgraph->setOutputs(p1->getInputs());
		}
		gtemp->addNodes(arrowgraph->getNodes());
		gtemp->addEdges(arrowgraph->getEdges(), true);

		if ((uintptr_t) p3 != 2) { // hashing
			Nodeset &temp = p2->getOutputs();
			Nodeset::iterator it;

			for (it = temp.begin(); it != temp.end(); it++) {
				gtemp->setAttribute(it->getId(), "hash", "true");
				p2->setAttribute(it->getId(), "hash", "true");
			}
		}

		if (FRAME_DEBUG) {
			cout << "result" << endl;
			*arrowgraph >> cout;
		}

		return arrowgraph;

	case ACT_MERGE:
		if (FRAME_DEBUG) {
			cout << "Performing action MERGE" << endl;
			cout << "p1" << endl;
			*p1 >> cout << endl;
			cout << "p2" << endl;
			*p2 >> cout << endl;
			cout << "p3" << endl;
			*p3 >> cout << endl;
		}

		gtemp->addNodes(p1->getNodes());
		gtemp->addNodes(p3->getNodes());
		gtemp->addEdges(p1->getEdges());
		gtemp->addEdges(p3->getEdges());

		if (p2->getName() == ".") {
			Nodeset *nst = new Nodeset();
			nst->addNodes(p1->getNodes());
			nst->addNodes(p3->getNodes());
			nst->setInputs(nst->getNodes());
			nst->setOutputs(nst->getNodes());
			p2 = nst;
		}

		else {
			gtemp->addNodes(p2->getNodes());
			gtemp->addEdges(p2->getEdges());
			gtemp->addEdges(leaf::link(*p1, *p2));
			gtemp->addEdges(leaf::link(*p3, *p2));
			gtemp->setOutputs(p2->getOutputs());
			gtemp->setInputs(p2->getInputs());
		}

		if ((uintptr_t) p4 == ACT_FLAG_HASH) {
			Nodeset &temp = p2->getInputs();
			Nodeset::iterator it;

			for (it = temp.begin(); it != temp.end(); it++) {
				gtemp->setAttribute(it->getId(), "hash", "true");
				p2->setAttribute(it->getId(), "hash", "true");
			}
		}

		if (FRAME_DEBUG)
			cout << "result" << endl;
		if (FRAME_DEBUG)
			*gtemp >> cout;

		return p2;

	case ACT_FORK:

		if (FRAME_DEBUG) {
			cout << "Performing action FORK" << endl;
			cout << "p1" << endl;
			*p1 >> cout << endl;
			cout << "p2" << endl;
			*p2 >> cout << endl;
			cout << "p3" << endl;
			*p3 >> cout << endl;
		}

		gtemp->addNodes(p1->getNodes());
		gtemp->addNodes(p3->getNodes());
		gtemp->addEdges(p1->getEdges());
		gtemp->addEdges(p3->getEdges());

		if (p2->getName() == ".") {
			Graph *nst = new Graph();
			nst->addNodes(p1->getNodes());
			nst->addNodes(p3->getNodes());
			nst->addEdges(p1->getEdges());
			nst->addEdges(p3->getEdges());
			Nodeset n1;
			n1.addNodes(p1->getInputs());
			n1.addNodes(p3->getInputs());
			nst->setInputs(n1.getNodes());
			Nodeset n2;
			n2.addNodes(p1->getOutputs());
			n2.addNodes(p3->getOutputs());
			nst->setOutputs(n2.getNodes());
			p2 = nst;
		}

		else {
			gtemp->addNodes(p2->getNodes());
			gtemp->addEdges(p2->getEdges(), true);
			gtemp->addEdges(leaf::link(*p2, *p1), true);
			Edgeset &es1 = leaf::link(*p2, *p3);
			gtemp->addEdges(es1, true);
			gtemp->switchEdgeIdOrder(gtemp->getEdgesRooted(*p3), es1);
			gtemp->setOutputs(p2->getOutputs());
			gtemp->setInputs(p2->getInputs());
		}

		if ((uintptr_t) p4 == ACT_FLAG_HASH) {

			Nodeset &temp = p2->getOutputs();
			Nodeset::iterator it;

			for (it = temp.begin(); it != temp.end(); it++) {
				gtemp->setAttribute(it->getId(), "hash", "true");
				p2->setAttribute(it->getId(), "hash", "true");
			}
		}

		if (FRAME_DEBUG) {
			cout << "result" << endl;
			*gtemp >> cout;
		}

		return p2;

	case ACT_DIAGRAM:
		if (FRAME_DEBUG)
			cout << "Performing action DIAGRAM" << endl;

		if (!name.empty()) {
			gtemp->setName(name);
			symboltable.addSymbol("global", name, gtemp);
			name = "global";
		}

		if (realins) {
			Nodeset::iterator i;
			for (i = realins->begin(); i != realins->end(); i++)
				i->setInConnector(inconnectors[i - realins->begin()]);
			gtemp->setInputs(*realins);
			if (FRAME_DEBUG) {
				cout << "*****************" << endl;
				*realins >> cout;
			}
			delete realins;
			inconnectors.clear();
			realins = 0;
		} else
			gtemp->setInputs(gtemp->getSources());

		if (realouts) {
			Nodeset::iterator i;
			for (i = realouts->begin(); i != realouts->end(); i++)
				i->setOutConnector(outconnectors[i - realouts->begin()]);
			gtemp->setOutputs(*realouts);
			delete realouts;
			outconnectors.clear();
			realouts = 0;
		} else
			gtemp->setOutputs(gtemp->getSinks());

		if (attribs.size() != 0) {
			gtemp->setAttribute(attribs[0].first, attribs[0].second);
			attribs[0].first = "";
		}

		if (FRAME_DEBUG)
			*gtemp >> cout;

		g->addNodes(gtemp->getNodes());
		g->addEdges(gtemp->getEdges(), true);

		gtemp = new Graph;
		return gtemp;

	}

	return 0;
}

Linkable &Frame::run(void) {
	yyin = _fid;
	int res = yyparse();
	if (res)
		throw(1);
	return *g;
}
