/*
 *  Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 *  This source code is licensed under the MIT license found in the LICENSE
 *  file in the root directory of this source tree.
 *
 */

/*
 *  THIS FILE IS AUTOGENERATED. DO NOT MODIFY IT; ALL CHANGES WILL BE LOST IN
 *  VAIN.
 *
 *  @generated
 */
#pragma once

#include <mcrouter/lib/carbon/TypeList.h>
#include <mcrouter/lib/network/CarbonRequestHandler.h>

#include "mcrouter/lib/carbon/test/gen/CarbonThriftTestMessages.h"

namespace carbon {
namespace test {

namespace detail {

using CarbonThriftTestRequestList = carbon::List<
    CustomRequest,
    DummyThriftRequest,
    ThriftTestRequest,
    facebook::memcache::McExecRequest,
    facebook::memcache::McQuitRequest,
    facebook::memcache::McShutdownRequest,
    facebook::memcache::McStatsRequest,
    facebook::memcache::McVersionRequest>;
} // namespace detail

template <class OnRequest>
class CarbonThriftTestRequestHandler
    : public carbon::
          CarbonRequestHandler<OnRequest, detail::CarbonThriftTestRequestList> {
 public:
  static constexpr const char* name = "CarbonThriftTest";

  template <class... Args>
  explicit CarbonThriftTestRequestHandler(Args&&... args)
      : carbon::CarbonRequestHandler<OnRequest, detail::CarbonThriftTestRequestList>(
            std::forward<Args>(args)...) {}
};
} // namespace test
} // namespace carbon
