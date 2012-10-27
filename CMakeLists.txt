project (LGLCompiler)
cmake_minimum_required (VERSION 2.6)
file(GLOB lglc_SRC
    "src/*.h"
    "src/*.cpp"
    "src/*.cc" 
)
add_executable(lglc ${lglc_SRC})
install (TARGETS lglc DESTINATION bin)

