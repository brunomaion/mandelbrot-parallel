import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv", sep=";")

dfOriginal = df.loc[df["Arquivo"] == "orig"]
dfOmp = df.loc[df["Arquivo"] == "openmp"]
dfMpi = df.loc[df["Arquivo"] == "mpi"]

media_tempos_orig = dfOriginal["Tempo(ms)"].mean() / 1000  # Converter para segundos
media_tempos_openmp = dfOmp["Tempo(ms)"].mean() / 1000  # Converter para segundos
media_tempos_mpi = dfMpi["Tempo(ms)"].mean() / 1000  # Converter para segundos

# Plotar o gráfico de barras
programas = ["Original", "OpenMP", "MPI"]
tempos_medios = [media_tempos_orig, media_tempos_openmp, media_tempos_mpi]

plt.bar(programas, tempos_medios)
plt.ylabel("Tempo Médio (s)")  # Atualizar o rótulo para segundos
plt.title("Tempo Médio de Execução por Programa")

# Adicionar os números no topo de cada barra
for i, tempo in enumerate(tempos_medios):
    plt.text(i, tempo, f"{tempo:.2f}", ha="center")  # Ajustar a distância entre o número e a barra

plt.savefig('Grafico', dpi=300, bbox_inches="tight")



