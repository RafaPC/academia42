#ifndef MAP_HPP
# define MAP_HPP

#include <functional> // less
#include <memory> // allocator
#include "../utility.hpp"
#include <cstdlib>
#include "node_tree.hpp"
#include "map_iterator.hpp" // MapIterator
namespace ft {

	template <	class Key, class T,
				class Compare = std::less<Key>,
				class Allocator = std::allocator<ft::pair<const Key, T> > >
		class map
		{
			public:
				typedef Key											key_type;
				typedef T											mapped_type;
				typedef ft::pair<const key_type, mapped_type>		value_type;
				typedef Compare										key_compare;
				// typedef noseque value_compare;
				typedef Allocator									allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_poiner;
				typedef MapIterator<value_type, Compare>				iterator;
				// typedef MapIterator<const value_type>		const_iterator;
				// typedef ft::reverse_iterator(iterator)		reverse_iterator;
				// typedef ft::reverse_iterator(const_iterator)	const_reverse_iterator;
				typedef std::ptrdiff_t								difference_type;
				typedef std::size_t									size_type;

				// CONSTRUCTORS
				// default
				explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()):
					_size(0), _compare(comp), _allocator(alloc) {}

				// range
				// template <class InputIterator>
				// 	map (InputIterator first, InputIterator last,
				// 		const key_compare& comp = key_compare(),
				// 		const allocator_type& alloc = allocator_type());

				// Constructs a container with a copy of each of the elements in x.
				map (const map& x): _size(x._size), _compare(x._compare), _allocator(x._allocator)
				{
					//TODO: borrar node antiguo y eso
				}

				bool		empty() const
				{
					return _size == 0;
				}

				size_type	size() const
				{
					return _size;
				}

				// custom method
				mapped_type	&operator[] (const key_type &k)
				{
					// if there's no root creates it and returns its mapped type
					if (_root_node.value == NULL)
					{
						_root_node.value = new ft::pair<const key_type, mapped_type>(k, mapped_type());
						_size = 1;
						return _root_node.value->second;
					}
					tree_node<value_type>	*current_node = &_root_node;
					tree_node<value_type>	*previous_node;
					while (current_node != NULL)
					{
						previous_node = current_node;
						if (_compare(k, current_node->value->first))
							current_node = current_node->child1;
						else if (_compare(current_node->value->first, k))
							current_node = current_node->child2;
						else
							return (current_node->value->second);
					}
					tree_node<value_type>	*new_node = new tree_node<value_type>(previous_node);
					if (_compare(k, previous_node->value->first))
						previous_node->child1 = new_node;
					else
						previous_node->child2 = new_node;
					new_node->value = new ft::pair<const key_type, mapped_type>(k, mapped_type());
					++_size;
					return new_node->value->second;
				}

				iterator	find (const key_type& k)
				{
					tree_node<value_type>	*current_node = _root_node;

					while (current_node)
					{
						if (_compare(k, current_node->value->first))
							current_node = current_node->child1;
						else if (_compare(current_node->value->first, k))
							current_node = current_node->child2;
						else
							return iterator(current_node);
					}
					return (end());
				}

				// ERASE
				size_type erase (const key_type& k)
				{

				}

				iterator begin()
				{
					// FIXME: esto creo que está bien
					tree_node<value_type>	*aux = _root_node.min();
					return iterator(aux);
				}
				iterator end()
				{
					// FIXME: obviamente hay que arreglarlo
					// cojo el máximo y le hago un ++

					//TODO: maybe el == del iterador compara si son iguales y luego si la variable _past_the_end es igual
					tree_node<value_type> *aux_node = _root_node.max();
					iterator aux_iterator(aux_node);
					++aux_iterator;
					return aux_iterator;
				}
			private:
				size_type	_size;
				Compare		_compare;
				Allocator	_allocator;
				// FIXME: hmm puntero al tree_node, puntero al value_type (pair<.....>) ????
				tree_node<value_type>	_root_node;

				bool	_are_equivalent(key_type key1, key_type key2)
				{
					return (!_compare(key1, key2) && !_compare(key2, key1));
				}
		};
};

#endif