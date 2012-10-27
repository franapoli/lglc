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
