#ifndef RB_TREE_HPP
# define RB_TREE_HPP

#include <memory> // allocator
#include <functional> // less
#include <limits> // numeric_limits
#include "../iterator.hpp" // reverse_iterator
#include "rb_tree_node.hpp"
#include "tree_iterator.hpp"
#include <iostream> // cout displayTree
namespace ft
{
	template <class Key, class Value, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, Value> > >
	class rb_tree
	{
		public:
			typedef ft::pair<const Key, Value>											value_type;
			typedef	ft::rb_tree_node<ft::pair<const Key, Value> >						node_type;
			typedef ft::MapIterator<value_type, node_type>								iterator;
			typedef ft::MapIterator<const value_type, ft::rb_tree_node<value_type> >	const_iterator;
			typedef ft::reverse_iterator<iterator>										reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
			typedef std::ptrdiff_t														difference_type;
			typedef std::size_t															size_type;

		private:
			Compare		_key_compare;
			Allocator	_allocator;
			size_type	_size;
			node_type	*_root;

		public:

			void displayTree(node_type *node = NULL)
			{
				if (!node)
				{
					node = _root;
					std::cout << std::endl;
				}
				if (node->right)
					displayTree(node->right);
				size_t offset = depth(node);
				while (offset--)
					std::cout << '\t';
				if (node->color == _color_red)
					std::cout << "\033[1;31m" << node->value.first << "\033[0m" << std::endl;
				else
					std::cout << node->value.first << std::endl;
				if (node->left)
					displayTree(node->left);
				if (node == _root)
					std::cout << "---------------------------------\n";
			}

		rb_tree(Compare compare = Compare(), Allocator allocator = Allocator()): _key_compare(compare), _allocator(allocator), _size(0)
		{
			_root = _allocator.allocate(1);
			_allocator.construct(_root, node_type(_color_black));
		}

		rb_tree(const rb_tree &other): _key_compare(other._key_compare), _allocator(other._allocator), _size(other._size)
		{
			_root = _copy_node(NULL, other._root);
		}

		rb_tree& operator= (const rb_tree& other)
		{
			_destroy_node_recursive(_root);
			_root = _copy_node(NULL, other._root);
			_size = other._size;
			return (*this);
		}

		~rb_tree()
		{
			_destroy_node_recursive(_root);
		}

		void swap (rb_tree& other)
		{
			std::swap(_root, other._root);
			std::swap(_size, other._size);
		}

		void	clear(void)
		{
			node_type *end_node = rightmost(_root);

			if (_size == 0)
				return ;
			end_node->parent->right = NULL;
			_destroy_node_recursive(_root);
			_root = end_node;
			_size = 0;
		}

		size_type	size(void) const { return _size; }

		size_type	max_size() const { return std::numeric_limits<difference_type>::max() / (sizeof(node_type)); }

		bool		empty(void) const { return _size == 0; }

		Compare		key_comp(void) const { return _key_compare; }

		Allocator	get_allocator(void) const { return _allocator; }

		node_type	*begin(void) const { return leftmost(_root); }

		node_type	*end(void) const { return rightmost(_root); }

		node_type	*find(const Key &key) const
		{
			node_type *current_node = _root;
			while (current_node)
			{
				if (_key_compare(key, current_node->value.first))
					current_node = current_node->left;
				else if (_key_compare(current_node->value.first, key))
					current_node = current_node->right;
				else
					return current_node;
			}
			return (rightmost(_root));
		}

		ft::pair<iterator, bool>	insert(const value_type& val)
		{
			ft::pair<iterator, bool>	return_pair;

			return_pair.second = find(val.first) == end();
			if (return_pair.second == true)
			{
				node_type	*new_node = _allocator.allocate(1);
				_allocator.construct(new_node, val);
				insert_node(new_node);
				return_pair.first = iterator(new_node);
			}
			else
				return_pair.first = find(val.first);

			return (return_pair);
		}

		void	insert_node(node_type *new_node)
		{
			node_type	**parent = &_root;
			node_type	**node = &_root;
			node_type	*end_node = rightmost(_root);

			++_size;

			while (*node && *node != end_node)
			{
				parent = node;
				node = _key_compare(new_node->value.first, (*node)->value.first) ? &(*node)->left : &(*node)->right;
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
				rightmost(new_node)->right = end_node;
			}
			new_node->color = _color_red;

			end_node = rightmost(_root);
			end_node->parent->right = NULL;
			_fix_insert_violation(new_node);
			_emplace_end_node(end_node);
		}

