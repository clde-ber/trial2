#ifndef ENABLEIF_H
#define ENABLEIF_H

namespace ft
{
    // template< typename T, class It = iter< T > >
    template <typename T, T val>
	struct storage
	{
		static const T value = val;
	};

	struct false_type : public storage<bool, false> {};
	struct true_type : public storage<bool, true> {};

	template <class T> struct is_integral : public false_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short> : public true_type {};
	template <> struct is_integral<unsigned short> : public true_type {};
	template <> struct is_integral<long> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};
	template <> struct is_integral<long long> : public true_type {};
	template <> struct is_integral<unsigned long long> : public true_type {};

	template<bool B, typename T = void>
		struct enable_if {};

	template<typename T>
		struct enable_if<true, T> { typedef T type; };
}

#endif