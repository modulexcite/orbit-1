// Copyright (c) 2020 The Orbit Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ORBIT_CLIENT_DATA_FUNCTION_INFO_SET_H_
#define ORBIT_CLIENT_DATA_FUNCTION_INFO_SET_H_

#include <absl/container/flat_hash_set.h>

#include "capture_data.pb.h"

namespace internal {
struct HashFunctionInfo {
  size_t operator()(const orbit_client_protos::FunctionInfo& function) const {
    return std::hash<uint64_t>{}(function.address()) * 37 + std::hash<uint64_t>{}(function.size());
  }
};

struct EqualFunctionInfo {
  bool operator()(const orbit_client_protos::FunctionInfo& left,
                  const orbit_client_protos::FunctionInfo& right) const {
    return left.size() == right.size() && left.name() == right.name() &&
           left.pretty_name() == right.pretty_name() &&
           left.loaded_module_path() == right.loaded_module_path() &&
           left.module_base_address() == right.module_base_address() &&
           left.address() == right.address() && left.load_bias() == right.load_bias() &&
           left.file().compare(right.file()) == 0 && left.line() == right.line();
  }
};

}  // namespace internal

using FunctionInfoSet =
    absl::flat_hash_set<orbit_client_protos::FunctionInfo, internal::HashFunctionInfo,
                        internal::EqualFunctionInfo>;

#endif  // ORBIT_CLIENT_DATA_FUNCTION_INFO_SET_H_
