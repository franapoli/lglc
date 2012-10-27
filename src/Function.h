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

#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <string>

class Function {
public:
	Function();
	virtual ~Function();

private:
	long _srcoffset;
	std::string _name;
	unsigned char _numpar;
};

#endif /* FUNCTION_H_ */
