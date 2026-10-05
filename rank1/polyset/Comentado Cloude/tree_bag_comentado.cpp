#include "tree_bag.hpp"
#include <iostream>

// Construtor por defeito: árvore vazia.
tree_bag::tree_bag() {
	tree = nullptr;
}

// Construtor de cópia (deep copy).
// Não basta copiar o ponteiro "tree" (isso seria "shallow copy": os dois
// objetos partilhariam os MESMOS nós, e destruir um deixaria o outro
// com ponteiros inválidos). Por isso clonamos a árvore inteira,
// nó a nó, através de copy_node (função recursiva auxiliar).
tree_bag::tree_bag(const tree_bag &src) {
	tree = copy_node(src.tree);
}

// Destrutor: destrói recursivamente todos os nós da árvore.
tree_bag::~tree_bag() {
	destroy_tree(tree);
}

// Operador de atribuição (a = b).
tree_bag &tree_bag::operator=(const tree_bag &src) {
	// Proteção contra auto-atribuição (a = a): sem isto, destruiríamos
	// a árvore antes de a tentar copiar de si própria.
	if (this != &src) {
		// Liberta a árvore ANTIGA deste objeto (evita memory leak)...
		destroy_tree(tree);
		// ...e clona a árvore nova a partir de "src".
		tree = copy_node(src.tree);
	}
	return *this;
}

// Retira a árvore de dentro deste objeto (transferência de posse, sem
// copiar nada): o objeto original fica com tree = nullptr (árvore
// "vazia"), e o ponteiro retirado passa a ser responsabilidade de quem
// chamou esta função.
tree_bag::node *tree_bag::extract_tree() {
	node *temp = tree;
	tree = nullptr;
	return temp;
}

// Substitui a árvore atual por "new_tree".
// Primeiro destrói a árvore que já existia (evita leak da árvore
// antiga), só depois assume posse da nova.
void tree_bag::set_tree(node *new_tree) {
	destroy_tree(tree);
	tree = new_tree;
}

// Insere um único valor, respeitando a propriedade da BST
// (esquerda < nó < direita).
void tree_bag::insert(int item) {
	// Aloca e prepara o novo nó ANTES de saber onde ele vai ficar.
	node *new_node = new node;
	std::cout << "create node: " << item << std::endl;
	new_node->value = item;
	new_node->l = nullptr;
	new_node->r = nullptr;

	if (tree == nullptr) {
		// Árvore ainda vazia: o novo nó torna-se a raiz.
		tree = new_node;
	} else {
		// Desce a árvore a partir da raiz, decidindo em cada nó se vai
		// para a esquerda ou para a direita, até encontrar um "buraco"
		// (filho nullptr) onde encaixar o novo nó.
		node *current = tree;
		while (true) {
			if (item < current->value) {
				if (current->l == nullptr) {
					current->l = new_node;
					break;
				} else {
					current = current->l;
				}
			} else if (item > current->value) {
				if (current->r == nullptr) {
					current->r = new_node;
					break;
				} else {
					current = current->r;
				}
			} else {
				// item == current->value: valor já existe na árvore.
				// Esta implementação de tree_bag rejeita duplicados
				// automaticamente (é uma característica da estrutura
				// BST usada aqui, não do conceito de "bag" em geral).
				// O nó que tínhamos alocado no início acaba por não
				// ser usado, por isso é preciso libertá-lo aqui para
				// não causar memory leak.
				std::cout << "duplicate value: delete node" << std::endl;
				delete new_node;
				break;
			}
		}
	}
}

// Insere vários valores de uma vez: simplesmente chama insert(int)
// para cada elemento do array, um a um.
void tree_bag::insert(int *items, int count) {
	for (int i = 0; i < count; i++) {
		insert(items[i]);
	}
}

// Imprime os elementos por ordem crescente.
// Isto é possível "de borla" graças à propriedade da BST: um percurso
// "in-order" (esquerda, nó, direita) visita sempre os valores em ordem
// crescente.
void tree_bag::print() const {
	print_node(tree);
	std::cout << std::endl;
}

// Esvazia o bag: destrói toda a árvore e repõe tree a nullptr.
void tree_bag::clear() {
	destroy_tree(tree);
	tree = nullptr;
}

// --- Funções auxiliares privadas (definidas como static na classe) ---

// Destrói recursivamente a árvore inteira, em pós-ordem (primeiro os
// filhos, só depois o próprio nó) — é a ordem correta para não perder
// a referência aos filhos antes de os visitar.
void tree_bag::destroy_tree(node *current) {
	if (current != nullptr) {
		std::cout << "destroying value: " << current->value << std::endl;
		destroy_tree(current->l);
		destroy_tree(current->r);
		delete current;
	}
}

// Percurso "in-order" (esquerda, nó, direita): imprime os valores por
// ordem crescente.
void tree_bag::print_node(node *current) {
	if (current != nullptr) {
		print_node(current->l);
		if (current->value != 0)
			std::cout << current->value << " ";
		print_node(current->r);
	}
}

// Clona recursivamente a árvore a partir de "current" (deep copy):
// para cada nó, cria um nó novo com o mesmo valor, e clona também as
// subárvores esquerda e direita. Um "current" nullptr devolve nullptr
// (caso base da recursão — árvore/subárvore vazia).
//
// Nota: a assinatura correta desta função devolve "node *", não
// "void *" — ver comentário no ficheiro .hpp sobre o bug de
// declaração que impede a compilação enquanto não for corrigido.
tree_bag::node *tree_bag::copy_node(node *current) {
	if (current == nullptr) {
		return nullptr;
	} else {
		node *new_node = new node;
		new_node->value = current->value;
		new_node->l = copy_node(current->l);
		new_node->r = copy_node(current->r);
		return new_node;
	}
}
