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

#include "Environment.h"
#include "NameSpace.h"

Environment::Environment() {
	NameSpace *global = new NameSpace;
	this->addNameSpace("global", *global);

}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
}
