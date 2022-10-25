/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConstConstMapIterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:12:15 by abensett          #+#    #+#             */
/*   Updated: 2022/10/06 11:58:32 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTMAPRITERATOR_HPP
#define CONSTMAPRITERATOR_HPP

#include "utils.hpp"

namespace ft
{

	template <class Key, class Value, class Iter>
    class MapIterator;

	template <class Key, class Value, class Iter>
		class ConstMapIterator
		{

			// MEMBER TYPES
			public:

				typedef Iter																iterator_type;
				typedef std::bidirectional_iterator_tag										iterator_category;
				typedef typename ft::iterator_traits<iterator_type>::value_type				value_type;
				typedef typename ft::iterator_traits<iterator_type>::difference_type		difference_type;
				typedef typename ft::iterator_traits<iterator_type>::pointer				pointer;
				typedef typename ft::iterator_traits<iterator_type>::reference				reference;
				typedef node<Key, Value>*													nodePointer;

			// MEMBER OBJECTS
			private:

				nodePointer																	_ptr;

			// MEMBER FUNTIONS
			public:

				// DEFAULT CONSTRUCTOR
				ConstMapIterator(nodePointer _ptr = NULL) :
					_ptr(_ptr)
				{
					return ;
				};

				// COPY CONSTRUCTOR
				template<class U>
					ConstMapIterator(const MapIterator<Key, Value, U> & other) :
						_ptr(other.base())
				{
					return ;
				};

				// OPERATOR =
				ConstMapIterator & operator = (const ConstMapIterator & other)
				{
					if (this == &other)
						return (*this);
					_ptr = other._ptr;
					return (*this);
				};

				// OPERATOR = MAP ITERATOR
				ConstMapIterator & operator = (const MapIterator<Key, Value, Iter> & other)
				{
					_ptr = other._ptr;
					return (*this);
				};

				// DESTRUCTOR
				~ConstMapIterator(void)
				{
					return ;
				};

				// BASE
				nodePointer base(void) const
				{
					return (_ptr);
				};

				// OPERATOR ==
				bool operator == (const ConstMapIterator & other) const
				{
					return (_ptr == other.base());
				};

				// OPERATOR !=
				bool operator != (const ConstMapIterator& other) const
				{
					return (_ptr != other.base());
				};

				// DEREFERENCE
				reference operator * (void) const
				{
					return (*(_ptr->data));
				};

				// DEREFERENCE
				pointer operator -> (void) const
				{
					return (_ptr->data);
				};

				// POST INCREMENTATION
				ConstMapIterator & operator ++ (void)
				{
					_ptr = next(_ptr);
					return (*this);
				};

				// PRE INCREMENTATION
				ConstMapIterator operator ++ (int)
				{
					ConstMapIterator	tmp(*this);

					_ptr = next(_ptr);
					return (tmp);
				};
				
				// POST DECREMENTATION
				ConstMapIterator& operator -- (void)
				{
					_ptr = prev(_ptr);
					return (*this);
				};

				// PRE DECREMENTATION
				ConstMapIterator operator -- (int)
				{
					ConstMapIterator	tmp(*this);

					_ptr = prev(_ptr);
					return (tmp);
				};

			private:

				nodePointer maximum(nodePointer node)
				{
					while (node->right->color != NIL)
						node = node->right;
					return (node);
				};

				nodePointer minimum(nodePointer node)
				{
					while (node->left->color != NIL)
						node = node->left;
					return (node);
				};

				nodePointer next(nodePointer node)
				{
					if (node->color == NIL)
						return (node);

					if (node->right->color != NIL)
						return (minimum(node->right));

					nodePointer _ptr = node->parent;
					while (_ptr->color != NIL && node == _ptr->right)
					{
						node = _ptr;
						_ptr = _ptr->parent;
					}
					return (_ptr);
				};

				nodePointer prev(nodePointer node)
				{
					if (node->color == NIL)
						return (node->parent);

					if (node->color != NIL && node->left->color != NIL)
						return (maximum(node->left));

					nodePointer _ptr = node->parent;
					while (_ptr->color != NIL && node == _ptr->left)
					{
						node = _ptr;
						_ptr = _ptr->parent;
					}
					if (_ptr->color != NIL)
						return (_ptr);
					return (node);
				};
			};

};
// End of namespace FT
#endif
