#pragma once

# include "searchable_bag.hpp"
# include "tree_bag.hpp"

/*
** searchable_tree_bag
**
** Igual em espírito a searchable_array_bag, mas combinando:
**   - searchable_bag : interface abstrata que exige has()
**   - tree_bag       : implementação concreta do bag usando uma árvore
**                       binária de pesquisa (BST) como estrutura interna
**
** Ambas herdam (virtualmente) de "bag", por isso não há ambiguidade de
** diamante: existe apenas UM sub-objeto "bag" partilhado entre os dois pais.
**
** Resultado: um bag baseado em árvore que sabe pesquisar (has), completando
** todos os métodos puramente virtuais (insert, print, clear vêm de
** tree_bag; has vem daqui).
*/
class	searchable_tree_bag : public searchable_bag, public tree_bag
{
	public:
		// Construtor por defeito.
		// Corpo vazio: tree_bag() já inicializa tree=nullptr automaticamente
		// (chamado implicitamente antes deste corpo correr).
		searchable_tree_bag() {};

		// Construtor de cópia.
		// Delega toda a cópia para o construtor de cópia de tree_bag,
		// que percorre e clona a árvore inteira nó a nó (deep copy,
		// via copy_node). searchable_tree_bag não tem atributos próprios,
		// por isso não há mais nada a copiar aqui.
		searchable_tree_bag(const searchable_tree_bag &other) : tree_bag(other) {};

		// Operador de atribuição (assignment).
		// Declarado aqui, implementado no .cpp (delega em tree_bag::operator=).
		searchable_tree_bag	&operator=(const searchable_tree_bag &other);

		// Implementação do método pesquisável exigido por searchable_bag.
		// Aproveita a propriedade de ordenação da BST (subárvore esquerda
		// < nó < subárvore direita) para pesquisar em O(log n) em média,
		// em vez de percorrer todos os elementos como em array_bag.
		// Marcado const: não modifica o estado do objeto, apenas consulta.
		bool	has(int value) const;

		// Nota: não há destrutor próprio declarado — e está correto assim.
		// tree_bag::~tree_bag() já trata de destruir a árvore inteira
		// (destroy_tree) e é chamado automaticamente.
};
