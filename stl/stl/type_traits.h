//
// Created by 17535 on 2022/6/25.
//

#ifndef MYSTL_TYPE_TRAITS_H
#define MYSTL_TYPE_TRAITS_H

namespace stl {

template <class T, T v>
struct stl_integral_constant {
  static constexpr T value = v;
};

template <bool b>
using stl_bool_constant = stl_integral_constant<bool, b>;

using stl_true_type     = stl_bool_constant<true>;
using stl_false_type    = stl_bool_constant<false>;

template <class T>
struct has_trivial_destructor : public stl_false_type {};

template <>
struct has_trivial_destructor<char> : public stl_true_type {};

template <>
struct has_trivial_destructor<signed char> : public stl_true_type {};

template <>
struct has_trivial_destructor<unsigned char> : public stl_true_type {};

template <>
struct has_trivial_destructor<short> : public stl_true_type {};

template <>
struct has_trivial_destructor<unsigned short> : public stl_true_type {};

template <>
struct has_trivial_destructor<int> : public stl_true_type {};

template <>
struct has_trivial_destructor<unsigned int> : public stl_true_type {};

template <>
struct has_trivial_destructor<long> : public stl_true_type {};

template <>
struct has_trivial_destructor<unsigned long> : public stl_true_type {};

template <>
struct has_trivial_destructor<float> : public stl_true_type {};

template <>
struct has_trivial_destructor<double> : public stl_true_type {};

template <>
struct has_trivial_destructor<long double> : public stl_true_type {};

template <class T>
struct has_trivial_destructor<T *> : public stl_true_type {};

template <class T>
struct has_trivial_default_constructor : public stl_false_type {};

template <>
struct has_trivial_default_constructor<char> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<signed char> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<unsigned char> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<short> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<unsigned short> :
    public stl_true_type {};

template <>
struct has_trivial_default_constructor<int> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<unsigned int> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<long> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<unsigned long> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<float> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<double> : public stl_true_type {};

template <>
struct has_trivial_default_constructor<long double> : public stl_true_type {};

template <class T>
struct has_trivial_default_constructor<T *> : public stl_true_type {};

template <class T>
struct has_trivial_copy_constructor : public stl_false_type {};

template <>
struct has_trivial_copy_constructor<char> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<signed char> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<unsigned char> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<short> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<unsigned short> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<int> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<unsigned int> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<long> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<unsigned long> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<float> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<double> : public stl_true_type {};

template <>
struct has_trivial_copy_constructor<long double> : public stl_true_type {};

template <class T>
struct has_trivial_copy_constructor<T *> : public stl_true_type {};

template <class T>
struct has_trivial_assignment_operator : public stl_false_type {};

template <>
struct has_trivial_assignment_operator<char> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<signed char> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<unsigned char> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<short> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<unsigned short> :
    public stl_true_type {};

template <>
struct has_trivial_assignment_operator<int> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<unsigned int> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<long> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<unsigned long> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<float> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<double> : public stl_true_type {};

template <>
struct has_trivial_assignment_operator<long double> : public stl_true_type {};

template <class T>
struct has_trivial_assignment_operator<T *> : public stl_true_type {};

template <class T>
struct is_POD_type : public stl_false_type {};

template <>
struct is_POD_type<char> : public stl_true_type {};

template <>
struct is_POD_type<signed char> : public stl_true_type {};

template <>
struct is_POD_type<unsigned char> : public stl_true_type {};

template <>
struct is_POD_type<short> : public stl_true_type {};

template <>
struct is_POD_type<unsigned short> : public stl_true_type {};

template <>
struct is_POD_type<int> : public stl_true_type {};

template <>
struct is_POD_type<unsigned int> : public stl_true_type {};

template <>
struct is_POD_type<long> : public stl_true_type {};

template <>
struct is_POD_type<unsigned long> : public stl_true_type {};

template <>
struct is_POD_type<float> : public stl_true_type {};

template <>
struct is_POD_type<double> : public stl_true_type {};

template <>
struct is_POD_type<long double> : public stl_true_type {};

template <class T>
struct is_POD_type<T *> : public stl_true_type {};

} // namespace stl

#endif // MYSTL_TYPE_TRAITS_H
