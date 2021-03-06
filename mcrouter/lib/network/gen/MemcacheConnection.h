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

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <mcrouter/lib/CacheClientStats.h>
#include <mcrouter/lib/carbon/connection/ExternalCarbonConnectionImpl.h>
#include <mcrouter/lib/carbon/connection/InternalCarbonConnectionImpl.h>
#include <mcrouter/lib/carbon/connection/PooledCarbonConnectionImpl.h>

#include "mcrouter/lib/network/gen/MemcacheMessages.h"
#include "mcrouter/lib/network/gen/MemcacheRouterInfo.h"

namespace facebook {
namespace memcache {

class MemcacheConnection {
 public:
  using RouterInfo = MemcacheRouterInfo;

  virtual ~MemcacheConnection() = default;

  virtual void sendRequestOne(
      const McAddRequest&,
      carbon::RequestCb<McAddRequest>) = 0;
  virtual void sendRequestOne(
      const McAppendRequest&,
      carbon::RequestCb<McAppendRequest>) = 0;
  virtual void sendRequestOne(
      const McCasRequest&,
      carbon::RequestCb<McCasRequest>) = 0;
  virtual void sendRequestOne(
      const McDecrRequest&,
      carbon::RequestCb<McDecrRequest>) = 0;
  virtual void sendRequestOne(
      const McDeleteRequest&,
      carbon::RequestCb<McDeleteRequest>) = 0;
  virtual void sendRequestOne(
      const McFlushAllRequest&,
      carbon::RequestCb<McFlushAllRequest>) = 0;
  virtual void sendRequestOne(
      const McFlushReRequest&,
      carbon::RequestCb<McFlushReRequest>) = 0;
  virtual void sendRequestOne(
      const McGatRequest&,
      carbon::RequestCb<McGatRequest>) = 0;
  virtual void sendRequestOne(
      const McGatsRequest&,
      carbon::RequestCb<McGatsRequest>) = 0;
  virtual void sendRequestOne(
      const McGetRequest&,
      carbon::RequestCb<McGetRequest>) = 0;
  virtual void sendRequestOne(
      const McGetsRequest&,
      carbon::RequestCb<McGetsRequest>) = 0;
  virtual void sendRequestOne(
      const McIncrRequest&,
      carbon::RequestCb<McIncrRequest>) = 0;
  virtual void sendRequestOne(
      const McLeaseGetRequest&,
      carbon::RequestCb<McLeaseGetRequest>) = 0;
  virtual void sendRequestOne(
      const McLeaseSetRequest&,
      carbon::RequestCb<McLeaseSetRequest>) = 0;
  virtual void sendRequestOne(
      const McMetagetRequest&,
      carbon::RequestCb<McMetagetRequest>) = 0;
  virtual void sendRequestOne(
      const McPrependRequest&,
      carbon::RequestCb<McPrependRequest>) = 0;
  virtual void sendRequestOne(
      const McReplaceRequest&,
      carbon::RequestCb<McReplaceRequest>) = 0;
  virtual void sendRequestOne(
      const McSetRequest&,
      carbon::RequestCb<McSetRequest>) = 0;
  virtual void sendRequestOne(
      const McTouchRequest&,
      carbon::RequestCb<McTouchRequest>) = 0;

  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McAddRequest>>&&,
      carbon::RequestCb<McAddRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McAppendRequest>>&&,
      carbon::RequestCb<McAppendRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McCasRequest>>&&,
      carbon::RequestCb<McCasRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McDecrRequest>>&&,
      carbon::RequestCb<McDecrRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McDeleteRequest>>&&,
      carbon::RequestCb<McDeleteRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McFlushAllRequest>>&&,
      carbon::RequestCb<McFlushAllRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McFlushReRequest>>&&,
      carbon::RequestCb<McFlushReRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McGatRequest>>&&,
      carbon::RequestCb<McGatRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McGatsRequest>>&&,
      carbon::RequestCb<McGatsRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McGetRequest>>&&,
      carbon::RequestCb<McGetRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McGetsRequest>>&&,
      carbon::RequestCb<McGetsRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McIncrRequest>>&&,
      carbon::RequestCb<McIncrRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McLeaseGetRequest>>&&,
      carbon::RequestCb<McLeaseGetRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McLeaseSetRequest>>&&,
      carbon::RequestCb<McLeaseSetRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McMetagetRequest>>&&,
      carbon::RequestCb<McMetagetRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McPrependRequest>>&&,
      carbon::RequestCb<McPrependRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McReplaceRequest>>&&,
      carbon::RequestCb<McReplaceRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McSetRequest>>&&,
      carbon::RequestCb<McSetRequest>) = 0;
  virtual void sendRequestMulti(
      std::vector<std::reference_wrapper<const McTouchRequest>>&&,
      carbon::RequestCb<McTouchRequest>) = 0;

