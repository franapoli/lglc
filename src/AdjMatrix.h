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

#ifndef ADJMATRIX_H_
#define ADJMATRIX_H_

#include <string>
#include "Nodeset.h"

class AdjMatrix {
public:
	AdjMatrix();
	virtual ~AdjMatrix();
	AdjMatrix(int n, int m);
	int *&operator[](unsigned i) {
		return *_mat[i];
	}
	//void toDot(Nodeset &ns, string fname);
	void set(unsigned, unsigned);
	ostream& operator>>(std::ostream &);

private:
	int ***_mat;
	int _n;
	int _m;
};

#endif /* ADJMATRIX_H_ */
