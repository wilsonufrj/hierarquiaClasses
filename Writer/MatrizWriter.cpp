#include "MatrizWriter.hpp"

#include <fstream>   // Para std::ofstream
#include <iomanip>   // Para std::fixed, std::setprecision
#include <iostream>  // Para std::cerr

bool MatrizWriter::gravarMatrizes(
    const std::string& nomeArquivo,
    const std::vector<std::unique_ptr<MatrizGeral>>& lista) {
  std::ofstream arquivo(nomeArquivo);

  if (!arquivo.is_open()) {
    std::cerr << "Erro: Não foi possível criar/abrir o arquivo para gravação '"
              << nomeArquivo << "'" << std::endl;
    return false;
  }

  arquivo << "# Lista de Matrizes gerada pela Calculadora de Matrizes\n";
  arquivo << "# Data de gravação: " << __DATE__ << " " << __TIME__ << "\n\n";

  for (size_t k = 0; k < lista.size(); ++k) {
    const MatrizGeral* matriz = lista[k].get();
    if (!matriz) {
      std::cerr
          << "Aviso: Encontrado ponteiro nulo na lista de matrizes. Pulando."
          << std::endl;
      continue;
    }

    arquivo << "# Matriz " << k + 1 << "\n";
    arquivo << "TIPO:" << getTipoMatrizString(matriz) << "\n";
    arquivo << "DIM:" << matriz->getLinhas() << "x" << matriz->getColunas()
            << "\n";
    arquivo << "DADOS:\n";

    // Configura a precisão para números de ponto flutuante
    arquivo << std::fixed
            << std::setprecision(6);  // 6 casas decimais por padrão

    for (int i = 0; i < matriz->getLinhas(); ++i) {
      for (int j = 0; j < matriz->getColunas(); ++j) {
        arquivo << matriz->get(i, j);
        if (j < matriz->getColunas() - 1) {
          arquivo << " ";  // Espaço entre os elementos da mesma linha
        }
      }
      arquivo << "\n";  // Quebra de linha para a próxima linha da matriz
    }
    arquivo << "\n";  // Linha em branco para separar as matrizes no arquivo
  }

  arquivo.close();
  return true;
}

std::string MatrizWriter::getTipoMatrizString(const MatrizGeral* matriz) {
  if (!matriz) {
    return "DESCONHECIDO";
  }
  // Usa dynamic_cast para determinar o tipo mais específico
  if (dynamic_cast<const MatrizDiagonal*>(matriz)) {
    return "DIAGONAL";
  } else if (dynamic_cast<const MatrizTriangularSuperior*>(matriz)) {
    return "TRIANGULAR_SUPERIOR";
  } else if (dynamic_cast<const MatrizTriangularInferior*>(matriz)) {
    return "TRIANGULAR_INFERIOR";
  } else if (dynamic_cast<const MatrizQuadrada*>(
                 matriz)) {  // MatrizQuadrada deve vir antes de MatrizGeral se
                             // não for nenhum dos especiais
    return "QUADRADA";
  } else {
    return "GERAL";  // Tipo base
  }
}