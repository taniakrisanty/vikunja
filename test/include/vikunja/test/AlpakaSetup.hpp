/* Copyright 2021 Hauke Mewes, Simeon Ehrig
 *
 * This file is part of vikunja.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <alpaka/alpaka.hpp>

namespace vikunja
{
    namespace test
    {
        template<
            typename TDim,
            typename TIdx,
            template<class, class>
            class THost,
            template<class, class>
            class TAcc,
            typename TQueue>
        struct TestAlpakaSetup
        {
        public:
            using Dim = TDim;
            using Idx = TIdx;
            using WorkDiv = alpaka::WorkDivMembers<Dim, Idx>;
            using Host = THost<Dim, Idx>;
            using Acc = TAcc<Dim, Idx>;
            using DevHost = alpaka::Dev<Host>;
            using DevAcc = alpaka::Dev<Acc>;
            using PltfHost = alpaka::Pltf<DevHost>;
            using PltfAcc = alpaka::Pltf<DevAcc>;
            using Queue = TQueue;
            using Event = alpaka::Event<Queue>;

            DevAcc devAcc;
            DevHost devHost;
            Queue queue;

            TestAlpakaSetup()
                : devAcc{alpaka::getDevByIdx<PltfAcc>(0u)}
                , devHost{alpaka::getDevByIdx<PltfHost>(0u)}
                , queue{devAcc}
            {
            }
        };
    } // namespace test
} // namespace vikunja
