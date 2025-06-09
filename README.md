# Calculadora de Matrizes em C++

Esta é uma calculadora de matrizes desenvolvida em C++ que oferece uma interface de linha de comando interativa para realizar diversas operações em diferentes tipos de matrizes. O projeto permite ao usuário gerenciar uma lista de matrizes, realizar cálculos e salvar/carregar matrizes de arquivos.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

*   `main.cpp`: Contém a lógica principal da interface do usuário (menu interativo) e coordena as operações.
*   `Makefile`: Define as regras para compilar o projeto.
*   `Reader/`: Contém as classes responsáveis pela leitura de matrizes de arquivos.
    *   `MatrizReader.hpp`: Declaração da classe `MatrizReader`.
    *   `MatrizReader.cpp`: Implementação da classe `MatrizReader`.
*   `Writer/`: Contém as classes responsáveis pela escrita de matrizes em arquivos.
    *   `MatrizWriter.hpp`: Declaração da classe `MatrizWriter`.
    *   `MatrizWriter.cpp`: Implementação da classe `MatrizWriter`.
*   `matrizes/`: Contém as definições e implementações das diferentes classes de matrizes.
    *   `MatrizGeral.hpp/.cpp`: Classe base para matrizes genéricas.
    *   `MatrizQuadrada/`: Subdiretório para a classe `MatrizQuadrada`.
    *   `MatrizDiagonal/`: Subdiretório para a classe `MatrizDiagonal`.
    *   `MatrizTriangular/`: Subdiretório para as classes `MatrizTriangularSuperior` e `MatrizTriangularInferior`.
*   `matrizes.txt` (ou similar): Arquivo de exemplo para entrada de matrizes. O programa tenta carregar `matrizes_para_leitor.txt` ao iniciar.

## Tipos de Matrizes Suportadas

O sistema suporta os seguintes tipos de matrizes:

*   **MatrizGeral**: Uma matriz padrão com M linhas e N colunas.
*   **MatrizQuadrada**: Uma matriz onde o número de linhas é igual ao número de colunas (N x N). Herda de `MatrizGeral`.
*   **MatrizDiagonal**: Uma matriz quadrada onde todos os elementos fora da diagonal principal são zero. Herda de `MatrizQuadrada`.
*   **MatrizTriangularSuperior**: Uma matriz quadrada onde todos os elementos abaixo da diagonal principal são zero. Herda de `MatrizQuadrada`.
*   **MatrizTriangularInferior**: Uma matriz quadrada onde todos os elementos acima da diagonal principal são zero. Herda de `MatrizQuadrada`.

O programa utiliza polimorfismo para tratar as diferentes especializações de matrizes de forma eficiente.

## Funcionalidades Principais

A calculadora oferece um menu interativo com as seguintes opções:

1.  **Imprimir Matriz(es)**:
    *   Permite visualizar uma matriz específica da lista (pelo seu ID) ou todas as matrizes armazenadas.

2.  **Inserir Nova Matriz**:
    *   **Ler do Teclado**: O usuário fornece as dimensões, o tipo e os elementos da matriz.
    *   **Ler de Arquivo**: Carrega uma matriz de um arquivo de texto (que deve conter apenas uma matriz no formato especificado).

3.  **Inserir Matriz Identidade**:
    *   Cria e adiciona à lista uma matriz identidade de tamanho N x N especificado pelo usuário.

4.  **Alterar ou Remover Matriz(es)**:
    *   **Alterar**: Permite ao usuário preencher novamente os elementos de uma matriz existente na lista, mantendo suas dimensões e tipo originais.
    *   **Remover**: Remove uma matriz da lista usando seu ID.

5.  **Apresentar Lista de Matrizes**:
    *   Exibe um resumo de todas as matrizes atualmente na memória, incluindo ID, dimensões e tipo.

6.  **Gravar Lista de Matrizes (Backup)**:
    *   Salva todas as matrizes da lista atual em um arquivo especificado pelo usuário. (Nota: A implementação em `MatrizWriter.cpp` pode precisar ser completada/verificada).

7.  **Carregar Outra Lista de Matrizes**:
    *   Lê matrizes de um arquivo e permite:
        *   Acrescentar as novas matrizes à lista existente.
        *   Substituir a lista existente pelas novas matrizes.

8.  **Zerar Lista de Matrizes**:
    *   Remove todas las matrizes da memória.

9.  **Realizar Operações com Matrizes**:
    *   Permite realizar as seguintes operações:
        *   **Soma (+)**: Soma de duas matrizes compatíveis.
        *   **Subtração (-)**: Subtração de duas matrizes compatíveis.
        *   **Multiplicação por Escalar (* escalar)**: Multiplica uma matriz por um número.
        *   **Transposição (T)**: Calcula a transposta de uma matriz. O tipo da matriz resultante pode mudar (ex: transposta de Triangular Superior é Triangular Inferior).
        *   **Multiplicação de Matrizes (A * B)**: Multiplica duas matrizes compatíveis.
    *   O resultado de uma operação pode ser salvo na lista de matrizes.

## Formato de Arquivo para Entrada/Saída

