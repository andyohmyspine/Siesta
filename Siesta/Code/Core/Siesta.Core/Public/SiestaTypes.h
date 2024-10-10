#pragma once

#include <cstdint>

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using STypeOfNull = decltype(nullptr);

#include <string>
#include <string_view>
#include <sstream>

using TString = std::string;
using TStringView = std::string_view;
using TStringStream = std::stringstream;

#include <memory>

template<typename T>
using PSharedPtr = std::shared_ptr<T>;

template<typename T>
using PUniquePtr = std::unique_ptr<T>;

template<typename T>
using PWeakPtr = std::weak_ptr<T>;

#include <vector>

template<typename T>
using PDefAllocator = std::allocator<T>;

template<typename T, typename Alloc = PDefAllocator<T>>
using PVector = std::vector<T, Alloc>;

#include <list>

template<typename T, typename Alloc = PDefAllocator<T>>
using PList = std::list<T, Alloc>;

#include <queue>

template<typename T>
using PQueue = std::queue<T>;

#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>

template<typename A, typename B>
using PPair = std::pair<A, B>;

template<typename T>
using PHasher = std::hash<T>;

template<typename Key, typename Value, typename Hasher = PHasher<Key>, typename Alloc = PDefAllocator<PPair<const Key, Value>>>
using PHashMap = std::unordered_map<Key, Value, Hasher, std::equal_to<Key>,  Alloc>;

template<typename Key, typename Value, typename Alloc = PDefAllocator<PPair<const Key, Value>>>
using PSortedHashMap = std::map<Key, Value, std::less<Key>, Alloc>;

template<typename Key, typename Hasher = PHasher<Key>, typename Alloc = PDefAllocator<Key>>
using PHashSet = std::unordered_set<Key, Hasher, std::equal_to<Key>, Alloc>;

template<typename Key, typename Alloc = PDefAllocator<Key>>
using PSortedHashSet = std::set<Key, std::less<Key>, Alloc>;

#include <future>
#include <mutex>

template<typename T>
using PFuture = std::future<T>;

using TMutex = std::mutex;
using TLockGuard = std::lock_guard<TMutex>;

#define SIESTA_STRINGIFY(x) #x