#include "searchable_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"

#include <iostream>

int main(int argc, char **argv) {
  // Sem argumentos extra na linha de comando, não há nada para testar.
  if (argc == 1)
    return 1;

  // --- Parte 1: testar searchable_tree_bag e searchable_array_bag ---
  //
  // Repara no tipo do ponteiro: "searchable_bag *", não
  // "searchable_tree_bag *"/"searchable_array_bag *". Isto é
  // polimorfismo em ação — o código que se segue só conhece a
  // INTERFACE (insert, print, has, clear), sem saber (nem precisar de
  // saber) qual é a implementação concreta por trás de cada ponteiro.
  searchable_bag *t = new searchable_tree_bag;
  searchable_bag *a = new searchable_array_bag;

  // Insere cada argumento da linha de comando (convertido de string
  // para int) em ambos os bags.
  for (int i = 1; i < argc; i++) {
    t->insert(atoi(argv[i]));
    a->insert(atoi(argv[i]));
  }
  t->print();
  a->print();

  // Para cada argumento, testa has() com o próprio valor (deve dar 1/true)
  // e com valor-1 (pode dar 0 ou 1, dependendo se esse valor também foi
  // inserido por coincidência).
  for (int i = 1; i < argc; i++) {
    std::cout << t->has(atoi(argv[i])) << std::endl;
    std::cout << a->has(atoi(argv[i])) << std::endl;
    std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
    std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
  }

  // Esvazia ambos os bags — devem ficar vazios mas ainda utilizáveis.
  t->clear();
  a->clear();

  // Testa o construtor de cópia de searchable_array_bag.
  // "*a" é um searchable_bag&, mas sabemos que o objeto real por trás
  // é um searchable_array_bag (foi o que fizemos "new" lá em cima),
  // por isso o static_cast é seguro aqui (downcast controlado).
  const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
  tmp.print();   // deve imprimir vazio, já que "a" foi limpo acima
  tmp.has(1);    // só testa que a chamada compila/corre sem crash

  // --- Parte 2: testar a classe set ---
  //
  // Cada "set" envolve (wrap) um searchable_bag já existente, através
  // de referência — não cria um bag novo, usa o mesmo "a"/"t" de cima.
  set sa(*a);
  set st(*t);

  for (int i = 1; i < argc; i++) {
    // Insere o argumento atual em ambos os sets.
    st.insert(atoi(argv[i]));
    sa.insert(atoi(argv[i]));

    sa.has(atoi(argv[i]));       // consulta (resultado não é usado aqui)
    sa.print();                   // imprime através da interface do set
    sa.get_bag().print();         // imprime diretamente o bag por trás do set
                                   // (deve dar o mesmo resultado que sa.print())
    st.print();

    // Reinicia o set "sa" e insere sempre os mesmos 4 valores fixos —
    // serve para testar o insert(int*, int) em lote, de forma repetível
    // em cada iteração do loop.
    sa.clear();
    sa.insert(
        (int[]){
            1,
            2,
            3,
            4,
        },
        4);
    std::cout << std::endl;
  }

  return 0;
}

/*
** Nota sobre "sa.insert((int[]){1,2,3,4}, 4)":
** Isto é um "compound literal" (sintaxe de C99), aceite pelo GCC como
** extensão em C++, mas que pode não compilar em todos os compiladores/
** flags (nomeadamente, dá erro "taking address of temporary array" em
** alguns modos do g++). Não é algo que precises de "corrigir" nos teus
** próprios ficheiros — é parte do main.cpp fornecido pelo enunciado.
** Se precisares de testar isto localmente e o teu compilador se
** queixar, podes substituir temporariamente por:
**   int arr[] = {1, 2, 3, 4};
**   sa.insert(arr, 4);
** só para efeitos de teste — sem alterar o ficheiro que entregas.
*/
