/* 
   The MIT License (MIT)

   Copyright (c) 2012-2013 Francesco Napolitano, franapoli@gmail.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
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
