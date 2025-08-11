# Interpretador de Código Ussaran com Tabela Hash e Estruturas de Dados Personalizadas

[![C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://isocpp.org/)

[![Estruturas de Dados](https://img.shields.io/badge/Tabela_Hash-green)](#)
[![Estruturas de Dados](https://img.shields.io/badge/Lista_Duplamente_Encadeada-blue)](#)
[![Estruturas de Dados](https://img.shields.io/badge/Pilha-orange)](#)
[![Estruturas de Dados](https://img.shields.io/badge/Fila-yellow)](#)

[![Status](https://img.shields.io/badge/Status-Concluído-success)](#)


Este projeto foi desenvolvido para interpretar programas escritos em uma linguagem fictícia chamada Ussaran, onde cada caractere é representado por uma sequência de três símbolos.
O sistema traduz esse código para caracteres legíveis, organiza as instruções e executa a lógica de controle de fluxo e manipulação de filas.
A implementação utiliza Tabela Hash, Listas Duplamente Encadeadas, Pilhas e Filas implementadas manualmente, sem bibliotecas externas.

---

## Funcionalidades

- Mapeamento de caracteres: tradução de símbolos Ussaran (::: , .|:, etc.) para letras.
- Leitura e armazenamento do programa em lista duplamente encadeada.
- Tradução completa do código para caracteres ASCII.
- Remoção de espaços iniciais para padronização das instruções.
- Interpretação de funções (declaração, chamadas e retorno).
- Manipulação de fila com comandos ENFILEIRA e DESENFILEIRA.
- Execução sequencial com controle de fluxo e pilha de endereços para chamadas de função.

---

## Estrutura do Projeto
```
│
├── Classe Letter
│ ├── Armazena chave (caractere traduzido) e valor (símbolo Ussaran)
│ ├── Operador == e impressão formatada
│
├── Classe Template Node
│ ├── Nó genérico para lista duplamente encadeada
│
├── Classe Template Stack (Pilha)
│ ├── push / pop / head / size / empty
│
├── Classe Template List (Lista Duplamente Encadeada)
│ ├── Inserção/remoção no início e fim
│ ├── Iteração via ListNavigator
│
├── Classe Template HashTable
│ ├── Dispersão com função hash polinomial
│ ├── Armazena listas encadeadas em cada bucket
│ ├── insert / search / print
│
├── Classe Template Queue (Fila Circular Estática)
│ ├── enqueue / dequeue / front / empty / size
│
├── Funções Principais
│ ├── alphabet – carrega o dicionário de símbolos Ussaran na HashTable
│ ├── lerPrograma – lê o código fonte Ussaran até o caractere ~
│ ├── traduzirPrograma – converte símbolos em letras usando a HashTable
│ ├── retirarEspacos – normaliza espaços iniciais
│ ├── interpretarPrograma – executa comandos, gerencia fila e funções
│
└── Função main
├── Inicializa estruturas de dados
├── Lê, traduz, normaliza e interpreta o código Ussaran
```

## Diagrama Simplificado
```
[ Programa Ussaran (memoria) ]
        │
        ▼
[ Tradução via HashTable<Letter> ]
        │
        ▼
[ Lista traduzida (traducao) ]
        │
        ▼
[ Remoção de espaços ]
        │
        ▼
[ Interpretador ]
   ├── Pilha de comandos
   ├── Pilha de endereços
   ├── Fila de execução

```

## Autoria
```
Jessica Rodrigues
Ana Klissia Furtado Martins
```
