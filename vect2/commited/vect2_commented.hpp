#ifndef VECT2_HPP
#define VECT2_HPP
// Include guards: impedem que este ficheiro seja incluído mais do que
// uma vez na mesma unidade de compilação (evita erros de "redefinição"
// se vect2.hpp for incluído indiretamente várias vezes).

#include <iostream>
// Necessário para std::ostream e std::cout, usados na declaração
// do operator<<.

class vect2
{
	private:
		// ------------------------------------------------------------
		// Atributos (dados-membro) do vetor: as duas componentes.
		// Privados -> só podem ser acedidos de dentro da própria classe
		// (o acesso de fora é feito através do operator[]).
		// ------------------------------------------------------------
		int x;
		int y;

	public:
		// ------------------------------------------------------------
		// Construtores / atribuição / destrutor
		// (os chamados "Orthodox Canonical Form" / "Big Three" do C++)
		// ------------------------------------------------------------
		vect2();                          // Construtor por omissão -> (0, 0)
		vect2(int num1, int num2);        // Construtor com parâmetros
		vect2(const vect2& source);       // Construtor de cópia
		vect2& operator=(const vect2& source); // Operador de atribuição

		// ------------------------------------------------------------
		// Acesso às componentes via []
		// Há DUAS versões (overload) consoante o objeto seja const ou não:
		// ------------------------------------------------------------
		int operator[](int index) const; // Versão para objetos const:
		                                  // devolve o VALOR (só leitura),
		                                  // ex: v3[0] com v3 const
		int& operator[](int index);      // Versão para objetos não-const:
		                                  // devolve uma REFERÊNCIA, o que
		                                  // permite escrever v1[1] = 12;
		                                  // (comentário original "NON-COST"
		                                  // = NON-CONST, com gralha)

		// ------------------------------------------------------------
		// Operadores aritméticos "simples" (devolvem um novo vect2,
		// não alteram o objeto atual)
		// ------------------------------------------------------------
		vect2 operator-() const;    // Negação unária: -v
		vect2 operator*(int num) const; // Multiplicação por escalar: v * 2

		// ------------------------------------------------------------
		// Operadores compostos (alteram o próprio objeto e devolvem
		// uma referência a si mesmo, para permitir encadeamento,
		// ex: a += b += c;)
		// ------------------------------------------------------------
		vect2& operator*=(int num);          // v *= 2
		vect2& operator+=(const vect2& obj); // v1 += v2
		vect2& operator-=(const vect2& obj); // v1 -= v2
		vect2& operator*=(const vect2& obj); // v1 *= v2 (multiplicação
		                                      // componente-a-componente,
		                                      // extra, não pedida no enunciado)

		// ------------------------------------------------------------
		// Operadores aritméticos entre dois vect2 (devolvem um novo vect2)
		// ------------------------------------------------------------
		vect2 operator+(const vect2& obj) const; // v1 + v2
		vect2 operator-(const vect2& obj) const; // v1 - v2
		vect2 operator*(const vect2& obj) const; // v1 * v2 (componente-a-
		                                          // componente, extra)

		// ------------------------------------------------------------
		// Incremento / decremento
		// A versão sem parâmetro é o PRÉ (++v); a versão com um "int"
		// fictício (não usado) é o PÓS (v++), por convenção do C++,
		// que serve apenas para o compilador distinguir as duas.
		// ------------------------------------------------------------
		vect2& operator++();     // ++v  -> incrementa e devolve *this
		vect2 operator++(int);   // v++  -> devolve cópia do valor antigo
		vect2& operator--();     // --v
		vect2 operator--(int);   // v--

		// ------------------------------------------------------------
		// Operadores de comparação
		// ------------------------------------------------------------
		bool operator==(const vect2& obj) const; // v1 == v2
		bool operator!=(const vect2& obj) const; // v1 != v2

		// ------------------------------------------------------------
		// Destrutor
		// Não há alocação dinâmica de memória nesta classe, por isso
		// não faz nada de especial, mas é boa prática declará-lo.
		// ------------------------------------------------------------
		~vect2();
};

// ----------------------------------------------------------------------
// Funções NÃO-membro (ficam fora da classe, ao nível global)
// ----------------------------------------------------------------------

// Multiplicação com o escalar do lado ESQUERDO: 3 * v2
// Não pode ser um método da classe vect2 porque o primeiro operando
// é um "int" e não um "vect2" (não se pode adicionar métodos ao tipo int).
vect2 operator*(int num, const vect2& obj);

// Operador de output (impressão): std::cout << v
// Também tem de ser não-membro porque o primeiro operando é um
// std::ostream (o std::cout) e não um vect2.
std::ostream& operator<<(std::ostream& os,const vect2& obj);

#endif
