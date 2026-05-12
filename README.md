# Projeto de Estrutura de Dados

**Repositório GitHub**:  
https://github.com/GiovanneIM/Projeto_ED

**Código de compilação**:  
g++ ./main.cpp ./src/*.cpp -I ./include -o main.exe

---  

## Descrição
Projeto acadêmico desenvolvido com o objetivo de estudar, implementar e analisar o comportamento de algoritmos de ordenação e busca em diferentes cenários e volumes de dados.

O projeto realiza benchmarks automatizados, coleta métricas de desempenho e gera análises estatísticas para comparação entre algoritmos clássicos da disciplina de Estrutura de Dados.

---

## Objetivos

- Implementar algoritmos clássicos de ordenação e busca
- Comparar desempenho em diferentes cenários
- Analisar complexidade prática dos algoritmos
- Coletar métricas de execução
- Gerar dados estatísticos para estudo e visualização

---

## Algoritmos de Ordenação

Atualmente o projeto possui implementações dos seguintes algoritmos:

- Bubble Sort
- Insertion Sort
- Selection Sort
- Merge Sort
- Quick Sort
- Quick Sort Randomizado
- Heap Sort
- Shell Sort

Veja mais em: [Algoritmos de Ordenação](./AlgoritmosOrdenacao.md)

---

## Algoritmos de Busca

Veja mais em: [Algoritmos de Busca](./AlgoritmosBusca.md)

---

## Métricas Coletadas

Durante os testes são coletadas diversas métricas, como:

- Número de comparações
- Número de trocas
- Quantidade de acessos
- Tempo de execução
- Uso de memória auxiliar
- Profundidade de recursão

Além disso, o sistema calcula:

- Média
- Desvio padrão
- Mediana
- Coeficiente de variação
- Intervalo de confiança (95%)
- Valores mínimo e máximo

---

## Cenários de Teste

Os algoritmos são avaliados em diferentes tipos de entrada:

- Vetor aleatório
- Vetor ordenado
- Vetor reverso
- Vetor parcialmente ordenado
- Vetor com alta repetição
- Distribuição gaussiana

---

## Estrutura do Projeto

```text
.
├── include/                # Módulos de funções
├── src/                    # Definicição das funções dos módulos
├── CSV/                    # Arquivos de armazenamento dos dados
├── graphics/               # Gráficos gerados com o arquivo dados.csv
├── main.cpp                # Código principal
├── AlgoritmosOrdenacao.md  # Documentação - Algoritmos de ordenação
├── AlgoritmosBusca.md      # Documentação - Algoritmos de busca
└── README.md