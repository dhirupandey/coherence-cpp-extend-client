/*
 * Copyright (c) 2000, 2020, Oracle and/or its affiliates.
 *
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 */
#ifndef COH_COMPARABLE_MAX_HPP
#define COH_COMPARABLE_MAX_HPP

#include "coherence/lang.ns"

#include "coherence/util/aggregator/AbstractComparableAggregator.hpp"
#include "coherence/util/ValueExtractor.hpp"

COH_OPEN_NAMESPACE3(coherence,util,aggregator)


/**
* Calculates a maximum among values extracted from a set of entries in a Map.
* This aggregator is most commonly used with objects that implement
* <tt>Comparable</tt> such as <tt>String<tt/>; a <tt>Comparator</tt> can also
* be supplied to perform the comparisons.
*
* @author djl/pp  2008.05.12
*/
class COH_EXPORT ComparableMax
    : public class_spec<ComparableMax,
        extends<AbstractComparableAggregator> >
    {
    friend class factory<ComparableMax>;

    // ----- constructors ---------------------------------------------------

    protected:
        /**
        * Default constructor (necessary for the PortableObject interface).
        */
        ComparableMax();

        /**
        * Construct a ComparableMax aggregator.
        *
        * @param vExtractor   the extractor that provides an object to be 
        *                     compared
        * @param vComparator  the comparator used to compare the extracted
        *                     object, if NULL then the extracted object must
        *                     implement Comparable
        */
        ComparableMax(ValueExtractor::View vExtractor,
                Comparator::View vComparator = NULL);

        /**
        * Construct a ComparableMax that will aggregate values extracted
        * from a set of InvocableMap::Entry objects.
        *
        * @param vsMethod     the name of the method that could be invoked via
        *                     reflection and that returns values to aggregate;
        *                     this parameter can also be a dot-delimited 
        *                     sequence of method names which would result in
        *                     an aggregator based
        *                     on the ChainedExtractor that is based on an
        *                     array of corresponding ReflectionExtractor
        *                     objects
        * @param vComparator  the comparator used to compare the extracted
        *                     object, if NULL then the extracted object must
        *                     implement Comparable
        *
        * @since Coherence 12.1.2
        */
        ComparableMax(String::View vsMethod, 
            Comparator::View vComparator = NULL);

    private:
        /**
        * Blocked copy constructor.
        */
        ComparableMax(const ComparableMax&);


    // ----- AbstractAggregator Interface  ----------------------------------

    protected:
        /**
        * {@inheritDoc}
        */
        virtual void process(Object::View v, bool fFinal);
    };

COH_CLOSE_NAMESPACE3

#endif // COH_COMPARABLE_MAX_HPP
