#ifndef RB_TREE_NODE_HPP
# define RB_TREE_NODE_HPP

#include "../utility.hpp"
#include <stddef.h> // size_t

namespace ft
{
	typedef enum	t_children_color { both_black, left_red, right_red, both_red } t_children_color;
	enum _rb_node_color { _color_red = false, _color_black = true };

	template <typename T>
	struct rb_tree_node
	{
		rb_tree_node (_rb_node_color color): color(color), value(T()), parent(NULL), left(NULL), right(NULL) {}
		rb_tree_node (const T &src = T(), rb_tree_node *parent = NULL): color(_color_black), value(src), parent(parent), left(NULL), right(NULL) {};

		_rb_node_color	color;
		T				value;
		rb_tree_node	*parent;
		rb_tree_node	*left;
		rb_tree_node	*right;

		t_children_color	has_red_children(void) const
		{
			if ((left && left->color == _color_red) && (right && right->color == _color_red))
				return (both_red);
			else if (left && left->color == _color_red)
				return (left_red);
			else if (right && right->color == _color_red)
				return (right_red);
			else
				return (both_black);
		}
	};

	template <typename T>
		rb_tree_node<T>	*leftmost(rb_tree_node<T> *node)
		{
			while (node->left)
				node = node->left;
			return (node);
		}
	
	template <typename T>
		rb_tree_node<T>	*rightmost(rb_tree_node<T> *node)
		{
			while (node->right)
				node = node->right;
			return (node);
		}

	template <typename T>
		size_t depth(rb_tree_node<T> *node)
		{
			if (!node || !node->parent)
				return (0);
			return (1 + depth(node->parent));
		}

	template <typename T>
		size_t	color_depth(rb_tree_node<T> *node)
		{
			if (!node)
				return (1);
			else
				return (abs(color_depth(node->left) - color_depth(node->right)) + (node->color == _color_black));
		}

	template <typename T>
		rb_tree_node<T>	*left_left_rotation(rb_tree_node<T> *node, rb_tree_node<T> **root)
		{
			rb_tree_node<T>	*parent = node->parent;
			rb_tree_node<T>	*grandparent = parent->parent;
			// grandparent right rotation
			right_rotation(grandparent, root);
			// grandparent and parent color swap
			std::swap(grandparent->color, parent->color);
			return (parent->left);
		}
	
	template <typename T>
		rb_tree_node<T>	*left_right_rotation(rb_tree_node<T> *node, rb_tree_node<T> **root)
		{
			rb_tree_node<T>	*parent = (node->parent) ? node->parent : *root;
			left_rotation(parent, root);
			return (left_left_rotation(parent, root));
		}
	
	template <typename T>
		rb_tree_node<T>	*right_right_rotation(rb_tree_node<T> *node, rb_tree_node<T> **root)
		{
			// grandparent right rotation
			rb_tree_node<T>	*parent = (node->parent) ? node->parent : *root;
			rb_tree_node<T>	*grandparent = (parent->parent) ? parent->parent : *root;
			left_rotation(grandparent, root);
			// grandparent and parent color swap
			std::swap(grandparent->color, parent->color);
			return (grandparent);
		}
	
	template <typename T>
		rb_tree_node<T>	*right_left_rotation(rb_tree_node<T> *node, rb_tree_node<T> **root)
		{
			right_rotation(node->parent, root);
			return (right_right_rotation(node->right, root));
		}

	template <typename T>
		void	left_rotation(rb_tree_node<T> *node, rb_tree_node<T> **root)
		{
			rb_tree_node<T>	*new_parent = node->right;
			*(parent_child_pointer(node, root)) = new_parent;
			node->right = new_parent->left;
			if (node->right)
				node->right->parent = node;
			new_parent->left = node;
			new_parent->parent = node->parent;
			node->parent = new_parent;
		}

	template <typename T>
		void	right_rotation(rb_tree_node<T> *node, rb_tree_node<T> **root)
		{
			rb_tree_node<T>	*new_parent = node->left;
			*(parent_child_pointer(node, root)) = new_parent;
			node->left = new_parent->right;
			if (node->left)
				node->left->parent = node;
			new_parent->right = node;
			new_parent->parent = node->parent;
			node->parent = new_parent;
		}

	template <typename T>
		rb_tree_node<T>	**parent_child_pointer(rb_tree_node<T> *node, rb_tree_node<T> **root)
		{
			if (node == *root)
				return (root);
			else
				return (node == node->parent->left) ? &node->parent->left : &node->parent->right;
		}

}

#endif