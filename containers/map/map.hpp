#ifndef MAP_HPP
# define MAP_HPP

// #include <functional> // less
#include <memory> // allocator
#include "../algorithm.hpp" // ft::equal
#include "../utility.hpp"
#include "../type_traits.hpp" // enable if
#include "rb_tree.hpp"

namespace ft {

	template <	class Key, class Val,
				class Compare = std::less<Key>,
				class Allocator = std::allocator<ft::pair<const Key, Val> > >
		class map
		{
			// TYPES
			private:
				typedef	ft::rb_tree_node<ft::pair<const Key, Val> > node_type;
				typedef	ft::rb_tree<Key, Val, Compare, typename Allocator::template rebind<node_type>::other> tree_type;
			public:
				typedef Key												key_type;
				typedef Val												mapped_type;
				typedef ft::pair<const key_type, mapped_type>			value_type;
				typedef Compare											key_compare;
				typedef Allocator										allocator_type;
				typedef typename allocator_type::reference				reference;
				typedef typename allocator_type::const_reference		const_reference;
				typedef typename allocator_type::pointer				pointer;
				typedef typename allocator_type::const_pointer			const_poiner;
				typedef typename tree_type::iterator					iterator;
				typedef typename tree_type::const_iterator				const_iterator;
				typedef typename tree_type::reverse_iterator			reverse_iterator;
				typedef typename tree_type::const_reverse_iterator		const_reverse_iterator;
				typedef typename tree_type::difference_type				difference_type;
				typedef typename tree_type::size_type					size_type;

			private:
				tree_type _tree;
				
			public:
				void	displayTree(void) { _tree.displayTree(); }
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
					_tree(comp, alloc) { }

				// range
				template <class InputIterator>
					map (InputIterator first, InputIterator last,
						const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type(),
						typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
						: _tree(comp, alloc)
						{
							for (; first != last; ++first)
								insert(*first);
						}

				// Constructs a container with a copy of each of the elements in x.
				map (const map& other): _tree(other._tree) { }

				~map() { }

				map& operator= (const map& other)
				{
					_tree = other._tree;
					return *this;
				}

				bool		empty() const { return _tree.empty(); }

				size_type	size() const { return _tree.size(); }

				size_type max_size() const { return _tree.max_size(); }

				// INSERT
				//single element
				ft::pair<iterator, bool>	insert(const value_type& val)
				{
					return _tree.insert(val);
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
					return (_tree.find(key));
				}

				const_iterator	find (const key_type& key) const
				{
					return (_tree.find(key));
				}

				size_type	count (const key_type& key) const
				{
					return (_tree.find(key) == _tree.end() ? 0 : 1);
				}

				// ERASE
				void erase (iterator position)
				{
					_tree.erase(position.base());
				}

				size_type erase (const key_type& key)
				{
					node_type *key_node = _tree.find(key);
					if (key_node != _tree.end())
					{
						_tree.erase(key_node);
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
					return iterator(_tree.begin());
				}

				const_iterator begin() const
				{
					return const_iterator(_tree.begin());
				}

				iterator end()
				{
					return iterator(_tree.end());
				}

				const_iterator end() const
				{
					return const_iterator(_tree.end());
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

				allocator_type get_allocator() const { return allocator_type(_tree.get_allocator()); }

				void swap (map& other)
				{
					_tree.swap(other._tree);
				}

				void clear()
				{
					_tree.clear();
				}

				key_compare key_comp() const { return _tree.key_comp(); }

				value_compare value_comp() const { return value_compare(_tree.key_comp()); }

				iterator lower_bound (const key_type& key)
				{
					return _tree.lower_bound(key);
				}

				const_iterator lower_bound (const key_type& key) const
				{
					return _tree.lower_bound(key);
				}

				iterator upper_bound (const key_type& key)
				{
					return _tree.upper_bound(key);
				}

				const_iterator upper_bound (const key_type& key) const
				{
					return _tree.upper_bound(key);
				}

				ft::pair<iterator,iterator>		equal_range (const key_type& key)
				{
					return _tree.equal_range(key);
				}

				ft::pair<const_iterator,const_iterator>		equal_range (const key_type& key) const
				{
					return _tree.equal_range(key);
				}

		};

		template <class Key, class Val, class Compare, class Alloc>
		bool operator== ( const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs )
		{
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		template <class Key, class Val, class Compare, class Alloc>
		bool operator!= ( const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs )
		{
			return !(lhs == rhs);
		}

		template <class Key, class Val, class Compare, class Alloc>
		bool operator< ( const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs )
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class Key, class Val, class Compare, class Alloc>
		bool operator<= ( const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs )
		{
			return !(rhs < lhs);
		}

		template <class Key, class Val, class Compare, class Alloc>
		bool operator> ( const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs )
		{
			return (rhs < lhs);
		}

		template <class Key, class Val, class Compare, class Alloc>
		bool operator>= ( const map<Key,Val,Compare,Alloc>& lhs, const map<Key,Val,Compare,Alloc>& rhs )
		{
			return !(lhs < rhs);
		}

		template <class Key, class Val, class Compare, class Alloc>
		void swap (map<Key,Val,Compare,Alloc>& x, map<Key,Val,Compare,Alloc>& y)
		{
			x.swap(y);
		}
};

#endif