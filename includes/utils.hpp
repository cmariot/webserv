/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:12:15 by abensett          #+#    #+#             */
/*   Updated: 2022/10/24 21:31:12 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <iterator>

namespace ft
{

	/*
	**	ITERATOR BASE CLASS
	** helper to define the iterator traits of an iterator.
	*/
	template<typename Category, typename T, typename Difference = std::ptrdiff_t, typename Pointer = T*, typename   Reference = T&>
	struct iterator{
	typedef T 					value_type;				// The type "pointed to" by the iterator.
	typedef Difference 			difference_type;		// The type to represent the difference between two iterators.
	typedef	Pointer				pointer;				// A type to represent a pointer-to-value_type
	typedef Reference 			reference;				// A type to represent a reference-to-value_type
	typedef Category			iterator_category;		// The iterator category (input, output, forward, bidirectional, random access)
	};




	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag  : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag{};		//Categories used to identify random access iterators

	/*
	**	ITERATOR_TRAITS
	** 	- A type trait class that provides a uniform interface to obtaining properties of iterator types.
	**  - specializations for iterator types
	** MANDATORY IF YOU WANT TO IMPLEMENT YOUR OWN ITERATOR
	*/
	// STRUCT public whereas CLASS private
	template <class Iterator> struct iterator_traits
	{
		typedef typename Iterator::difference_type 			difference_type;
		typedef typename Iterator::value_type				value_type;
		typedef	typename Iterator::pointer					pointer;
		typedef typename Iterator::reference 				reference;
		typedef typename Iterator::iterator_category		iterator_category;
	};

	template <class T> struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t 							difference_type;
		typedef T 										value_type;
  		typedef T* 										pointer;
  		typedef T& 										reference;
   		typedef std::random_access_iterator_tag 		iterator_category;
	};

	template <class T> struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t 							difference_type;
		typedef T										value_type;
		typedef const	T* 								pointer;
		typedef const	T&								reference;
		typedef std::random_access_iterator_tag 		iterator_category;
	};

/* REVERSE_ITERATOR
// **
// ** 	- A reverse iterator is an iterator that moves in the opposite
// ** direction of a given iterator.
// */
template <class Iterator> class reverse_iterator
{
	public :
		Iterator 										_base_iterator;
		typedef ft::iterator_traits<Iterator>			traits;			// specify the iterator traits
		typedef Iterator 								iterator_type;
		typedef typename traits::value_type				value_type;
		typedef	typename traits::difference_type		difference_type;
		typedef	typename traits::pointer				pointer;
		typedef	typename traits::reference				reference;
		typedef	typename traits::iterator_category		iterator_category;

		// CONSTRUCTORS
		// default constructor
		reverse_iterator () { _base_iterator = iterator_type(); };
		// initialize constructor
		reverse_iterator (iterator_type it)	{ _base_iterator = it; };
		// copy constructor
		template <class Iter> reverse_iterator(const reverse_iterator<Iter>& rev_it)
		{ *this = rev_it; };

		// OPERATORS
		// assignation operator
		template< class U >
		reverse_iterator& operator=( const reverse_iterator<U>& other )
		{
			_base_iterator = other.base();
			return *this;
		};
		// base -> returns the underlying iterator
		iterator_type base() const { return _base_iterator; };
		// * -> dereference operator
		reference operator*() const
		{
			Iterator tmp = _base_iterator;
			return *--tmp;
		};
		// + -> addition operator
		reverse_iterator operator+(difference_type n) const
		{ return( base() - n); };
		// ++ -> increment operator
		reverse_iterator& operator++()
		{
			--_base_iterator;
			return *this;
		};
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--_base_iterator;
			return tmp;
		};
		// += -> addition and assignment operator
		reverse_iterator& operator+=(difference_type n)
		{
			_base_iterator -= n;
			return *this;
		};
		// - -> subtraction operator
		reverse_iterator operator-(difference_type n) const
		{ return (base() + n);};

		// -- -> decrement operator
		reverse_iterator& operator--()
		{
			++_base_iterator;
			return *this;
		};
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++_base_iterator;
			return tmp;
		};
		// -= -> subtraction and assignment operator
		reverse_iterator& operator-=(difference_type n)
		{
			_base_iterator += n;
			return *this;
		};
		// -> deference operator
		pointer operator->() const
		{ return &(operator*()); };

		// [] -> mem access operator : access the element at n and return a reference
		reference operator[](difference_type n) const
		{ return *(*this + n); };
};
// End of class reverse_iterator

// Non-member function overloads of reverse_iterator operators
// Comparison operators
// =
template< class Iterator1, class Iterator2 >
 bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{ return lhs.base() == rhs.base(); };
// !=
template< class Iterator1, class Iterator2 >
 bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{ return lhs.base() != rhs.base(); };
// <
template< class Iterator1, class Iterator2 >
bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{ return lhs.base() > rhs.base(); };
// <=
template< class Iterator1, class Iterator2 >
bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{ return lhs.base() >= rhs.base(); };
// >
template< class Iterator1, class Iterator2 >
bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{ return lhs.base() < rhs.base(); };
// >=
template< class Iterator1, class Iterator2 >
 bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
{ return lhs.base() <= rhs.base(); };

