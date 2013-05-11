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

#ifndef FRAME_H_
#define FRAME_H_

#include "Environment.h"
#include "Linkable.h"
#include "globals.h"
#include <stdio.h>

extern FILE *yyin;
class Linkable;

class Frame {
public:
	Frame();
	virtual ~Frame();
	Environment const& getEnv() const {
		return _env;
	}

	void setEnv(Environment _env) {
		this->_env = _env;
	}

	Linkable* doAction(ACTION_TYPE type, Linkable *, Linkable *, Linkable *,
			Linkable *);

	Linkable &run(void);

	void setStream(FILE *fid) {
		_fid = fid;
	}

private:
	Environment _env;
	FILE *_fid;
	Graph *g;
};

#endif /* FRAME_H_ */
