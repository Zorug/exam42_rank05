/*
-   É uma diretiva de pré-processador que garante que este ficheiro de cabeçalho seja 
    incluído apenas uma vez durante a compilação
-   Funciona como os "include guards" tradicionais (#ifndef ... #define ... #endif)*/
#pragma once

# include "searchable_bag.hpp"
# include "array_bag.hpp"

/*
- Define a classe searchable_array_bag
- Herança múltipla: herda publicamente de ambas as classes base
- Isto significa que a classe combina a capacidade de pesquisa (de searchable_bag) 
com a implementação baseada em array (de array_bag)
*/
class	searchable_array_bag : public searchable_bag, public array_bag
{
public:
//  - Construtor vazio (não faz nada)
//  - Inicializa implicitamente as classes base com seus construtores padrão
	searchable_array_bag() {};
//  - Construtor que cria um novo objeto a partir de outro existente
//  - Nota importante: Só inicializa explicitamente array_bag, não searchable_bag
//  - Isto pode ser problemático porque searchable_bag será construído com seu 
//      construtor padrão, não copiado
//  - Provavelmente isso acontece porque searchable_bag é uma classe abstrata ou 
//      não tem dados para copiar
	searchable_array_bag(const searchable_array_bag &other) : array_bag(other) {}
//  - Declaração (não implementação) do operador de atribuição
//  - Retorna uma referência ao próprio objeto (permite encadeamento como a = b = c)
//  - Nota: Esta função é declarada mas não implementada neste ficheiro 
//      (provavelmente está no ficheiro .cpp)
	searchable_array_bag	&operator=(const searchable_array_bag &other);

//  - Declaração do método has que verifica se um valor existe no saco
//  - Recebe um int como parâmetro
//  - É const porque não modifica o objeto
//  - Este método provavelmente implementa a funcionalidade de pesquisa herdada de searchable_bag
	bool	has(int value) const;
};