#-------------------------------------------------------------------------------
# Copyright (c) 2012 Francesco Napolitano.
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the GNU Public License v3.0
# which accompanies this distribution, and is available at
# http://www.gnu.org/licenses/gpl.html
# 
# Contributors:
#     Francesco Napolitano - initial API and implementation
#-------------------------------------------------------------------------------
These are source files for flex and bison, necessary to generate
source code for lexycal and syntactical analysis in lglc.

In order to generate the source files, issue the following commands:
   
   flex --header-file=lglc.yy.hh -o lglc.yy.cc lglc.ll
   bison --defines lglc.yy

That will create the files:
     
     lglc.yy.hh
     lglc.yy.cc
     lglc.tab.hh
     lglc.tab.cc

Such files are part of the source code that is necessary to build
lglc.
