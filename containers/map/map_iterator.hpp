#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "../utility.hpp"
#include <iterator>
#include "node_tree.hpp"

namespace ft
{
	template< typename T, class node_type>
		class MapIterator
		{
			public:
				typedef std::bidirectional_iterator_tag		iterator_category;
				typedef std::ptrdiff_t						difference_type;
				typedef T									value_type;
				typedef value_type*							pointer;
				typedef value_type&							reference;

				MapIterator(void) : _node(NULL) {}

				MapIterator(node_type *base_node) : _node(base_node) {}

				MapIterator(MapIterator const &other) : _node(other._node) {}

				MapIterator &operator=(const MapIterator &other)
				{
					_node = other._node;
					return (*this);
				};

				// conversion operator to const MapIterator
				// just constructs a MapIterator of const T
				operator	MapIterator<const T, node_type>(void) const
				{
					return (MapIterator<const T, node_type>(_node));
				}

				node_type	*base(void) const { return _node; }

				reference operator*() const { return (_node->value); }

				pointer operator->() const { return (&_node->value); }

				MapIterator &operator++()
				{
					if (_node->right != NULL)
						_node = leftmost(_node->right);
					else
					{
						node_type	*aux = _node;
						node_type	*aux_parent = aux->parent;
						while (aux_parent && aux == aux_parent->right)
						{
							aux = aux_parent;
							aux_parent = aux_parent->parent;
						}
						if (aux_parent)
							_node = aux_parent;
					}
					return (*this);
				}

				MapIterator operator++(int)
				{
					MapIterator temp(_node);
					operator++();
					return (temp);
				}

				MapIterator &operator--()
				{
					if (_node->left != NULL)
						_node = rightmost(_node->left);
					else
					{
						node_type	*aux = _node;
						node_type	*aux_parent = aux->parent;
						while (aux_parent && aux == aux_parent->left)
						{
							aux = aux_parent;
							aux_parent = aux_parent->parent;
						}
						if (aux_parent)
							_node = aux_parent;
					}
					return (*this);
				}

				MapIterator operator--(int)
				{
					MapIterator temp(_node);
					operator--();
					return (temp);
				}
			
			private:
				node_type	*_node;
		};

	template <class T1, class U1, class T2, class U2>
		bool	operator ==(const MapIterator<T1, U1> &lhs, const MapIterator<T2, U2> &rhs)
		{
			return (lhs.base() == rhs.base());
		}
	template <class T1, class U1, class T2, class U2>
		bool	operator !=(const MapIterator<T1, U1> &lhs, const MapIterator<T2, U2> &rhs)
		{
			return (!(lhs == rhs));
		}
};

#endif