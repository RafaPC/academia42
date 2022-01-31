#ifndef MAP_HPP
# define MAP_HPP

#include <functional> // less
#include <memory> // allocator
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

			private:
				typedef	tree_node<value_type> node_type;
				node_type	*_root_node;
				size_type	_size;
				Compare		_compare;
				typename Allocator::template rebind<node_type>::other	_allocator;
				
			public:
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
					_size(0), _compare(comp), _allocator(alloc)
					{
						_root_node = _allocator.allocate(1);
						_allocator.construct(_root_node, node_type(false));
					}

				// range
				template <class InputIterator>
					map (InputIterator first, InputIterator last,
						const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type(),
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
						: _size(0), _compare(comp), _allocator(alloc)
						{
							_root_node = _allocator.allocate(1);
							_allocator.construct(_root_node, node_type(false));
							for (; first != last; ++first)
								insert(*first);
						}

				// Constructs a container with a copy of each of the elements in x.
				map (const map& x): _size(x._size), _compare(x._compare), _allocator(x._allocator)
				{
					_root_node = _copy_node(NULL, x._root_node);
				}

				~map()
				{
					_destroy_node_recursive(_root_node);
				}

				map& operator= (const map& x)
				{
					_destroy_node_recursive(_root_node);
					_root_node = _copy_node(NULL, x._root_node);
					_size = x._size;
					return (*this);
				}

				bool		empty() const { return _size == 0; }

				size_type	size() const { return _size; }

				size_type max_size() const { return std::numeric_limits<difference_type>::max() / (sizeof(node_type)); }

				// INSERT
				//single element
				ft::pair<iterator, bool>	insert(const value_type& val)
				{
					ft::pair<iterator, bool>	return_pair;

					return_pair.second = !this->count(val.first);
					if (return_pair.second == true)
					{
						node_type	*new_node = _allocator.allocate(1);
						_allocator.construct(new_node, node_type(val));
						node_type	**parent = &_root_node;
						node_type	**node = &_root_node;
						node_type	*end_node = rightmost(_root_node);

						++_size;
						while (*node && *node != end_node)
						{
							parent = node;
							node = _compare(new_node->value.first, (*node)->value.first) ? &(*node)->left : &(*node)->right;
						}

						if (*node == NULL)
						{
							*node = new_node;
							new_node->parent = (*parent);
						}
						else // if (*node == end_node)
						{
							*node = new_node;
							new_node->parent = end_node->parent;
							end_node->parent = rightmost(new_node);
							rightmost(new_node)->right = end_node; // in case new_node isnt alone
						}
						return_pair.first = iterator(new_node);
						new_node->is_red = true;
						if (_size)
						{
							end_node = rightmost(_root_node);
							end_node->parent->right = NULL;
							_fix_insert_violation(new_node);
							_emplace_end_node(end_node);
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
					// saco el nodo end_node
					node_type *end_node = rightmost(_root_node);
					end_node->parent->right = NULL;

					node_type *erased = position.base();

					node_type *replace_node = NULL;
					node_type **remove_place = &_root_node;

					--_size;
					if (erased == _root_node && _size == 0)
					{
						_root_node = end_node;
						end_node->parent = NULL;
						_destroy_node(erased);
						return ;
					}
					else if (erased->parent)
						remove_place = (erased->parent->left == erased) ? &erased->parent->left : &erased->parent->right;

					if (erased->right)
					{
						replace_node = leftmost(erased->right);
						if (replace_node != erased->right)
						{
							replace_node->parent->left = replace_node->right;
							if (replace_node->parent->left)
								replace_node->right->parent = replace_node->parent;
						}
					}
					else if (erased->left)
						replace_node = erased->left;

					//FIX ERASE VIOLATION
					node_type *parent = NULL;
					bool x_is_left_child = false;

					// DARLE VALOR A X
					node_type *x;
					if (erased->left && erased->right)
					{
						x = replace_node->right;
						if (replace_node->parent != erased)
						{
							parent = replace_node->parent;
							x_is_left_child = true;
						}
						else
							x_is_left_child = false;
					}
					else if (erased->left)
					{
						x = erased->left;
						x_is_left_child = true;
					}
					else if (erased->right)
					{
						x = erased->right;
						x_is_left_child = false;
					}
					else
					{
						x_is_left_child = erased == erased->parent->left;
						x = NULL;
					}

					if (replace_node)
					{
						replace_node->parent = erased->parent;
						if (erased->left && erased->left != replace_node)
						{
							replace_node->left = erased->left;
							replace_node->left->parent = replace_node;
						}
						if (erased->right && erased->right != replace_node)
						{
							replace_node->right = erased->right;
							replace_node->right->parent = replace_node;
						}
					}
					*remove_place = replace_node;

					_fix_erase_violation(replace_node, erased, x, parent, x_is_left_child);
					_emplace_end_node(end_node);
					_destroy_node(erased);
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
					node_type *end_node = end().base();

					if (_size == 0)
						return ;
					end_node->parent->right = NULL;
					_destroy_node_recursive(_root_node);
					_root_node = end_node;
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
					if (!_compare(it->first, key) && !_compare(key, it->first))
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
					if (!_compare(it->first, key) && !_compare(key, it->first))
						return ft::make_pair(it, ++it);
					else
						return ft::make_pair(it, it);
				}

				void displayTree(node_type *node)
				{
					if (!node)
					{
						node = _root_node;
						std::cout << std::endl;
					}
					if (node->right)
						displayTree(node->right);
					size_t offset = depth(node);
					while (offset--)
						std::cout << '\t';
					if (node->is_red)
						std::cout << "\033[1;31m" << node->value.first << "\033[0m" << std::endl;
					else
						std::cout << node->value.first << std::endl;
					if (node->left)
						displayTree(node->left);
					if (node == _root_node)
						std::cout << "---------------------------------\n";
				}

			private:

				void	_fix_insert_violation(node_type *node)
				{
					node_type *parent = NULL;
					node_type *grandparent = NULL;
					while (node && node != _root_node && node->is_red && node->parent->is_red)
					{
						parent = node->parent;
						grandparent = parent->parent;
						const bool	parent_is_left_child = (parent == grandparent->left);
						node_type	*uncle = (parent_is_left_child) ? grandparent->right : grandparent->left;
						if (uncle && uncle->is_red)
						{
							parent->is_red = false;
							uncle->is_red = false;
							grandparent->is_red = true;
							node = grandparent;
						}
						else
						{
							if (parent == grandparent->left && node == parent->left)
								left_left_rotation(node, &_root_node);
							else if (parent == grandparent->right && node == parent->right)
								right_right_rotation(node, &_root_node);
							else if (parent == grandparent->left && node == parent->right)
								left_right_rotation(node, &_root_node);
							else
								right_left_rotation(node, &_root_node);
							if (node->parent)
								node = node->parent->parent;
						}
					}
					_root_node->is_red = false;
				}

				void	_fix_erase_violation(node_type *replace_node, node_type *erased, node_type *x, node_type *parent, bool x_is_left_child)
				{
					if (erased->is_red && (replace_node == NULL || replace_node->is_red))
						return ;
					else if (erased->is_red && (!replace_node || !replace_node->is_red))
						replace_node->is_red = true;
					else if (!erased->is_red && replace_node && replace_node->is_red)
					{
						replace_node->is_red = false;
						return ;
					}
					else if (!erased->is_red && (!replace_node || !replace_node->is_red) && x == _root_node)
						return ;

					// declares and initialices parent and sibling pointers
					if (!parent && replace_node)
						parent = replace_node;
					else if (!parent && !replace_node)
						parent = erased->parent;
					node_type *sibling = NULL;

					if (parent)
						sibling = (x == parent->left) ? parent->right : parent->left;

					int		sibling_childs_redness = 0;
					if (sibling)
						sibling_childs_redness = sibling->has_red_childs();

					if (replace_node == _root_node)
						return ;

					// leaf has been deleted, if deletedNode was black, then doubleBlack case
					bool repeat;
					do
					{
						repeat = false;
						if (sibling)
							sibling_childs_redness = sibling->has_red_childs();

						if (x && x->is_red) 														// CASE 0
						{
							x->is_red = false;
							return ;
						}
						else if ((!x || !x->is_red) && sibling->is_red) 							// CASE 1
						{
							sibling->is_red = false;
							parent->is_red = true;
							if (x == parent->left)
							{
								left_rotation(parent, &_root_node);
								sibling = parent->right;
							}
							else
							{
								right_rotation(parent, &_root_node);
								sibling = parent->left;
							}
							if (sibling)
								sibling_childs_redness = sibling->has_red_childs();
						}
						if ((!x || !x->is_red) && sibling && !sibling->is_red && sibling_childs_redness == 0)	// CASE 2
						{
							sibling->is_red = true;
							x = parent;
							x_is_left_child = (x->parent) ? x == x->parent->left : true;
							if (x->is_red)
							{
								x->is_red = false;
								return ;
							}
							else if (!x->is_red && x != _root_node)
							{
								parent = parent->parent;
								sibling = x == parent->left ? parent->right : parent->left;
								repeat = true;
							}
							else
								return ;
						}
						else if ((!x || !x->is_red) && sibling && !sibling->is_red &&
						((x_is_left_child && sibling_childs_redness == 1) || (!x_is_left_child && sibling_childs_redness == 2)))
						{																			// CASE 3
							sibling->is_red = true;
							if (x_is_left_child)
							{
								sibling->left->is_red = false;
								right_rotation(sibling, &_root_node);
								sibling = parent->right;
							}
							else
							{
								sibling->right->is_red = false;
								left_rotation(sibling, &_root_node);
								sibling = parent->left;
							}
							sibling_childs_redness = sibling->has_red_childs();
						}

						if ((!x || !x->is_red) && (!sibling || !sibling->is_red) &&
						((x_is_left_child && sibling_childs_redness >= 2) || (!x_is_left_child && sibling_childs_redness == 1)))
						{																// CASE 4
							sibling->is_red = parent->is_red;
							parent->is_red = false;
							if (x_is_left_child)
							{
								sibling->right->is_red = false;
								left_rotation(parent, &_root_node);
							}
							else
							{
								sibling->left->is_red = false;
								right_rotation(parent, &_root_node);
							}
						}

					} while (repeat);
				}

				// Places the end node received as argument on the rightmost position
				void	_emplace_end_node(node_type *end_node)
				{
					node_type *parent = rightmost(_root_node);
					parent->right = end_node;
					end_node->parent = parent;
				}

				/*
				**	Receives a pointer to the node it'll copy and other to its parent
				**	Allocates the new node and asigns its parent pointer to its parent variable
				**	If the original node has any child, the same function is called recursively with its
				**	own pointer as the parent argument, and the child as the original node
				**	Then returns its direction
				*/
				node_type	*_copy_node(node_type *parent, node_type *original_node)
				{
					node_type	*new_node = _allocator.allocate(1);
					_allocator.construct(new_node, node_type(original_node->value, parent));
					new_node->is_red = original_node->is_red;
					if (original_node->left)
						new_node->left = _copy_node(new_node, original_node->left);
					if (original_node->right)
						new_node->right = _copy_node(new_node, original_node->right);
					return (new_node);
				}

				// Calls allocator destroy and deallocate on a node
				void	_destroy_node(node_type *node)
				{
					_allocator.destroy(node);
					_allocator.deallocate(node, 1);
				}

				// Calls _destroy_node() on a node and all of its children recursively
				void	_destroy_node_recursive(node_type *node)
				{
					if (node->left)
						_destroy_node_recursive(node->left);
					if (node->right)
						_destroy_node_recursive(node->right);

					_destroy_node(node);
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