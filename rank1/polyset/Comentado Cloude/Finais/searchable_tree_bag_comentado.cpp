#include "searchable_tree_bag.hpp"

// Operador de atribuição (assignment).
// searchable_tree_bag não tem atributos próprios (a árvore "tree" pertence
// a tree_bag), por isso a única coisa a fazer é delegar no operator=
// de tree_bag, que trata de:
//   1. destruir a árvore atual deste objeto (destroy_tree)
//   2. clonar a árvore de "other" nó a nó (copy_node) — deep copy
searchable_tree_bag	&searchable_tree_bag::operator=(const searchable_tree_bag &other)
{
	// Proteção contra auto-atribuição (ex: a = a;).
	// Sem isto, tree_bag::operator= destruiria a árvore antes de a
	// tentar copiar de volta a partir de si própria, perdendo os dados.
	if (this != &other)
		tree_bag::operator=(other);
	return (*this);
}

// Implementação de has(), exigida pela interface searchable_bag.
// Aproveita a propriedade de ordenação da árvore binária de pesquisa
// (BST): tudo à esquerda de um nó é menor, tudo à direita é maior.
// Isto permite eliminar metade da árvore a cada passo, em vez de
// percorrer todos os nós (O(log n) em média, contra O(n) num array).
bool	searchable_tree_bag::has(int value) const
{
	// "tree" é o membro protected herdado de tree_bag (a raiz da árvore).
	// Começamos a descer a partir da raiz.
	node	*tmp = tree;

	// Percorre a árvore enquanto não cair fora dela (nó nulo = não encontrado
	// nesse ramo).
	while (tmp)
	{
		// Encontrámos o valor: para de procurar.
		if (value == tmp->value)
			return (true);
		// O valor procurado é menor que o nó atual: só pode estar
		// (se existir) na subárvore esquerda.
		else if (value < tmp->value)
			tmp = tmp->l;
		// Caso contrário (value > tmp->value): só pode estar
		// na subárvore direita.
		else
			tmp = tmp->r;
	}
	// Chegámos a um nó nulo sem encontrar o valor: não existe na árvore.
	return (false);
}

/*
** Nota: "tree_bag::node" é uma struct "protected" dentro de tree_bag,
** por isso searchable_tree_bag acede-lhe diretamente (tmp->l, tmp->r,
** tmp->value) por herança pública — sem precisar de nenhum getter.
*/
