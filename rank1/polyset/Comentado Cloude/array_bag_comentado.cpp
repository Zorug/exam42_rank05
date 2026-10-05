#include "array_bag.hpp"
#include <iostream>

// Construtor por defeito.
// Bag vazio: nenhum elemento alocado, size a 0.
array_bag::array_bag() {
  size = 0;
  data = nullptr;
}

// Construtor de cópia (deep copy).
// Não basta copiar o ponteiro "data" (isso seria uma "shallow copy" e
// os dois objetos apontariam para a MESMA memória — um "delete[]" no
// destrutor de um deixaria o outro com um ponteiro inválido).
// Por isso alocamos um array NOVO do mesmo tamanho e copiamos
// elemento a elemento.
array_bag::array_bag(const array_bag &src) {
  size = src.size;
  data = new int[size];
  for (int i = 0; i < size; i++) {
	data[i] = src.data[i];
  }
}

// Operador de atribuição (a = b).
// Mesma lógica de deep copy do construtor de cópia, mas com dois
// cuidados extra específicos da atribuição:
array_bag &array_bag::operator=(const array_bag &src) {
	// 1) Proteção contra auto-atribuição (a = a). Sem isto, o passo
	//    seguinte apagaria "data" antes de o tentar copiar de si próprio,
	//    perdendo os dados.
	if (this != &src) {
		// 2) Liberta a memória ANTIGA deste objeto antes de alocar a nova
		//    — senão teríamos um memory leak (o array antigo ficaria
		//    "perdido" sem nunca ser libertado).
		if (data != nullptr) {
			delete[] data;
			data = nullptr;
		}
		size = src.size;
		data = new int[size];
		for (int i = 0; i < size; i++) {
			data[i] = src.data[i];
		}
	}
	return *this;
}

// Destrutor.
// Liberta a memória alocada dinamicamente, evitando memory leaks
// quando o objeto deixa de existir.
array_bag::~array_bag() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
}

// Insere UM elemento.
// Como um array normal em C++ tem tamanho fixo, para "crescer" temos de:
//   1. alocar um array novo com espaço para mais um elemento (size + 1)
//   2. copiar todos os elementos antigos para o array novo
//   3. colocar o novo elemento na última posição
//   4. libertar o array antigo e substituir o ponteiro
// Nota de performance: isto é O(n) por cada inserção (realoca e copia
// tudo de cada vez), o que torna inserções sucessivas O(n²) no total.
// Não é o mais eficiente, mas é simples e correto.
void array_bag::insert(int item) {
	int *new_data = new int[size + 1];
	for (int i = 0; i < size; i++) {
		new_data[i] = data[i];
	}
	new_data[size] = item;
	if (data != nullptr) {
		delete[] data;
	}
	data = new_data;
	size++;
}

// Insere VÁRIOS elementos de uma vez (array "items" com "count" valores).
// Mesma lógica do insert(int), mas alocando espaço para todos de uma vez
// só (mais eficiente do que chamar insert(int) "count" vezes seguidas,
// já que evita realocar a cada elemento individual).
void array_bag::insert(int *items, int count) {
	int *new_data = new int[size + count];
	for (int i = 0; i < size; i++) {
		new_data[i] = data[i];
	}
	for (int i = 0; i < count; i++) {
		new_data[size + i] = items[i];
	}
	if (data != nullptr) {
		delete[] data;
	}
	data = new_data;
	size += count;
}

// Imprime todos os elementos, separados por espaço, seguidos de newline.
// const: só lê o estado, não o modifica.
void array_bag::print() const {
	for (int i = 0; i < size; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}

// Esvazia o bag: liberta a memória e repõe size a 0, deixando o objeto
// num estado "vazio" mas ainda válido e reutilizável (mesmo estado de
// logo após o construtor por defeito).
void array_bag::clear() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
	size = 0;
}
