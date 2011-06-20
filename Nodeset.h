/*
 * Nodeset.h
 *
 *  Created on: 01/apr/2010
 *      Author: ciccio
 */

#ifndef NODESET_H_
#define NODESET_H_


#include "Node.h"
#include <vector>
#include "Edgeset.h"

using namespace std;

class Nodeset : public Linkable, public std::vector<Node> {
friend class Edgeset;
friend class Graph;
friend class AdjMatrix;
friend Edgeset & leaf::link(Linkable & l1, Linkable & l2);

public:
	Nodeset();
	Nodeset(Node &);
	Nodeset(const Nodeset &);
	virtual ~Nodeset();
	void AddNode(Node &);
	void AddNodes(Nodeset &);
	void AddNewNode(string label);
	Edgeset& link(Nodeset &);
	std::ostream & operator>>(std::ostream &);
	virtual Edgeset &GetEdges(void) {return *new Edgeset();}
	bool has(string name);
	bool has(unsigned id);
	Node &findNode(unsigned id);
	//operator class Graph();
	virtual Linkable &Clone(){Nodeset &ns=*new Nodeset; ns=*this; return ns;}
	//vector<Node>	_nodes;
	void UpdateIds(){Nodeset::iterator i; for(i=begin();i!=end();i++)i->UpdateIds();}
	void SetAttribute(unsigned, std::string s1, std::string s2);

	Nodeset& GetOutputs(void)	{return *this;}
	Nodeset& GetInputs(void)	{return *this;}
	Nodeset& GetNodes(void) 	{return *this;}
	void SetInputs(Nodeset &);
	void SetOutputs(Nodeset &);

private:
	Nodeset& GetSources(void) 	{return *this;}
	Nodeset& GetSinks(void) 	{return *this;}
};



#endif /* NODESET_H_ */
