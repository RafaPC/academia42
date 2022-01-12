#ifndef NODE_TREE_HPP
# define NODE_TREE_HPP

#include "../utility.hpp"

namespace ft
{
	template <typename T>
	struct tree_node
	{
		bool _unused;
		tree_node (const T &src = T()): value(src), parent(NULL), child1(NULL), child2(NULL) {};
		int whatever; //FIXME: solo sirve para que de el mismo tamaño teórico
		T				value;
		tree_node		*parent;
		tree_node		*child1;
		tree_node		*child2;

	};

	template <typename T>
		tree_node<T>	*leftmost(tree_node<T> *node)
		{
			while (node->child1)
				node = node->child1;
			return (node);
		}
	
	template <typename T>
		tree_node<T>	*rightmost(tree_node<T> *node)
		{
			while (node->child2)
				node = node->child2;
			return (node);
		}

}

#endif