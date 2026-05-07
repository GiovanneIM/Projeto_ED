# Algoritmos de ordenação

- [Algoritmos de Ordenação](#algoritmos-de-ordenação)
  - [Bubble Sort](#bubble-sort)
  - [Insertion Sort](#insertion-sort)
  - [Selection Sort](#selection-sort)
  - [Merge Sort](#merge-sort)
  - [Quick Sort](#quick-sort)
  - [Quick Sort Randomizado](#quick-sort-randomizado)
  - [Heap Sort](#heap-sort)
  - [Shell Sort](#shell-sort)



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

---



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

---



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

---



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

---



## Quick Sort

---



## Quick Sort Randomizado

---



## Heap Sort

---



## Shell Sort

---