		void	erase (node_type *erased)
		{
			// saco el nodo end_node
			node_type *end_node = rightmost(_root);
			end_node->parent->right = NULL;


			node_type *replace_node = NULL;
			node_type **remove_place = &_root;

			--_size;
			if (erased == _root && _size == 0)
			{
				_root = end_node;
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

		iterator		lower_bound (const Key& key)
		{
			iterator it = begin();
			iterator last = end();
			while (it != last && _key_compare(it->first, key))
				++it;
			return (it);
		}

		const_iterator	lower_bound (const Key& key) const
		{
			const_iterator it = begin();
			const_iterator last = end();
			while (it != last && _key_compare(it->first, key))
				++it;
			return (it);
		}

		iterator		upper_bound (const Key& key)
		{
			iterator it = begin();
			iterator last = end();
			while (it != last && !_key_compare(key, it->first))
				++it;
			return (it);
		}

		const_iterator	upper_bound (const Key& key) const
		{
			const_iterator it = begin();
			const_iterator last = end();
			while (it != last && !_key_compare(key, it->first))
				++it;
			return (it);
		}

		ft::pair<iterator,iterator>		equal_range (const Key& key)
		{
			iterator it = begin();
			iterator last = end();
			while (it != last && _key_compare(it->first, key))
				++it;
			if (!_key_compare(it->first, key) && !_key_compare(key, it->first))
				return ft::make_pair(it, ++it);
			else
				return ft::make_pair(it, it);
		}

		ft::pair<const_iterator,const_iterator>		equal_range (const Key& key) const
		{
			const_iterator it = begin();
			const_iterator last = end();
			while (it != last && _key_compare(it->first, key))
				++it;
			if (!_key_compare(it->first, key) && !_key_compare(key, it->first))
				return ft::make_pair(it, ++it);
			else
				return ft::make_pair(it, it);
		}

		private:

		void	_fix_insert_violation(node_type *node)
		{
			node_type *parent = NULL;
			node_type *grandparent = NULL;
			while (node && node != _root && node->color == _color_red && node->parent->color == _color_red)
			{
				parent = node->parent;
				grandparent = parent->parent;
				const bool	parent_is_left_child = (parent == grandparent->left);
				node_type	*uncle = (parent_is_left_child) ? grandparent->right : grandparent->left;
				if (uncle && uncle->color == _color_red)
				{
					parent->color = _color_black;
					uncle->color = _color_black;
					grandparent->color = _color_red;
					node = grandparent;
				}
				else
				{
					if (parent == grandparent->left && node == parent->left)
						left_left_rotation(node, &_root);
					else if (parent == grandparent->right && node == parent->right)
						right_right_rotation(node, &_root);
					else if (parent == grandparent->left && node == parent->right)
						left_right_rotation(node, &_root);
					else
						right_left_rotation(node, &_root);
					if (node->parent)
						node = node->parent->parent;
				}
			}
			_root->color = _color_black;
		}

		void	_fix_erase_violation(node_type *replace_node, node_type *erased, node_type *x, node_type *parent, bool x_is_left_child)
		{
			if (erased->color == _color_red && (replace_node == NULL || replace_node->color == _color_red))
				return ;
			else if (erased->color == _color_red && (!replace_node || replace_node->color == _color_black))
				replace_node->color = _color_red;
			else if (erased->color == _color_black && replace_node && replace_node->color == _color_red)
			{
				replace_node->color = _color_black;
				return ;
			}
			else if (erased->color == _color_black && (!replace_node || replace_node->color == _color_black) && x == _root)
				return ;

			// declares and initialices parent and sibling pointers
			if (!parent && replace_node)
				parent = replace_node;
			else if (!parent && !replace_node)
				parent = erased->parent;
			node_type *sibling = NULL;

			if (parent)
				sibling = (x == parent->left) ? parent->right : parent->left;

			t_children_color	sibling_children_color = both_black;
			if (sibling)
				sibling_children_color = sibling->has_red_children();

			if (replace_node == _root)
				return ;

			// leaf has been deleted, if deletedNode was black, then doubleBlack case
			bool repeat;
			do
			{
				repeat = false;
				if (sibling)
					sibling_children_color = sibling->has_red_children();

				if (x && x->color == _color_red)
				{
					x->color = _color_black;
					return ;
				}
				else if ((!x || x->color == _color_black) && sibling->color == _color_red)
				{
					sibling->color = _color_black;
					parent->color = _color_red;
					if (x == parent->left)
					{
						left_rotation(parent, &_root);
						sibling = parent->right;
					}
					else
					{
						right_rotation(parent, &_root);
						sibling = parent->left;
					}
					if (sibling)
						sibling_children_color = sibling->has_red_children();
				}
				if ((!x || x->color == _color_black) && sibling && sibling->color == _color_black && sibling_children_color == both_black)
				{
					sibling->color = _color_red;
					x = parent;
					x_is_left_child = (x->parent) ? x == x->parent->left : true;
					if (x->color == _color_red)
					{
						x->color = _color_black;
						return ;
					}
					else if (x->color == _color_black && x != _root)
					{
						parent = parent->parent;
						sibling = x == parent->left ? parent->right : parent->left;
						repeat = true;
					}
					else
						return ;
				}
				else if ((!x || x->color == _color_black) && sibling && sibling->color == _color_black &&
				((x_is_left_child && sibling_children_color == left_red) || (!x_is_left_child && sibling_children_color == right_red)))
				{
					sibling->color = _color_red;
					if (x_is_left_child)
					{
						sibling->left->color = _color_black;
						right_rotation(sibling, &_root);
						sibling = parent->right;
					}
					else
					{
						sibling->right->color = _color_black;
						left_rotation(sibling, &_root);
						sibling = parent->left;
					}
					sibling_children_color = sibling->has_red_children();
				}

				if ((!x || x->color == _color_black) && (!sibling || sibling->color == _color_black) &&
				((x_is_left_child && sibling_children_color >= right_red) || (!x_is_left_child && sibling_children_color == left_red)))
				{
					sibling->color = parent->color;
					parent->color = _color_black;
					if (x_is_left_child)
					{
						sibling->right->color = _color_black;
						left_rotation(parent, &_root);
					}
					else
					{
						sibling->left->color = _color_black;
						right_rotation(parent, &_root);
					}
				}

			} while (repeat);
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
			new_node->color = original_node->color;
			if (original_node->left)
				new_node->left = _copy_node(new_node, original_node->left);
			if (original_node->right)
				new_node->right = _copy_node(new_node, original_node->right);
			return (new_node);
		}

		// Places the end node received as argument on the rightmost position
		void	_emplace_end_node(node_type *end_node)
		{
			node_type *parent = rightmost(_root);
			parent->right = end_node;
			end_node->parent = parent;
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

		// Calls allocator destroy and deallocate on a node
		void	_destroy_node(node_type *node)
		{
			_allocator.destroy(node);
			_allocator.deallocate(node, 1);
		}

	};

}
#endif