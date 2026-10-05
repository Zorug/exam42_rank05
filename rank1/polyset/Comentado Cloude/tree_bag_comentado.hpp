#pragma once

#include "bag.hpp"

/*
** tree_bag
**
** Implementação CONCRETA de "bag", usando uma árvore binária de
** pesquisa (BST — Binary Search Tree) como estrutura de armazenamento.
** Propriedade da BST: para qualquer nó, tudo na subárvore esquerda é
** MENOR, e tudo na subárvore direita é MAIOR. É essa propriedade que
** mais tarde permite pesquisas eficientes em searchable_tree_bag.
**
** "virtual public bag": herança virtual pela mesma razão de array_bag —
** evitar duplicação do sub-objeto "bag" quando searchable_tree_bag
** herdar simultaneamente desta classe e de searchable_bag.
*/
class tree_bag : virtual public bag {
protected:
  // Nó interno da árvore: aponta para filho esquerdo (l), filho
  // direito (r), e guarda o valor do inteiro.
  // Está "protected" dentro da classe para que subclasses (como
  // searchable_tree_bag) possam percorrer a árvore diretamente.
  struct node {
    node *l;
    node *r;
    int value;
  };
  node *tree;   // raiz da árvore (nullptr se a árvore estiver vazia)

public:
  // --- Forma Canónica Ortodoxa ---
  // Necessária porque esta classe gere um recurso próprio: os nós da
  // árvore, alocados dinamicamente com "new".
  tree_bag();                          // construtor por defeito (tree = nullptr)
  tree_bag(const tree_bag &);          // construtor de cópia (deep copy da árvore)
  tree_bag  &operator=(const tree_bag &); // atribuição (deep copy da árvore)
  ~tree_bag();                          // destrutor (destrói todos os nós)

  // Métodos auxiliares "extra" (não fazem parte da interface "bag"):
  // permitem manipular a árvore interna diretamente, transferindo posse.

  // Retira a árvore de dentro deste objeto (o objeto fica com tree=nullptr)
  // e devolve o ponteiro para a raiz retirada. Útil para transferir a
  // posse da árvore para outro sítio sem copiar tudo.
  node *extract_tree();

  // Substitui a árvore atual por "new_tree": primeiro destrói a árvore
  // que já lá estava (evita leak), depois assume posse da nova.
  void set_tree(node *);

  // --- Implementação dos métodos puramente virtuais de "bag" ---
  // Marcados "virtual" explicitamente aqui (já eram virtuais por
  // herdarem de "bag", mas repetir a palavra-chave é só uma questão
  // de estilo/clareza — não muda o comportamento).
  virtual void insert(int);             // insere respeitando a ordem da BST
  virtual void insert(int *array, int size); // insere vários, um a um
  virtual void print() const;           // imprime em ordem (in-order traversal)
  virtual void clear();                  // destrói toda a árvore

private:
  // Funções auxiliares privadas, todas "static" porque operam sobre um
  // "node*" recebido como parâmetro em vez de sobre "this" — não
  // precisam de aceder a nenhum atributo de instância diretamente.
  static void destroy_tree(node *);   // liberta recursivamente todos os nós
  static void print_node(node *);      // imprime recursivamente (in-order)

  // ATENÇÃO — bug conhecido: esta assinatura está incorreta.
  // A implementação em tree_bag.cpp define copy_node a devolver "node *",
  // mas aqui está declarada a devolver "void *". Isto causa um erro de
  // compilação ("conflicting declaration"), porque a assinatura da
  // declaração tem de bater certo com a da definição.
  // Correção necessária: mudar para "static node *copy_node(node *);"
  static void *copy_node(node *);   // This needs to be changed from `void *` to `node *`
};
