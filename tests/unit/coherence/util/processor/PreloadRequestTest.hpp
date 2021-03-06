/*
 * Copyright (c) 2000, 2020, Oracle and/or its affiliates.
 *
 * Licensed under the Universal Permissive License v 1.0 as shown at
 * http://oss.oracle.com/licenses/upl.
 */
#include "cxxtest/TestSuite.h"
#include "mock/CommonMocks.hpp"
#include "coherence/lang.ns"
#include "coherence/util/InvocableMap.hpp"
#include "coherence/util/processor/PreloadRequest.hpp"
#include "coherence/util/filter/AlwaysFilter.hpp"
#include "coherence/util/filter/NeverFilter.hpp"

using namespace coherence::lang;
using namespace coherence::util::processor;
using namespace coherence::util::filter;
using namespace mock;

/**
* Test Suite for the PreloadRequest object.
*/
class PreloadRequestSuite : public CxxTest::TestSuite
        {
        public:

        /**
        * Test process
        */
        void testProcess()
            {
            MockInvocableMapEntry::Handle hMockEntry =
                MockInvocableMapEntry::create();

            //set expectations
            hMockEntry->isPresent();
            hMockEntry->lastExpectation()->setBoolReturn(false);
            hMockEntry->getValue();

            PreloadRequest::Handle hProc =
                    PreloadRequest::create();
            //replay
            hMockEntry->replay();
            hProc->process(hMockEntry);

            //verify
            hMockEntry->verify();
            }

        /**
        * Test processAll
        */
        void testProcessAll()
            {
            MockInvocableMapEntry::Handle hMockEntry =
                MockInvocableMapEntry::create();
            Set::Handle hSet = HashSet::create();
            hSet->add(hMockEntry);

            //set expectations
            hMockEntry->isPresent();
            hMockEntry->lastExpectation()->setBoolReturn(false);
            hMockEntry->getValue();

            PreloadRequest::Handle hProc =
                    PreloadRequest::create();
            //replay
            hMockEntry->replay();
            hProc->processAll(hSet);

            //verify
            hMockEntry->verify();
            }

        /**
        * Test equals
        */
        void testEquals()
            {
            PreloadRequest::Handle hProc =
                    PreloadRequest::create();

            TS_ASSERT(hProc->equals(hProc));

            PreloadRequest::Handle hProc2 =
                    PreloadRequest::create();

            TS_ASSERT(hProc->equals(hProc2));
            TS_ASSERT(hProc2->equals(hProc));
            }

        };

