#include "vect2.hpp"

int main()
{
	// ------------------------------------------------------------------
	// Construção de vetores
	// ------------------------------------------------------------------
	vect2 v1;             // Construtor por omissão -> v1 = (0, 0)
	vect2 v2(1, 2);        // Construtor com parâmetros -> v2 = (1, 2)
	const vect2 v3(v2);    // Construtor de cópia -> v3 = (1, 2), e é const
	                        // (não pode ser modificado depois disto)
	vect2 v4 = v2;          // Também chama o construtor de cópia
	                        // (v4 é criado a partir de v2, não é uma atribuição)

	// ------------------------------------------------------------------
	// Teste ao operator<< e ao operator[] const
	// ------------------------------------------------------------------
	std::cout << "v1: " << v1 << std::endl;
	// Usa o operator<< -> deve imprimir: v1: {0, 0}

	std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl;
	// Constrói o mesmo output manualmente com operator[]
	// Serve para confirmar que operator<< e operator[] são consistentes
	// -> deve imprimir: v1: {0, 0}  (igual à linha anterior)

	std::cout << "v2: " << v2 << std::endl;  // v2: {1, 2}
	std::cout << "v3: " << v3 << std::endl;  // v3: {1, 2}  (v3 é const, mas
	                                          // ler com operator[] const funciona)
	std::cout << "v4: " << v4 << std::endl;  // v4: {1, 2}

	// ------------------------------------------------------------------
	// Testes de incremento / decremento (pré e pós)
	// v4 começa em (1, 2)
	// ------------------------------------------------------------------
	std::cout << v4++ << std::endl; // pós-incremento: imprime (1, 2) ANTES
	                                 // de incrementar; DEPOIS desta linha v4 = (2, 3)
	std::cout << ++v4 << std::endl; // pré-incremento: incrementa PRIMEIRO,
	                                 // depois imprime; v4 passa a (3, 4) e imprime (3, 4)
	std::cout << v4-- << std::endl; // pós-decremento: imprime (3, 4) ANTES
	                                 // de decrementar; DEPOIS desta linha v4 = (2, 3)
	std::cout << --v4 << std::endl; // pré-decremento: decrementa PRIMEIRO,
	                                 // depois imprime; v4 passa a (1, 2) e imprime (1, 2)

	// ------------------------------------------------------------------
	// Testes de operações aritméticas compostas e entre vetores
	// (os comentários // à direita mostram o valor esperado depois de
	// cada linha ser executada)
	// ------------------------------------------------------------------

	v2 += v3;
	// v2 = (1,2) + (1,2) = (2, 4)

	v1 -= v2;
	// v1 = (0,0) - (2,4) = (-2, -4)

	v2 = v3 + v3 * 2;
	// v3 * 2 = (1,2)*2 = (2,4)
	// v3 + (2,4) = (1,2)+(2,4) = (3, 6)
	// v2 = (3, 6)

	v2 = 3 * v2;
	// Usa o operator* não-membro (int * vect2)
	// 3 * (3,6) = (9, 18)
	// v2 = (9, 18)

	v2 += v2 += v3;
	// Avaliação da direita para a esquerda:
	// 1) v2 += v3  ->  v2 = (9,18) + (1,2) = (10, 20)   (e devolve v2 por referência)
	// 2) v2 += (resultado anterior, ou seja, o próprio v2 já atualizado)
	//    v2 += v2  ->  v2 = (10,20) + (10,20) = (20, 40)
	// v2 = (20, 40)

	v1 *= 42;
	// v1 era (-2, -4)
	// v1 = (-2*42, -4*42) = (-84, -168)

	v1 = v1 - v1 + v1;
	// v1 - v1 = (0, 0)
	// (0,0) + v1 = v1 (sem alteração)
	// v1 continua (-84, -168)
	// (serve para testar que operator+ e operator- não corrompem os operandos)

	// ------------------------------------------------------------------
	// Impressão dos resultados finais
	// ------------------------------------------------------------------
	std::cout << "v1: " << v1 << std::endl;   // v1: {-84, -168}
	std::cout << "v2: " << v2 << std::endl;   // v2: {20, 40}
	std::cout << "-v2: " << -v2 << std::endl; // operator- unário -> {-20, -40}
	                                           // (não altera v2, apenas devolve um novo vetor)

	// ------------------------------------------------------------------
	// Testes ao operator[] não-const (leitura e escrita)
	// ------------------------------------------------------------------
	std::cout << "v1[1]: " << v1[1] << std::endl;  // v1[1] = -168
	v1[1] = 12;                                     // modifica diretamente a
	                                                 // componente y de v1 através do []
	std::cout << "v1[1]: " << v1[1] << std::endl;  // v1[1] = 12 (confirma a alteração)

	std::cout << "v3[1]: " << v3[1] << std::endl;  // v3[1] = 2
	// v3 é const, por isso aqui é obrigatoriamente chamada a versão
	// operator[] const (a que devolve int, não int&)

	// ------------------------------------------------------------------
	// Testes aos operadores de comparação
	// v1 neste ponto = (-84, 12) ; v3 = (1, 2)
	// ------------------------------------------------------------------
	std::cout << "v1 == v3: " << (v1 == v3) << std::endl; // false (0) -> componentes diferentes
	std::cout << "v1 == v1: " << (v1 == v1) << std::endl; // true  (1) -> vetor comparado consigo mesmo
	std::cout << "v1 != v3: " << (v1 != v3) << std::endl; // true  (1) -> são diferentes
	std::cout << "v1 != v1: " << (v1 != v1) << std::endl; // false (0) -> são iguais

	return (0);
}
