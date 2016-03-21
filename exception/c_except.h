/*
\file c_except.h

Implements a cross-language exception that can be generated from D-lang.

	- Exception should inherit from std::exception.
	- Expose interface to d-lang for throwing C++ exceptions from D
*/

#include <exception>
/*
Impl. Ideas:
	- Represent D-lang exceptions in a way that stores that type (object.Exception.TypeInfo) of the
	exception, the location (Throwable.file and Throwable.line), the stack info (Throwable.TraceInfo),
	and other information stored in the Dlang exception.
Impl. Reqs.:
	- Be convertible from CppException (see: d_except) back to original exception type in C++.
	- Be convertible back to the original D-lang exception type from which it originated
*/

class DlangException : std::exception
{

}