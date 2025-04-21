import unicodedata
import re

def limpar_texto(texto):
    # normaliza e remove acentos
    texto = unicodedata.normalize('NFD', texto)
    texto = texto.encode('ascii', 'ignore').decode('utf-8')
    # converte para minusculo, remove espacos, pontuacoes e numeros
    texto = re.sub(r'[^a-zA-Z]', '', texto.upper())
    return texto

entrada = input()
saida = limpar_texto(entrada)
print(saida)