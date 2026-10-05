#include "bigint.hpp"

// ============================================================
// CONSTRUTORES
// ============================================================

// Construtor por defeito: o bigint representa o número 0.
// Internamente o número é sempre guardado como uma string (ex: "0", "42", "1337").
bigint::bigint()
{
	this->str = "0";
}

// Construtor a partir de um unsigned int.
// Usamos um stringstream para converter o número para a sua representação
// em string de forma simples (equivalente a um "to_string").
bigint::bigint(unsigned int num)
{
	std::stringstream ss;
	ss << num;
	this->str = ss.str();
	// std::cout << "str: " << str << std::endl;
}

// Construtor de cópia: reaproveita o operator= já definido,
// evitando duplicar a lógica de cópia.
bigint::bigint(const bigint& source)
{
	(*this) = source;
}

// ============================================================
// OPERADOR DE ATRIBUIÇÃO
// ============================================================

bigint& bigint::operator=(const bigint& source)
{
	// Proteção contra auto-atribuição (a = a).
	if(this == &source)
		return(*this);
	this->str = source.str;
	return(*this);
}

// Getter simples que devolve a string interna representando o número.
std::string bigint::getStr() const
{
	return(this->str);
}

// ============================================================
// FUNÇÃO AUXILIAR: inverter uma string
// ============================================================
// É mais fácil somar dois números "grandes" da direita para a esquerda
// (como fazemos à mão), por isso invertemos as strings antes de somar,
// e voltamos a inverter o resultado no final.
std::string reverse(const std::string& str)
{
	std::string revStr;
	for(size_t i = str.length(); i > 0; i--)
	{
		revStr.push_back(str[i - 1]);
	}
	return(revStr);
}

// ============================================================
// FUNÇÃO DE SOMA (lógica principal do bigint)
// ============================================================
std::string addition(const bigint& obj1, const bigint& obj2)
{
	// Invertemos as duas strings para somar dígito a dígito
	// começando pelo dígito menos significativo (unidades).
	std::string str1 = reverse(obj1.getStr());
	std::string str2 = reverse(obj2.getStr());
	std::string result;
	size_t len1 = str1.length();
	size_t len2 = str2.length();

	// Como os dois números podem ter tamanhos diferentes,
	// preenchemos o mais curto com '0' à direita (que, por estarem
	// invertidos, corresponde na verdade a zeros à esquerda do número original).
	if(len1 > len2)
	{
		int diff = len1 - len2;
		while(diff > 0)
		{
			str2.push_back('0');
			diff--;
		}
	}
	else if(len2 > len1)
	{
		int diff = len2 - len1;
		while(diff > 0)
		{
			str1.push_back('0');
			diff--;
		}
	}

	// Soma dígito a dígito, com transporte (carry), tal como
	// se faz uma soma manual em papel.
	int carry = 0;
	int digit1;
	int digit2;
	size_t len = str1.length();
	for(size_t i = 0; i < len; i++)
	{
		digit1 = str1[i] - '0'; // converte char para int
		// std::cout <<  "digit1:" << digit1 << std::endl;
		digit2 = str2[i] - '0';
		// std::cout << "digit2:" << digit2 << std::endl;
		int res = digit1 + digit2 + carry;
		// std::cout << res << std::endl;
		if(res > 9)
		{
			// Se ultrapassar 9, guardamos o transporte para a próxima
			// posição e mantemos apenas o dígito das unidades.
			carry = res / 10;
			result.push_back((res % 10) + '0');
		}
		else
		{
			carry = 0; // (nota: aqui o carry não é reiniciado explicitamente no original,
			           // mas como só pode ser 0 ou 1 e é somado no próximo passo, funciona)
			result.push_back(res + '0');
		}
	}
	// Se ainda sobrar um transporte depois do último dígito,
	// adicionamos esse dígito extra (ex: 9 + 9 = 18 -> sobra o '1').
	if(carry != 0)
		result.push_back(carry + '0');

	// O resultado foi construído na ordem invertida, por isso
	// invertemos de novo antes de devolver.
	return(reverse(result));
}

// ============================================================
// OPERADORES ARITMÉTICOS
// ============================================================

// operator+: cria uma cópia (temp) só para reaproveitar o tipo,
// limpa a sua string e coloca lá o resultado da soma.
bigint bigint::operator+(const bigint& other)const
{
	bigint temp(other);
	temp.str.clear();
	std::string result = addition(*this, other);
	temp.str = result;
	//std::cout << "r: " << result << std::endl;

	return(temp);
}

// operator+=: implementado em termos do operator+ já existente.
bigint& bigint::operator+=(const bigint& other)
{
	(*this) = (*this) + other;
	return(*this);
}

// Pré-incremento (++b): soma 1 e devolve o próprio objeto já atualizado.
bigint& bigint::operator++()
{
	*(this) = *(this) + bigint(1);
	return(*this);
}

