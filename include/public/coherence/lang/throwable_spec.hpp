/*
 * Copyright (c) 2000, 2020, Oracle and/or its affiliates.
 *
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 */
#ifndef COH_THROWABLE_SPEC_HPP
#define COH_THROWABLE_SPEC_HPP

#include "coherence/lang/compatibility.hpp"

#include "coherence/lang/class_spec.hpp"
#include "coherence/lang/lang_spec.hpp"
#include "coherence/lang/TypedHandle.hpp"
#include "coherence/lang/TypedHolder.hpp"

#include <stdexcept>

COH_OPEN_NAMESPACE2(coherence,lang)

class Exception;

// ----- local helpers ------------------------------------------------------

/**
* Return an empty std::exception derivative.
*
* @return an empty exception.
*/
template<class E> inline E coh_get_default_exception()
    {
    return E("");
    }

/**
* Return an empty std::exception derivative.
* @internal
*
* @return an empty exception.
*/
template<> inline std::exception coh_get_default_exception<std::exception>()
    {
    return std::exception();
    }

/**
* Return an empty std::exception derivative.
* @internal
*
* @return an empty exception.
*/
template<> inline std::bad_cast coh_get_default_exception<std::bad_cast>()
    {
    return std::bad_cast();
    }

/**
* Return an empty std::exception derivative.
* @internal
*
* @return an empty exception.
*/
template<> inline std::bad_typeid coh_get_default_exception<std::bad_typeid>()
    {
    return std::bad_typeid();
    }

/**
* Return an empty std::exception derivative.
* @internal
*
* @return an empty exception.
*/
template<> inline std::bad_alloc coh_get_default_exception<std::bad_alloc>()
    {
    return std::bad_alloc();
    }

/**
* @internal
*/
template<> class Alias<Exception>
    {
    public:
        typedef std::exception alias;
    };

/**
* Helper for defining a throwable managed class.
*
* It addition to the features auto-generated by the class_spec<> helper template
* throwable_spec<> auto-generates an implementation of "raise() const"
* which (re)throws the exception as a View.
*
* A normal throwable class definition would be:
* @code
* class MyException
*   : public throwable_spec<MyException,
*       extends<SomeOtherException, std::exception> >
*   {
*   // add support for auto-generated static create methods
*   friend class factory<MyException>;
*
*   protected:
*       // Constructors are defined as protected, and access via
*       // auto-generated create methods, with matching signatures
*       MyException(String::View vsMessage = String::null_string,
*                   Exception::View vCause = NULL)
*           : super(vsMessage, vCause)
*           {
*           }
*   };
* @endcode
*
* The extends template class for throwables is used to define an alias
* exception in the std::exception hierarchy, via a second template parameter.
* When thrown the resulting throwable can be caught by its View type hierarchy
* or by its std::exception hierarchy.  This parameter is optional and defaults
* to the alias type of the parent exception.
*
* @see Exception
* @see extends
* @see implements
*
* @author mf 2008.07.14
*/
template<class T,
         class E,
         class I = implements<>,
         class H = typename E::inherited::hierarchy >
class throwable_spec
    : public class_spec<T, E, I>
    {
    // ----- typedefs -------------------------------------------------------

    public:
        /**
        * Specification definition
        */
        typedef throwable_spec this_spec;

        /**
        * Definition T's parent class
        */
        typedef throwable_spec super;

        /**
        * Definition of the spec's parent class
        */
        typedef class_spec<T, E, I> super_spec;

        /**
        * Alias into std::exception hierarchy
        */
        typedef typename E::alias alias;

        /**
        * View definition
        */
        typedef typename class_spec<T, E, I>::View View;

    // ----- nested type: hierarchy -----------------------------------------

    public:
        /**
        * The hierarchy class wraps the Coherence C++ Exception classes in a
        * object that preserves their hierarchical structure.
        */
        class hierarchy
            : public View, public H
            {
            // ----- constructors ---------------------------------------

            public:
                /**
                * Default constructor
                */
                hierarchy()
                    {
                    }

                /**
                * Copy constructor
                */
                hierarchy(const hierarchy& that)
                        : View(that), H(that)
                    {
                    }

                /**
                 * Create a new hierarchy based on a View.
                 */
                explicit hierarchy(const View& vE)
                        : View(vE), H(vE)
                    {
                    }
            };


    // ----- nested class: bridge -------------------------------------------

    public:
        /**
        * bridge joins two hierarchy types into a single type.
        *
        * The intended usage is to merge support for std exceptions into the
        * coherence exception hierarchy.
        *
        * @author mf  2008.05.15
        */
        class bridge
            : public hierarchy, public alias
            {
            // ----- constructors ---------------------------------------

            public:
                /**
                * Construct a bridge with a specific object.
                *
                * @param vEx  A view to the object this bridge should contain
                */
                bridge(const View &vEx)
                    : hierarchy(vEx), alias(coh_get_default_exception<alias>())
                    {
                    }

                /**
                * Copy constructor.
                *
                * @param that  The hierarchyBase to copy.
                */
                bridge(const bridge& that)
                    : hierarchy(that), alias(that)
                    {
                    }

                /**
                * Destructor.
                */
                virtual ~bridge() throw()
                    {
                    }


            // ----- std::exception interface ---------------------------

            public:
                /**
                * Returns a C-style character string describing the general
                * cause of the current error.
                *
                * Note: The memory for the returned array is managed by the
                *       referenced Exception and is only valid for the
                *       lifetime of the Exception.
                *
                * @return the C-style character string describing the general
                *         cause of the current error.
                */
                virtual const char* what() const throw()
                    {
                    return ((View)(*this))
                        ->getDescription()->getCString();
                    }
            };

    // ----- constructors ---------------------------------------------------

    protected:
        /**
        * Generate a set of proxy constructors matching the signatures of the
        * parent class's constructors.
        *
        * NOTE: Compilation errors referencing this line likely indicate that
        *       class being defined by this spec makes calls a "super"
        *       constructor supplying a set of parameters for which there is
        *       no exact match on the parent class.
        */
        COH_DEFINE_PROXY_CONSTRUCTORS(throwable_spec)

    public:
        /**
        * @inheritDoc
        */
        virtual void raise() const
            {
            throw bridge(static_cast<const T*>(this));
            }
    };

COH_CLOSE_NAMESPACE2

#endif // COH_THROWABLE_SPEC_HPP
