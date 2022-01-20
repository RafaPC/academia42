#ifndef NODE_TREE_HPP
# define NODE_TREE_HPP

#include "../utility.hpp"

namespace ft
{
	template <typename T>
	struct tree_node
	{
		tree_node (const T &src = T()): value(src), parent(NULL), left(NULL), right(NULL) {};
		bool is_red;
		int whatever; //FIXME: solo sirve para que de el mismo tamaño teórico
		T				value;
		tree_node		*parent;
		tree_node		*left;
		tree_node		*right;

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
		int		height(tree_node<T> *node)
		{
			if (node == NULL)
				return (0);
			else
				return (1 + std::max(height(node->left), height(node->right)));
		}

	template <typename T>
		size_t depth(tree_node<T> *node)
		{
			if (!node)
				return (0);
			return (1 + depth(node->parent));
		}

	template <typename T>
		void displayTree(tree_node<T> *node)
		{
			if (!node)
				return;
			displayTree(node->right);
			size_t offset = depth(node);
			while (offset--)
				std::cout << '\t';
			std::cout << node->value.first << "\n";
			displayTree(node->left);
		}
}

#endif