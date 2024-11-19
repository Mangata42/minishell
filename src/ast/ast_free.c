#include "../../include/minishell.h"

void add_root(t_ast_node *node, t_ast_node *root)
{
	if(!node)
		return ;
	node->root = root;
	add_root(node->left, root);
	add_root(node->right, root);
}

void free_node(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			free(node->argv[i]);
			i++;
		}
		free(node->argv);
	}
	if (node->filename)
		free(node->filename);
	free(node);
}
