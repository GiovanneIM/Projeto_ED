# Algoritmos de Busca

## Índice

- [Busca Sequencial](#busca-sequencial)
- [Busca Binária](#busca-binária)
- [Busca Binária Instrumentada](#busca-binária-instrumentada-comparações--acessos)

<hr style="margin: 3rem 0;">

## Busca Sequencial

### DEFINIÇÃO

A **Busca Sequencial** (ou **Busca Linear**) é um algoritmo utilizado para encontrar um elemento em um vetor ou lista.

Ela funciona **percorrendo os elementos um a um**, do início até o fim, **comparando cada valor com o elemento procurado**.

O algoritmo termina quando:

- o elemento é encontrado;
- ou quando todos os elementos forem verificados.

### COMO A BUSCA SEQUENCIAL FUNCIONA

O algoritmo segue os seguintes passos:

1. Começa no primeiro elemento do vetor;
2. Compara o elemento atual com o valor procurado;
3. Se forem iguais, a busca termina;
4. Caso contrário, passa para o próximo elemento;
5. O processo se repete até o final do vetor.

### EXEMPLO DE FUNCIONAMENTO

Vetor: `[4, 3, 7, 5, 10]`  

Valor procurado: `7`

### Passo 1
Compara: `4 == 7 ?`  

Resultado: `Falso`

### Passo 2
Compara: `3 == 7 ?`  

Resultado: `Falso`

### Passo 3
Compara: `7 == 7 ?`  

Resultado: `Verdadeiro`

> O elemento foi encontrado no índice **3**.

### COMPLEXIDADE

### Melhor caso

O elemento está na primeira posição:
```
O(1)
```

### Pior caso

O elemento está na última posição ou não existe:
```
O(n)
```


<hr style="margin: 3rem 0;">



## Busca Binária

### DEFINIÇÃO

A **Busca Binária** é um algoritmo de busca utilizado para encontrar elementos em **vetores ordenados**.

Ela **funciona dividindo repetidamente o vetor ao meio**, **eliminando metade dos elementos a cada comparação**.

Isso torna a busca muito mais eficiente que a busca sequencial em grandes volumes de dados.

> **Obs:** A busca binária exige que o vetor esteja ordenado.

### COMO A BUSCA BINÁRIA FUNCIONA

O algoritmo segue os seguintes passos:

1. Encontra o elemento central do vetor;
2. Compara o valor central com o elemento procurado;
3. Se forem iguais, a busca termina;
4. Se o valor procurado for menor, busca-se na metade esquerda;
5. Se o valor procurado for maior, busca-se na metade direita;
6. O processo se repete até encontrar o elemento ou esgotar o vetor.

### EXEMPLO DE FUNCIONAMENTO

Vetor: `[1, 3, 5, 7, 9, 11, 13]`

Valor procurado: `9`

### Passo 1

Elemento central: `7`

Comparação: `9 > 7`

O elemento procurado está na metade direita.

Novo intervalo: `[9, 11, 13]`

### Passo 2

Elemento central: `11`

Comparação: `9 < 11`

O elemento procurado está na metade esquerda.

Novo intervalo: `[9]`

### Passo 3

Elemento central: `9`

Comparação: `9 == 9`

> O elemento foi encontrado no índice **4**.

### COMPLEXIDADE

### Melhor caso

O elemento está exatamente no meio do vetor ordenado:
```
O(1)
```

### Caso médio e pior caso

O vetor é dividido pela metade a cada etapa:
```
O(log n)
```


<hr style="margin: 3rem 0;">



## Busca Binária Instrumentada 
#### (Comparações + Acessos)

### DEFINIÇÃO

A **Busca Binária Instrumentada** é uma versão da busca binária tradicional que adiciona mecanismos de monitoramento durante a execução do algoritmo.

O objetivo da instrumentação é coletar informações sobre o comportamento da busca, como:

- quantidade de comparações;
- quantidade de iterações;
- tempo de execução;
- posições visitadas;
- desempenho do algoritmo.

Esse tipo de implementação é muito utilizado em:

- análise de algoritmos;
- testes de desempenho;
- trabalhos acadêmicos;
- depuração de programas

### COMO A BUSCA BINÁRIA INSTRUMENTADA FUNCIONA

O funcionamento da busca continua sendo o mesmo da busca binária tradicional:

1. encontra-se o elemento central;
2. compara-se o valor central com o valor procurado;
3. elimina-se metade do vetor;
4. repete-se o processo até encontrar o elemento.

A diferença é que, durante a execução, o algoritmo registra informações estatísticas.

### EXEMPLO DE FUNCIONAMENTO

Vetor ordenado: `[1, 3, 5, 7, 9, 11, 13]`  

Valor procurado: `9`

### Passo 1

Intervalo atual: `[1, 3, 5, 7, 9, 11, 13]`

Elemento central: `7`

Comparação realizada: `9 > 7`

Contador de comparações: `1`

O algoritmo descarta a metade esquerda.

### Passo 2

Novo intervalo: `[9, 11, 13]`

Elemento central: `11`

Comparação: `9 < 11`

Contador de comparações: `2`

O algoritmo descarta a metade direita.

### Passo 3

Novo intervalo: `[9]`

Elemento central: `9`

Comparação: `9 == 9`

Contador de comparações: `3`

> O elemento foi encontrado no índice **3**.

### COMPLEXIDADE

A instrumentação não altera significativamente a complexidade da busca binária.

### Melhor caso
```
O(1)
```

### Caso médio e pior caso
```
O(log n)
```

<hr style="margin: 3rem 0;">

