/*
 * Copyright (c) 2000, 2020, Oracle and/or its affiliates.
 *
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 */
#ifndef COH_INVOKE_FILTER_REQUEST_HPP
#define COH_INVOKE_FILTER_REQUEST_HPP

#include "coherence/lang.ns"

#include "coherence/io/pof/PofReader.hpp"
#include "coherence/io/pof/PofWriter.hpp"

#include "coherence/net/PriorityTask.hpp"

#include "coherence/util/InvocableMap.hpp"

#include "private/coherence/component/net/extend/AbstractPofResponse.hpp"

#include "private/coherence/component/net/extend/protocol/cache/AbstractFilterRequest.hpp"



COH_OPEN_NAMESPACE6(coherence,component,net,extend,protocol,cache)

using coherence::component::net::extend::AbstractPofResponse;
using coherence::io::pof::PofReader;
using coherence::io::pof::PofWriter;
using coherence::net::PriorityTask;
using coherence::util::InvocableMap;


/**
* InvocableMap::invokeAll(Filter::View vFilter, EntryProcessor::View vAgent)
* Request message.
*
* @author jh  2008.02.29
*/
class COH_EXPORT InvokeFilterRequest
    : public class_spec<InvokeFilterRequest,
        extends<AbstractFilterRequest>,
        implements<PriorityTask> >
    {
    friend class factory<InvokeFilterRequest>;

    // ----- constructors ---------------------------------------------------

    protected:
        /**
        * Create a new InvokeFilterRequest instance.
        */
        InvokeFilterRequest();


    // ----- Message interface ----------------------------------------------

    public:
        /**
        * {@inheritDoc}
        */
        virtual int32_t getTypeId() const;


    // ----- PortableObject interface ---------------------------------------

    public:
        /**
        * {@inheritDoc}
        */
        virtual void readExternal(PofReader::Handle hIn);

        /**
        * {@inheritDoc}
        */
        virtual void writeExternal(PofWriter::Handle hOut) const;


    // ----- PriorityTask interface -----------------------------------------

    public:
        /**
        * {@inheritDoc}
        */
        virtual int32_t getSchedulingPriority() const;

        /**
        * {@inheritDoc}
        */
        virtual int64_t getExecutionTimeoutMillis() const;

        /**
        * {@inheritDoc}
        */
        virtual int64_t getRequestTimeoutMillis() const;

        /**
        * {@inheritDoc}
        */
        virtual void runCanceled(bool fAbandoned);


    // ----- Describable interface ------------------------------------------

    public:
        /**
        * {@inheritDoc}
        */
        virtual String::View getDescription() const;


    // ----- internal methods -----------------------------------------------

    protected:
        /**
        * Factory method: create a new Response instance.
        *
        * @param  the MessageFactory used to create the new Response object
        *
        * @return a new Response object
        */
        virtual AbstractPofResponse::Handle instantiateResponse(
                Protocol::MessageFactory::View vFactory) const;
    
        /**
        * {@inheritDoc}
        */
        virtual void onRun(AbstractPofResponse::Handle hResponse);


    // ----- accessors ------------------------------------------------------

    public:
        /**
        * Return the EntryProcessor associated with this Request.
        *
        * @return the EntryProcessor associated with this Request
        */
        virtual InvocableMap::EntryProcessor::View getProcessor() const;

        /**
        * Return the EntryProcessor associated with this Request.
        *
        * @return the EntryProcessor associated with this Request
        */
        virtual InvocableMap::EntryProcessor::Handle getProcessor();

        /**
        * Associate the given EntryProcessor with this Request.
        *
        * @param hProcessor  the EntryProcessor to associate with this
        *                    Request
        */
        virtual void setProcessor(
                    InvocableMap::EntryProcessor::Handle hProcessor);

        /**
        * Getter for property Cookie.
        * 
        * @return the opaque cookie used to support streaming.
        */
        virtual Binary::View getCookie() const;
        
        /**
        * Setter for property Cookie.
        * 
        * @param vBin  the opaque cookie used to support streaming.
        */
        virtual void setCookie(Binary::View vBin);

        
    // ----- constants ------------------------------------------------------

    public:
        /**
        * The type identifier of this Message class.
        */
        static const int32_t type_id = 55;


    // ----- data members ---------------------------------------------------

    protected:
        /**
        * The EntryProcessor associated with this Request.
        */
        FinalHandle<InvocableMap::EntryProcessor> f_hProcessor;

        /**
        * The opaque cookie used to support streaming.
        */
        FinalView<Binary> f_vCookie;
    };

COH_CLOSE_NAMESPACE6

#endif // COH_INVOKE_FILTER_REQUEST_HPP
