#include "set.hpp"

// Pergunta se um valor existe no set, delegando diretamente no has()
// do searchable_bag por trás (é aí que a pesquisa real acontece —
// linear se for um array_bag, em árvore se for um tree_bag).
bool	set::has(int value)
{
	return (_bag.has(value));
}

// Insere um valor no set.
//
// ATENÇÃO — esta implementação insere SEMPRE, sem verificar primeiro
// se o valor já existe (não chama has() antes de _bag.insert()).
// Isto significa que, tal como está, esta função NÃO garante a
// propriedade fundamental de um "set" matemático: a ausência de
// duplicados.
//
// Com um searchable_tree_bag por trás, isto "parece" funcionar, porque
// a própria árvore binária de pesquisa já rejeita valores repetidos
// internamente (ver tree_bag::insert) — mas essa proteção vem da
// estrutura de dados, não desta classe "set". Com um
// searchable_array_bag por trás, não há proteção nenhuma, e inserir o
// mesmo valor duas vezes resulta em duplicados visíveis no print().
//
// Para garantir mesmo a semântica de conjunto independentemente do bag
// por trás, seria necessário algo como:
//   void set::insert(int value)
//   {
//       if (!_bag.has(value))
//           _bag.insert(value);
//   }
void	set::insert(int value)
{
	_bag.insert(value);
}

// Insere vários valores de uma vez.
// Mesma observação do insert(int) acima: delega diretamente em
// _bag.insert(arr, size) sem filtrar duplicados nem verificar has()
// para cada elemento do array.
void	set::insert(int *arr, int size)
{
	_bag.insert(arr, size);
}

// Imprime o conteúdo do set, delegando no print() do bag por trás.
void	set::print() const
{
	_bag.print();
}

// Esvazia o set, delegando no clear() do bag por trás.
void	set::clear()
{
	_bag.clear();
}

// Devolve uma referência const ao bag por trás do set — permite
// aceder/inspecionar o bag diretamente (ex: chamar print() nele),
// sem dar acesso de escrita (const protege contra modificações
// através desta referência).
const searchable_bag	&set::get_bag() const
{
	return (_bag);
}
