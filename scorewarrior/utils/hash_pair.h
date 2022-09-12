#ifndef SCOREWARRIOR_UTILS_HASH_PAIR_H_
#define SCOREWARRIOR_UTILS_HASH_PAIR_H_

#include <bits/functional_hash.h>
#include <cstddef>
#include <utility>

namespace scorewarrior::utils {

struct HashPair {
  template <class T1, class T2>
  size_t operator()(const std::pair<T1, T2>& p) const {
    auto hash1 = std::hash<T1>{}(p.first);
    auto hash2 = std::hash<T2>{}(p.second);

    if (hash1 != hash2) {
      return hash1 ^ hash2;
    }

    // If hash1 == hash2, their XOR is zero.
    return hash1;
  }
};

} // namespace scorewarrior::utils

#endif // SCOREWARRIOR_UTILS_HASH_PAIR_H_
