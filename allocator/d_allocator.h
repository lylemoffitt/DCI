/*
Notes:
	- allocator that calls D's allocator for storage
	- see: https://dlang.org/phobos/std_experimental_allocator.html

To Do:
	- Replace method bodies with calls to D-lang's std.allocator
*/


/** @file ext/new_allocator.h
 *  This file is a GNU extension to the Standard C++ Library.
 */

#ifndef _NEW_ALLOCATOR_H
#define _NEW_ALLOCATOR_H 1

#include <new>
#include <bits/functexcept.h>

_GLIBCXX_BEGIN_NAMESPACE(__gnu_cxx)

  using std::size_t;
  using std::ptrdiff_t;

  /**
   *  @brief  An allocator that uses global new, as per [20.4].
   *
   *  This is precisely the allocator defined in the C++ Standard.
   *    - all allocation calls operator new
   *    - all deallocation calls operator delete
   */
  template<typename _Tp>
    class new_allocator
    {
    public:
      typedef size_t     size_type;
      typedef ptrdiff_t  difference_type;
      typedef _Tp*       pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp&       reference;
      typedef const _Tp& const_reference;
      typedef _Tp        value_type;

      template<typename _Tp1>
        struct rebind
        { typedef new_allocator<_Tp1> other; };

      new_allocator() throw() { }

      new_allocator(const new_allocator&) throw() { }

      template<typename _Tp1>
        new_allocator(const new_allocator<_Tp1>&) throw() { }

      ~new_allocator() throw() { }

      pointer
      address(reference __x) const { return &__x; }

      const_pointer
      address(const_reference __x) const { return &__x; }


      /*
      Allocates n * sizeof(T) bytes of uninitialized storage by calling ::operator new(std::size_t),
       but it is unspecified when and how this function is called. The pointer hint may be used
       to provide locality of reference: the allocator, if supported by the implementation,
       will attempt to allocate the new memory block as close as possible to hint.

      Parameters
      	n	-	the number of objects to allocate storage for
      	hint	-	pointer to a nearby memory location
      Return value
      	Pointer to the first byte of a memory block suitably aligned and sufficient to hold an
      	array of n objects of type T.
      */
      // NB: __n is permitted to be 0.  The C++ standard says nothing
      // about what the return value is when __n == 0.
      pointer
      allocate(size_type __n, const void* = 0)
      {
      	if (__builtin_expect(__n > this->max_size(), false))
        	  std::__throw_bad_alloc();

        return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
      }

		/*
		Deallocates the storage referenced by the pointer p, which must be a pointer obtained by
		 an earlier call to allocate(). The argument n must be equal to the first argument of
		 the call to allocate() that originally produced p.

        Calls ::operator delete(void*), but it is unspecified when and how it is called.

        Parameters
        p	-	pointer obtained from allocate()
        n	-	number of objects earlier passed to allocate()
		*/
      void
      deallocate(pointer __p, size_type)      // __p is not permitted to be a null pointer.
      { ::operator delete(__p); }

	  /*
		Returns the maximum theoretically possible value of n, for which the call allocate(n, 0)
		 could succeed.
    	In most implementations, this returns std::numeric_limits<size_type>::max().
      */
      size_type
      max_size() const throw()
      { return size_t(-1) / sizeof(_Tp); }


      /*
      Constructs an object of type T in allocated uninitialized storage pointed to by p,
      using placement-new

       	Calls new((void *)p) T(val)

      p	-	pointer to allocated uninitialized storage
      val	-	the value to use as the copy constructor argument
      */
      void
      construct(pointer __p, const _Tp& __val)
      { ::new(__p) _Tp(__val); }


      /*
      Constructs an object of type T in allocated uninitialized storage pointed to by p,
      using placement-new

      	Calls ::new((void *)p) U(std::forward<Args>(args)...)

      p	-	pointer to allocated uninitialized storage
      val	-	the value to use as the copy constructor argument
      args...	-	the constructor arguments to use
      */
      template< class U, class... Args >
      void construct( U* p, Args&&... args );

      /*
      Calls the destructor of the object pointed to by p

      	Calls ((T*)p)->~T()

      p	-	pointer to the object that is going to be destroyed
      */
      void
      destroy(pointer __p) { __p->~_Tp(); }

      /*
      Calls the destructor of the object pointed to by p

      	Calls p->~U()

      p	-	pointer to the object that is going to be destroyed
      */
      template< class U >
      void destroy( U* p );
    };

	/*
    Compares two default allocators. Since default allocators are stateless, two default allocators are always equal.
    */
  	template<typename _Tp>
    inline bool
    operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return true; }

    /*
    Compares two default allocators. Since default allocators are stateless, two default allocators are always equal.
    */
    template<typename _Tp>
    inline bool
    operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return false; }

_GLIBCXX_END_NAMESPACE

#endif
