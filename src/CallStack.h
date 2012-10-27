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
