%module mmrunner
%{
#define SWIG_FILE_WITH_INIT
// #include "MDAEvent.h"
#include "MDAPosition.h"
// #include "MMRunner.h"
%}

// %include "MDAEvent.h"
%include "MDAPosition.h"
// %include "MMRunner.h"

// swig -c++ -python mmrunner_swig.i 
// c++ -c mmrunner_swig_wrap.cxx -I/home/ubuntu/miniconda3/envs/micro-manager/include/python3.7m -fPIC
// c++ -shared mmrunner_swig_wrap.o  -o _mmrunner.o