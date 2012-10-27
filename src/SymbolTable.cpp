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

#include "SymbolTable.h"
#include "NameSpace.h"

SymbolTable::SymbolTable() {
	NameSpace *global = new NameSpace;
	this->addNameSpace("global", *global);

}

SymbolTable::~SymbolTable() {
	// TODO Auto-generated destructor stub
}
