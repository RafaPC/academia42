#ifndef MAP_HPP
# define MAP_HPP

#include <functional> // less
#include <memory> // allocator
#include <cstdlib>
#include <limits> // numeric_limits
#include "../algorithm.hpp" // ft::equal
#include "../utility.hpp"
#include "../iterator.hpp" // reverse_iterator
#include "../type_traits.hpp" // enable if
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
				typedef Allocator									allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_poiner;
				typedef ft::MapIterator<value_type, tree_node<value_type> >		iterator;
				typedef ft::MapIterator<const value_type, tree_node<value_type> >	const_iterator;
				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
				typedef std::ptrdiff_t								difference_type;
				typedef std::size_t									size_type;

				// Nested function class to compare elements
				class value_compare
				{
					friend class map;
					protected:
						Compare comp;
						value_compare (Compare c): comp(c) {}
					public:
						typedef bool result_type;
						typedef value_type first_argument_type;
						typedef value_type second_argument_type;
						bool operator() (const value_type& x, const value_type& y) const
						{
							return (comp(x.first, y.first));
						}
				};


				// CONSTRUCTORS
				// empty
				explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()):
					_size(0), _compare(comp)
					{
						_root_node = _allocator.allocate(1);
						_allocator.construct(_root_node, node_type());
					}

				// range
				template <class InputIterator>
					map (InputIterator first, InputIterator last,
						const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type(),
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
						{
							_root_node = _allocator.allocate(1);
							_allocator.construct(_root_node, node_type());
							_compare = comp;
							_size = 0;
							for (; first != last; ++first)
								insert(*first);
						}

				// Constructs a container with a copy of each of the elements in x.
				map (const map& x): _size(x._size), _compare(x._compare)
				{
					_root_node = _copy_node(NULL, x._root_node);
				}

				~map()
				{
					_destroy_node(_root_node);
				}

				map& operator= (const map& x)
				{
					clear();
					//FIXME: creo que con copy node daba algun error, volver a poner el copy_node mas adelante
					// y solucionar el error
					this->insert(x.begin(), x.end());
					_size = x._size;
					return (*this);
				}

				bool		empty() const { return _size == 0; }

				size_type	size() const { return _size; }

				//FIXME:
				size_type max_size() const
				{
					return std::numeric_limits<difference_type>::max() / (sizeof(node_type) / 2);
				}

				// INSERT
				//single element
				ft::pair<iterator, bool>	insert (const value_type& val)
				{
					ft::pair<iterator, bool>	return_pair;

					return_pair.second = !this->count(val.first);
					if (return_pair.second == true)
					{
						node_type	*new_node = _allocator.allocate(1);
						_allocator.construct(new_node, node_type(val));

						node_type	**parent = &_root_node;
						node_type	**node = &_root_node;
						node_type	*ghost = rightmost(_root_node);
						bool side_left = true;

						++_size;
						while (*node && *node != ghost)
						{
							parent = node;
							side_left = _compare(new_node->value.first, (*node)->value.first);
							node = (side_left ? &(*node)->left : &(*node)->right);
						}

						if (*node == NULL)
						{
							*node = new_node;
							new_node->parent = (*parent);
						}
						else // if (*node == ghost)
						{
							*node = new_node;
							new_node->parent = ghost->parent;
							ghost->parent = rightmost(new_node);
							rightmost(new_node)->right = ghost; // in case new_node isnt alone
						}
						return_pair.first = iterator(new_node);
						if (_size)
						{
							ghost = rightmost(_root_node);
							ghost->parent->right = NULL;
							_root_node = _balanceTree(_root_node);
							rightmost(_root_node)->right = ghost;
						}
					}
					else
						return_pair.first = find(val.first);

					return (return_pair);
				}

				// with hint
				iterator insert (iterator position, const value_type& value)
				{
					static_cast<void>(position);
					return insert(value).first;
				}

				template <class InputIterator>
					void insert (InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
					{
						for (; first != last; ++first)
							insert(*first);
					}

				// custom method
				mapped_type	&operator[] (const key_type &key)
				{
					return (*((this->insert(ft::make_pair(key, mapped_type()))).first)).second;
				}

				iterator	find (const key_type& key)
				{
					node_type	*current_node = _root_node;

					while (current_node)
					{
						if (_compare(key, current_node->value.first))
							current_node = current_node->left;
						else if (_compare(current_node->value.first, key))
							current_node = current_node->right;
						else
							return iterator(current_node);
					}
					return (end());
				}

				const_iterator	find (const key_type& key) const
				{
					node_type	*current_node = _root_node;

					while (current_node)
					{
						if (_compare(key, current_node->value.first))
							current_node = current_node->left;
						else if (_compare(current_node->value.first, key))
							current_node = current_node->right;
						else
							return const_iterator(current_node);
					}
					return (end());
				}

				size_type	count (const key_type& key) const
				{
					return (find(key) == end() ? 0 : 1);
				}

				// ERASE
				void erase (iterator position)
				{
					node_type *aux = position.base();

					node_type *replace_node = NULL;
					node_type **remove_place = &_root_node;

					--_size;
					if (aux->parent)
						remove_place = (aux->parent->left == aux) ? &aux->parent->left : &aux->parent->right;

					if (aux->left == NULL)
						replace_node = aux->right;
					else if (aux->left || aux->right)
					{
						replace_node = rightmost(aux->left);
						if (replace_node != aux->left)
						{
							replace_node->parent->right = replace_node->left;
							if (replace_node->parent->right)
								replace_node->left->parent = replace_node->parent;
						}
					}

					if (replace_node)
					{
						replace_node->parent = aux->parent;
						if (aux->left && aux->left != replace_node)
						{
							replace_node->left = aux->left;
							replace_node->left->parent = replace_node;
						}
						if (aux->right && aux->right != replace_node)
						{
							replace_node->right = aux->right;
							replace_node->right->parent = replace_node;
						}
					}
					*remove_place = replace_node;
					_allocator.destroy(aux);
					_allocator.deallocate(aux, 1);
					//FIXME:
					if (_size)
					{
						node_type *ghost = rightmost(_root_node);
						ghost->parent->right = NULL;
						_root_node = _balanceTree(_root_node);
						rightmost(_root_node)->right = ghost;
					}
				}

				size_type erase (const key_type& key)
				{
					iterator key_it = find(key);
					if (key_it != end())
					{
						erase(key_it);
						return (1);
					}
					else
						return (0);
				}

				void erase (iterator first, iterator last)
				{
					iterator it = first;
					while (first != last)
					{
						++first;
						erase(it);
						it = first;
					}
				}

				iterator begin()
				{
					return iterator(leftmost(_root_node));
				}

				const_iterator begin() const
				{
					return const_iterator(leftmost(_root_node));
				}

				iterator end()
				{
					return iterator(rightmost(_root_node));
				}

				const_iterator end() const
				{
					return const_iterator(rightmost(_root_node));
				}

				reverse_iterator rbegin()
				{
					return (reverse_iterator(end()));
				}

				const_reverse_iterator rbegin() const
				{
					return (const_reverse_iterator(end()));
				}

				reverse_iterator rend()
				{
					return (reverse_iterator(begin()));
				}

				const_reverse_iterator rend() const
				{
					return (reverse_iterator(begin()));
				}

				allocator_type get_allocator() const { return _allocator; }

				void swap (map& x)
				{
					std::swap(_root_node, x._root_node);
					std::swap(_size, x._size);
				}

				void clear()
				{
					node_type *ghost = end().base();

					if (_size == 0)
						return ;
					ghost->parent->right = NULL;
					_destroy_node(_root_node);
					_root_node = ghost;
					_size = 0;
				}

				key_compare key_comp() const { return _compare; }

				value_compare value_comp() const { return value_compare(Compare()); }

				iterator lower_bound (const key_type& key)
				{
					iterator it = begin();
					iterator last = end();
					while (it != last && _compare(it->first, key))
						++it;
					return (it);
				}

				const_iterator lower_bound (const key_type& key) const
				{
					const_iterator it = begin();
					const_iterator last = end();
					while (it != last && _compare(it->first, key))
						++it;
					return (it);
				}

				iterator upper_bound (const key_type& key)
				{
					iterator it = begin();
					iterator last = end();
					while (it != last && !_compare(key, it->first))
						++it;
					return (it);
				}

				const_iterator upper_bound (const key_type& key) const
				{
					const_iterator it = begin();
					const_iterator last = end();
					while (it != last && !_compare(key, it->first))
						++it;
					return (it);
				}

				ft::pair<iterator,iterator>		equal_range (const key_type& key)
				{
					iterator it = begin();
					iterator last = end();
					while (it != last && _compare(it->first, key))
						++it;
					if (_are_equivalent(it->first, key))
						return ft::make_pair(it, ++it);
					else
						return ft::make_pair(it, it);
				}

				ft::pair<const_iterator,const_iterator>		equal_range (const key_type& key) const
				{
					const_iterator it = begin();
					const_iterator last = end();
					while (it != last && _compare(it->first, key))
						++it;
					if (_are_equivalent(it->first, key))
						return ft::make_pair(it, ++it);
					else
						return ft::make_pair(it, it);
				}

				typedef	tree_node<value_type> node_type;
				node_type	*_root_node;
			private:
				size_type	_size;
				Compare		_compare;
				typename Allocator::template rebind<node_type>::other	_allocator;

				node_type *_find_in_node(const key_type &to_find, node_type **node, node_type **last_node)
				{
					// (*last_node) = (*node);
					while (*node)
					{
						(*last_node) = (*node);
						if (to_find == (*node)->value.first)
							return (*node);
						if (_compare(to_find, (*node)->value.first))
							node = &(*node)->left;
						else
							node = &(*node)->right;
					}
					return (*node);
				}

				void _insert_node(node_type *node, node_type *parent)
				{
					if (!node || !parent)
						return ;
					_find_in_node(node->value.first, &parent, &parent);
					if (_compare(parent->value.first, node->value.first))
						parent->right = node;
					else
						parent->left = node;
					node->parent = parent;
				}

				node_type	*_balanceTree(node_type *node)
				{
					if (!node)
						return NULL;
					int imbalance;
					node_type *aux;

					while (true)
					{
						imbalance = height(node->left) - height(node->right);
						aux = node;
						if (imbalance == -2)
						{
							node = node->right;
							aux->right = NULL;
						}
						else if (imbalance == 2)
						{
							node = node->left;
							aux->left = NULL;
						}
						else
							break;
						node->parent = aux->parent;
						_insert_node(aux, node);
					}
					node->left = _balanceTree(node->left);
					node->right = _balanceTree(node->right);
					return (node);
				}

				// Checks wether 2 keys are equivalent
				bool	_are_equivalent(key_type key1, key_type key2) const
				{
					return (!_compare(key1, key2) && !_compare(key2, key1));
				}



				// ÁRBOL AVL

				/*
				**	Receives a pointer to its parent and other to the node it's copying
				**	Allocates the new node and asigns its parent pointer to its parent variable
				**	If the original node has any child, the same function is called recursively with its
				**	own pointer as the parent argument, and the child as the original node
				**	Then returns its direction
				*/
				node_type	*_copy_node(node_type *parent, node_type *original_node)
				{
					node_type	*new_node = _allocator.allocate(1);
					_allocator.construct(new_node, node_type(original_node->value));
					new_node->parent = parent;
					if (original_node->left)
						new_node->left = _copy_node(new_node, original_node->left);
					if (original_node->right)
						new_node->right = _copy_node(new_node, original_node->right);
					return (new_node);
				}

				// Deletes its value and calls itself passing its childs as argument
				void	_destroy_node(node_type *node)
				{
					if (node->left)
						_destroy_node(node->left);
					if (node->right)
						_destroy_node(node->right);
					_allocator.destroy(node);
					_allocator.deallocate(node, 1);
				}
		};

		template <class Key, class T, class Compare, class Alloc>
		bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return !(lhs == rhs);
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator< ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return !(rhs < lhs);
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator> ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return (rhs < lhs);
		}

		template <class Key, class T, class Compare, class Alloc>
		bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
		{
			return !(lhs < rhs);
		}

		template <class Key, class T, class Compare, class Alloc>
		void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
		{
			x.swap(y);
		}
};

#endif