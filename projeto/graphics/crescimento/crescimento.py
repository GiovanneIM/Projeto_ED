import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# LENDO O CSV
df = pd.read_csv("../../CSV/dados.csv", sep=";")

# FILTRANDO APENAS TEMPO DO QUICKSORT
tempo = df[df["Dado"] == "TEMPO"]
quick = tempo[tempo["Algoritmo"] == "QuickSort"]

plt.figure()

for cenario in quick["Cenario"].unique():
    dados = quick[quick["Cenario"] == cenario]

    n = dados["Tamanho"]
    normalizado = dados["Media"] / (n * np.log2(n))

    plt.plot(
        n,
        normalizado,
        marker="o",
        label=cenario
    )

plt.xlabel("n")
plt.ylabel(r"Tempo / (n log₂ n)")
plt.title("QuickSort — Análise de Crescimento Normalizado")
plt.legend()
plt.grid(True, which="both", linestyle="--", alpha=0.3)

plt.savefig("crescimento_quicksort.png", dpi=300, bbox_inches="tight")
plt.close()


