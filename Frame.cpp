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

using namespace std;

bool FRAME_DEBUG = 0;

Frame::Frame() {
	g=new Graph();
	// TODO Auto-generated constructor stub

}

Frame::~Frame() {
	// TODO Auto-generated destructor stub
}



Linkable* Frame::doAction(ACTION_TYPE type, Linkable * p1, Linkable * p2, Linkable * p3, Linkable * p4)
{
	Node *n;
	stringstream ss;
	Nodeset *ns;
	static string name="global";
	Linkable *l;
	static Graph *gtemp = new Graph;
	static Nodeset *realins ;
	static Nodeset *realouts;
	Graph *arrowgraph;
	static string connector = "";
	static vector<string> inconnectors;
	static vector<string> outconnectors;
	bool isold = false;
	static vector< pair <string, string> > attribs;
	static bool suspend_actions = false;
	static unsigned int groupid=0;


	if(suspend_actions) {
		if((int)p1 == 0 && type == ACT_FUNCTDEF) {
			suspend_actions = false;
			if(FRAME_DEBUG) cout << "Re-enabling actions" << endl;
		}
		else return 0;
	}

	switch(type)
	{
	case ACT_ATTRIBUTE:
		pair<string, string> *attr;
		attr = new pair<string, string>((const char *)p1, (const char *)p2);
		attribs.push_back(*attr);
		return (Linkable *) attr;

	case ACT_FUNCTDEF:
		if((int)p1 == 1) {
			suspend_actions = true;
			if(FRAME_DEBUG) cout << "Suspending actions" << endl;
		}
		return p1;


	case ACT_CHAINASFORKSON:
		if(FRAME_DEBUG) cout << "Performing action CHAINASFORKSON" << endl;
		p1->SetInputs(p1->GetSources());
		if(FRAME_DEBUG) *p1>>cout << endl;
		return p1;

	case ACT_REFERENCE:
		if(FRAME_DEBUG) cout << "Performing action REFERENCE" << endl;
		l = symboltable.getSymbol(name, (const char *)p1);
	//	*namesp >> cout;
		if(l) {
			if(FRAME_DEBUG) *l>>cout << endl;
			return l;
		}
		else cerr << "Reference not found: " <<(const char *)p1 << endl;
		exit(1);

	case ACT_GRAPHNAME:
		name = (const char *)p1;
		symboltable.addNameSpace(name, *new NameSpace);
		if((int) p2)
			attribs.push_back(pair<string, string>(((pair<string, string>*)p2)->first, ((pair<string, string>*)p2)->second));

		return p1;

	case ACT_GROUP:
	{ //necessary
	Nodeset &nodes = p1->GetNodes();
	Nodeset::iterator ni;

	for(ni = nodes.begin(); ni!=nodes.end(); ni++) {
		std::stringstream out;
		out << groupid;
			gtemp->SetAttribute(ni->getId(), "group", out.str());
		}

	groupid++;
	return p1;

	}


	case ACT_PARENTHESIS:
		/*quadopenpar+=(int)p2;
		roundopenpar+=(int)p1;*/

		return p3;


	case ACT_CONNECTOR:
		if(FRAME_DEBUG) cout << "Performing action CONNECTOR" << endl;
		if(FRAME_DEBUG) cout << (const char *)p1 << endl;
		return (Linkable *) p1;

	case ACT_NODE:
		if(FRAME_DEBUG) cout << "Performing action NODE" << endl;
		ss << (char *)p1;


		l = symboltable.getSymbol(name, (const char *)p1);
		if(l) {
			isold=true;
			if(FRAME_DEBUG) {cout << "Found existing symbol:" << endl;
			*l >> cout << endl;}
			Linkable &l2=l->Clone();
			l2.UpdateIds();
			symboltable.addSymbol(name, ss.str(), &l2);
			gtemp->AddNodes(l2.GetNodes());
			gtemp->AddEdges(l2.GetEdges());
			if(FRAME_DEBUG) cout << "Result:" << endl;
			if(FRAME_DEBUG) l2 >> cout << endl;
			l=&l2;
		}

		else {
		l = new Node(ss.str());
		}

		if(attribs.size()!=0) {
			vector< pair <string, string> >::iterator i;
			for(i=attribs.begin(); i!=attribs.end(); ++i)
				l->SetAttribute((*i).first, (*i).second);
			attribs.clear();
		}

		if((int) p4 == 1){
			if(!realins)
				realins = new Nodeset;
			realins->AddNode(*(Node *)l);
			inconnectors.push_back((const char *) p2);
		}
		if((int) p4 == 2){
			if(!realouts)
				realouts = new Nodeset;
			realouts->AddNode(*(Node *)l);
			outconnectors.push_back((const char *) p2);
		}

		if(l->getName()==".")
			isold=true;

		if(!isold){
		symboltable.addSymbol(name, ss.str(), (Node *)l);
		gtemp->AddNode(*(Node *)l);
		}


		if(FRAME_DEBUG) {cout << "Result:" << endl;
						*(Node *)l >> cout << endl;}

		return l;

	case ACT_COMMA:
		if(FRAME_DEBUG)	{
			cout << "Performing action COMMA" << endl;
			cout << "p1" << endl;
			*p1 >> cout << endl;
			cout << "p2" << endl;
			*p2 >> cout << endl;
		}

		ns = &leaf::merge(*p1, *p2);

		if(FRAME_DEBUG) {cout << "Result:"<<endl;
						*ns >> cout;}
		return ns;


	case ACT_ARROW:
		if(FRAME_DEBUG) {
			cout << "Performing action ARROW" << endl;
			cout << "p1" << endl;
			*p1 >> cout << endl;
			cout << "p2" << endl;
			*p2 >> cout << endl;
		}

		arrowgraph=new Graph;

		arrowgraph->AddNodes(p1->GetNodes());
		arrowgraph->AddNodes(p2->GetNodes());
		arrowgraph->AddEdges(p1->GetEdges());
		arrowgraph->AddEdges(p2->GetEdges());

		arrowgraph->AddEdges(leaf::link(*p1, *p2));

		if(!p4) {
			arrowgraph->SetOutputs(p2->GetOutputs());
			arrowgraph->SetInputs(p1->GetInputs());
			}

		else {
			arrowgraph->SetInputs(p2->GetOutputs());
			arrowgraph->SetOutputs(p1->GetInputs());
		}
		gtemp->AddNodes(arrowgraph->GetNodes());
		gtemp->AddEdges(arrowgraph->GetEdges());

		if ((int) p3 != 2){ // hashing
					Nodeset &temp = p2->GetOutputs();
					Nodeset::iterator it;

					for(it = temp.begin(); it!=temp.end(); it++){
						gtemp->SetAttribute(it->getId(), "hash", "true");
						p2->SetAttribute(it->getId(), "hash", "true");
					}
		}


		if(FRAME_DEBUG)
			{ cout << "result" << endl;
			*arrowgraph >> cout;}

		return arrowgraph;


	case ACT_MERGE:
		if(FRAME_DEBUG) {
			cout << "Performing action MERGE" << endl;
			cout << "p1" << endl;
			*p1 >> cout << endl;
			cout << "p2" << endl;
			*p2 >> cout << endl;
			cout << "p3" << endl;
			*p3 >> cout << endl;
			}


		gtemp->AddNodes(p1->GetNodes());
		gtemp->AddNodes(p3->GetNodes());
		gtemp->AddEdges(p1->GetEdges());
		gtemp->AddEdges(p3->GetEdges());

		if (p2->getName()=="."){
				Nodeset *nst = new Nodeset();
				nst->AddNodes(p1->GetNodes());
				nst->AddNodes(p3->GetNodes());
				nst->SetInputs(nst->GetNodes());
				nst->SetOutputs(nst->GetNodes());
				p2 = nst;
		}

		else {
			gtemp->AddNodes(p2->GetNodes());
			gtemp->AddEdges(p2->GetEdges());
			gtemp->AddEdges(leaf::link(*p1, *p2));
			gtemp->AddEdges(leaf::link(*p3, *p2));
			gtemp->SetOutputs(p2->GetOutputs());
			gtemp->SetInputs(p2->GetInputs());
		}

		if ((int) p4 == ACT_FLAG_HASH){
			Nodeset &temp = p2->GetInputs();
			Nodeset::iterator it;

			for(it = temp.begin(); it!=temp.end(); it++){
				gtemp->SetAttribute(it->getId(), "hash", "true");
				p2->SetAttribute(it->getId(), "hash", "true");
			}
		}

		if(FRAME_DEBUG) cout << "result" << endl;
		if(FRAME_DEBUG) *gtemp >> cout;

		return p2;


	case ACT_FORK:

		if(FRAME_DEBUG)	{
			cout << "Performing action FORK" << endl;
			cout << "p1" << endl;
			*p1 >> cout << endl;
			cout << "p2" << endl;
			*p2 >> cout << endl;
			cout << "p3" << endl;
			*p3 >> cout << endl;
		}

		gtemp->AddNodes(p1->GetNodes());
		gtemp->AddNodes(p3->GetNodes());
		gtemp->AddEdges(p1->GetEdges());
		gtemp->AddEdges(p3->GetEdges());

		if (p2->getName()=="."){
				Graph *nst = new Graph();
				nst->AddNodes(p1->GetNodes());
				nst->AddNodes(p3->GetNodes());
				nst->AddEdges(p1->GetEdges());
				nst->AddEdges(p3->GetEdges());
				Nodeset n1;
				n1.AddNodes(p1->GetInputs());
				n1.AddNodes(p3->GetInputs());
				nst->SetInputs(n1.GetNodes());
				Nodeset n2;
				n2.AddNodes(p1->GetOutputs());
				n2.AddNodes(p3->GetOutputs());
				nst->SetOutputs(n2.GetNodes());
				p2 = nst;
		}


		else {
			gtemp->AddNodes(p2->GetNodes());
			gtemp->AddEdges(p2->GetEdges());
			gtemp->AddEdges(leaf::link(*p2, *p1));
			gtemp->AddEdges(leaf::link(*p2, *p3));
			gtemp->SetOutputs(p2->GetOutputs());
			gtemp->SetInputs(p2->GetInputs());
		}

		if ((int) p4 == ACT_FLAG_HASH){

			Nodeset &temp = p2->GetOutputs();
			Nodeset::iterator it;

			for(it = temp.begin(); it!=temp.end(); it++){
				gtemp->SetAttribute(it->getId(), "hash", "true");
				p2->SetAttribute(it->getId(), "hash", "true");
			}
		}




		if(FRAME_DEBUG)
			{cout << "result" << endl;
			*gtemp >> cout;}

		return p2;


	case ACT_DIAGRAM:
		if(FRAME_DEBUG) cout << "Performing action DIAGRAM" << endl;

		if(!name.empty()){
			gtemp->setName(name);
			symboltable.addSymbol("global", name, gtemp);
			name="global";
		}

		if(realins) {
			Nodeset::iterator i;
			for(i=realins->begin(); i!=realins->end();i++)
				i->setInConnector(inconnectors[i-realins->begin()]);
			gtemp->SetInputs(*realins);
			if(FRAME_DEBUG) {cout << "*****************" << endl;
				*realins >> cout;}
			delete realins;
			inconnectors.clear();
			realins=0;
		}
		else gtemp->SetInputs(gtemp->GetSources());

		if(realouts) {
			Nodeset::iterator i;
			for(i=realouts->begin(); i!=realouts->end();i++)
				i->setOutConnector(outconnectors[i-realouts->begin()]);
			gtemp->SetOutputs(*realouts);
			delete realouts;
			outconnectors.clear();
			realouts=0;
		}
		else gtemp->SetOutputs(gtemp->GetSinks());

		if(attribs.size()!=0){
			gtemp->SetAttribute(attribs[0].first, attribs[0].second);
			attribs[0].first="";
		}

		if(FRAME_DEBUG) *gtemp >> cout;

		g->AddNodes(gtemp->GetNodes());
		g->AddEdges(gtemp->GetEdges());

		gtemp = new Graph;
		return gtemp;

	}

return 0;
}

Linkable &Frame::Run(void)
{
	yyin = _fid;
	int res = yyparse();
	if(res)
		throw(1);
	return *g;
}
