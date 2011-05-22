/*
 * Frame.h
 *
 *  Created on: 22/mag/2010
 *      Author: ciccio
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
    Environment const& getEnv() const
    {
        return _env;
    }

    void setEnv(Environment _env)
    {
        this->_env = _env;
    }

    Linkable* doAction(ACTION_TYPE type, Linkable *, Linkable *, Linkable *, Linkable *);

    Linkable &Run(void);

    void setStream(FILE *fid) {_fid = fid;}

private:
	Environment _env;
	FILE *_fid;
	Graph *g;
};

#endif /* FRAME_H_ */
