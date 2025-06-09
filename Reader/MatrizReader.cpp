
#include "MatrizReader.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<std::unique_ptr<MatrizGeral>> MatrizReader::lerMatrizesDoArquivo(
    const std::string& nomeArquivo) {
  std::vector<std::unique_ptr<MatrizGeral>> listaDeMatrizes;
  std::ifstream arquivo(nomeArquivo);
  std::string linha;

  if (!arquivo.is_open()) {
    std::cerr << "Erro: Não foi possível abrir o arquivo '" << nomeArquivo
              << "'" << std::endl;
    return listaDeMatrizes;
  }

  std::string tipoMatrizStr;
  int linhas = 0, colunas = 0;
  std::unique_ptr<MatrizGeral> matrizAtual = nullptr;

  while (std::getline(arquivo, linha)) {
    if (linha.empty() || linha[0] == '#') {
      continue;
    }

    size_t first = linha.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) continue;
    size_t last = linha.find_last_not_of(" \t\n\r");
    linha = linha.substr(first, (last - first + 1));

    if (linha.rfind("TIPO:", 0) == 0) {
      tipoMatrizStr = linha.substr(5);
    } else if (linha.rfind("DIM:", 0) == 0) {
      try {
        std::pair<int, int> dim = parseDimensoes(linha.substr(4));
        linhas = dim.first;
        colunas = dim.second;
      } catch (const std::invalid_argument& e) {
        std::cerr << "Erro de parse de dimensão: " << e.what()
                  << ". Pulando matriz." << std::endl;

        tipoMatrizStr.clear();
        linhas = 0;
        colunas = 0;
        continue;
      }
    } else if (linha.rfind("DADOS:", 0) == 0) {
      if (linhas == 0 || colunas == 0 || tipoMatrizStr.empty()) {
        std::cerr << "Erro: Informações de tipo/dimensão faltando antes dos "
                     "dados da matriz. Linha: "
                  << linha << std::endl;
        continue;
      }

      matrizAtual.reset(criarMatrizDoTipo(tipoMatrizStr, linhas, colunas));
      if (!matrizAtual) {
        std::cerr << "Erro: Tipo de matriz desconhecido ou dimensões "
                     "incompatíveis para o tipo '"
                  << tipoMatrizStr << "'. Pulando matriz." << std::endl;
        tipoMatrizStr.clear();
        linhas = 0;
        colunas = 0;
        continue;
      }

      bool dadosLidosComErro = false;
      for (int i = 0; i < linhas; ++i) {
        if (!std::getline(arquivo, linha)) {
          std::cerr << "Erro: Dados insuficientes para a matriz "
                    << tipoMatrizStr << " " << linhas << "x" << colunas
                    << ". Faltam linhas de dados." << std::endl;
          matrizAtual.reset();
          dadosLidosComErro = true;
          break;
        }

        first = linha.find_first_not_of(" \t\n\r");
        if (std::string::npos == first) {
          std::cerr << "Erro: Linha de dados vazia para matriz "
                    << tipoMatrizStr << " na linha " << i + 1 << "."
                    << std::endl;
          matrizAtual.reset();
          dadosLidosComErro = true;
          break;
        }
        last = linha.find_last_not_of(" \t\n\r");
        linha = linha.substr(first, (last - first + 1));

        std::stringstream ss(linha);
        double valor;
        for (int j = 0; j < colunas; ++j) {
          if (!(ss >> valor)) {
            std::cerr << "Erro: Dados mal formatados na linha " << i + 1
                      << ", coluna " << j + 1
                      << " da matriz atual. (Esperava número, encontrou '"
                      << linha << "')" << std::endl;
            matrizAtual.reset();
            dadosLidosComErro = true;
            break;
          }
          try {
            matrizAtual->set(i, j, valor);
          } catch (const std::invalid_argument& e) {
            std::cerr << "Aviso: Tentativa de 'set' inválida para matriz "
                      << tipoMatrizStr << " em (" << i << "," << j << "). "
                      << e.what() << std::endl;

          } catch (const std::out_of_range& e) {
            std::cerr << "Erro de índice ao definir elemento da matriz: "
                      << e.what() << std::endl;
            matrizAtual.reset();
            dadosLidosComErro = true;
            break;
          }
        }
        if (dadosLidosComErro) break;
      }

      if (matrizAtual && !dadosLidosComErro) {
        listaDeMatrizes.push_back(std::move(matrizAtual));
      }
      matrizAtual = nullptr;
      tipoMatrizStr.clear();
      linhas = 0;
      colunas = 0;
    }
  }

  arquivo.close();
  return listaDeMatrizes;
}

std::pair<int, int> MatrizReader::parseDimensoes(const std::string& linhaDim) {
  size_t xPos = linhaDim.find('x');
  if (xPos == std::string::npos) {
    throw std::invalid_argument("Formato de dimensão inválido. Esperado LxW.");
  }
  int l = std::stoi(linhaDim.substr(0, xPos));
  int c = std::stoi(linhaDim.substr(xPos + 1));
  return {l, c};
}

MatrizGeral* MatrizReader::criarMatrizDoTipo(const std::string& tipo,
                                             int linhas, int colunas) {
  // Para tipos de matrizes especiais (Diagonal, Triangular), eles devem ser
  // quadrados.
  if (tipo == "DIAGONAL" || tipo == "TRIANGULAR_SUPERIOR" ||
      tipo == "TRIANGULAR_INFERIOR") {
    if (linhas != colunas) {
      std::cerr << "Aviso: Matriz declarada como '" << tipo
                << "' mas não é quadrada (" << linhas << "x" << colunas
                << "). Não será criada ou pode ser criada como MatrizGeral se "
                   "o tipo for compatível."
                << std::endl;
      return nullptr;  // Matrizes especiais não podem ser não-quadradas.
    }
    if (tipo == "DIAGONAL") {
      return new MatrizDiagonal(linhas);
    } else if (tipo == "TRIANGULAR_SUPERIOR") {
      return new MatrizTriangularSuperior(linhas);
    } else if (tipo == "TRIANGULAR_INFERIOR") {
      return new MatrizTriangularInferior(linhas);
    }
  }
  // Se não é um tipo especial, ou se o tipo especial não é quadrado,
  // verifica se é uma MatrizQuadrada ou MatrizGeral.
  if (tipo == "QUADRADA") {
    if (linhas != colunas) {
      std::cerr << "Aviso: Matriz declarada como QUADRADA mas dimensões não "
                   "são iguais ("
                << linhas << "x" << colunas
                << "). Criando MatrizGeral em vez de MatrizQuadrada."
                << std::endl;
      return new MatrizGeral(linhas,
                             colunas);  // Ainda pode ser uma MatrizGeral
    }
    return new MatrizQuadrada(linhas);
  } else if (tipo == "GERAL" || tipo.empty()) {  // Um tipo "GERAL" explícito ou
                                                 // se não especificado
    return new MatrizGeral(linhas, colunas);
  } else {
    // Tipo desconhecido, retorna nullptr e o chamador deve tratar
    return nullptr;
  }
}