import pandas as pd
import matplotlib.pyplot as plt
import os

# Carpeta donde se encuentran los archivos CSV
carpeta_datos = '/home/ak0mak0/Escritorio/Entregable_2/experiment_get_results'

# Lista de nombres de archivos CSV que quieres graficar
archivos = ['separate_chaining.csv', 'linear_probing.csv', 'quadratic_probing.csv', 'double_hashing.csv', 'unordered_map.csv']

# Graficar para cada archivo CSV
for archivo in archivos:
    # Leer los datos desde un archivo CSV
    df = pd.read_csv(os.path.join(carpeta_datos, archivo), delimiter=';')

    # Convertir la columna de tiempo de ejecución a valores numéricos
    df['tiempo'] = df['tiempo'].astype(float)

    # Filtrar los datos por dataset
    user_id_data = df[df['dataset'] == 'user_id']
    user_name_data = df[df['dataset'] == 'user_name']

    # Graficar los datos
    plt.figure(figsize=(10, 6))

    plt.plot(range(1, len(user_id_data) + 1), user_id_data['tiempo'], label='User ID')
    plt.plot(range(1, len(user_name_data) + 1), user_name_data['tiempo'], label='User Name')

    plt.xlabel('N° de búsqueda')
    plt.ylabel('Tiempo de ejecución (ns)')
    plt.title(f'Tiempo de ejecución por búsqueda de usuario almacenado - {archivo[:-4]}')
    plt.grid(True)
    plt.legend()

    # Ajustar el rango del eje y
    plt.ylim(0, max(user_id_data['tiempo'].max(), user_name_data['tiempo'].max()) * 1.1)  # Aumentar el límite superior en un 10% del máximo valor

    # Guardar la gráfica como imagen
    plt.savefig(f'grafico_{archivo[:-4]}.png')

    plt.show()
