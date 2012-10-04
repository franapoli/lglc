/*
 * AdjMatrix.h
 *
 *  Created on: 17/apr/2010
 *      Author: ciccio
 */

#ifndef ADJMATRIX_H_
#define ADJMATRIX_H_

#include <string>
#include "Nodeset.h"

class AdjMatrix {
public:
	AdjMatrix();
	virtual ~AdjMatrix();
	AdjMatrix(int n, int m);
	int *&operator[](unsigned i) {return *_mat[i];}
	void toDot(Nodeset &ns, string fname);
	void Set(unsigned, unsigned);
	ostream& operator>>(std::ostream &);

private:
	int ***_mat;
	int _n;
	int _m;
};

#endif /* ADJMATRIX_H_ */