  virtual facebook::memcache::CacheClientCounters getStatCounters() const noexcept = 0;
  virtual std::unordered_map<std::string, std::string> getConfigOptions() = 0;
  virtual bool healthCheck() = 0;
  virtual std::unique_ptr<MemcacheConnection> recreate() = 0;
};

template <class Impl>
class MemcacheConnectionImpl : public MemcacheConnection {
 public:
  template <class... Args>
  explicit MemcacheConnectionImpl(Args&&... args)
      : impl_(std::forward<Args>(args)...) {}

  ~MemcacheConnectionImpl() = default;

  facebook::memcache::CacheClientCounters getStatCounters() const noexcept {
    return impl_.getStatCounters();
  }

  std::unordered_map<std::string, std::string> getConfigOptions() {
    return impl_.getConfigOptions();
  }

  bool healthCheck() {
    return impl_.healthCheck();
  }

  std::unique_ptr<MemcacheConnection> recreate() {
    return impl_.template recreate<MemcacheConnectionImpl<Impl>>();
  }

  void sendRequestOne(
      const McAddRequest& req,
      carbon::RequestCb<McAddRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McAppendRequest& req,
      carbon::RequestCb<McAppendRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McCasRequest& req,
      carbon::RequestCb<McCasRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McDecrRequest& req,
      carbon::RequestCb<McDecrRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McDeleteRequest& req,
      carbon::RequestCb<McDeleteRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McFlushAllRequest& req,
      carbon::RequestCb<McFlushAllRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McFlushReRequest& req,
      carbon::RequestCb<McFlushReRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McGatRequest& req,
      carbon::RequestCb<McGatRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McGatsRequest& req,
      carbon::RequestCb<McGatsRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McGetRequest& req,
      carbon::RequestCb<McGetRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McGetsRequest& req,
      carbon::RequestCb<McGetsRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McIncrRequest& req,
      carbon::RequestCb<McIncrRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McLeaseGetRequest& req,
      carbon::RequestCb<McLeaseGetRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McLeaseSetRequest& req,
      carbon::RequestCb<McLeaseSetRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McMetagetRequest& req,
      carbon::RequestCb<McMetagetRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McPrependRequest& req,
      carbon::RequestCb<McPrependRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McReplaceRequest& req,
      carbon::RequestCb<McReplaceRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McSetRequest& req,
      carbon::RequestCb<McSetRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }
  void sendRequestOne(
      const McTouchRequest& req,
      carbon::RequestCb<McTouchRequest> cb) {
    return impl_.sendRequestOne(req, std::move(cb));
  }

  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McAddRequest>>&& reqs,
      carbon::RequestCb<McAddRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McAppendRequest>>&& reqs,
      carbon::RequestCb<McAppendRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McCasRequest>>&& reqs,
      carbon::RequestCb<McCasRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McDecrRequest>>&& reqs,
      carbon::RequestCb<McDecrRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McDeleteRequest>>&& reqs,
      carbon::RequestCb<McDeleteRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McFlushAllRequest>>&& reqs,
      carbon::RequestCb<McFlushAllRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McFlushReRequest>>&& reqs,
      carbon::RequestCb<McFlushReRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McGatRequest>>&& reqs,
      carbon::RequestCb<McGatRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McGatsRequest>>&& reqs,
      carbon::RequestCb<McGatsRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McGetRequest>>&& reqs,
      carbon::RequestCb<McGetRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McGetsRequest>>&& reqs,
      carbon::RequestCb<McGetsRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McIncrRequest>>&& reqs,
      carbon::RequestCb<McIncrRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McLeaseGetRequest>>&& reqs,
      carbon::RequestCb<McLeaseGetRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McLeaseSetRequest>>&& reqs,
      carbon::RequestCb<McLeaseSetRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McMetagetRequest>>&& reqs,
      carbon::RequestCb<McMetagetRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McPrependRequest>>&& reqs,
      carbon::RequestCb<McPrependRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McReplaceRequest>>&& reqs,
      carbon::RequestCb<McReplaceRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McSetRequest>>&& reqs,
      carbon::RequestCb<McSetRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }
  void sendRequestMulti(
      std::vector<std::reference_wrapper<const McTouchRequest>>&& reqs,
      carbon::RequestCb<McTouchRequest> cb) {
    return impl_.sendRequestMulti(std::move(reqs), std::move(cb));
  }

 private:
  Impl impl_;
};

using MemcachePooledConnection =
    MemcacheConnectionImpl<carbon::PooledCarbonConnectionImpl<MemcacheConnection>>;
using MemcacheInternalConnection =
    MemcacheConnectionImpl<carbon::InternalCarbonConnectionImpl<MemcacheConnection>>;
using MemcacheExternalConnection =
    MemcacheConnectionImpl<carbon::ExternalCarbonConnectionImpl<MemcacheRouterInfo>>;
} // namespace memcache
} // namespace facebook
