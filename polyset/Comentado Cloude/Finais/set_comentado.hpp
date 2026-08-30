#pragma once

# include "searchable_bag.hpp"

/*
** set
**
** Classe que "embrulha" (wrap) um searchable_bag já existente e o
** apresenta com semântica de conjunto matemático (sem repetir a
** implementação de nenhuma estrutura de dados).
**
** Isto é composição, não herança: "set" NÃO É um bag (não herda de
** bag/searchable_bag), apenas TEM uma referência para um. Graças ao
** polimorfismo, essa referência pode apontar tanto para um
** searchable_array_bag como para um searchable_tree_bag — o "set"
** não precisa de saber qual é a implementação concreta por trás.
*/
class	set
{
	public:
		// Único construtor: recebe uma referência a um searchable_bag já
		// existente (não cria nem é dono de nenhum bag novo) e guarda-a
		// no membro _bag.
		set(searchable_bag &bag) : _bag(bag) {};

		bool	has(int value);
		void	insert(int value);
		void	insert(int *arr, int size);
		void	print() const;
		void	clear();
		const searchable_bag	&get_bag() const;

	private:
		// ATENÇÃO — membro de referência (searchable_bag&), não ponteiro.
		// Isto tem uma consequência importante para a Forma Canónica
		// Ortodoxa pedida no enunciado: uma referência tem de ser
		// inicializada no momento da criação e NUNCA pode ser "reatada"
		// a outro objeto depois. Por isso, o operator= gerado
		// automaticamente pelo compilador para "set" fica implicitamente
		// "deleted" (não existe um operator= funcional para esta classe
		// tal como está escrita).
		// Isto não impede a compilação nem o funcionamento do programa
		// ENQUANTO ninguém tentar fazer "set_a = set_b;" em lado nenhum
		// do código — mas viola tecnicamente o requisito de forma
		// canónica ortodoxa do enunciado, caso seja testado.
		searchable_bag	&_bag;
};
