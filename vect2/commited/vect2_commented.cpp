#include "vect2.hpp"

// ------------------------------------------------------------------
// Construtor por omissão (default constructor)
// Chamado quando se escreve: vect2 v1;
// Inicializa as duas componentes a 0.
// ------------------------------------------------------------------
vect2::vect2()
{
	this->x = 0;
	this->y = 0;
}

// ------------------------------------------------------------------
// Construtor com parâmetros
// Chamado quando se escreve: vect2 v2(1, 2);
// Inicializa x e y com os valores passados como argumento.
// ------------------------------------------------------------------
vect2::vect2(int num1, int num2)
{
	this->x = num1;
	this->y = num2;
}

// ------------------------------------------------------------------
// Construtor de cópia (copy constructor)
// Chamado quando se cria um novo objeto a partir de outro já existente:
// const vect2 v3(v2);
// Aqui reaproveita-se o operator= para copiar x e y.
// ------------------------------------------------------------------
vect2::vect2(const vect2& source)
{
	*this = source;
}

// ------------------------------------------------------------------
// Operador de atribuição (operator=)
// Chamado quando se atribui um vect2 já existente a outro:
// vect2 v4 = v2;   (na prática, aqui é o copy constructor que é chamado,
//                    mas operator= é usado em atribuições como v1 = v2;)
// Copia x e y de "source" para o objeto atual.
// A verificação (this != &source) protege contra auto-atribuição (v = v).
// ------------------------------------------------------------------
vect2& vect2::operator=(const vect2& source)
{
	if(this != &source)
	{
		this->x = source.x;
		this->y = source.y;
	}
	return(*this);
}

// ------------------------------------------------------------------
// operator[] const (versão só de leitura)
// Usado quando o objeto é const, ex: v3[0]
// Devolve o valor da componente (não uma referência), por isso não
// pode ser usado para modificar o vetor.
// index == 0 -> x ; qualquer outro valor -> y (sem verificação de limites)
// ------------------------------------------------------------------
int vect2::operator[](int index) const
{
	if(index == 0)
		return(this->x);
	return(this->y);
}

// ------------------------------------------------------------------
// operator[] não-const (versão de leitura E escrita)
// Usado em objetos não-const, ex: v1[1] = 12;
// Devolve uma REFERÊNCIA (int&) para a componente, o que permite
// modificá-la diretamente através do [].
// ------------------------------------------------------------------
int& vect2::operator[](int index)
{
	if(index == 0)
		return(this->x);
	return(this->y);
}

// ------------------------------------------------------------------
// Operador unário "-" (negação)
// Chamado em: -v2
// Devolve um novo vetor com as componentes com o sinal trocado.
// Não modifica o vetor original.
// ------------------------------------------------------------------
vect2 vect2::operator-() const
{
	vect2 temp = *this;
	temp[0] = -temp[0];
	temp[1] = -temp[1];
	return(temp);
}

// ------------------------------------------------------------------
// Multiplicação por escalar: vect2 * int
// Chamado em: v * 2
// Devolve um NOVO vetor (não altera o original), com cada componente
// multiplicada pelo número.
// ------------------------------------------------------------------
vect2 vect2::operator*(int num) const
{
	vect2 temp;

	temp.x = this->x * num;
	temp.y = this->y * num;
	return(temp);
}

// ------------------------------------------------------------------
// Multiplicação composta por escalar: vect2 *= int
// Chamado em: v1 *= 42;
// Modifica o próprio objeto (multiplica x e y por num) e devolve
// uma referência a si mesmo, para permitir encadeamento (a *= b *= c).
// ------------------------------------------------------------------
vect2& vect2::operator*=(int num)
{
	this->x *= num;
	this->y *= num;
	return(*this);
}

// ------------------------------------------------------------------
// Soma composta: vect2 += vect2
// Chamado em: v2 += v3;
// Soma componente a componente ao próprio objeto e devolve-se a si
// mesmo (por referência), permitindo encadear: v2 += v2 += v3;
// ------------------------------------------------------------------
vect2& vect2::operator+=(const vect2& obj)
{
	this->x += obj.x;
	this->y += obj.y;
	return(*this);
}

// ------------------------------------------------------------------
// Subtração composta: vect2 -= vect2
// Chamado em: v1 -= v2;
// Subtrai componente a componente ao próprio objeto.
// ------------------------------------------------------------------
vect2& vect2::operator-=(const vect2& obj)
{
	this->x -= obj.x;
	this->y -= obj.y;
	return(*this);
}

// ------------------------------------------------------------------
// Multiplicação composta entre dois vetores: vect2 *= vect2
// (Não é pedida pelo enunciado, mas foi adicionada como extra)
// Multiplica componente a componente (x*=obj.x, y*=obj.y).
// ------------------------------------------------------------------
vect2& vect2::operator*=(const vect2& obj)
{
	this->x *= obj.x;
	this->y *= obj.y;
	return(*this);
}

