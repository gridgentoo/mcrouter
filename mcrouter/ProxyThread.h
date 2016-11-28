/*
 *  Copyright (c) 2016, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include <folly/io/async/EventBase.h>

#include "mcrouter/Proxy.h"

namespace facebook { namespace memcache { namespace mcrouter {

class McrouterInstance;
class Proxy;

class ProxyThread {
 public:
  ProxyThread(McrouterInstance& router, size_t id);

  /**
   * Stops the underlying proxy thread and joins it.
   * Does nothing if "spawn" was not called.
   * Should be called at most once per process, i.e. it's fine to call it
   * after fork - only parent process will join the thread.
   */
  void stopAndJoin() noexcept;

  /**
   * Spawns a new proxy thread for execution. Should be called at most once.
   *
   * @throws std::system_error  If failed to spawn thread
   */
  void spawn();

  Proxy& proxy() {
    return proxyRef_;
  }
  folly::EventBase& eventBase() { return evbRef_; }

 private:
  std::unique_ptr<folly::EventBase> evb_;
  Proxy::Pointer proxy_;
  folly::EventBase& evbRef_;
  Proxy& proxyRef_;
  std::thread thread_;

  void stopAwriterThreads();
  static void proxyThreadRun(
      std::unique_ptr<folly::EventBase> evb,
      Proxy::Pointer proxy);
};
}}}  // facebook::memcache::mcrouter