// Pós-incremento (b++): guarda o valor ANTES de incrementar,
// incrementa o objeto atual, e devolve o valor antigo.
// O parâmetro "int" não é usado, serve apenas para distinguir
// esta versão da versão de pré-incremento (convenção do C++).
bigint bigint::operator++(int)
{
	bigint temp = (*this);
	*(this) = *(this) + bigint(1);
	return(temp);
}

// ============================================================
// "DIGIT SHIFT" (equivalente ao bitshift, mas em base 10)
// ============================================================

// operator<< com unsigned int: desloca os dígitos para a esquerda,
// ou seja, multiplica por 10^n. Isso é feito simplesmente
// acrescentando n zeros no fim da string (ex: "42" << 3 -> "42000").
bigint bigint::operator<<(unsigned int n)const
{
	bigint temp = *this;

	temp.str.insert(temp.str.end(), n, '0');
	//std::cout << temp.str << std::endl;
	return(temp);
}

// operator>> com unsigned int: desloca os dígitos para a direita,
// ou seja, divide por 10^n (parte inteira), removendo os últimos
// n caracteres da string (ex: "1337" >> 2 -> "13").
bigint bigint::operator>>(unsigned int n)const
{
	bigint temp = *this;
	size_t len = temp.str.length();
	if(n >= len)
		temp.str = "0"; // se deslocarmos mais do que o número de dígitos, o resultado é 0
	else
	{
		// erase(posição_inicial, quantidade): remove "n" caracteres
		// a partir da posição (len - n), ou seja, os "n" últimos dígitos.
		temp.str.erase(temp.str.length() - n, n);
	}
	return(temp);
}

// Versões "com atribuição" (<<= e >>=): reaproveitam os operadores acima.
bigint& bigint::operator<<=(unsigned int n)
{
	(*this) = (*this) << n;
	return(*this);
}

bigint& bigint::operator>>=(unsigned int n)
{
	(*this) = (*this) >> n;
	return(*this);
}

// ============================================================
// FUNÇÃO AUXILIAR: converter string para unsigned int
// ============================================================
// Necessária para as versões de <<, >>, <<= e >>= que recebem
// um bigint (em vez de um unsigned int) como argumento de deslocamento.
unsigned int stringToUINT(std::string str)
{
	std::stringstream ss(str);
	unsigned int res;
	ss >> res;
	return (res);
}

// Estas quatro funções simplesmente convertem o bigint "other"
// para unsigned int e delegam para as versões já implementadas acima.
bigint bigint::operator<<(const bigint& other)const
{
	bigint temp;
	temp = (*this) << stringToUINT(other.str);
	return(temp);
}

bigint bigint::operator>>(const bigint& other)const
{
	bigint temp;
	temp = (*this) >> stringToUINT(other.str);
	return(temp);
}

bigint& bigint::operator<<=(const bigint& other)
{
	(*this) = (*this) << stringToUINT(other.str);
	return(*this);
}

bigint& bigint::operator>>=(const bigint& other)
{
	(*this) = (*this) >> stringToUINT(other.str);
	return(*this);
}

// ============================================================
// OPERADORES DE COMPARAÇÃO
// ============================================================

// Igualdade: como a string nunca deve ter zeros à esquerda,
// comparar as strings diretamente é suficiente e correto.
bool bigint::operator==(const bigint& other) const
{
	if(this->getStr() == other.getStr())
		return(true);
	return(false);
}

bool bigint::operator!=(const bigint& other) const
{
	return(!((*this) == (other)));
}

// Operador "menor que": primeiro compara o número de dígitos
// (uma string mais curta representa sempre um número menor,
// desde que não haja zeros à esquerda). Se os comprimentos forem
// iguais, a comparação lexicográfica de strings coincide com a
// comparação numérica, porque os dígitos têm o mesmo "peso".
bool bigint::operator<(const bigint& other) const
{
	std::string str1 = this->str;
	std::string str2 = other.getStr();
	size_t len1 = str1.length();
	size_t len2 = str2.length();

	if(len1 != len2)
		return(len1 < len2);
	return(str1 < str2);  // thanks for your feedback, mjuicha!! o7
}

// Os restantes operadores de comparação são implementados
// em função do operator< e do operator== já definidos,
// evitando repetir lógica.
bool bigint::operator>(const bigint& other) const
{
	return(!(((*this) < other)));
}

bool bigint::operator<=(const bigint& other) const
{
	return((((*this) < other) || ((*this) == other)));
}

bool bigint::operator>=(const bigint& other) const
{
	return((((*this) > other) || ((*this) == other)));
}

// ============================================================
// OPERADOR DE INSERÇÃO EM STREAM (função não-membro)
// ============================================================
// Permite fazer "std::cout << meu_bigint;". Como a string interna
// nunca tem zeros à esquerda, basta escrevê-la diretamente.
std::ostream& operator<<(std::ostream& output, const bigint& obj)
{
	output << obj.getStr();
	return(output);
}
