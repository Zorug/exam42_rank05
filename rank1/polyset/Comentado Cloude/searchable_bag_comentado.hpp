#pragma once

#include "bag.hpp"

/*
** searchable_bag
**
** Extensão da interface "bag": continua a ser 100% abstrata (não pode
** ser instanciada), mas acrescenta a exigência de um método has(),
** que permite perguntar "este valor está no bag?".
**
** "virtual public bag": a herança é marcada como VIRTUAL de propósito.
** Isto é essencial para o resto do projeto, por causa da herança
** múltipla que vai acontecer mais tarde em searchable_array_bag e
** searchable_tree_bag:
**
**              bag
**             /   \
**   searchable_bag   array_bag   (ambas herdam de "bag")
**             \   /
**       searchable_array_bag     (herda das duas ao mesmo tempo)
**
** Sem "virtual" nas duas heranças de "bag", searchable_array_bag teria
** DOIS sub-objetos "bag" distintos e ambíguos (um vindo de searchable_bag,
** outro vindo de array_bag) — o clássico "problema do diamante". Com
** "virtual", ambos os caminhos partilham o MESMO único sub-objeto "bag",
** eliminando a ambiguidade.
*/
class searchable_bag : virtual public bag {
public:
	// Pergunta se um determinado valor existe no bag.
	// A forma como a pesquisa é feita (linear, em árvore, etc.) fica
	// completamente a cargo de cada implementação concreta.
	// const: apenas consulta, não deve alterar o estado do bag.
	virtual bool has(int) const = 0;
};
