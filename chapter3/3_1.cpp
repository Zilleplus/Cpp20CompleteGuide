#include <compare>
#include <type_traits>

template <typename T>
T maxValue1(T a, T b) {
  return b < a ? a : b;
}

//

template <typename T>
requires(!std::is_pointer_v<T>) T maxValue2(T a, T b) { return b < a ? a : b; }

//

template <typename T>
concept IsPointer = std::is_pointer_v<T>;

template <typename T>
T maxValue3(T a, T b) {
  return b < a ? a : b;
}

auto test3 = maxValue3(4, 3);

// overloading with concepts

template <typename T>
T maxValue4(T a, T b) requires !std::is_pointer_v<T> {
  return b < a ? a : b;
}

template <typename T>
T maxValue4(T a, T b) requires std::is_pointer_v<T> {
  return maxValue4(*a, *b);
}

auto test4 = maxValue4(4, 3);

// overload resolution with concepts
// -> just constraint the first part

template <typename T>
T maxValue5(T a, T b) {
  return b < a ? a : b;
}

template <typename T>
T maxValue5(T a, T b) requires std::is_pointer_v<T> {
  return maxValue5(*a, *b);
}

auto test5 = maxValue5(4, 3);

// type constraint

template <IsPointer T>
T maxValue5(T a, T b) {
  return maxValue(*a, *b);
}

auto maxValue6(IsPointer auto a, IsPointer auto b) { return maxValue1(*a, *b); }

auto test6 = maxValue6(new int{4}, new int{3});

// trailing requires: standard concept:

auto maxValue7(IsPointer auto a, IsPointer auto b) requires
    std::three_way_comparable_with<decltype(*a), decltype(*b)> {
  return maxValue1(a, b);
}

// trailing requires: standard concept:

template <typename T>
concept IsPointer2 = requires(T p) {
  *p;
};

template <typename T>
concept IsPointer3 = requires(T p) {  // requires expression
  *p;
  { p < p } -> std::convertible_to<bool>;  // yields bool
  p == nullptr;                            // can compare with nullptr
};

// we use 2 times the requires keyword
// first time: requires clause
// second time: requires expression
template <typename T>
requires requires(T p) { *p; }  // constraint template wiht ad-hoc requirement
auto maxValue(T a, T b) { return maxValue1(*a, *b); }
