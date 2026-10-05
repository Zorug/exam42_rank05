#include "searchable_array_bag.hpp"

// Operador de atribuição (assignment).
// searchable_array_bag não tem atributos próprios (data e size pertencem
// a array_bag), por isso a única coisa a fazer é delegar no operator=
// de array_bag, que copia o array e o size corretamente (aloca novo
// array, copia elemento a elemento, liberta o antigo).
searchable_array_bag	&searchable_array_bag::operator=(const searchable_array_bag &other)
{
	// Proteção contra auto-atribuição (ex: a = a;).
	// Sem isto, array_bag::operator= faria delete[] ao próprio array
	// antes de o tentar copiar de volta, corrompendo o objeto.
	if (this != &other)
		array_bag::operator=(other);
	return (*this);
}

// Implementação de has(), exigida pela interface searchable_bag.
// Faz uma pesquisa linear (O(n)) pelo array "data" (herdado de array_bag,
// acessível diretamente por ser "protected").
bool	searchable_array_bag::has(int value) const
{
	// Percorre todos os elementos guardados...
	for (int i = 0; i < size; ++i)
		// ...e assim que encontra uma correspondência, retorna
		// imediatamente (não precisa de continuar a procurar).
		if (data[i] == value)
			return (true);
	// Chegou ao fim sem encontrar: o valor não está no bag.
	return (false);
}

/*
** Nota de desempenho: has() aqui é O(n), ao contrário de
** searchable_tree_bag::has(), que aproveita a propriedade da árvore
** binária de pesquisa para ser O(log n) em média. É uma diferença
** esperada dada a estrutura de dados subjacente, não um erro.
*/
