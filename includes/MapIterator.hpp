/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensett <abensett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:12:15 by abensett          #+#    #+#             */
/*   Updated: 2022/09/29 21:37:02 by abensett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#include "utils.hpp"
#include "ConstMapIterator.hpp"

namespace ft
{

	template <class Key, class Value, class Iter>
		class MapIterator
		{

			// MEMBER TYPES
			public:

				typedef node<Key, Value>*												nodePointer;

			// MEMBER OBJECTS
			private:

				nodePointer																_ptr;

			// MEMBER FUNCTIONS
			public:

				// DEFAULT CONSTRUCTOR
				MapIterator(nodePointer _ptr = NULL) :
					_ptr(_ptr)
				{
					return ;
				};

				// OPERATOR =
				MapIterator& operator = (const MapIterator& other)
				{
					if (this == &other)
						return (*this);
					_ptr = other._ptr;
					return (*this);
				};

				// OPERATOR = FOR CONST ITERATOR
				MapIterator& operator = (const ConstMapIterator<Key, Value, Iter> & other)
				{
					_ptr = other._ptr;
					return (*this);
				};

				// DESTRUCTOR
				~MapIterator(void)
				{
					return ;
				};

				// BASE
				nodePointer base(void) const
				{
					return (_ptr);
				};

				// OPERATOR ==
				bool operator == (const MapIterator& other) const
				{
					return (_ptr == other.base());
				};

				// OPERATOR !=
				bool operator != (const MapIterator& other) const
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
					if (_ptr)
						return (_ptr->data);
					return (NULL);
				};

				// PRE-INCREMENTATION
				MapIterator& operator ++ (void)
				{
					_ptr = next(_ptr);
					return (*this);
				};

				// POST-INCREMENTATION
				MapIterator operator ++ (int)
				{
					MapIterator	tmp(*this);

					_ptr = next(_ptr);
					return (tmp);
				};

				// PRE-DECREMENATION
				MapIterator & operator -- (void)
				{
					_ptr = prev(_ptr);
					return (*this);
				};

				// POST-DECREMENATION
				MapIterator operator -- (int)
				{
					MapIterator	tmp(*this);

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
vector
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

		}; // END OF MapIterator CLASS

}; // END OF NAMESPACE FT
// End of namespace FT
#endif
