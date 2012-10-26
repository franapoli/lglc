/*
 * CallStack.h
 *
 *  Created on: 23/mag/2010
 *      Author: ciccio
 */

#ifndef CALLSTACK_H_
#define CALLSTACK_H_

#include "Frame.h"
#include <stack>
#include "Linkable.h"

class CallStack: public std::stack<Frame> {
public:
	CallStack();
	virtual ~CallStack();
	Linkable &Run(void) {
		Linkable &g = top().run();
		pop();
		return g;
	}
};

#endif /* CALLSTACK_H_ */
