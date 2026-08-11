// Header guard: evita que este ficheiro seja incluído mais do que
// uma vez na mesma unidade de compilação (o que causaria erro de
// "redefinição" da classe).
#ifndef BIGINT
#define BIGINT

#include <sstream>   // std::stringstream, usado para converter números <-> string
#include <iostream>  // std::ostream, usado no operator<< para imprimir o bigint
#include <string>    // std::string, usado para guardar o número internamente
#include <cstdlib>

// ============================================================
// CLASSE bigint
// ============================================================
// Representa um número inteiro sem sinal (unsigned) de precisão
// arbitrária (ou seja, sem limite de tamanho, ao contrário de int
// ou unsigned int que têm um valor máximo fixo).
//
// A ideia central é guardar o número como uma std::string (ex: "12345"),
// em vez de num tipo numérico nativo, para não haver limite de tamanho.
class bigint
{
	private:
		// Representação interna do número, em base 10, sem zeros
		// à esquerda (ex: "0", "42", "1337").
		std::string str;
		//std::string result;

	public:
		// ------------------------------------------------------
		// Construtores
		// ------------------------------------------------------
		bigint();                        // construtor por defeito -> representa 0
		bigint(unsigned int num);        // construtor a partir de um unsigned int
		bigint(const bigint& source);    // construtor de cópia

		// Devolve a representação em string do número (só leitura).
		std::string getStr()const;

		// Operador de atribuição (a = b).
		bigint& operator=(const bigint& source);

		// ------------------------------------------------------
		// Soma
		// ------------------------------------------------------
		bigint operator+(const bigint& other)const;  // a + b -> devolve novo bigint
		bigint& operator+=(const bigint& other);      // a += b -> modifica o próprio objeto

		// ------------------------------------------------------
		// Incrementos
		// ------------------------------------------------------
		bigint& operator++();     // pré-incremento:  ++x  (incrementa e devolve referência)
		bigint operator++(int);   // pós-incremento:  x++  (devolve valor antigo, depois incrementa)

		// ------------------------------------------------------
		// "Digitshift" com um unsigned int
		// ------------------------------------------------------
		// Tal como o bitshift (<<, >>) desloca bits, aqui deslocamos
		// dígitos em base 10:
		//   a << n  equivale a multiplicar "a" por 10^n
		//   a >> n  equivale a dividir "a" por 10^n (parte inteira)
		bigint operator<<(unsigned int n)const;
		bigint operator>>(unsigned int n)const;
		bigint& operator<<=(unsigned int n);
		bigint& operator>>=(unsigned int n);

		// ------------------------------------------------------
		// "Digitshift" com outro bigint como argumento
		// ------------------------------------------------------
		// Permitem escrever, por exemplo, "a << b" quando "b" também
		// é um bigint (em vez de um unsigned int). Internamente,
		// "b" é convertido para unsigned int antes de aplicar o shift.
		bigint operator<<(const bigint& other)const;
		bigint operator>>(const bigint& other)const;
		bigint& operator<<=(const bigint& other);
		bigint& operator>>=(const bigint& other);

		// ------------------------------------------------------
		// Operadores de comparação: ==, !=, <, >, <=, >=
		// ------------------------------------------------------
		// Permitem comparar dois bigint como se fossem tipos
		// numéricos nativos (a == b, a < b, etc.).
		bool operator==(const bigint& other) const;
		bool operator!=(const bigint& other) const;
		bool operator<(const bigint& other) const;
		bool operator>(const bigint& other) const;
		bool operator<=(const bigint& other) const;
		bool operator>=(const bigint& other) const;

		// ~bigint();
		// (destrutor não é necessário aqui, pois a única "recurso"
		// da classe é uma std::string, que já gere a sua própria
		// memória automaticamente)

};

// Operador de inserção em stream (função não-membro), permite fazer
// "std::cout << meu_bigint;" tal como faríamos com um int normal.
std::ostream& operator<<(std::ostream& output, const bigint& obj);

#endif
