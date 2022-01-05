#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "../utility.hpp"
#include <iterator>
#include "node_tree.hpp"

namespace ft
{
	template< typename T, class Compare>
	// FIXME: COMO COMPARAR CLAVES, NECESITA ALGO PARA COMPARARLAS
		class MapIterator
		{
			public:
				typedef std::bidirectional_iterator_tag		iterator_category;
				typedef std::ptrdiff_t						difference_type;
				typedef T									value_type;
				typedef value_type*							pointer;
				typedef value_type&							reference;

				MapIterator(void) : _node(NULL), _past_the_end(false) {}

				// FIXME: puntero / no puntero ¿?¿?
				MapIterator(tree_node<value_type> *base_node) : _node(base_node), _past_the_end(false), _key_compare(Compare()) {}

				MapIterator(MapIterator const &other) : _node(other._node), _past_the_end(other._past_the_end), _key_compare(Compare()) {}

				MapIterator &operator=(const MapIterator &other)
				{
					*_node = *other._node;
					_past_the_end = other._past_the_end;
					_key_compare = other._key_compare;
					return (*this);
				};

				// conversion operator to const MapIterator
				// just constructs a MapIterator of const T
				operator	MapIterator<const T, Compare>(void) const
				{
					return (MapIterator<const T, Compare>(_node)); // FIXME: aqui pondría el past the end a false
				}

				reference operator*() const
				{
					return (*_node->value);
				}

				pointer operator->() const
				{
					return (_node->value);
				}

				//TODO: no sé bien cual será el valor del nodo para el iterador end()
				MapIterator &operator++()
				{
					const key_type	initial_key = _node->value->first;
					//FIXME: ver como funciona el iterador normal si hago el past_the_end de más

					if (_past_the_end)
						return (*this);
					else if (_node->child2 != NULL)
					{
						_node = _node->child2;
						while (_node->child1 != NULL)
							_node = _node->child1;
					}
					else
					{
						// sale del while bien porque llega a un nodo con una clave mayor
						// o porque llega al nodo base
						while (_node->parent != NULL && _node->value->first <= initial_key)
							_node = _node->parent;
						if (_node->value->first <= initial_key)
							_past_the_end = true;
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
					const key_type	initial_key = _node->value->first;

					// Al hacer -- estando en el past the end, se va al elemento máximo
					if (_past_the_end)
					{
						_past_the_end = false;
						_node = _node->max();
					}
					else if (_node->child1 != NULL)
					{
						_node = _node->child1;
						while (_node->child2 != NULL)
							_node = _node->child2;
					}
					else
					{
						// sale del while bien porque llega a un nodo con una clave mayor
						// o porque llega al nodo base
						while (_node->parent != NULL && _node->value->first >= initial_key)
							_node = _node->parent;
					}
					return (*this);
				}

				MapIterator operator--(int)
				{
					MapIterator temp(_node);
					operator--();
					return (temp);
				}

			bool	operator ==(MapIterator<value_type, Compare> &other)
			{
				return (!_key_compare(other._node->value->first, _node->value->first) &&
					!_key_compare(_node->value->first, other._node->value->first) && _past_the_end == other._past_the_end);

			}

			bool	operator !=(MapIterator<value_type, Compare> &other)
			{
				return (!(*this == other));
			}

			private:
				typedef typename value_type::first_type		key_type;
				tree_node<value_type>						*_node;
				// typedef _node->value->first					key;
				bool										_past_the_end;
				Compare										_key_compare;
		};
};

#endif