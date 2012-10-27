
ABOUT lglc

This is README.txt file for lglc source package. lglc (Leaf Graph
Language Compiler) is a compiler for the LGL language whose target
code is a subset of the DOT language (http://www.graphviz.org). The
LGL language is an ASCII-ART based graph definition language, whose
aim is to code graph structures in a readable way. Here is an example:

        /C
A -> B <
        \   /E -> @C
         D <
            \F -> G, H
;

The code above defines the graph structure that can be easily
guessed. Note that the code "E -> @C" creates a loop with the
previously defined node C. Also note that "F -> G, H" creates two
edges. The resulting graph can be visualized converting this code to
DOT language through the lglc compiler and then using Graphviz tools.

The LGL compiler is part of a pipeline management system, so it lacks
some standalone stuff at the moment (notably documentation).
