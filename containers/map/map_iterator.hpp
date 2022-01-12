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

				MapIterator(void) : _node(NULL), _past_the_end(false) {}

				MapIterator(node_type *base_node) : _node(base_node), _past_the_end(false) {}

				MapIterator(MapIterator const &other) : _node(other._node), _past_the_end(other._past_the_end) {}

				MapIterator &operator=(const MapIterator &other)
				{
					_node = other._node;
					_past_the_end = other._past_the_end;
					return (*this);
				};

				// conversion operator to const MapIterator
				// just constructs a MapIterator of const T
				operator	MapIterator<const T, node_type>(void) const
				{
					MapIterator<const T, node_type> new_iterator(_node);
					new_iterator._past_the_end = _past_the_end;
					return (new_iterator);
				}

				node_type	*base(void) { return _node; }

				reference operator*() const { return (_node->value); }

				pointer operator->() const { return (&_node->value); }

				MapIterator &operator++()
				{
					if (_past_the_end)
						return (*this);
					else if (_node->child2 != NULL)
						_node = leftmost(_node->child2);
					else
					{
						node_type	*aux = _node;
						node_type	*aux_parent = aux->parent;
						while (aux_parent && aux == aux_parent->child2)
						{
							aux = aux_parent;
							aux_parent = aux_parent->parent;
						}
						if (!aux_parent) // significa que solo venia de hijos de la derecha
							_past_the_end = true;
						else
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
					if (_past_the_end)
						_past_the_end = false;
					else if (_node->child1 != NULL)
						_node = rightmost(_node->child1);
					else
					{
						node_type	*aux = _node;
						node_type	*aux_parent = aux->parent;
						while (aux_parent && aux == aux_parent->child1)
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

				//FIXME: me gustaría sacarlos fuera para que fueran constantes pero no podría acceder al past the end sin hacerlo
				// friend, y entonces dejaría de ser constante
				bool	operator ==(const MapIterator<value_type, node_type> &other)
				{
					return (_node == other._node && _past_the_end == other._past_the_end);
				}

				bool	operator !=(const MapIterator<value_type, node_type> &other)
				{
					return (!(*this == other));
				}

			template <class, class>
			friend class MapIterator;
			
			private:
				node_type	*_node;
				bool		_past_the_end;
		};
};

#endif