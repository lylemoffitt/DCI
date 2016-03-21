/*
	Test file for DCI/object
*/

#include <vector> //see: /usr/include/c++/4.2.1/debug/vector
#include "object.h"

// Explicitly instantiate class; all non-template methods of the class will also be instantiated
template class std::vector<RootObject>;

// Explicitly instantiate template methods of template class

#define instantiate( _ret_, _class_name_ ,_method_name_ )\
template _ret_  _class_name_ ## :: ## _method_name_ ## <RootObject>(int);