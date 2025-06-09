#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../matrizes/MatrizDiagonal/MatrizDiagonal.hpp"
#include "../matrizes/MatrizGeral.hpp"
#include "../matrizes/MatrizQuadrada/MatrizQuadrada.hpp"
#include "../matrizes/MatrizTriangular/MatrizTriangularInferior.hpp"
#include "../matrizes/MatrizTriangular/MatrizTriangularSuperior.hpp"

class MatrizWriter {
 public:
  /**
   * @brief Grava uma lista de matrizes em um arquivo de texto.
   * Utiliza o mesmo formato que MatrizReader para compatibilidade.
   * @param nomeArquivo O nome do arquivo para gravação.
   * @param lista A lista de unique_ptr para MatrizGeral a ser gravada.
   * @return true se a gravação for bem-sucedida, false caso contrário.
   */
  static bool gravarMatrizes(
      const std::string& nomeArquivo,
      const std::vector<std::unique_ptr<MatrizGeral>>& lista);

 private:
  // Função auxiliar para obter a string do tipo da matriz para gravação
  static std::string getTipoMatrizString(const MatrizGeral* matriz);
};