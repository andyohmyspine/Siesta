#pragma once

#include <cstdint>
#include <concepts>

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

using real32 = float;
using real64 = double;

template<typename T>
concept CReal = std::floating_point<T>;

using TTypeOfNull = decltype(nullptr);

#include <string>
#include <string_view>
#include <sstream>

using TString = std::string;
using TStringView = std::string_view;
using TStringStream = std::stringstream;

#include <memory>

template<typename T>
using PSharedPtr = std::shared_ptr<T>;

template<typename T, typename ... Args>
inline PSharedPtr<T> MakeShared(Args&&... InArgs)
{
	return std::make_shared<T>(std::forward<Args>(InArgs)...);
}

template<typename T>
using PUniquePtr = std::unique_ptr<T>;

template<typename T, typename ... Args>
inline PUniquePtr<T> MakeUnique(Args&&... InArgs)
{
	return std::make_unique<T>(std::forward<Args>(InArgs)...);
}

template<typename T>
inline PUniquePtr<T> WrapUnique(T* Obj)
{
	return PUniquePtr<T>(Obj);
}


template<typename T>
using PWeakPtr = std::weak_ptr<T>;

#include <vector>

template<typename T>
using PDefAllocator = std::allocator<T>;

template<typename T, typename Alloc = PDefAllocator<T>>
using PDynArray = std::vector<T, Alloc>;

#include <array>
template<typename T, uint64 Size>
using PArray = std::array<T, Size>;

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

#include <variant>

template<typename ... Types>
using PVariant = std::variant<Types...>;

using TMonostate = std::monostate;

#include <stdexcept>
using TRuntimeError = std::runtime_error;

// Macros
#define SIESTA_STRINGIFY(x) #x

inline constexpr auto MakeVariantFromValuesHelper(auto... Values)
{
	return PVariant<TMonostate, decltype(Values)...>();
}

#include <functional>

template<typename TRv>
using PFunction = std::function<TRv>;

#define SIESTA_MAKE_VARIANT_TYPE_FROM_VALUES(Name, ...) using Name = decltype(MakeVariantFromValuesHelper(__VA_ARGS__))
#define SIESTA_MAKE_TUPLE_TYPE_FROM_VALUES(Name, ...) using Name = decltype(std::make_tuple(__VA_ARGS__))

#define SIESTA_PASTE(a, b) a ## b
#define SIESTA_PASTE_2(a, b) SIESTA_PASTE(a, b)
#define SIESTA_PASTE_3(a, b, c) SIESTA_PASTE_2(a, SIESTA_PASTE_2(b, c))

#define SIESTA_SIMPLE_TYPE_CONVERTER(_type)                                                          \
	inline constexpr _type SIESTA_PASTE_2(to_, _type)(std::convertible_to<_type> auto value) noexcept \
	{                                                                                                \
		return static_cast<_type>(value);                                                            \
	}

SIESTA_SIMPLE_TYPE_CONVERTER(uint8);
SIESTA_SIMPLE_TYPE_CONVERTER(uint16);
SIESTA_SIMPLE_TYPE_CONVERTER(uint32);
SIESTA_SIMPLE_TYPE_CONVERTER(uint64);
SIESTA_SIMPLE_TYPE_CONVERTER(int8);
SIESTA_SIMPLE_TYPE_CONVERTER(int16);
SIESTA_SIMPLE_TYPE_CONVERTER(int32);
SIESTA_SIMPLE_TYPE_CONVERTER(int64);
SIESTA_SIMPLE_TYPE_CONVERTER(float);
SIESTA_SIMPLE_TYPE_CONVERTER(double);

#define match_enum(x) [&, x] { using _internal_It = decltype(x); switch(x) 
#define match_case(x) case _internal_It::x: 
#define match_default() throw TRuntimeError("Unknown switch case.")
#define end_match throw TRuntimeError("Unknown match case."); }()