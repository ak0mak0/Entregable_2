import pandas as pd
import matplotlib.pyplot as plt
import os

# Carpeta donde se encuentran los archivos CSV
carpeta_datos = '/home/ak0mak0/Escritorio/Entregable_2/experiment_put_results/'

# Lista de nombres de archivos CSV que quieres graficar
archivos = ['separate_chaining.csv', 'linear_probing.csv', 'quadratic_probing.csv', 'double_hashing.csv', 'unordered_map.csv']

# Graficar para cada archivo CSV
for archivo in archivos:
    # Leer los datos desde un archivo CSV
    df = pd.read_csv(os.path.join(carpeta_datos, archivo), delimiter=';')

    # Convertir la columna de tiempo de ejecución promedio a valores numéricos
    df['tiempo_ejecucion_promedio'] = df['tiempo_ejecucion_promedio'].str.replace(' ns', '').astype(float)

    # Separar los datos por dataset
    user_id_data = df[df['dataset'] == 'user_id']
    user_name_data = df[df['dataset'] == 'user_name']

    # Agrupar por cantidad de consultas y calcular el promedio del tiempo de ejecución
    user_id_avg_times = user_id_data.groupby('cantidad_consultas')['tiempo_ejecucion_promedio'].mean()
    user_name_avg_times = user_name_data.groupby('cantidad_consultas')['tiempo_ejecucion_promedio'].mean()

    # Graficar los datos
    plt.figure(figsize=(10, 6))

    plt.plot(user_id_avg_times.index, user_id_avg_times.values, marker='o', label='User ID')
    plt.plot(user_name_avg_times.index, user_name_avg_times.values, marker='x', label='User Name')

    plt.xlabel('Cantidad de consultas')
    plt.ylabel('Tiempo de ejecución promedio (ns) en 20 experimentos')
    plt.title(f'Tiempo de ejecución promedio por cantidad de consultas - {archivo[:-4]}')
    plt.grid(True)
    plt.legend()

    # Ajustar el rango del eje y
    plt.ylim(0, max(user_id_avg_times.max(), user_name_avg_times.max()) * 1.1)  # Aumentar el límite superior en un 10% del máximo valor

    # Guardar la gráfica como imagen
    plt.savefig(f'grafico_{archivo[:-4]}.png')

    plt.show()
