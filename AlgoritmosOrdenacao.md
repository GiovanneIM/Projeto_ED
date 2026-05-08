# Algoritmos de ordenação

## Índice

- [Bubble Sort](#bubble-sort)
- [Insertion Sort](#insertion-sort)
- [Selection Sort](#selection-sort)
- [Merge Sort](#merge-sort)
- [Quick Sort](#quick-sort)
- [Quick Sort Randomizado](#quick-sort-randomizado)
- [Heap Sort](#heap-sort)
- [Shell Sort](#shell-sort)

<hr style="margin: 3rem 0;">

## Bubble Sort

### DEFINIÇÃO

O **Bubble Sort** funciona comparando **elementos adjacentes** e trocando-os de posição sempre que estiverem fora de ordem.  
A cada passagem completa pelo vetor, o **maior elemento é levado para o final**.

### EXEMPLO DE FUNCIONAMENTO

Vetor inicial: `[5, 1, 4, 2, 8]`

### Primeira passagem

Compara-se cada par de elementos adjacentes:

- Compara `5` e `1` → troca  
`[1, 5, 4, 2, 8]`

- Compara `5` e `4` → troca  
`[1, 4, 5, 2, 8]`

- Compara `5` e `2` → troca  
`[1, 4, 2, 5, 8]`

- Compara `5` e `8` → não troca  

Ao final da passagem, o **8** está na posição correta.

### Segunda passagem

Vetor no início da passagem: `[1, 4, 2, 5, 8]`

- Compara `1` e `4` → não troca

- Compara `4` e `2` → troca  
`[1, 2, 4, 5, 8]`

- Compara `4` e `5` → não troca  

Ao final da passagem, o **5** está na posição correta.

### Finalização

O algoritmo continua realizando passagens até que **nenhuma troca seja necessária**, indicando que o vetor está completamente ordenado.

Resultado: `[1, 2, 4, 5, 8]`



<hr style="margin: 3rem 0;">



## Insertion Sort

### DEFINIÇÃO

O **Insertion Sort** funciona percorrendo um vetor da esquerda para a direita e, a cada passo, **insere o elemento atual na posição correta entre os elementos já ordenados**.

### EXEMPLO DE FUNCIONAMENTO

Vetor inicial: `[5, 2, 4, 6, 1, 3]`

### Passo 1  

`[5 | 2, 4, 6, 1, 3]`

- Compara `2` com `5`
- Move `5` para a direita
- Insere `2` antes de `5`

Resultado: `[2, 5, 4, 6, 1, 3]`

### Passo 2  

`[2, 5 | 4, 6, 1, 3]`

- Compara `4` com `5`
- Move `5` para a direita
- Compara `4` com `2` - Não move `2`
- Insere `4` entre `2` e `5`

Resultado: `[2, 5, 4, 6, 1, 3]`

### Finalização
O algoritmo continua até inserir o último elemento

Resultado: `[1, 2, 3, 4, 5, 6]`



<hr style="margin: 3rem 0;">



## Selection Sort

### DEFINIÇÃO

O **Selection Sort** funciona percorrendo, da esquerda para a direita, a parte não ordenada de um vetor e a cada passagem, **selecionar o menor elemento da parte não ordenada e movê-lo para a posição correta**.

O Selection Sort **divide o vetor em duas partes**
- Parte ordenada (à esquerda)
- Parte não ordenada (à direita)

### EXEMPLO DE FUNCIONAMENTO

Vetor inicial: `[5, 2, 4, 6, 1, 3]`

### Passo 1

Parte não ordenada: `[5, 2, 4, 6, 1, 3]`

- O menor elemento da parte não ordenada é `1`
- Troca `1` com o primeiro elemento (`5`)

Resultado: `[1, 2, 4, 6, 5, 3]`

### Passo 2

Parte não ordenada: `[1 | 2, 4, 6, 5, 3]`

- O menor elemento da parte não ordenada é `2`
- Já está na posição correta - Não troca

Resultado: `[1, 2, 4, 6, 5, 3]`

### Passo 3

Parte não ordenada: `[1, 2 | 4, 6, 5, 3]`

- O menor elemento da parte não ordenada é `3`
- Troca `3` com `4`

Resultado: `[1, 2, 3, 6, 5, 4]`

### Finalização
O algoritmo continua até que toda a parte não ordenada seja percorrida e o vetor esteja completamente ordenado

Resultado: `[1, 2, 3, 4, 5, 6]`



<hr style="margin: 3rem 0;">



## Merge Sort

### DEFINIÇÃO
O **Merge Sort**  é um algoritmo baseado na ideia de **dividir para conquistar**.

O Merge Sort funciona em três etapas:

1. **Divide** o vetor em duas metade;
2. **Ordena recursivamente** cada metade;
3. **Mescla (merge)** as duas metades ordenadas em um único vetor ordenado.

Ele repete esse processo até que os subvetores tenham **apenas um elemento**, que por definição já está ordenado.

### EXEMPLO DE FUNCIONAMENTO

Vetor inicial: `[5, 2, 4, 6, 1, 3]`

### Etapa 1 - Divisão

Divide o vetor ao meio repetidamente, até chegar em vetores unitários:  

```
[5, 2, 4]   [6, 1, 3] 

[5] [2, 4]  [6] [1, 3] 
  
[5] [2] [4] [6] [1] [3]
```

### Etapa 2 - Ordenação recursiva

Vetores com **1 elemento** já estão ordenados.  
Agora começa a fusão (merge):
- Junta `[2]` e `[4]` → `[2, 4]`
- Junta `[5]` e `[2, 4]` → `[2, 4, 5]`  
- **Primeira metade ordenada**

- Junta `[1]` e `[3]` → `[1, 3]`
- Junta `[6]` e `[1, 3]` → `[1, 3, 6]`
- **Segunda metade ordenada**

### Etapa 3 - Mesclagem Final

As duas metades ordenadas são mescladas:

`[2, 4, 5] + [1, 3, 6]`

Comparando elemento por elemento, obtém-se:

`[1, 2, 3, 4, 5, 6]`



<hr style="margin: 3rem 0;">



## Quick Sort

### DEFINIÇÃO
O **Quick Sort**  é um algoritmo baseado na ideia de **dividir para conquistar**.

O Merge Sort funciona escolhendo um elemento chamado **pivô** e reorganizando o vetor de modo que:

- os elementos menores que o pivô fiquem à esquerda;
- os maiores fiquem à direita.

Depois disso, o processo é repetido recursivamente nas duas partes do vetor.

### EXEMPLO DE FUNCIONAMENTO

Vetor inicial: `[5, 2, 4, 6, 1, 3]`

### Passo 1

Escolhe-se um pivô.
Supondo que escolhamos o elemento central do vetor (`4`).
Pivô = `4`

### Passo 2

Reorganiza-se o vetor:

```
Menores que 4 → 2, 1, 3
Maiores que 4 → 5, 6

[2, 1, 3, 4, 5, 6]
```

Note que:

- Valores menores que 4 → Esquerda
- Valores maiores que 4 → Direita

Isso significa que o pivô ficou em sua posição correta no vetor.

### Finalização

Repete-se os passo nos subvetores:

- À esquerda do pivô `[2, 1, 3]`
- À direita do pivô: `[5, 6]`

O processo continua até que o vetor esteja ordenado.

Resultado: `[1, 2, 3, 4, 5, 6]`



<hr style="margin: 3rem 0;">



## Quick Sort Randomizado

### DEFINIÇÃO

O **Quick Sort Randomizado** é uma variação do **Quick Sort**.

A principal diferença entre está na forma como o pivô é escolhido.

No Quick Sort tradicional, segue-se uma lógica pré-estabelecida, por exemplo:
- o primeiro elemento;
- o último elemento;
- ou o elemento do meio.

Enquanto que, no Quick Sort randomizado, um **elemento aleatório é escolhido como pivô**.
Essa estratégia reduz a chance de ocorrer o pior caso do Quick Sort.

### Por que randomizar o pivô?

Supondo o vetor inicial `[2, 1, 3, 4, 5, 6]`

Note que, ao utilizar a lógica ***último elemento como pivô***, obtêm-se uma divisão desbalanceada ao reorganizar o vetor:

```
Menores que 6 → 2, 1, 3, 4, 5
Maiores que 6 → 

[2, 1, 3, 4, 5 | 6]
```

- Sub-vetor à esquerda: `[2, 1, 3, 4, 5]`
- Sub-vetor à direita: `[]`

Essa escolha não dividiu o vetor, apenas posiciona um elemento corretamente.

Além disso, esse comportamento tende a se repetir nos subvetores, tornando as divisões cada vez mais desbalanceadas.

Esse comportamento aproxima a execução do pior caso.

Ao escolher um **pivô aleatório reduz-se significativamente a chance de desse acontecimento**.



<hr style="margin: 3rem 0;">



## Heap Sort

### DEFINIÇÃO

O **Heap Sort** é um algoritmo de ordenação baseado em uma estrutura de dados chamada **Heap**.

Ele funciona organizando os elementos em uma árvore binária especial e, em seguida, removendo repetidamente o maior elemento para colocá-lo na posição correta do vetor.

O Heap Sort utiliza, normalmente, um tipo de heap chamado **Max Heap**.

### O que é um Heap?

Um **Heap** é uma árvore binária que segue uma propriedade específica.

No caso do **Max Heap**:

- O nó pai sempre possui valor maior que os filhos.

Exemplo:
```
        9
      /   \
     7     6
    / \   / \
   5   2 1   3
```

Note que:
- 9 > 7 e 6
- 7 > 5 e 2
- 6 > 1 e 3

O maior valor é a raiz da árvore

### EXEMPLO DE FUNCIONAMENTO

Vetor inicial: `[4, 10, 3, 5, 1]`

### Passo 1 - Construção do Heap

O algoritmo reorganiza os elementos para formar um Max Heap.

Heap: `[10, 5, 3, 4, 1]`

Representação: 
```
        10
       /  \
      5    3
     / \
    4   1
```

Agora o maior elemento está na raiz

### Passo 2 - Ordenação

O maior elemento é trocado com o último elemento do vetor.

`[1, 5, 3, 4, 10]`

O valor `10` já está ordenado.

### Finalização

Depois disso:
- reduz-se o tamanho do heap;
- reorganiza-se o heap novamente.

Novo heap: `[5, 4, 3, 1 | 10]`

Repete-se o processo até ordenar todo o vetor.

Resultado final: `[1, 3, 4, 5, 10]`



<hr style="margin: 3rem 0;">



## Shell Sort

### DEFINIÇÃO

O **Shell Sort** é um algoritmo de ordenação baseado no **Insertion Sort**.

A ideia principal é comparar elementos que estão distantes entre si, reduzindo gradualmente essa distância até que o vetor seja ordenado.

Essa distância é chamada de **gap**.

O Shell Sort **melhora o desempenho** do Insertion Sort porque **reduz a quantidade de deslocamentos** necessários durante a ordenação.

### COMO O SHELL SORT FUNCIONA

O algoritmo funciona em etapas:

1. Escolhe-se um valor inicial para o gap
2. Elementos separados por esse gap são ordenados;
3. O gap é reduzido;
4. O processo se repete até que o gap seja igual a 1.

**Quando o gap chega em 1, o algoritmo funciona como um Insertion Sort tradicional**, porém com o vetor parcialmente ordenado.

### EXEMPLO DE FUNCIONAMENTO

Vetor inicial: `[8, 5, 3, 7, 6, 2, 1, 4]`

### Passo 1 - Gap = 4

Compara-se elementos separados por 4 posições.
```
[6, _, _, _, 8, _, _, _]
[_, 2, _, _, _, 5, _, _]
[_, _, 1, _, _, _, 3, _]
[_, _, _, 4, _, _, _, 7]
```
Cada linha representa uma subsequência ordenada separadamente.

Comparações:
```
8 ↔ 6
5 ↔ 2
3 ↔ 1
7 ↔ 4
```

Após reorganizar: `[6, 2, 1, 4, 8, 5, 3, 7]`

### Passo 2 - Gap = 2

Compara-se elementos separados por 2 posições.
```
[6, _, 1, _, 8, _, 3, _]
[_, 2, _, 4, _, 5, _, 7]
```
Cada linha representa uma subsequência ordenada separadamente.

Após reorganizar: `[1, 2, 3, 4, 6, 5, 8, 7]`


### Passo 3 - Gap = 1

Agora o algoritmo executa um Insertion Sort comum.

Resultado final: `[1, 2, 3, 4, 5, 6, 7, 8]`

---