// ------------------------------------------------------------------
// Soma entre dois vetores: vect2 + vect2
// Chamado em: v2 = v3 + v3 * 2;
// Cria uma cópia do objeto atual (temp), soma-lhe "obj" e devolve
// essa cópia. Não modifica nem *this nem obj.
// ------------------------------------------------------------------
vect2 vect2::operator+(const vect2& obj) const
{
	vect2 temp = *this;

	temp.x += obj.x;
	temp.y += obj.y;
	return(temp);
}

// ------------------------------------------------------------------
// Subtração entre dois vetores: vect2 - vect2
// Igual à soma, mas subtraindo componente a componente.
// ------------------------------------------------------------------
vect2 vect2::operator-(const vect2& obj) const
{
	vect2 temp = *this;
	temp.x -= obj.x;
	temp.y -= obj.y;
	return(temp);
}

// ------------------------------------------------------------------
// Multiplicação entre dois vetores: vect2 * vect2
// (extra, não pedida no enunciado) Multiplica componente a componente.
// ------------------------------------------------------------------
vect2 vect2::operator*(const vect2& obj) const
{
	vect2 temp = *this;
	temp.x *= obj.x;
	temp.y *= obj.y;
	return(temp);
}

// ------------------------------------------------------------------
// Pré-incremento: ++v
// Incrementa x e y em 1 diretamente no objeto e devolve uma
// referência ao próprio objeto JÁ incrementado.
// Por isso: std::cout << ++v4 << std::endl; mostra o valor DEPOIS
// de incrementar.
// ------------------------------------------------------------------
vect2& vect2::operator++()
{
	this->x += 1;
	this->y += 1;
	return(*this);
}

// ------------------------------------------------------------------
// Pós-incremento: v++
// O parâmetro "int" aqui não é usado, serve apenas para o compilador
// distinguir esta versão da do pré-incremento (é uma convenção do C++).
// Guarda o estado ANTES de incrementar (temp), incrementa o objeto
// através do operator++() pré-incremento, e devolve o estado antigo.
// Por isso: std::cout << v4++ << std::endl; mostra o valor ANTES
// de incrementar.
// ------------------------------------------------------------------
vect2 vect2::operator++(int)
{
	vect2 temp = *this;

	++(*this);
	return(temp);
}

// ------------------------------------------------------------------
// Pré-decremento: --v
// Mesma lógica do pré-incremento, mas subtraindo 1.
// ------------------------------------------------------------------
vect2& vect2::operator--()
{
	this->x -= 1;
	this->y -= 1;
	return(*this);
}

// ------------------------------------------------------------------
// Pós-decremento: v--
// Mesma lógica do pós-incremento, mas subtraindo 1.
// ------------------------------------------------------------------
vect2 vect2::operator--(int)
{
	vect2 temp = *this;

	--(*this);
	return(temp);
}

// ------------------------------------------------------------------
// Operador de igualdade: vect2 == vect2
// Devolve true apenas se AMBAS as componentes (x e y) forem iguais.
// ------------------------------------------------------------------
bool vect2::operator==(const vect2& obj) const
{
	if((this->x == obj.x) && (this->y == obj.y))
		return(true);
	return(false);
}

// ------------------------------------------------------------------
// Operador de diferença: vect2 != vect2
// Reaproveita o operator== já definido: é a negação de "obj == *this".
// ------------------------------------------------------------------
bool vect2::operator!=(const vect2& obj) const
{
	return(!(obj == *this));
}

// ------------------------------------------------------------------
// Destrutor
// Não há memória alocada dinamicamente (sem "new"), por isso não
// há nada específico a libertar. Fica vazio.
// ------------------------------------------------------------------
vect2::~vect2()
{

}

// ------------------------------------------------------------------
// Operador << (impressão)
// Função NÃO membro da classe (por isso não tem "vect2::" à frente),
// necessária para que a sintaxe "std::cout << v" funcione (o std::cout
// tem de estar do lado esquerdo do operador).
// Escreve no formato {x, y}.
//
// ATENÇÃO / BUG: esta função devia escrever para o stream "os"
// (o parâmetro recebido) e não diretamente para "std::cout".
// Se alguém usar esta função com outro stream (ex: um ficheiro,
// ou um std::ostringstream), o resultado vai sempre parar à consola
// em vez de ir para esse stream. O correto seria:
//     os << "{" << obj[0] << ", " << obj[1] << "}";
// ------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os,const vect2& obj)
{
	std::cout << "{" << obj[0] << ", " << obj[1] << "}";
	return(os);
}

// ------------------------------------------------------------------
// Multiplicação escalar * vect2 (ordem inversa): int * vect2
// Chamada em: v2 = 3 * v2;
// Função não-membro, necessária porque o "int" está do lado esquerdo
// (não é possível adicionar um método a "int"). Simplesmente reaproveita
// o operator*= já existente sobre uma cópia do vetor (temp).
// ------------------------------------------------------------------
vect2 operator*(int num, const vect2& obj)
{
	vect2 temp(obj);
	temp *= num;
	return(temp);
}
