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


#include "AdjMatrix.h"
#include <stdio.h>
#include <vector>
#include "globals.h"

using namespace std;

AdjMatrix::AdjMatrix() {
	// TODO Auto-generated constructor stub

}

AdjMatrix::~AdjMatrix() {

	for (int i = 0; i < _n; i++)
		delete (*_mat)[i];

	delete *_mat;
	delete _mat;
}

AdjMatrix::AdjMatrix(int n, int m) {
	_n = n;
	_m = m;
	_mat = new int **;
	(*_mat) = new int *[n];

	for (int i = 0; i < n; i++) {
		(*_mat)[i] = new int[m];
		for (int j = 0; j < m; j++)
			(*_mat)[i][j] = 0;
	}
}
/* THE FOLLOWING WORKS BUT NOW THE SAME IS DONE IN Graph.cpp
 void AdjMatrix::toDot(Nodeset &Ns, string fname) {
 FILE *fid;
 Nodeset::iterator i;
 Nodeset::iterator j;
 int ii=0, ij=0;
 fid=fopen((string(fname)).c_str(), "w");
 string attr_string="";
 std::map<std::string, std::string>::iterator mapit;
 std::map<std::string, std::string> attribs;

 fprintf(fid, "digraph G {\n");
 fprintf(fid, "node [shape=box, style=rounded];\n");
 fprintf(fid, "rankdir=LR;\n");



 for(i=Ns.begin(); i!=Ns.end(); ++i){
 attr_string = "[ label = ";
 attr_string += i->getName();

 attribs = i->GetAttributes();
 for(mapit = attribs.begin(); mapit!=attribs.end(); mapit++){
 attr_string += ", ";
 attr_string += (mapit -> first).c_str();
 attr_string += " = ";
 attr_string += (mapit -> second).c_str();
 }
 attr_string += "] ";

 fprintf(fid, "%d %s;\n", i->getId(), attr_string.c_str());
 //fprintf(fid, "%d [ label = \"%s\", color = \"%s\" ];\n", i->getId(), i->getName().c_str(), i->GetAttribute("color").c_str());


 }


 for (ii=0, i=Ns.begin(); ii<_n; ++ii, ++i){              // process ARCs
 for (ij=0; ij<_m; ++ij) {
 if((*_mat)[ii][ij]) {
 bool found = false;
 attribs = i->GetAttributes();
 for(mapit = attribs.begin(); mapit!=attribs.end(); mapit++){
 if(mapit->first == "LEAF_FLAGS" && mapit->second == "F") {
 fprintf(fid, "%d->%d [arrowhead = \"empty\"];\n", ii, ij);
 found = true;
 }
 }
 if (!found)
 fprintf(fid, "%d->%d;\n", ii, ij);
 }
 }
 }
 fprintf(fid, "}");
 fclose(fid);


 }
 */
void AdjMatrix::set(unsigned i, unsigned j) {
	(*_mat)[i][j] = 1;
}

ostream& AdjMatrix::operator>>(std::ostream &o) {
	int j, i;

	for (i = 0; i < _n; i++) {
		for (j = 0; j < _m - 1; j++)
			o << (*_mat)[i][j] << ",";
		o << (*_mat)[i][j] << endl;
	}

	return o;
}
