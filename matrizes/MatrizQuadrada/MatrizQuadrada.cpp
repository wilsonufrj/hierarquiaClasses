#include "MatrizQuadrada.hpp"

MatrizQuadrada::MatrizQuadrada(int tamanho) : MatrizGeral(tamanho, tamanho) {}

MatrizQuadrada::~MatrizQuadrada() {}

double MatrizQuadrada::traco() const {
  double traco = 0.0;
  for (int i = 0; i < linhas; ++i) {
    traco += get(i, i);
  }
  return traco;
}