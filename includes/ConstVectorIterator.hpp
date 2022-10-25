/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConstVectorIterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:12:15 by abensett          #+#    #+#             */
/*   Updated: 2022/10/06 11:57:18 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTVECTORITERATOR_HPP
#define CONSTVECTORITERATOR_HPP

#include "utils.hpp"
#include "VectorIterator.hpp"

namespace ft
{
	template <class T>
	class VectorIterator;
	// Const vector iterator
	template <typename T>
	class ConstVectorIterator
	{
		public:
			typedef ft::iterator_traits<iterator<std::random_access_iterator_tag, const T> >		traits;			// specify the iterator traits
			typedef typename traits::value_type												value_type;
			typedef	typename traits::difference_type										difference_type;
			typedef	typename traits::pointer												pointer;
			typedef	typename traits::reference												reference;
			typedef	typename traits::iterator_category										iterator_category;

			// Constructors
			ConstVectorIterator() : _ptr(NULL) {};
			// Copy, constructor from pointer
			ConstVectorIterator(pointer ptr) : _ptr(ptr) {};
			// Copy from other const iterator
			ConstVectorIterator(const ConstVectorIterator &rhs) : _ptr(rhs._ptr) {};
			// Copy from other random iterator
			ConstVectorIterator(const VectorIterator<T> &rhs) : _ptr(rhs._ptr) {};
			// destructor
			~ConstVectorIterator() {};
			// Operators
			// assignation operator
			ConstVectorIterator operator=( const ConstVectorIterator & rhs)
			{
				// protection de l'autodéfinition
				if (*this != &rhs)
					this->_ptr = rhs._ptr;
				return (*this);
			};
			ConstVectorIterator operator=( const VectorIterator<T> & rhs)
			{
				
				this->_ptr = rhs._ptr;
				return (*this);
			};
			// comparison operators
			bool operator==(const ConstVectorIterator &rhs) const { return (_ptr == rhs._ptr); };
			bool operator!=(const ConstVectorIterator &rhs) const { return (_ptr != rhs._ptr); };
			// rvalue dereferencing operator
			reference operator*() const { return (*_ptr); };
			// pointer dereferencing operator
			pointer operator->() const { return (_ptr); };
			// lvalue pointer dereferencing operator
			pointer operator&() const { return (_ptr); };
			// incrementation operator iterator++
			ConstVectorIterator  & operator ++ () { ++_ptr; return (*this); };
			// post-incrementation operator ++iterator
			ConstVectorIterator operator++(int) {
				ConstVectorIterator tmp(*this);
				++_ptr;
				return (tmp); };
			// decrementation operator iterator--
			ConstVectorIterator &operator--() { --_ptr; return (*this); };
			// post-decrementation operator --iterator
			ConstVectorIterator operator--(int) {
				ConstVectorIterator tmp(*this);
				--_ptr;
				return (tmp); };

			// addition operator iterator + int
			ConstVectorIterator operator+(difference_type n) const
			{ 
				ConstVectorIterator tmp(*this);
				tmp += n;
				return (tmp); 
			};
			// addition operator int + iterator
			friend ConstVectorIterator operator+(difference_type n,  ConstVectorIterator &rhs) 
			{	return (rhs + n);	};
			// difference_type operator iterator - int
			ConstVectorIterator operator- (difference_type n) 
			{ 
				ConstVectorIterator tmp(*this);
				tmp -= n;
				return (tmp); 
			};
			// difference_type operator iterator1 - iterator2
			difference_type operator - (const ConstVectorIterator &rhs) const { return (_ptr - rhs._ptr); };

			// COMPARAISON OPERATORS
			// rvalue dereferencing operator
			// comparison operator iterator1 < iterator2
			bool operator<(const ConstVectorIterator &rhs) const { return (_ptr < rhs._ptr); };
			// comparison operator iterator1 > iterator2
			bool operator>(const ConstVectorIterator &rhs) const { return (_ptr > rhs._ptr); };
			// comparison operator iterator1 <= iterator2
			bool operator<=(const ConstVectorIterator &rhs) const { return (_ptr <= rhs._ptr); };
			// comparison operator iterator1 >= iterator2
			bool operator>=(const ConstVectorIterator &rhs) const { return (_ptr >= rhs._ptr); };

			// With non const operators
			bool operator==(const VectorIterator<T> &rhs) const { return (_ptr == rhs._ptr); };
			bool operator!=(const  VectorIterator<T> &rhs) const { return (_ptr != rhs._ptr); };
			// rvalue dereferencing operator
			// comparison operator iterator1 < iterator2
			bool operator<(const VectorIterator<T> &rhs) const { return (_ptr < rhs._ptr); };
			// comparison operator iterator1 > iterator2
			bool operator>(const VectorIterator<T> &rhs) const { return (_ptr > rhs._ptr); };
			// comparison operator iterator1 <= iterator2
			bool operator<=(const VectorIterator<T> &rhs) const { return (_ptr <= rhs._ptr); };
			// comparison operator iterator1 >= iterator2
			bool operator>=(const VectorIterator<T> &rhs) const { return (_ptr >= rhs._ptr); };

			// addition assignation operator iterator += int
			ConstVectorIterator &operator+=(difference_type n) 
			{ 
				_ptr += n;
				return (*this);
			};
			// diffrence assignation operator iterator -= int
			ConstVectorIterator &operator-=(difference_type n) { _ptr -= n; return (*this); };

			// dereferencing operator iterator[int]
			reference operator[](difference_type n) const { return (_ptr[n]); };

			// pointer to the current element
			pointer															_ptr;

	};
	

};
// End of namespace FT
#endif
