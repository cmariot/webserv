/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:12:15 by abensett          #+#    #+#             */
/*   Updated: 2022/10/24 19:50:46 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP

#include "utils.hpp"
#include "ConstVectorIterator.hpp"

namespace ft
{
	template <typename T>

	// Iterator Vector = random access iterator
	// template <class T>
	// class ConstVectorIterator;
	
	class VectorIterator
	{
		public:
			typedef ft::iterator_traits<iterator<std::random_access_iterator_tag, T> >		traits;			// specify the iterator traits
			typedef typename traits::value_type												value_type;
			typedef	typename traits::difference_type										difference_type;
			typedef	typename traits::pointer												pointer;
			typedef	typename traits::reference												reference;
			typedef	typename traits::iterator_category										iterator_category;

			// Constructors
			VectorIterator() : _ptr(NULL) {};
			// Copy, constructor from pointer
			VectorIterator(pointer ptr) : _ptr(ptr) {};
			// destructor
			~VectorIterator() {};
			// Operators
			// assignation operator
			VectorIterator operator=( const VectorIterator &rhs)
			{
				// protection de l'autodéfinition
				if (*this != rhs)
					this->_ptr = rhs._ptr;
				return (*this);
			}
			// comparison operators
			bool operator==(const VectorIterator &rhs) const { return (_ptr == rhs._ptr); };
			bool operator!=(const VectorIterator &rhs) const { return (_ptr != rhs._ptr); };
			// rvalue dereferencing operator
			reference operator*() const { return (*_ptr); };
			// pointer dereferencing operator
			pointer operator->() const { return (_ptr); };
			// lvalue pointer dereferencing operator
			pointer operator&() const { return (_ptr); };
			// incrementation operator iterator++
			VectorIterator &operator++() { ++_ptr; return (*this); };
			// post-incrementation operator ++iterator
			VectorIterator operator++(int) {
				VectorIterator tmp(*this);
				++_ptr;
				return (tmp); };
			// decrementation operator iterator--
			VectorIterator &operator--() { --_ptr; return (*this); };
			// post-decrementation operator --iterator
			VectorIterator operator--(int) {
				VectorIterator tmp(*this);
				--_ptr;
				return (tmp); };

			// addition operator iterator + int
			VectorIterator operator+(difference_type n) const { return (VectorIterator(_ptr + n)); };
			// addition operator int + iterator
			friend VectorIterator operator+(difference_type n, const VectorIterator &rhs)  { return (VectorIterator(rhs._ptr + n)); };
			// difference_type operator iterator - int
			VectorIterator operator-(difference_type n) 
			{
				VectorIterator tmp(*this);
				tmp -= n;
				return (tmp);
			};
			// difference_type operator iterator1 - iterator2
			difference_type operator-( VectorIterator rhs)  { return (_ptr - rhs._ptr); };
			// difference_type operator iterator1 - cons iterator2
			difference_type operator-( ConstVectorIterator<T> rhs)  { return (_ptr - rhs._ptr); };
			
			// COMPARAISON OPERATORS
			// comparison operator iterator1 < iterator2
			bool operator<(const VectorIterator &rhs) const { return (_ptr < rhs._ptr); };
			// comparison operator iterator1 > iterator2
			bool operator>(const VectorIterator &rhs) const { return (_ptr > rhs._ptr); };
			// comparison operator iterator1 <= iterator2
			bool operator<=(const VectorIterator &rhs) const { return (_ptr <= rhs._ptr); };
			// comparison operator iterator1 >= iterator2
			bool operator>=(const VectorIterator &rhs) const { return (_ptr >= rhs._ptr); };

			// With const operators
			bool operator==(const ConstVectorIterator<T> &rhs) const { return (_ptr == rhs._ptr); };
			bool operator!=(const ConstVectorIterator<T> &rhs) const { return (_ptr != rhs._ptr); };
			bool operator<(const ConstVectorIterator<T> &rhs) const { return (_ptr < rhs._ptr); };
			// comparison operator iterator1 > iterator2
			bool operator>(const ConstVectorIterator<T> &rhs) const { return (_ptr > rhs._ptr); };
			// comparison operator iterator1 <= iterator2
			bool operator<=(const ConstVectorIterator<T> &rhs) const { return (_ptr <= rhs._ptr); };
			// comparison operator iterator1 >= iterator2
			bool operator>=(const ConstVectorIterator<T> &rhs) const { return (_ptr >= rhs._ptr); };
			
			// addition assignation operator iterator += int
			VectorIterator &operator+=(difference_type n) { _ptr += n; return (*this); };
			// diffrence assignation operator iterator -= int
			VectorIterator &operator-=(difference_type n) { _ptr -= n; return (*this); };

			// dereferencing operator iterator[int]
			reference operator[](difference_type n) const { return (_ptr[n]); };

			// pointer to the current element
			pointer 															_ptr;

	};

};
// End of namespace FT
#endif
