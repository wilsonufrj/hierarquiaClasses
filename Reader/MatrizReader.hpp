#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../matrizes/MatrizDiagonal/MatrizDiagonal.hpp"
#include "../matrizes/MatrizGeral.hpp"
#include "../matrizes/MatrizQuadrada/MatrizQuadrada.hpp"
#include "../matrizes/MatrizTriangular/MatrizTriangularInferior.hpp"
#include "../matrizes/MatrizTriangular/MatrizTriangularSuperior.hpp"

class MatrizReader {
 public:
  // Função que lê o arquivo e retorna um vetor de ponteiros únicos para
  // MatrizGeral
  static std::vector<std::unique_ptr<MatrizGeral>> lerMatrizesDoArquivo(
      const std::string& nomeArquivo);

 private:
  // Funções auxiliares para parsear o tipo e as dimensões
  static std::pair<int, int> parseDimensoes(const std::string& linhaDim);
  static MatrizGeral* criarMatrizDoTipo(const std::string& tipo, int linhas,
                                        int colunas);
};
