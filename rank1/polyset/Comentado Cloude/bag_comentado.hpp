#pragma once

/*
** bag
**
** Interface abstrata pura (todos os métodos são = 0, "pure virtual").
** Não tem nenhum atributo — é apenas um "contrato": qualquer classe que
** queira ser considerada um "bag" tem de implementar estes 4 métodos.
**
** Por ser 100% abstrata, "bag" NUNCA pode ser instanciada diretamente
** (new bag() daria erro de compilação). Serve só como tipo-base comum,
** permitindo polimorfismo: podemos ter um bag* que aponta para um
** array_bag, um tree_bag, ou qualquer outra implementação futura, e
** chamar sempre os mesmos métodos sem saber qual é a implementação real.
**
** Nota: não há destrutor virtual declarado aqui. Isto é normalmente
** considerado uma "boa prática em falta" — se alguém fizer
**   bag *b = new array_bag();
**   delete b;
** o destrutor de array_bag NUNCA seria chamado (comportamento indefinido,
** e memory leak certo, já que array_bag aloca memória dinamicamente).
** No main.cpp fornecido isto nunca chega a acontecer (não há "delete"
** através de um bag*/searchable_bag*), mas é importante teres a noção
** deste detalhe caso o projeto evolua.
*/
class bag {
public:
	// Insere um único elemento no bag.
	virtual void insert (int) = 0;

	// Insere vários elementos de uma vez, a partir de um array de "count"
	// inteiros. Útil para inserções em lote sem chamar insert(int) num
	// loop externo repetidamente.
	virtual void insert (int *, int) = 0;

	// Imprime o conteúdo do bag (formato decidido por cada implementação).
	// const: apenas consulta, não deve alterar o estado do bag.
	virtual void print() const = 0;

	// Remove todos os elementos, deixando o bag vazio (mas ainda válido
	// e reutilizável, não destruído).
	virtual void clear() = 0;
};
