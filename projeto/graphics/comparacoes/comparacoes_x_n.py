import pandas as pd
import matplotlib.pyplot as plt

# LENDO O CSV
df = pd.read_csv("../../CSV/dados.csv", sep=";")

# FILTRANDO APENAS TEMPO
tempo = df[df["Dado"] == "COMPARACOES"]



# PARA CADA CENÁRIO, GERAR UM GRÁFICO
for cenario in tempo["Cenario"].unique():

    dados_cenario = tempo[tempo["Cenario"] == cenario]

    plt.figure()  # cria um gráfico novo

    for algoritmo in dados_cenario["Algoritmo"].unique():
        dados_alg = dados_cenario[dados_cenario["Algoritmo"] == algoritmo]

        plt.plot(
            dados_alg["Tamanho"],
            dados_alg["Media"],
            marker="o",
            label=algoritmo
        )

    # CONFIGURAÇÕES DO GRÁFICO
    plt.xlabel("n")
    plt.ylabel("Comparações")
    plt.title(f"Comparações × n — Cenário: {cenario}")
    plt.legend()
    plt.grid(True, which="both", linestyle="--", alpha=0.3)

    # SALVANDO O GRÁFICO COMO IMAGEM
    nome_arquivo = f"comparacoes_x_n_{cenario}.png"
    plt.savefig(nome_arquivo, dpi=300, bbox_inches="tight")
    plt.close()

    print(f"Gráfico salvo: {nome_arquivo}")
