/*
 * Edgeset.h
 *
 *  Created on: 08/apr/2010
 *      Author: ciccio
 */

#ifndef EDGESET_H_
#define EDGESET_H_

#include <vector>
#include "Edge.h"
//#include <iostream>

class Nodeset;
class Edge;
class Edgeset: public vector<Edge> {
	friend class Graph;
public:
	Edgeset();
	Edgeset(Nodeset &, Nodeset &);
	virtual ~Edgeset();
	void AddEdge(Edge &);
//	Edge & AddEdge(Node &, Node &);
	Edge & addEdge(unsigned int id1, unsigned int id2);
	Edge & addEdge(unsigned int id1, unsigned int id2, unsigned id);
	void addEdges(Edgeset &, bool copyid = false);
	//Nodeset &GetInNodes(Node &);
	//Nodeset &GetOutNodes(Node &);
	std::ostream & operator>>(std::ostream &str);
	bool has(unsigned iid, unsigned jid);

private:

};

#endif /* EDGESET_H_ */
