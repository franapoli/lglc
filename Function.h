/*
 * Function.h
 *
 *  Created on: 23/mag/2010
 *      Author: ciccio
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
