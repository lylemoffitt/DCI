/*
\file c_except.h

Implements a cross-language exception that can be generated from D-lang.

	- Exception should inherit from std::exception.
	- Expose interface to d-lang for throwing C++ exceptions from D
*/

/*
Impl. Reqs.:
	- Be convertible from CppException (see: d_except) back to original exception type in C++.
*/