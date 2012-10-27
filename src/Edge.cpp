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

#include "Edge.h"
#include "Graph.h"
#include <assert.h>

unsigned Edge::_lastsocketid = 0;

Edge::Edge() {
	// TODO Auto-generated constructor stub
	_socketid = ++_lastsocketid;
}

/*Edge::Edge(Node & n1, Node & n2)
 {
 _srcnodeid=n1.getId();
 _dstnodeid=n2.getId();
 n2._issource = false;
 n1._issink = false;
 }*/

Edge::Edge(unsigned id1, unsigned id2) {
	_srcnodeid = id1;
	_dstnodeid = id2;
	_socketid = ++_lastsocketid;
	//n2._issource = false;
	//n1._issink = false;
}

Edge::Edge(unsigned id1, unsigned id2, unsigned eid) {
	_srcnodeid = id1;
	_dstnodeid = id2;
	_socketid = eid;
	//assert(eid>=_lastsocketid);
	//n2._issource = false;
	//n1._issink = false;
}

Edge::~Edge() {
	// TODO Auto-generated destructor stub
}
ostream & Edge::operator>>(std::ostream &str) {
	str << "E";
	str << _socketid;
	str << "[";
	str << _srcnodeid;
	str << ", ";
	str << _dstnodeid;
	str << "]";
	return str;
}

/*Node & Edge::getSrcNode(void)
 {return _mygraph->findNode(_srcnodeid);}
 */

/*Node & Edge::getDstNode(void)
 {return _mygraph->findNode(_dstnodeid);}
 */
