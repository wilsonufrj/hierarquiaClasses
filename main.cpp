#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "./matrizes/MatrizDiagonal/MatrizDiagonal.hpp"
#include "./matrizes/MatrizGeral.hpp"
#include "./matrizes/MatrizQuadrada/MatrizQuadrada.hpp"
#include "./matrizes/MatrizTriangular/MatrizTriangularInferior.hpp"
#include "./matrizes/MatrizTriangular/MatrizTriangularSuperior.hpp"
#include "Reader/MatrizReader.hpp"
#include "Writer/MatrizWriter.hpp"

void limparBuffer() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void imprimirMatriz(const MatrizGeral& m, const std::string& nome = "Matriz") {
  std::cout << "\n--- " << nome << " (" << m.getLinhas() << "x"
            << m.getColunas() << ") ---" << std::endl;
  for (int i = 0; i < m.getLinhas(); ++i) {
    for (int j = 0; j < m.getColunas(); ++j) {
      std::cout.width(10);
      std::cout << std::fixed << std::setprecision(2) << m.get(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "------------------------------------------" << std::endl;
}

void apresentarListaMatrizes(
    const std::vector<std::unique_ptr<MatrizGeral>>& lista) {
  if (lista.empty()) {
    std::cout << "\nNenhuma matriz na lista." << std::endl;
    return;
  }
  std::cout << "\n--- Lista de Matrizes Armazenadas ---" << std::endl;
  for (size_t i = 0; i < lista.size(); ++i) {
    std::cout << "ID: " << i << " | ";
    std::cout << "Dimensões: " << lista[i]->getLinhas() << "x"
              << lista[i]->getColunas() << " | ";

    if (dynamic_cast<MatrizDiagonal*>(lista[i].get())) {
      std::cout << "Tipo: DIAGONAL";
    } else if (dynamic_cast<MatrizTriangularSuperior*>(lista[i].get())) {
      std::cout << "Tipo: TRIANGULAR SUPERIOR";
    } else if (dynamic_cast<MatrizTriangularInferior*>(lista[i].get())) {
      std::cout << "Tipo: TRIANGULAR INFERIOR";
    } else if (dynamic_cast<MatrizQuadrada*>(lista[i].get())) {
      std::cout << "Tipo: QUADRADA";
    } else {
      std::cout << "Tipo: GERAL";
    }
    std::cout << std::endl;
  }
  std::cout << "-------------------------------------\n" << std::endl;
}

std::unique_ptr<MatrizGeral> lerMatrizDoTeclado() {
  int linhas, colunas;
  std::string tipoStr;
  std::cout << "Digite o número de linhas: ";
  while (!(std::cin >> linhas) || linhas <= 0) {
    std::cout << "Entrada inválida. Digite um número positivo para linhas: ";
    std::cin.clear();
    limparBuffer();
  }
  std::cout << "Digite o número de colunas: ";
  while (!(std::cin >> colunas) || colunas <= 0) {
    std::cout << "Entrada inválida. Digite um número positivo para colunas: ";
    std::cin.clear();
    limparBuffer();
  }
  limparBuffer();

  std::cout << "Digite o tipo da matriz (GERAL, QUADRADA, DIAGONAL, "
               "TRIANGULAR_SUPERIOR, TRIANGULAR_INFERIOR): ";
  std::getline(std::cin, tipoStr);

  for (char& c : tipoStr) c = std::toupper(c);

  std::unique_ptr<MatrizGeral> novaMatriz = nullptr;
  try {
    if (tipoStr == "GERAL") {
      novaMatriz = std::make_unique<MatrizGeral>(linhas, colunas);
    } else if (tipoStr == "QUADRADA") {
      if (linhas != colunas)
        throw std::invalid_argument(
            "Matriz Quadrada deve ter o mesmo número de linhas e colunas.");
      novaMatriz = std::make_unique<MatrizQuadrada>(linhas);
    } else if (tipoStr == "DIAGONAL") {
      if (linhas != colunas)
        throw std::invalid_argument("Matriz Diagonal deve ser quadrada.");
      novaMatriz = std::make_unique<MatrizDiagonal>(linhas);
    } else if (tipoStr == "TRIANGULAR_SUPERIOR") {
      if (linhas != colunas)
        throw std::invalid_argument(
            "Matriz Triangular Superior deve ser quadrada.");
      novaMatriz = std::make_unique<MatrizTriangularSuperior>(linhas);
    } else if (tipoStr == "TRIANGULAR_INFERIOR") {
      if (linhas != colunas)
        throw std::invalid_argument(
            "Matriz Triangular Inferior deve ser quadrada.");
      novaMatriz = std::make_unique<MatrizTriangularInferior>(linhas);
    } else {
      std::cout << "Tipo de matriz inválido. Criando MatrizGeral por padrão."
                << std::endl;
      novaMatriz = std::make_unique<MatrizGeral>(linhas, colunas);
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "Erro ao criar matriz: " << e.what() << std::endl;
    return nullptr;
  }

  if (!novaMatriz) {
    std::cerr << "Erro desconhecido ao criar matriz. Retornando nulo."
              << std::endl;
    return nullptr;
  }

  std::cout << "Digite os elementos da matriz (" << linhas << "x" << colunas
            << "):" << std::endl;
  std::cout << "Para " << tipoStr
            << " preencha os zeros necessários ou o sistema pode lançar um "
               "erro ou sobrescrevê-los para o tipo correto."
            << std::endl;
  for (int i = 0; i < linhas; ++i) {
    std::cout << "Linha " << i + 1 << ": ";
    for (int j = 0; j < colunas; ++j) {
      double valor;
      while (!(std::cin >> valor)) {
        std::cout << "Entrada inválida. Digite um número para o elemento ("
                  << i + 1 << "," << j + 1 << "): ";
        std::cin.clear();
        limparBuffer();
      }
      try {
        novaMatriz->set(i, j, valor);
      } catch (const std::invalid_argument& e) {
        std::cout << "Aviso: " << e.what() << " Elemento (" << i + 1 << ","
                  << j + 1 << ") será mantido como 0." << std::endl;
      } catch (const std::out_of_range& e) {
        std::cerr << "Erro fatal de índice ao definir elemento: " << e.what()
                  << std::endl;
        return nullptr;
      }
    }
  }
  limparBuffer();

  return novaMatriz;
}

std::unique_ptr<MatrizGeral> inserirMatrizIdentidade() {
  int tamanho;
  std::cout << "Digite o tamanho (n) da matriz identidade (n x n): ";
  while (!(std::cin >> tamanho) || tamanho <= 0) {
    std::cout << "Entrada inválida. Digite um número inteiro positivo: ";
    std::cin.clear();
    limparBuffer();
  }
  limparBuffer();

  std::unique_ptr<MatrizGeral> identidade =
      std::make_unique<MatrizQuadrada>(tamanho);
  for (int i = 0; i < tamanho; ++i) {
    identidade->set(i, i, 1.0);
  }
  std::cout << "Matriz Identidade " << tamanho << "x" << tamanho
            << " criada com sucesso." << std::endl;
  return identidade;
}

void realizarOperacoes(std::vector<std::unique_ptr<MatrizGeral>>& lista) {
  if (lista.empty()) {
    std::cout << "A lista de matrizes está vazia. Insira matrizes primeiro."
              << std::endl;
    return;
  }

  apresentarListaMatrizes(lista);

  std::cout << "\n--- Operações com Matrizes ---" << std::endl;
  std::cout << "Selecione o tipo de operação:\n";
  std::cout << "1. Soma (+)\n";
  std::cout << "2. Subtração (-)\n";
  std::cout << "3. Multiplicação por Escalar (* escalar)\n";
  std::cout << "4. Transposição (T)\n";
  std::cout << "5. Multiplicação de Matrizes (A * B)\n";  // NOVA OPÇÃO
  std::cout << "0. Voltar ao menu principal\n";
  std::cout << "Escolha uma opção: ";

  int escolhaOperacao;
  while (!(std::cin >> escolhaOperacao) || escolhaOperacao < 0 ||
         escolhaOperacao > 5) {  // Ajuste o > para o número máximo de opções
    std::cout << "Opção inválida. Escolha entre 0 e 5: ";
    std::cin.clear();
    limparBuffer();
  }
  limparBuffer();

  if (escolhaOperacao == 0) return;

  size_t idMatriz1, idMatriz2;

  if (escolhaOperacao == 4) {
    std::cout << "Digite o ID da matriz para transpor: ";
    while (!(std::cin >> idMatriz1) || idMatriz1 >= lista.size()) {
      std::cout << "ID inválido. Digite um ID existente: ";
      std::cin.clear();
      limparBuffer();
    }
    limparBuffer();

    try {
      std::unique_ptr<MatrizGeral> resultado;
      // Para transpor, precisamos de dynamic_cast para chamar o método
      // específico
      if (MatrizDiagonal* md =
              dynamic_cast<MatrizDiagonal*>(lista[idMatriz1].get())) {
        resultado = std::make_unique<MatrizDiagonal>(md->transposta());
      } else if (MatrizTriangularSuperior* mts =
                     dynamic_cast<MatrizTriangularSuperior*>(
                         lista[idMatriz1].get())) {
        // A transposta de uma TriangularSuperior é uma TriangularInferior
        resultado =
            std::make_unique<MatrizTriangularInferior>(mts->transposta());
      } else if (MatrizTriangularInferior* mti =
                     dynamic_cast<MatrizTriangularInferior*>(
                         lista[idMatriz1].get())) {
        // A transposta de uma TriangularInferior é uma TriangularSuperior
        resultado =
            std::make_unique<MatrizTriangularSuperior>(mti->transposta());
      } else {  // MatrizGeral ou MatrizQuadrada
        resultado =
            std::make_unique<MatrizGeral>(lista[idMatriz1]->transposta());
      }

      imprimirMatriz(*resultado,
                     "Transposta da Matriz " + std::to_string(idMatriz1));
      std::cout << "Deseja salvar a matriz transposta na lista? (s/n): ";
      char opcaoSalvar;
      std::cin >> opcaoSalvar;
      limparBuffer();
      if (std::tolower(opcaoSalvar) == 's') {
        lista.push_back(std::move(resultado));
        std::cout << "Matriz transposta salva com sucesso. Novo ID: "
                  << lista.size() - 1 << std::endl;
      }
    } catch (const std::exception& e) {
      std::cerr << "Erro ao transpor matriz: " << e.what() << std::endl;
    }

  } else {  // Operações binárias (+, -, *)
    std::cout << "Digite o ID da primeira matriz: ";
    while (!(std::cin >> idMatriz1) || idMatriz1 >= lista.size()) {
      std::cout << "ID inválido. Digite um ID existente: ";
      std::cin.clear();
      limparBuffer();
    }
    limparBuffer();

    if (escolhaOperacao == 3) {  // Multiplicação por Escalar
      double escalar;
      std::cout << "Digite o valor do escalar: ";
      while (!(std::cin >> escalar)) {
        std::cout << "Entrada inválida. Digite um número: ";
        std::cin.clear();
        limparBuffer();
      }
      limparBuffer();

      try {
        // Para multiplicação por escalar, podemos usar o operador da
        // MatrizGeral (se definido) ou o operador específico de cada subtipo se
        // quisermos manter a classe do resultado
        std::unique_ptr<MatrizGeral> resultado;

        if (MatrizDiagonal* md =
                dynamic_cast<MatrizDiagonal*>(lista[idMatriz1].get())) {
          resultado = std::make_unique<MatrizDiagonal>(*md * escalar);
        } else if (MatrizTriangularSuperior* mts =
                       dynamic_cast<MatrizTriangularSuperior*>(
                           lista[idMatriz1].get())) {
          resultado =
              std::make_unique<MatrizTriangularSuperior>(*mts * escalar);
        } else if (MatrizTriangularInferior* mti =
                       dynamic_cast<MatrizTriangularInferior*>(
                           lista[idMatriz1].get())) {
          resultado =
              std::make_unique<MatrizTriangularInferior>(*mti * escalar);
        } else {  // MatrizGeral ou MatrizQuadrada (assumindo operator* em
                  // MatrizGeral)
          // Se você não tem operator* em MatrizGeral, precisaria de uma
          // implementação aqui ou de uma função auxiliar que opere no tipo
          // base.
          resultado =
              std::make_unique<MatrizGeral>(*lista[idMatriz1] * escalar);
        }

        imprimirMatriz(*resultado, "Resultado da Multiplicação por Escalar");
        std::cout << "Deseja salvar a matriz resultante na lista? (s/n): ";
        char opcaoSalvar;
        std::cin >> opcaoSalvar;
        limparBuffer();
        if (std::tolower(opcaoSalvar) == 's') {
          lista.push_back(std::move(resultado));
          std::cout << "Matriz resultante salva com sucesso. Novo ID: "
                    << lista.size() - 1 << std::endl;
        }
      } catch (const std::exception& e) {
        std::cerr << "Erro ao multiplicar por escalar: " << e.what()
                  << std::endl;
      }
    }
    if (escolhaOperacao == 5) {
      std::cout << "Digite o ID da primeira matriz (A): ";
      while (!(std::cin >> idMatriz1) || idMatriz1 >= lista.size()) {
        std::cout << "ID inválido. Digite um ID existente: ";
        std::cin.clear();
        limparBuffer();
      }
      limparBuffer();

      std::cout << "Digite o ID da segunda matriz (B): ";
      while (!(std::cin >> idMatriz2) || idMatriz2 >= lista.size()) {
        std::cout << "ID inválido. Digite um ID existente: ";
        std::cin.clear();
        limparBuffer();
      }
      limparBuffer();

      try {
        // Chama o operador de multiplicação da MatrizGeral
        std::unique_ptr<MatrizGeral> resultado = std::make_unique<MatrizGeral>(
            *lista[idMatriz1] * *lista[idMatriz2]);
        imprimirMatriz(*resultado,
                       "Resultado da Multiplicação de Matrizes (A * B)");
        std::cout << "Deseja salvar a matriz resultante na lista? (s/n): ";
        char opcaoSalvar;
        std::cin >> opcaoSalvar;
        limparBuffer();
        if (std::tolower(opcaoSalvar) == 's') {
          lista.push_back(std::move(resultado));
          std::cout << "Matriz resultante salva com sucesso. Novo ID: "
                    << lista.size() - 1 << std::endl;
        }
      } catch (const std::exception& e) {
        std::cerr << "Erro ao multiplicar matrizes: " << e.what() << std::endl;
      }
    } else {  // Soma ou Subtração
      std::cout << "Digite o ID da segunda matriz: ";
      while (!(std::cin >> idMatriz2) || idMatriz2 >= lista.size()) {
        std::cout << "ID inválido. Digite um ID existente: ";
        std::cin.clear();
        limparBuffer();
      }
      limparBuffer();

      // Verificação de compatibilidade de tipos e tamanhos
      if (lista[idMatriz1]->getLinhas() != lista[idMatriz2]->getLinhas() ||
          lista[idMatriz1]->getColunas() != lista[idMatriz2]->getColunas()) {
        std::cerr << "Erro: Matrizes de tamanhos diferentes não podem ser "
                     "somadas/subtraídas."
                  << std::endl;
        return;
      }

      // Tentativa de operação específica do tipo, ou fallback para MatrizGeral
      std::unique_ptr<MatrizGeral> resultado = nullptr;
      try {
        if (MatrizDiagonal* md1 =
                dynamic_cast<MatrizDiagonal*>(lista[idMatriz1].get())) {
          if (MatrizDiagonal* md2 =
                  dynamic_cast<MatrizDiagonal*>(lista[idMatriz2].get())) {
            resultado = (escolhaOperacao == 1)
                            ? std::make_unique<MatrizDiagonal>(*md1 + *md2)
                            : std::make_unique<MatrizDiagonal>(*md1 - *md2);
          }
        } else if (MatrizTriangularSuperior* mts1 =
                       dynamic_cast<MatrizTriangularSuperior*>(
                           lista[idMatriz1].get())) {
          if (MatrizTriangularSuperior* mts2 =
                  dynamic_cast<MatrizTriangularSuperior*>(
                      lista[idMatriz2].get())) {
            resultado =
                (escolhaOperacao == 1)
                    ? std::make_unique<MatrizTriangularSuperior>(*mts1 + *mts2)
                    : std::make_unique<MatrizTriangularSuperior>(*mts1 - *mts2);
          }
        } else if (MatrizTriangularInferior* mti1 =
                       dynamic_cast<MatrizTriangularInferior*>(
                           lista[idMatriz1].get())) {
          if (MatrizTriangularInferior* mti2 =
                  dynamic_cast<MatrizTriangularInferior*>(
                      lista[idMatriz2].get())) {
            resultado =
                (escolhaOperacao == 1)
                    ? std::make_unique<MatrizTriangularInferior>(*mti1 + *mti2)
                    : std::make_unique<MatrizTriangularInferior>(*mti1 - *mti2);
          }
        }

        // Se não foi possível operar como tipo específico, tenta como
        // MatrizGeral
        if (!resultado) {
          // TO-DO: Você precisaria de operadores '+' e '-' em MatrizGeral para
          // isso funcionar ou uma função auxiliar que opere em MatrizGeral* Por
          // enquanto, vamos lançar um erro ou assumir que MatrizGeral tem esses
          // operadores. Supondo que você tem operator+ e operator- na
          // MatrizGeral:
          if (escolhaOperacao == 1) {
            resultado = std::make_unique<MatrizGeral>(*lista[idMatriz1] +
                                                      *lista[idMatriz2]);
          } else {  // escolhaOperacao == 2
            resultado = std::make_unique<MatrizGeral>(*lista[idMatriz1] -
                                                      *lista[idMatriz2]);
          }
          std::cout << "Operação realizada como MatrizGeral." << std::endl;
        }

        imprimirMatriz(*resultado,
                       (escolhaOperacao == 1 ? "Soma" : "Subtração") +
                           std::string(" das Matrizes"));
        std::cout << "Deseja salvar a matriz resultante na lista? (s/n): ";
        char opcaoSalvar;
        std::cin >> opcaoSalvar;
        limparBuffer();
        if (std::tolower(opcaoSalvar) == 's') {
          lista.push_back(std::move(resultado));
          std::cout << "Matriz resultante salva com sucesso. Novo ID: "
                    << lista.size() - 1 << std::endl;
        }

      } catch (const std::exception& e) {
        std::cerr << "Erro durante a operação de matriz: " << e.what()
                  << std::endl;
      }
    }
  }
}

// --- Funções de Manipulação da Lista ---
// (Implementações parciais ou placeholders)

// 1. Imprimir uma, ou mais, matrizes da lista.
void imprimirMatrizes(const std::vector<std::unique_ptr<MatrizGeral>>& lista) {
  if (lista.empty()) {
    std::cout << "A lista de matrizes está vazia." << std::endl;
    return;
  }
  std::cout << "\n--- Imprimir Matrizes ---" << std::endl;
  apresentarListaMatrizes(lista);
  std::cout << "Digite o ID da matriz que deseja imprimir (ou -1 para imprimir "
               "todas): ";
  int id;
  while (!(std::cin >> id) || (id < -1) ||
         (id >= static_cast<int>(lista.size()))) {
    std::cout << "ID inválido. Digite um ID existente ou -1: ";
    std::cin.clear();
    limparBuffer();
  }
  limparBuffer();

  if (id == -1) {
    for (size_t i = 0; i < lista.size(); ++i) {
      imprimirMatriz(*lista[i], "Matriz " + std::to_string(i));
    }
  } else {
    imprimirMatriz(*lista[id], "Matriz " + std::to_string(id));
  }
}

// 2. Inserir uma nova matriz lida do teclado ou de um arquivo que contenha
// somente uma matriz.
void inserirNovaMatriz(std::vector<std::unique_ptr<MatrizGeral>>& lista) {
  std::cout << "\n--- Inserir Nova Matriz ---" << std::endl;
  std::cout << "1. Ler do teclado\n";
  std::cout << "2. Ler de arquivo (contém apenas uma matriz)\n";
  std::cout << "0. Voltar\n";
  std::cout << "Escolha uma opção: ";
  int escolha;
  while (!(std::cin >> escolha) || escolha < 0 || escolha > 2) {
    std::cout << "Opção inválida. Escolha entre 0 e 2: ";
    std::cin.clear();
    limparBuffer();
  }
  limparBuffer();

  if (escolha == 1) {
    std::unique_ptr<MatrizGeral> novaMatriz = lerMatrizDoTeclado();
    if (novaMatriz) {
      lista.push_back(std::move(novaMatriz));
      std::cout << "Matriz inserida com sucesso! Novo ID: " << lista.size() - 1
                << std::endl;
    } else {
      std::cout << "Falha ao ler matriz do teclado." << std::endl;
    }
  } else if (escolha == 2) {
    std::cout << "Digite o nome do arquivo (ex: 'minha_matriz.txt'): ";
    std::string nomeArquivo;
    std::getline(std::cin, nomeArquivo);

    // O MatrizReader lê UMA lista de matrizes. Para ler APENAS UMA,
    // precisaríamos adaptar o MatrizReader ou criar uma função específica.
    // Por simplicidade aqui, vamos criar uma lista temporária e pegar a
    // primeira.
    std::vector<std::unique_ptr<MatrizGeral>> tempLista =
        MatrizReader::lerMatrizesDoArquivo(nomeArquivo);
    if (!tempLista.empty()) {
      if (tempLista.size() > 1) {
        std::cout << "Aviso: O arquivo continha mais de uma matriz. Apenas a "
                     "primeira será adicionada."
                  << std::endl;
      }
      lista.push_back(std::move(tempLista[0]));
      std::cout << "Matriz do arquivo inserida com sucesso! Novo ID: "
                << lista.size() - 1 << std::endl;
    } else {
      std::cout << "Falha ao ler matriz do arquivo ou o arquivo está vazio/mal "
                   "formatado."
                << std::endl;
    }
  }
}

// 3. Inserir uma matriz identidade n x n.
// Já implementado como `inserirMatrizIdentidade()` e chamada no main.

// 4. Alterar ou remover uma, ou mais matrizes da lista.
void alterarRemoverMatrizes(std::vector<std::unique_ptr<MatrizGeral>>& lista) {
  if (lista.empty()) {
    std::cout << "A lista de matrizes está vazia." << std::endl;
    return;
  }
  std::cout << "\n--- Alterar ou Remover Matrizes ---" << std::endl;
  apresentarListaMatrizes(lista);
  std::cout << "1. Alterar uma matriz (preencher novamente)\n";
  std::cout << "2. Remover uma matriz\n";
  std::cout << "0. Voltar\n";
  std::cout << "Escolha uma opção: ";
  int escolha;
  while (!(std::cin >> escolha) || escolha < 0 || escolha > 2) {
    std::cout << "Opção inválida. Escolha entre 0 e 2: ";
    std::cin.clear();
    limparBuffer();
  }
  limparBuffer();

  if (escolha == 0) return;

  size_t id;  // Usar size_t para IDs de vetor
  std::cout << "Digite o ID da matriz: ";
  while (!(std::cin >> id) || id >= lista.size()) {
    std::cout << "ID inválido. Digite um ID existente: ";
    std::cin.clear();
    limparBuffer();
  }
  limparBuffer();

  if (escolha == 1) {  // Alterar
    std::cout << "ATENÇÃO: Você irá preencher a matriz ID " << id
              << " novamente." << std::endl;
    std::cout << "Tipo original: ";
    if (dynamic_cast<MatrizDiagonal*>(lista[id].get()))
      std::cout << "DIAGONAL";
    else if (dynamic_cast<MatrizTriangularSuperior*>(lista[id].get()))
      std::cout << "TRIANGULAR SUPERIOR";
    else if (dynamic_cast<MatrizTriangularInferior*>(lista[id].get()))
      std::cout << "TRIANGULAR INFERIOR";
    else if (dynamic_cast<MatrizQuadrada*>(lista[id].get()))
      std::cout << "QUADRADA";
    else
      std::cout << "GERAL";
    std::cout << " (" << lista[id]->getLinhas() << "x"
              << lista[id]->getColunas() << ")\n";

    std::cout << "Deseja realmente alterar? (s/n): ";
    char confirm;
    std::cin >> confirm;
    limparBuffer();
    if (std::tolower(confirm) == 's') {
      std::unique_ptr<MatrizGeral> novaVersao = lerMatrizDoTeclado();
      if (novaVersao && novaVersao->getLinhas() == lista[id]->getLinhas() &&
          novaVersao->getColunas() == lista[id]->getColunas()) {
        lista[id] = std::move(novaVersao);  // Substitui a matriz existente
        std::cout << "Matriz ID " << id << " alterada com sucesso."
                  << std::endl;
      } else if (novaVersao) {
        std::cerr << "Erro: As novas dimensões da matriz devem ser as mesmas "
                     "para alteração direta."
                  << std::endl;
        std::cerr << "Sugestão: Remova a antiga e insira uma nova."
                  << std::endl;
      } else {
        std::cerr << "Falha ao ler nova versão da matriz." << std::endl;
      }
    } else {
      std::cout << "Alteração cancelada." << std::endl;
    }

  } else if (escolha == 2) {  // Remover
    std::cout << "Deseja realmente remover a matriz ID " << id << "? (s/n): ";
    char confirm;
    std::cin >> confirm;
    limparBuffer();
    if (std::tolower(confirm) == 's') {
      lista.erase(lista.begin() + id);
      std::cout << "Matriz ID " << id << " removida com sucesso." << std::endl;
      // Os IDs das matrizes subsequentes serão ajustados automaticamente
    } else {
      std::cout << "Remoção cancelada." << std::endl;
    }
  }
}

// 6. Gravar a lista com um nome diferente (backup).
// Esta função exigirá uma nova classe MatrizWriter.hpp/cpp
// Placeholder:
// class MatrizWriter {
// public:
//     static bool gravarMatrizes(const std::string& nomeArquivo, const
//     std::vector<std::unique_ptr<MatrizGeral>>& lista);
// };
void gravarListaMatrizes(
    const std::vector<std::unique_ptr<MatrizGeral>>& lista) {
  if (lista.empty()) {
    std::cout << "A lista de matrizes está vazia. Nada para gravar."
              << std::endl;
    return;
  }
  std::cout << "Digite o nome do arquivo para salvar a lista (ex: "
               "'backup_matrizes.txt'): ";
  std::string nomeArquivo;
  std::getline(std::cin, nomeArquivo);

  // TO-DO: Implementar MatrizWriter::gravarMatrizes
  // if (MatrizWriter::gravarMatrizes(nomeArquivo, lista)) {
  //     std::cout << "Lista de matrizes salva com sucesso em '" << nomeArquivo
  //     << "'." << std::endl;
  // } else {
  //     std::cerr << "Erro ao salvar a lista de matrizes." << std::endl;
  // }
  std::cout << "Funcionalidade de gravação ainda não implementada. (TO-DO: "
               "MatrizWriter)"
            << std::endl;
}

// 7. Ler uma outra lista de matrizes, acrescentando à lista existente, ou a
// substituindo.
void carregarOutraListaMatrizes(
    std::vector<std::unique_ptr<MatrizGeral>>& lista) {
  std::cout << "\n--- Carregar Outra Lista de Matrizes ---" << std::endl;
  std::cout << "Digite o nome do arquivo para carregar a lista (ex: "
               "'novas_matrizes.txt'): ";
  std::string nomeArquivo;
  std::getline(std::cin, nomeArquivo);

  std::vector<std::unique_ptr<MatrizGeral>> novasMatrizes =
      MatrizReader::lerMatrizesDoArquivo(nomeArquivo);

  if (novasMatrizes.empty()) {
    std::cout << "Nenhuma matriz foi lida do arquivo ou ocorreu um erro."
              << std::endl;
    return;
  }

  std::cout << "Deseja: \n";
  std::cout << "1. Acrescentar à lista existente\n";
  std::cout << "2. Substituir a lista existente\n";
  std::cout << "0. Voltar\n";
  std::cout << "Escolha uma opção: ";
  int escolha;
  while (!(std::cin >> escolha) || escolha < 0 || escolha > 2) {
    std::cout << "Opção inválida. Escolha entre 0 e 2: ";
    std::cin.clear();
    limparBuffer();
  }
  limparBuffer();

  if (escolha == 1) {  // Acrescentar
    for (auto& matriz : novasMatrizes) {
      lista.push_back(std::move(matriz));
    }
    std::cout << novasMatrizes.size()
              << " matrizes adicionadas à lista existente." << std::endl;
  } else if (escolha == 2) {           // Substituir
    lista.clear();                     // Limpa a lista atual
    lista = std::move(novasMatrizes);  // Move as novas matrizes
    std::cout << lista.size() << " matrizes substituíram a lista existente."
              << std::endl;
  } else {
    std::cout << "Operação de carregamento cancelada." << std::endl;
  }
}

// 8. Zerar a lista de matrizes.
void zerarListaMatrizes(std::vector<std::unique_ptr<MatrizGeral>>& lista) {
  std::cout << "\n--- Zerar Lista de Matrizes ---" << std::endl;
  if (lista.empty()) {
    std::cout << "A lista já está vazia." << std::endl;
    return;
  }
  std::cout << "Deseja realmente zerar a lista de matrizes? (s/n): ";
  char confirm;
  std::cin >> confirm;
  limparBuffer();
  if (std::tolower(confirm) == 's') {
    lista.clear();
    std::cout << "Lista de matrizes zerada com sucesso." << std::endl;
  } else {
    std::cout << "Operação cancelada." << std::endl;
  }
}

// --- Função Principal (Main) ---

int main() {
  // Lista para armazenar as matrizes
  std::vector<std::unique_ptr<MatrizGeral>> listaDeMatrizes;

  // Carregar matrizes iniciais de um arquivo (se existir)
  std::cout << "Tentando carregar matrizes de 'matrizes_para_leitor.txt'..."
            << std::endl;
  listaDeMatrizes =
      MatrizReader::lerMatrizesDoArquivo("matrizes_para_leitor.txt");
  std::cout << listaDeMatrizes.size() << " matrizes carregadas inicialmente."
            << std::endl;

  int escolha;
  do {
    std::cout << "\n--- Menu Principal da Calculadora de Matrizes ---"
              << std::endl;
    std::cout << "1. Imprimir matriz(es)\n";
    std::cout << "2. Inserir nova matriz\n";
    std::cout << "3. Inserir matriz identidade\n";
    std::cout << "4. Alterar ou remover matriz(es)\n";
    std::cout << "5. Apresentar lista de matrizes (IDs e tipos)\n";
    std::cout << "6. Gravar lista de matrizes (Backup)\n";
    std::cout << "7. Carregar outra lista de matrizes\n";
    std::cout << "8. Zerar lista de matrizes\n";
    std::cout << "9. Realizar Operações com Matrizes\n";
    std::cout << "0. Sair\n";
    std::cout << "Escolha uma opção: ";

    while (!(std::cin >> escolha) || escolha < 0 || escolha > 9) {
      std::cout << "Opção inválida. Escolha entre 0 e 9: ";
      std::cin.clear();
      limparBuffer();
    }
    limparBuffer();

    switch (escolha) {
      case 1:
        imprimirMatrizes(listaDeMatrizes);
        break;
      case 2:
        inserirNovaMatriz(listaDeMatrizes);
        break;
      case 3: {
        std::unique_ptr<MatrizGeral> idMatriz = inserirMatrizIdentidade();
        if (idMatriz) {
          listaDeMatrizes.push_back(std::move(idMatriz));
          std::cout << "Matriz identidade adicionada à lista. Novo ID: "
                    << listaDeMatrizes.size() - 1 << std::endl;
        }
        break;
      }
      case 4:
        alterarRemoverMatrizes(listaDeMatrizes);
        break;
      case 5:
        apresentarListaMatrizes(listaDeMatrizes);
        break;
      case 6:
        gravarListaMatrizes(listaDeMatrizes);
        break;
      case 7:
        carregarOutraListaMatrizes(listaDeMatrizes);
        break;
      case 8:
        zerarListaMatrizes(listaDeMatrizes);
        break;
      case 9:
        realizarOperacoes(listaDeMatrizes);
        break;
      case 0:
        std::cout << "Saindo da calculadora de matrizes. Até mais!"
                  << std::endl;
        break;
      default:
        std::cout << "Opção inválida. Tente novamente." << std::endl;
        break;
    }
  } while (escolha != 0);

  return 0;
}