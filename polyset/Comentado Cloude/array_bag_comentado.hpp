#pragma once

#include "bag.hpp"

/*
** array_bag
**
** Implementação CONCRETA de "bag", usando um array dinâmico de int
** como estrutura de armazenamento subjacente. Ao contrário de "bag"
** e "searchable_bag" (ambas abstratas), esta classe implementa TODOS
** os métodos puramente virtuais herdados, por isso já pode ser
** instanciada diretamente (new array_bag() é válido).
**
** "virtual public bag": tal como em searchable_bag, a herança é virtual
** para evitar duplicação do sub-objeto "bag" quando, mais tarde,
** searchable_array_bag herdar simultaneamente de array_bag E de
** searchable_bag (ambos descendentes de "bag").
**
** Sem função de pesquisa (has): um array_bag "puro" não sabe procurar
** elementos — essa capacidade só é acrescentada pela subclasse
** searchable_array_bag, que combina esta classe com searchable_bag.
*/
class array_bag : virtual public bag
{
 protected:
	// "protected" (em vez de "private") é uma escolha deliberada: permite
	// que classes derivadas (como searchable_array_bag) acedam
	// diretamente a "data" e "size" para implementar has() sem precisar
	// de getters extra.
	int *data;   // array alocado dinamicamente com os elementos do bag
	int size;    // número de elementos atualmente guardados em "data"

 public:
	// --- Forma Canónica Ortodoxa (Orthodox Canonical Form) ---
	// As 4 funções abaixo são obrigatórias sempre que uma classe gere
	// recursos próprios (aqui: memória alocada com "new[]"), para
	// garantir cópias seguras e evitar leaks / double-free / dangling
	// pointers.

	array_bag();                              // construtor por defeito
	array_bag(const array_bag &);             // construtor de cópia (deep copy)
	array_bag &operator=(const array_bag &other); // atribuição (deep copy)
	~array_bag();                             // destrutor (liberta "data")

	// --- Implementação dos métodos puramente virtuais de "bag" ---
	void insert(int);          // insere um elemento (realoca o array)
	void insert(int *, int);   // insere vários elementos de uma vez
	void print() const;        // imprime todos os elementos, separados por espaço
	void clear();               // liberta "data" e repõe size a 0
};