// operator+ : addition operator and  subtraction operator
// +
template <class Iterator> reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
{ return reverse_iterator<Iterator>(rev_it.base() - n); };
//-
template <class Iterator> typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{ return rhs.base() - lhs.base(); };

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator - (const reverse_iterator<Iterator1> & lhs, const reverse_iterator<Iterator2> & rhs)
{
		return (rhs.base() - lhs.base());
};
// End of reverse_iterator

// REVERSE_ITERATOR OPERATORS

/* ENABLE_IF
**
**- A type trait that provides a member typedef type if the condition is true, otherwise no member typedef is provided.
** SFINAE  Substitution Failure Is Not An Error
** Using types that are not enabled by enable_if
** for template specialization will result in compile-time error.
*/
template <bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

/* IS_INTEGRAL
**
**- A type trait that determines whether T is an integral type.
** - Integral types are those that can be represented as a sequence of bits.
** - bool, char, wchar_t, char16_t, char32_t, short, int, long, long long,
** - unsigned short, unsigned int, unsigned long, unsigned long long
**
** - if integral type then static const bool value = true
*/
template< class T > struct is_integral
{	static const bool value = false; };

template <> struct is_integral<bool> { static const bool value = true; };
template <> struct is_integral<char> { static const bool value = true; };
template <> struct is_integral<wchar_t> { static const bool value = true; };
template <> struct is_integral<short> { static const bool value = true; };
template <> struct is_integral<int> { static const bool value = true; };
template <> struct is_integral<long> { static const bool value = true; };
template <> struct is_integral<long long> { static const bool value = true; };
template <> struct is_integral<unsigned short> { static const bool value = true; };
template <> struct is_integral<unsigned int> { static const bool value = true; };
template <> struct is_integral<unsigned long> { static const bool value = true; };
template <> struct is_integral<unsigned long long> { static const bool value = true; };

/* LEXICOGRAPHICAL_COMPARE
**
** - Compares the elements in the range [first1,last1) with those of the range beginning at first2,
** and returns true if all the elements in both ranges match or if the first range is lexicographically less than the second.
** - The elements are compared using operator< for this verions
*/
template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
 							InputIt2 first2, InputIt2 last2)
{
	for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
	{
		if (*first1 < *first2)
			return true;
		if (*first2 < *first1)
			return false;
	}
	return (first1 == last1) && (first2 != last2);
}


/* EQUAL
*	- Compares the elements in the range [first1,last1) with those of the range beginning at first2,
*	and returns true if all the elements in both ranges match.
*	- The elements are compared using operator== for this verions
*/
// template<class InputIt1, class InputIt2>
// bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
// {
//     for (; first1 != last1; ++first1, ++first2) {
//         if (!(*first1 == *first2)) {
//             return false;
//         }
//     }
//     return true;
// }

template <class InputIterator1, class InputIterator2>
bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
{
	while (lit != lend)
	{
		if (rit == rend || *rit != *lit)
			return (false);
		++lit, ++rit;
	}
	return (rit == rend);
}

template <class T>
bool equal (T & a, T & b)
{
	return (a == b);
}

/* PAIR
**
** - A pair is a simple container defined in <utility> that stores two heterogeneous objects as a single unit.
*/


template< class T1, class T2>
struct pair
{
	typedef T1 first_type;												// The type of the first element
	typedef T2 second_type;												// The type of the second element

	first_type 	first;													// the first stored value
	second_type second;													// the second stored value


	pair() : first(first_type()), second(second_type()) {};				// DEFAULT CONSTRUCTOR

	pair(const ft::pair <T1, T2 > & other):								// COPY CONSTRUCTOR
	first(other.first), second(other.second) {};

	template<class U, class V> pair (const ft::pair<U,V>& pr)				//  TEMPLATE COPY CONSTRUCTOR
	:first(pr.first),
	second(pr.second)
	{
	};
	pair (const first_type& a, const second_type& b) : first(a), second(b) {};	// INITIALIZATION CONSTRUCTOR

	pair& operator= (const pair& pr)						// ASSIGNMENT OPERATOR
	{
		if (this == &pr)
					return (*this);
		first = pr.first;
		second = pr.second;
		return *this;
	};

};

// NON-MEMBER FUNCTIONS FOR PAIR (RELATIONAL OPERATORS)
template <class T1, class T2>  bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{	return lhs.first == rhs.first && lhs.second == rhs.second;};
template <class T1, class T2>  bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{	return !(lhs == rhs);};
template <class T1, class T2>  bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); };
template <class T1, class T2> bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(rhs<lhs); };
template <class T1, class T2>  bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return rhs<lhs; };
template <class T1, class T2>  bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs<rhs); }


/* MAKE PAIR
**
** - Constructs a pair object with its elements initialized to the values passed as arguments.
*/
template <class T1, class T2>  pair<T1,T2> make_pair (T1 x, T2 y)
{ return ( pair<T1,T2>(x,y) ); };


};
// End of namespace FT
#endif