As classes `MatrizReader` e `MatrizWriter` utilizam um formato de texto simples para armazenar e carregar matrizes. Um arquivo pode conter múltiplas matrizes.

O formato para cada matriz é o seguinte:

1.  **Tipo da Matriz**: Uma string indicando o tipo (ex: `GERAL`, `QUADRADA`, `DIAGONAL`, `TRIANGULAR_SUPERIOR`, `TRIANGULAR_INFERIOR`).
2.  **Dimensões**: Dois inteiros na mesma linha, separados por espaço, representando o número de LINHAS e COLUNAS.
3.  **Dados da Matriz**:
    *   Para `GERAL`, `QUADRADA`, `TRIANGULAR_SUPERIOR`, `TRIANGULAR_INFERIOR`: Cada linha da matriz é representada por uma linha no arquivo, com elementos separados por espaços.
    *   Para `DIAGONAL`: Apenas os elementos da diagonal principal são listados, um por linha (ou todos na mesma linha, dependendo da implementação exata do `MatrizReader` para este caso específico ao ler – a escrita padrão do `MatrizWriter` provavelmente salvará o formato completo).

**Exemplo de Arquivo (`matrizes.txt`):**

```
GERAL
2 3
1.0 2.5 3.0
4.0 5.0 6.5
QUADRADA
2 2
10.0 0.0
0.0 20.0
DIAGONAL
3 3
1.0 0.0 0.0
0.0 2.0 0.0
0.0 0.0 3.0
TRIANGULAR_SUPERIOR
2 2
5.0 6.0
0.0 7.0
```

**Nota:** Ao ler do teclado, para matrizes especializadas (Diagonal, Triangular), o usuário deve inserir os zeros conforme necessário, ou o sistema pode corrigi-los ou lançar um erro se um valor não zero for colocado em uma posição que deveria ser zero.

## Como Compilar o Projeto

O projeto utiliza um `Makefile` para facilitar a compilação. Certifique-se de ter um compilador C++ (como g++) e o utilitário `make` instalados em seu sistema.

1.  **Clone o repositório** (se ainda não o fez):
    ```bash
    git clone <url_do_repositorio>
    cd <diretorio_do_projeto>
    ```

2.  **Compile o projeto**:
    Navegue até o diretório raiz do projeto (onde o `Makefile` está localizado) e execute o comando:
    ```bash
    make
    ```
    Isso compilará todos os arquivos fonte e gerará o executável `calculadora_matrizes` (ou o nome definido no `Makefile`).

3.  **Para limpar os arquivos de compilação** (arquivos objeto e o executável):
    ```bash
    make clean
    ```

## Como Usar

Após a compilação bem-sucedida, um executável chamado `calculadora_matrizes` será criado no diretório raiz do projeto.

1.  **Execute a calculadora**:
    ```bash
    ./calculadora_matrizes
    ```

2.  **Interface do Menu**:
    *   Ao iniciar, o programa tentará carregar matrizes de um arquivo padrão (ex: `matrizes_para_leitor.txt`).
    *   Você será apresentado a um menu principal com opções numeradas.
    *   Digite o número da opção desejada e pressione Enter.
    *   Siga as instruções na tela para cada operação (ex: fornecer IDs de matrizes, valores escalares, nomes de arquivos, etc.).
    *   A opção `0` geralmente é usada para sair do menu atual ou do programa.

**Exemplo de Interação Inicial:**

```
Tentando carregar matrizes de 'matrizes_para_leitor.txt'...
X matrizes carregadas inicialmente.

--- Menu Principal da Calculadora de Matrizes ---
1. Imprimir matriz(es)
2. Inserir nova matriz
3. Inserir matriz identidade
4. Alterar ou remover matriz(es)
5. Apresentar lista de matrizes (IDs e tipos)
6. Gravar lista de matrizes (Backup)
7. Carregar outra lista de matrizes
8. Zerar lista de matrizes
9. Realizar Operações com Matrizes
0. Sair
Escolha uma opção:
```

## Possíveis Melhorias Futuras

*   **Validação de Entrada Aprimorada**: Implementar verificações mais robustas para todas as entradas do usuário.
*   **Conclusão do `MatrizWriter`**: Garantir que a funcionalidade de salvar a lista de matrizes (`MatrizWriter::gravarMatrizes`) esteja totalmente implementada e testada, especialmente para todos os tipos de matrizes e formatos.
*   **Mais Operações**: Adicionar outras operações de matrizes, como cálculo de determinante, inversa (para matrizes invertíveis), resolução de sistemas lineares, etc.
*   **Testes Unitários**: Desenvolver um conjunto de testes unitários para cada classe e funcionalidade para garantir a corretude e facilitar a manutenção.
*   **Interface Gráfica (GUI)**: Para uma experiência de usuário mais amigável, uma interface gráfica poderia ser desenvolvida.
*   **Tratamento de Erros Detalhado**: Melhorar as mensagens de erro para serem mais específicas e úteis para o usuário.
*   **Documentação do Código**: Adicionar comentários Doxygen ou similar para gerar documentação diretamente do código fonte.
