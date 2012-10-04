/*
 * Graph.h
 *
 *  Created on: 08/apr/2010
 *      Author: ciccio
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Nodeset.h"
#include "Edgeset.h"
#include "AdjMatrix.h"

class Graph : public Linkable {

public:
	Graph();
	Graph(Nodeset &, Edgeset&);
	virtual ~Graph();
	void MergeWith(Graph &);
	void FindNode(string);
	void Destroy(void);
	Nodeset& GetOutputs(void);
	Nodeset& GetInputs(void);
	AdjMatrix &Visit(void);
	ostream& operator>>(std::ostream &);
	Edgeset& GetEdges(void) {return _E;}
	void AddEdges(Edgeset &e);
	void AddNodes(Nodeset &e) {_V.AddNodes(e);}
	Nodeset& GetNodes(void) {return _V;}
	void SetInputs(Nodeset &);
	void SetOutputs(Nodeset &);
	Nodeset& GetSources(void);
	Nodeset& GetSinks(void);
	virtual operator Nodeset();
	void AddNode(Node &);
	Node &findNode(unsigned id){return _V.findNode(id);}
	Nodeset &GetOutNodes(Node &);
	virtual Linkable &Clone(){Graph &g=*new Graph; g = *this; return g;}
	void UpdateIds();
	void SetAttribute(std::string s1, std::string s2);
	void SetAttribute(unsigned n, std::string s1, std::string s2){_V.SetAttribute(n,s1,s2);}

private:
	Edgeset  _E;
	Nodeset  _V;
};



#endif /* GRAPH_H_ */
