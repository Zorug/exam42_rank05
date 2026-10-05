#include "searchable_array_bag.hpp"

/*
- Implementa o operador de atribuição (=) para a classe
- if (this != &other) - verifica se não estamos a atribuir o objeto a si próprio 
    (auto-atribuição)
- array_bag::operator=(other) - chama o operador de atribuição da classe base 
    array_bag para copiar os dados
- return (*this) - retorna o objeto atual para permitir encadeamento
*/
searchable_array_bag	&searchable_array_bag::operator=(const searchable_array_bag &other)
{
	if (this != &other)
		array_bag::operator=(other);
	return (*this);
}

/*
- Parâmetro: Recebe um int value - o valor que queremos procurar
- Const: O método não modifica o objeto (apenas lê)
- Loop: Percorre todos os elementos do array
    - size - provavelmente uma variável herdada de array_bag que guarda o número de elementos
    - data[] - provavelmente o array onde os elementos estão armazenados
- Comparação: Para cada elemento, verifica se é igual ao valor procurado
- Retorno:
    - return (true) - se encontrar o valor (sai imediatamente do loop)
    - return (false) - se percorrer todo o array sem encontrar
*/
bool	searchable_array_bag::has(int value) const
{
	for (int i = 0; i < size; ++i)
		if (data[i] == value)
			return (true);
	return (false);
}

/*
has é um método que verifica se um determinado valor existe no saco (bag). É a 
implementação concreta da funcionalidade de "pesquisa" prometida pela classe base 
searchable_bag.
*/