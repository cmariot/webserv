/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:12:15 by abensett          #+#    #+#             */
/*   Updated: 2022/10/24 19:35:41 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <stdexcept>
#include <limits>
#include <iostream>
#include "utils.hpp"
#include "VectorIterator.hpp"

// https://en.cppreference.com/w/cpp/container/vector

namespace ft
{
	// VECTOR CLASS
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		/*
		** Public Member Functions divided into 6 categories
		* 1. Member types
		* 2. Member functions
		* 3. Iterators
		* 4. Capacity
		* 5. Element access
		* 6. Modifiers
		*/

	public:
			/************************************************************
			 * 						MEMBER TYPES						*
			 ************************************************************/

			// typedef -> to define a type -> always the type specifer in first
			// typename -> specifies that the next identifier is a type

			/* First template parameter T -> represents the type of _begin stored */
			typedef T											value_type;
			/* Second template parameter Alloc
			** default allocator template used if not specified in args
			** (allocator<value_type>)
			**/
			typedef Alloc                                       allocator_type;
			/*
			** allocator_type::reference
			** A type provides a reference to an element stored in
			** a vector.

			** For the default allocator is a reference to value_type
			** (value_type&)
			*/
			typedef  T &     									 reference;

			/*
			** allocator_type::const_reference
			** Type that give a reference to a const element stored.
			** Useful to read and perform const operator.
			** A type const_reference can't be used to modify the value
			** of an element.
			** For the default allocat or is a const reference to value_type
			** (const value_type&)
			*/
			typedef  const T &								const_reference;

			/*
			** allocator_type::pointer
			** Type that gives a pointer to an element stored.
			** A type pointer can be used to modify the value of
			** an element.

			** For the default allocator is a pointer to value_type
			** (value_type*)
			*/
			typedef  T*							   		         pointer;

			/*
			** allocator_type::const_pointer
			** Type that gives a const pointer to an element stored.
			**  !!  Can't be used to modify the value of an element. !!
			** Better be using and iterator.

			** For the default allocator is a const pointer to value_type
			** (const value_type*)
			*/
			typedef  const T*								   	 const_pointer;

			/*
			** A random access iterator to value_type
			** That can read or modify any element stored.
			** !! Works like standard pointers !!
			** Convertible to const_iterator;
			*/
			typedef	typename ft::VectorIterator<value_type>          	   iterator;

			/*
			** A random access iterator to const value_type
			** That can read element stored.
			*/
			typedef typename ft::ConstVectorIterator<value_type>            const_iterator;

			/*
			** ft::reverse_iterator<iterator>
			** That can read or modify any element in a reversed vector.
			** Iterate in reverse.
			** !! Works like standard pointers !!
			*/
			typedef typename ft::reverse_iterator<iterator>            		 reverse_iterator;

			/*
			** ft::reverse_iterator<const_iterator>
			** That can read any element in a reversed the vector.
			*/
			typedef typename ft::reverse_iterator<const_iterator>      		 const_reverse_iterator;

			/*
			** A signed integral type.
			** Usually the same as ptrdiff_t.
			** Can represent the difference_type between iterators to the
			** element actually stored.
			** "The number of elements between two iterators."
			*/
			typedef typename ft::iterator_traits<iterator>::difference_type    difference_type;

			/*
			** An unsigned integral type that can represent any
			** non-negative value of difference_type_type
			** Usually the same as size_t.
			** = number of elements
			*/
			typedef typename std::size_t       				   size_type;

			public:
			/************************************************************
			 * 				CONSTRUCTEURS/DESTRUCTOR					*
			 ************************************************************/

			/*
			** DEFAULT CONSTRUCTOR
			** Constructs an empty container, with no elements.
			*/
			explicit vector (const allocator_type& alloc = allocator_type()):
				_alloc(alloc), _begin(NULL), _size(0), _capacity(0)
				{};

			/*
			** FILL CONSTRUCTOR
			** Constructs a container with n elements.
			*/
			explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()):
				_alloc(alloc)
				{
					_begin = _alloc.allocate(n);
					_size = n;
					_capacity = n;
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_begin + i, val);
				};
			/*
			** RANGE CONSTRUCTOR
			** Constructs a container with as many elements as the range
			** from first to last, with each element constructed from its
			** corresponding element in that range.
			*/
			template <class InputIterator>
			vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
                 const allocator_type& alloc = allocator_type())
				 : _alloc(alloc)
				 {
					_size = 0;
					for(InputIterator it = first; it != last; it++)
						_size++;
					_capacity = _size;
					 _begin = _alloc.allocate(_capacity);
					 for (size_type i = 0; i < _size; i++)
						 _alloc.construct(_begin + i, *(first++));
				 };
			/*
			** COPY CONSTRUCTOR
			** Constructs a container with a copy of each of the elements
			*/
			vector (const vector& x) :
			_alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				_begin = _alloc.allocate(x._capacity);
				for (size_type i = 0; i < x._size; i++)
					_alloc.construct(_begin + i, x._begin[i]);
			};
			/*
			** Destructor
			** Destroys the container object.
			*/
			~vector()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_alloc.deallocate(_begin, _capacity);
			};


			/*
			** Overload of the assignement operator
			** Assigns new contents to the container, replacing its current
			** contents, and modifying its size accordingly.
			*/
			vector& operator= (const vector& x)
			{
				vector tmp(x);
				swap(tmp);
				return (*this);
			};

			allocator_type	get_allocator(void) const
			{
				return (_alloc);
			};
			/************************************************************
			 * 					      ITERATORS		   		 		    *
			 ************************************************************/
			//Returns an iterator pointing to the first element in the vector.
			iterator begin() { return (iterator(_begin)); };
			//Returns a const_iterator pointing to the first element in the vector.
			const_iterator begin() const {return (const_iterator(_begin)); };
			// Returns an iterator referring to the past-the-end element in the vector container.
			iterator end()	{ return (iterator(_begin + _size)); };
			// Returns a const_iterator referring to the past-the-end element in the vector container.
			const_iterator end() const { return (const_iterator(_begin + _size)); };
			// Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
			reverse_iterator rbegin() { return (reverse_iterator(_begin + _size)); };
			// Returns a const_reverse_iterator pointing to the last element in the vector (i.e., its reverse beginning).
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(_begin + _size)); };
			// Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector
			// (which is considered its reverse end).
			reverse_iterator rend() { return (reverse_iterator(_begin)); };
			// Returns a const_reverse_iterator pointing to the theoretical element preceding the first element in the vector
			const_reverse_iterator rend() const { return (const_reverse_iterator(_begin)); };


			/************************************************************
			 * 					      CAPACITY		   		 		    *
			 ************************************************************/

			// Returns the number of elements in the vector.
			size_type size() const { return (_size); };
			// Returns the maximum number of elements that the vector can hold.
			size_type max_size() const { return (_alloc.max_size()); };
			// Returns the number of elements the storage space currently allocated for the vector
			size_type capacity() const { return (_capacity); };
			// Returns whether the vector is empty (i.e. whether its size is 0).
			bool empty() const { return (begin() == end()); };
			/*
			** Requests that the vector capacity be at least enough to contain n elements.
			** If n is greater than the current vector capacity, the function causes
			** the container to reallocate its storage increasing its capacity to n (or greater).
			*/
			void reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n > _capacity)
				{
					pointer tmp = _alloc.allocate(n);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(tmp + i, _begin[i]);
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_begin + i);
					_alloc.deallocate(_begin, _size);
					_begin = tmp;
					_capacity = n;
				}

			};
			/*
			** Resizes the container so that it contains n elements.
			** If n is smaller than the current container size,
			** the content is reduced to its first n elements,
			*/
			void resize (size_type n, value_type val = value_type())
			{
				if (n < _size)
				{
						while (n < _size)
						{
							_alloc.destroy(&_begin[_size - 1]);
							_size--;
						}
				}
				else
				{
					if (_capacity == 0 || n > 2 * _capacity)
						reserve(n);
					else if (n > _capacity)
						reserve(_capacity * 2);
					while (_size < n)
					{
						_alloc.construct(_begin + _size, val);
						++_size;
					}
			}
			};

			/************************************************************
			 * 					  Element access	   		 		    *
			 ************************************************************/

			// Returns a reference to the element at position n in the vector container.
			reference operator[] (size_type n) { return (_begin[n]); };
			// Returns a const_reference to the element at position n in the vector container.
			const_reference operator[] (size_type n) const { return (_begin[n]); };
			// Returns a reference to the element at position n in the vector.
			// Checks if out of range
			reference at (size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector::at");
				return (_begin[n]);
			};
			// Returns a const_reference to the element at position n in the vector.
			// Checks too
			const_reference at (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector::at");
				return (_begin[n]);
			};
			// Returns a reference to the first element in the vector.
			reference front() {return (*_begin); };
			// Returns a const_reference to the first element in the vector.
			const_reference front() const { return (*_begin); };
			// Returns a reference to the last element in the vector.
			reference back() { return (*(end() - 1)); };
			// Returns a const_reference to the last element in the vector.
			const_reference back() const { return (*(end() - 1)); };


			/************************************************************
			 * 						  Modifiers	   		 		 	    *
			 ************************************************************/

			// RANGE
			// Assigns new contents to the container, replacing its current contents,
			// and modifying its size accordingly. In the range between first and last
			template <class InputIterator>
			void assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				size_type n = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				if (n > _capacity)
					reserve(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_size = 0;
				for (InputIterator it = first; it != last; it++)
					push_back(*it);
			};

			/* FILL
			** Assigns new contents to the container, replacing its current contents,
			** the new contents are n elements, each initialized to a copy of val.
			*/
			void assign (size_type n, const value_type& val)
			{
				if (n > _capacity)
					reserve(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_size = 0;
				for (size_type i = 0; i < n; i++)
					push_back(val);
			};

			// Adds a new element at the end of the vector, after its current last element.
			void push_back (const value_type& val)
			{
				if (_capacity == 0)
					reserve(1);
				if (_size == _capacity)
					reserve(_capacity * 2);
				get_allocator().construct(_begin + _size, val);
				_size++;
			};

			// Removes the last element in the vector, effectively reducing the container size by one.
			void pop_back()
			{
				get_allocator().destroy(_begin + _size - 1);
				_size--;
			};

			/* single element (1)
			** insents a new element before the element at the specified position
			** return an iterator pointing to the inserted element.
			**
			** !! begin() before reserve() !!
			*/
			iterator insert (iterator position, const value_type& val)
			{

					iterator	it = begin();

					if (_size + 1 > _capacity)
					{
						if (_capacity == 0 || _size + 1 > 2 * _capacity)
							reserve(_size + 1);
						else if (_size + 1 > _capacity)
							reserve(_capacity * 2);
					}
					size_type pos = position - it;
					for (size_type i = _size; i > pos; i--)
						_alloc.construct(_begin + i, _begin[i - 1]);
					_alloc.construct(&_begin[pos], val);
					_size += 1;
					return (begin() + pos);
			};
			/* fill (2)
			** inserts n new elements before the element at the specified position.
			** !!! pos before realocation !!
			*/
			void insert (iterator position, size_type n, const value_type& val)
			{
						iterator	it = begin();

						if (_size + n > _capacity)
							{
								if (_capacity == 0 || _size + n >= 2 * _capacity)
									reserve(_size + n);
								else if (_size + n < _size * 2)
									reserve(_size * 2);
								else
									reserve(_capacity * 2);
							}
						size_type pos = position - it;
						size_type	j = 1;
						for (size_type i = pos; i < _size; i++)
						{
								_alloc.construct(&_begin[_size + n - j], _begin[_size - j]);
								_alloc.destroy(&_begin[_size - j++]);
						}

						for (size_type i = 0; i < n; i++)
								_alloc.construct(&_begin[pos++], val);

						_size += n;
				};
			// range (3)
			// inserts new elements before the element at the specified position.
			template <class InputIterator>
				void insert (iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type
				 first, InputIterator last)
			{
						iterator	it = begin();
						size_type	distance = std::distance(first, last);
						size_type	i = 0;
						size_type	j = 1;
						size_type	k = 0;

						if (_size + distance > _capacity)
						{
							if (_capacity == 0 || _size + distance > 2 * _capacity)
								reserve(_size + distance);
							else if (_size + distance > _capacity)
								reserve(_capacity * 2);
						}
						while (it != position)
						{
							it++;
							i++;
						}
						size_type backup = i;
						while (i < _size)
						{
							get_allocator().construct(&_begin[_size + distance - j], _begin[_size - j]);
							get_allocator().destroy(&_begin[_size - j]);
							j++;
							i++;
						}
						while (k < distance)
						{
							get_allocator().construct(&_begin[backup], *first);
							first++;
							k++;
							backup++;
						}
						_size += distance;
			};

			/*
			** Removes from the vector either a single element (position)
			** vectors use an array as their underlying storage, erasing elements in positions other than the vector end
			** causes the container to relocate all the elements after the segment erased to their new positions
			*/
			iterator erase (iterator position)
			{
				size_type n = position - begin();
				_alloc.destroy(_begin + n);
				for (size_type i = n; i < _size - 1; i++)
					_alloc.construct(_begin + i, _begin[i + 1]);
				_size--;
				return (_begin + n);
			};
			// or a range of elements ([first,last)).
			// return an iterator pointing to the new location of the
			// element that followed the last element erased by the function call.
			// or vector::end if no such element exists.
			iterator erase (iterator first, iterator last)
			{
				size_t n = last - first;
				for(size_t i = 0; i != n; i++)
					erase(first);
				return (first);
			};

			// Exchanges the content of the container by the content of x, which is another vector object of the same type.
			// size may differ
			void swap (vector& x)
			{
				pointer tmp 				= _begin;
				allocator_type tmp_alloc 	= _alloc;
				size_type tmp_size			= _size;
				size_type tmp_capacity		= _capacity;

				_begin 		= x._begin;
				_alloc 		= x._alloc;
				_size 		= x._size;
				_capacity 	= x._capacity;

				x._begin 	= tmp;
				x._alloc 	= tmp_alloc;
				x._size 	= tmp_size;
				x._capacity = tmp_capacity;
			};
			// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_size = 0;
			};

			protected :
				allocator_type		_alloc;		// Allocator
				pointer				_begin;		// Pointer to the first element
				size_type			_size;		// Number of elements
				size_type			_capacity;	// Size of the allocated storage capacity
		};
	// END OF VECTOR

			/************************************************************
			 * 				Non-member function overloads	   	 	    *
			 ************************************************************/
	// Relational operators
	// Compares whether the contents of lhs are equal to the contents of rhs.
	// lefhandside is compared to the righthandside
	template <class T, class Alloc>
		bool operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			for (size_t i = 0; i < lhs.size(); i++)
				if (lhs[i] != rhs[i])
					return (false);
			return (true);
		};

	template <class T, class Alloc>
		bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(lhs == rhs));
		};
	template <class T, class Alloc>
		bool operator<  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return(ft::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end()));
		};
	template <class T, class Alloc>
		bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (!(rhs < lhs));
		};
	template <class T, class Alloc>
		bool operator>  (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return (rhs < lhs);
		};

	template <class T, class Alloc>
		bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
		{
			return !(lhs < rhs);
		};
	// The contents of container x are exchanged with those of y.
	// Both container objects must be of the same type (same template parameters), although sizes may differ.
	template <class T, class Alloc>
		void swap (vector<T,Alloc>& x, vector<T,Alloc>&y)
	{
		x.swap(y);
	};
};
// END OF FT


#endif
