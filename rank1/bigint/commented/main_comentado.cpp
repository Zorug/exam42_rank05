#include "bigint.hpp"

int main(void)
{
	// ------------------------------------------------------
	// Criação de vários bigint, testando os 3 construtores:
	// ------------------------------------------------------
	const bigint a(42);   // construtor a partir de unsigned int -> a = "42"
	bigint b(21);         // construtor a partir de unsigned int -> b = "21"
	bigint c;              // construtor por defeito             -> c = "0"
	bigint d(1337);        // construtor a partir de unsigned int -> d = "1337"
	bigint e(d);            // construtor de cópia                -> e = "1337" (cópia de d)

	// ------------------------------------------------------
	// base test: só imprime os valores para confirmar que os
	// construtores e o operator<< (impressão) funcionam.
	// ------------------------------------------------------
	std::cout << "a = " << a << std::endl; // a = 42
	std::cout << "b = " << b << std::endl; // b = 21
	std::cout << "c = " << c << std::endl; // c = 0
	std::cout << "d = " << d << std::endl; // d = 1337
	std::cout << "e = " << e << std::endl; // e = 1337

	// ------------------------------------------------------
	// Testa a soma (operator+), incluindo somar com o valor 0.
	// ------------------------------------------------------
	std::cout << "a + b = " << a + b << std::endl; // 42 + 21 = 63
	std::cout << "a + c = " << a + c << std::endl; // 42 + 0  = 42 (soma com c, que vale 0)

	// c += a  -> modifica o próprio "c", que passa a valer 42.
	std::cout << "(c += a) = " << (c += a) << std::endl; // c = 0 + 42 = 42

	// ------------------------------------------------------
	// Testa pré-incremento (++b) e pós-incremento (b++).
	// ------------------------------------------------------
	std::cout << "b = " << b << std::endl; // b ainda é 21 aqui

	// ++b: incrementa PRIMEIRO, depois imprime o novo valor.
	std::cout << "++b = " << ++b << std::endl; // b passa a 22, imprime 22

	// b++: imprime o valor ANTIGO (22), só DEPOIS incrementa
	// b internamente para 23.
	std::cout << "b++ = " << b++ << std::endl; // imprime 22, mas b fica 23

	// ------------------------------------------------------
	// Testa o "digitshift" combinado com soma.
	// Neste ponto b vale 23 (por causa do b++ acima).
	// b << 10 desloca "23" acrescentando 10 zeros -> 230000000000
	// depois soma-se 42 ao resultado.
	// ------------------------------------------------------
	// b = 23, b << 10 -> 23000000000 + 42 = 23000000042
	std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;

	// ------------------------------------------------------
	// Testa <<= e >>= (versões que modificam o próprio objeto),
	// usando tanto unsigned int como um bigint como argumento.
	// ------------------------------------------------------

	// d <<= 4 : d passa a ser "1337" com 4 zeros a mais no fim
	// (equivale a multiplicar d por 10^4).
	std::cout << "(d <<= 4) = " << (d <<= 4) << ", d: " << d << std::endl;

	// d >>= (const bigint)2 : aqui o argumento é um bigint, não um
	// unsigned int, por isso é usada a versão de operator>>=(const bigint&),
	// que converte "2" para unsigned int internamente antes de aplicar
	// o shift (remove os últimos 2 dígitos, equivale a dividir por 100).
	std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << ", d: " << d << std::endl;

	// ------------------------------------------------------
	// Confirma que "a" não foi alterado por nenhuma das operações
	// acima (é const, e além disso nunca foi passado por referência
	// não-const a nenhuma função que o modificasse).
	// ------------------------------------------------------
	std::cout << "a = " << a << std::endl; // a = 42
	std::cout << "d = " << d << std::endl; // d = 5348

	// ------------------------------------------------------
	// Testa todos os operadores de comparação entre d e a.
	// ------------------------------------------------------
	std::cout << "(d < a) = " << (d < a) << std::endl;   // (d < a) = 0
	std::cout << "(d > a) = " << (d > a) << std::endl;   // (d > a) = 1
	std::cout << "(d == d) = " << (d == d) << std::endl; // (d == d) = 1 (comparação com ele próprio)
	std::cout << "(d != a) = " << (d != a) << std::endl; // (d != a) = 1
	std::cout << "(d <= a) = " << (d <= a) << std::endl; // (d <= a) = 0
	std::cout << "(d >= a) = " << (d >= a) << std::endl; // (d >= a) = 1

	// ============================================================
	// extra: testes adicionais, feitos pelo autor do main para
	// verificar casos além dos pedidos no enunciado original,
	// nomeadamente shift usando um bigint como argumento (em vez
	// de um unsigned int) e comparação depois de vários shifts.
	// ============================================================
	bigint x(12345678); // x = "12345678"
	bigint y(5);          // y = "5"

	// x << y : aqui "y" é um bigint, por isso usa-se
	// operator<<(const bigint&), que converte y para 5 (unsigned int)
	// e desloca x 5 casas para a esquerda. Nota: isto NÃO modifica x
	// nem y, porque operator<< (sem o "=") devolve um NOVO bigint.
	std::cout << "(x << y) = " << (x << y) << ", x: " << x << ", y: " << y << std::endl;

	// x >>= y : esta versão COM o "=" modifica x diretamente,
	// removendo os últimos 5 (valor de y) dígitos de x.
	std::cout << "(x >>= y) = " << (x >>= y) << ", x: " << x << ", y: " << y << std::endl;

	// Compara x (já modificado acima) com y.
	std::cout << "(x >= y) = " << (x >= y) << ", x: " << x << ", y: " << y << std::endl;

	// Aplica shift com atribuição a ambos, em simultâneo na mesma
	// linha, só para testar várias chamadas encadeadas na mesma
	// instrução de output.
	std::cout << "x= " << (x <<= 5) << ", y= " << (y <<= 12) << std::endl;

	// Compara de novo, depois destes novos shifts, para confirmar
	// que a comparação continua correta mesmo com números bem
	// maiores (mais dígitos) do que no início.
	std::cout << "(x >= y) = " << (x >= y) << ", x: " << x << ", y: " << y << std::endl;

	return (0);
}
