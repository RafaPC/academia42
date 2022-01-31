#ifndef NODE_TREE_HPP
# define NODE_TREE_HPP

#include "../utility.hpp"
#include <iostream> //FIXME: borrar

namespace ft
{
	template <typename T>
	struct tree_node
	{
		tree_node (bool	is_red): is_red(is_red), value(T()), parent(NULL), left(NULL), right(NULL) {}
		tree_node (const T &src = T(), tree_node *parent = NULL): is_red(), value(src), parent(parent), left(NULL), right(NULL) {};

		bool is_red;
		int whatever; //FIXME: solo sirve para que de el mismo tamaño teórico
		T				value;
		tree_node		*parent;
		tree_node		*left;
		tree_node		*right;

		int	has_red_childs(void) const
		{
			if ((left && left->is_red) && (right && right->is_red))
				return (3);
			else if (left && left->is_red)
				return (1);
			else if (right && right->is_red)
				return (2);
			else
				return (0);
		}
	};

	template <typename T>
		tree_node<T>	*leftmost(tree_node<T> *node)
		{
			while (node->left)
				node = node->left;
			return (node);
		}
	
	template <typename T>
		tree_node<T>	*rightmost(tree_node<T> *node)
		{
			while (node->right)
				node = node->right;
			return (node);
		}

	template <typename T>
		size_t depth(tree_node<T> *node)
		{
			if (!node || !node->parent)
				return (0);
			return (1 + depth(node->parent));
		}

	template <typename T>
		size_t	color_depth(tree_node<T> *node)
		{
			if (!node)
				return (1);
			else
				return (abs(color_depth(node->left) - color_depth(node->right)) + (!node->is_red));
		}

	template <typename T>
		tree_node<T>	*left_left_rotation(tree_node<T> *node, tree_node<T> **root)
		{
			tree_node<T>	*parent = node->parent;
			tree_node<T>	*grandparent = parent->parent;
			// grandparent right rotation
			right_rotation(grandparent, root);
			// grandparent and parent color swap
			std::swap(grandparent->is_red, parent->is_red);
			return (parent->left);
		}
	
	template <typename T>
		tree_node<T>	*left_right_rotation(tree_node<T> *node, tree_node<T> **root)
		{
			tree_node<T>	*parent = (node->parent) ? node->parent : *root;
			left_rotation(parent, root);
			// left left rotation
			return (left_left_rotation(parent, root));
		}
	
	template <typename T>
		tree_node<T>	*right_right_rotation(tree_node<T> *node, tree_node<T> **root)
		{
			// grandparent right rotation
			tree_node<T>	*parent = (node->parent) ? node->parent : *root;
			tree_node<T>	*grandparent = (parent->parent) ? parent->parent : *root;
			left_rotation(grandparent, root);
			// grandparent and parent color swap
			std::swap(grandparent->is_red, parent->is_red);
			return (grandparent);
		}
	
	template <typename T>
		tree_node<T>	*right_left_rotation(tree_node<T> *node, tree_node<T> **root)
		{
			right_rotation(node->parent, root);
			return (right_right_rotation(node->right, root));
		}

	template <typename T>
		void	left_rotation(tree_node<T> *node, tree_node<T> **root)
		{
			tree_node<T>	*new_parent = node->right;
			*(parent_child_pointer(node, root)) = new_parent;
			node->right = new_parent->left;
			if (node->right)
				node->right->parent = node;
			new_parent->left = node;
			new_parent->parent = node->parent;
			node->parent = new_parent;
		}

	template <typename T>
		void	right_rotation(tree_node<T> *node, tree_node<T> **root)
		{
			tree_node<T>	*new_parent = node->left;
			*(parent_child_pointer(node, root)) = new_parent;
			node->left = new_parent->right;
			if (node->left)
				node->left->parent = node;
			new_parent->right = node;
			new_parent->parent = node->parent;
			node->parent = new_parent;
		}

	template <typename T>
		tree_node<T>	**parent_child_pointer(tree_node<T> *node, tree_node<T> **root)
		{
			if (node == *root)
				return (root);
			else
				return (node == node->parent->left) ? &node->parent->left : &node->parent->right;
		}
}

#endif