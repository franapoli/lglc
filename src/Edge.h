/*
 * Copyright (c) 2012 Francesco Napolitano.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Public License v3.0
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/gpl.html
 * 
 * Contributors:
 *     Francesco Napolitano - initial API and implementation
 */

#ifndef EDGE_H_
#define EDGE_H_

#include "Node.h"

class Edge {
	friend class Edgeset;

public:
	Edge();
	//Edge(Node &, Node &);
	Edge(unsigned, unsigned);
	Edge(unsigned id1, unsigned id2, unsigned eid);
	virtual ~Edge();
	std::ostream & operator>>(std::ostream &);
	//Node & getSrcNode(void);
	//Node & getDstNode(void);

	unsigned int getSrcNodeId(void) {
		return _srcnodeid;
	}
	unsigned int getDstNodeId(void) {
		return _dstnodeid;
	}
	void setSrcNodeId(unsigned id) {
		_srcnodeid = id;
	}
	void setDstNodeId(unsigned id) {
		_dstnodeid = id;
	}
	unsigned int getId(void) {
		return _socketid;
	}
	void shiftId(int s) {
		_socketid += s;
		if (_socketid > _lastsocketid)
			_lastsocketid = _socketid;
	}

private:
	unsigned int _srcnodeid;
	unsigned int _dstnodeid;
	unsigned int _socketid;
	static unsigned int _lastsocketid;
	bool _directed;

};

#endif /* EDGE_H_ */
