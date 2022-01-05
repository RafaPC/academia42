#ifndef NODE_TREE_HPP
# define NODE_TREE_HPP

namespace ft
{
	template <typename T>
	class tree_node
	{
		public:
			tree_node (void): parent(NULL), child1(NULL), child2(NULL) {};
			tree_node (tree_node *parent): parent(parent), child1(NULL), child2(NULL) {};

			// tree_node operator= (const tree_node &other)
			// {

			// }

			tree_node *min(void)
			{
				tree_node	*aux = this;
				while (aux->child1)
					aux = aux->child1;
				return (aux);
			}

			tree_node *max(void)
			{
				tree_node	*aux = this;
				while (aux->child2)
					aux = aux->child2;
				return (aux);
			}

			T				*value;
			tree_node		*parent;
			tree_node		*child1;
			tree_node		*child2;

	};
}

#endif