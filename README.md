# Busca de endereços com Árvore AVL (C++)

Sistema de busca textual por logradouros desenvolvido em C++ para consultas eficientes em grandes bases de endereços, projetado para consultas rápidas por meio de indexação com [árvore AVL](https://www.geeksforgeeks.org/dsa/introduction-to-avl-tree/), garantindo operações em `O(log n)`.

## Visão geral

O sistema recebe uma base de endereços e permite buscas por partes do nome do logradouro, retornando os resultados mais compatíveis ordenados por proximidade.  

***Principais objetivos***: eficiência algorítmica, baixo tempo de espera por consulta e organização modular.


## Arquitetura

- Indexação dos termos em uma árvore AVL balanceada;
- Recuperação e filtragem de candidatos;
- Ordenação por distância para retorno dos Top-K resultados.

## Execução

Programa principal:
```
make
./bin/buscador.out < input.txt > output.txt
```
    
Testes:
```
make tests
```

## Entrada / Saída

**Entrada**: N (número de endereços), seguido dos N registros (IdEnd;IdLog;TipoLog;Log;Num;Bairro;Regiao;CEP;Lat;Long). Por fim, vem a parte das consultas, com M (quantidade de consultas), R (número de respostas) e as M consultas (IdConsulta;Consulta;LatOrigem;LongOrigem).  

**Saída**: M seguido dos resultados de cada consulta (IdConsulta;NumeroDeRespostas e IdLog;Logradouro para todas as respostas).

> [!NOTE] 
> Exemplos completos de entrada/saída podem ser encontrados em `tests/exemplos`