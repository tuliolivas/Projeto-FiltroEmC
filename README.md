# Projeto Filtro em C

Este projeto foi criado como Trabalho final da disciplina Laboratório de Programação e implementa uma rotina em C para processar imagens PGM usando o descritor Local Binary Pattern (LBP), gerar um histograma de intensidade de padrões locais e registrar os resultados em um arquivo CSV.

## Objetivo

O programa percorre imagens armazenadas em um diretório, lê cada arquivo em formato PGM, calcula o histograma LBP da imagem e grava os valores em `Histograma.csv`. O nome do arquivo é usado como rótulo para identificar a amostra processada.

## Como funciona

A execução segue esta sequência:

1. abre o diretório `Colon_TMA/`;
2. ignora as entradas `.` e `..`;
3. lê cada imagem `.pgm`;
4. zera o vetor de histograma;
5. aplica o cálculo LBP pixel a pixel;
6. incrementa as frequências do padrão encontrado;
7. salva o histograma no arquivo CSV;
8. exibe no terminal o nome da imagem e o tempo de processamento.

## Estrutura dos arquivos

- `main.c`: programa principal, responsável por percorrer o diretório e controlar a execução.
- `pj.c`: implementação das funções de leitura da imagem, processamento LBP e escrita do histograma.
- `pj.h`: definições de estruturas, constantes e protótipos das funções.
- `Colon_TMA/`: conjunto de imagens PGM utilizadas como entrada do algoritmo.
- `imagens/`: diretório com outras imagens de suporte.
- `Histograma.csv`: arquivo gerado pela execução do programa.
- `filtro`: binário compilado (quando gerado).

## Requisitos

- compilador GCC;
- ambiente Linux, macOS ou WSL;
- terminal para execução.

## Compilação

No diretório raiz do projeto, execute:

```bash
gcc main.c pj.c -o filtro
```

## Execução

```bash
./filtro
```

Ao executar, o programa vai processar todas as imagens contidas em `Colon_TMA/` e gerar/atualizar o arquivo `Histograma.csv`.

## Observações importantes

- O programa assume que as imagens estão em formato PGM válido.
- A escrita do CSV é feita em modo de anexação (`"a"`), então dados anteriores podem continuar no arquivo.
- Para reiniciar os dados do histograma, remova o arquivo antes de rodar novamente:

```bash
rm -f Histograma.csv
```

## Saída esperada

No terminal, o programa imprime:

- o nome de cada imagem processada;
- o tempo médio por imagem;
- o tempo total de processamento.

## Observação sobre o algoritmo

O LBP compara cada pixel com seus vizinhos em uma vizinhança local e gera um valor binário que representa o padrão visual daquele ponto. O histograma acumulado ao longo da imagem representa a distribuição desses padrões.

