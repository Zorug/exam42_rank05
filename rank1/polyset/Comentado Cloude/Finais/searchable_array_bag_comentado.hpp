#pragma once

# include "searchable_bag.hpp"
# include "array_bag.hpp"

/*
** searchable_array_bag
**
** Combina duas classes-base através de herança múltipla:
**   - searchable_bag : interface abstrata que exige a implementação de has()
**   - array_bag      : implementação concreta do bag usando um array dinâmico
**
** Ambas herdam (virtualmente) de "bag", pelo que aqui não há ambiguidade
** de diamante: só existe UM sub-objeto "bag" partilhado entre os dois pais.
**
** Resultado: um bag baseado em array que sabe pesquisar (has), completando
** assim todos os métodos puramente virtuais (insert, print, clear vêm de
** array_bag; has vem daqui).
*/
class	searchable_array_bag : public searchable_bag, public array_bag
{
	public:
		// Construtor por defeito.
		// Corpo vazio: array_bag() já inicializa data=nullptr e size=0
		// automaticamente (é chamado implicitamente antes deste corpo correr).
		searchable_array_bag() {};

		// Construtor de cópia.
		// Delega toda a cópia dos dados (array + size) para o construtor
		// de cópia de array_bag, que é quem realmente possui esses membros.
		// searchable_array_bag não acrescenta nenhum atributo próprio,
		// por isso não há mais nada para copiar aqui.
		searchable_array_bag(const searchable_array_bag &other) : array_bag(other) {}

		// Operador de atribuição (assignment).
		// Declarado aqui, implementado no .cpp (delega em array_bag::operator=).
		searchable_array_bag	&operator=(const searchable_array_bag &other);

		// Implementação do método pesquisável exigido por searchable_bag.
		// Marcado const: não modifica o estado do objeto, apenas consulta.
		bool	has(int value) const;

		// Nota: não há destrutor próprio declarado — e está correto assim.
		// array_bag::~array_bag() já trata do delete[] de "data" e é
		// chamado automaticamente quando este objeto é destruído.
};
