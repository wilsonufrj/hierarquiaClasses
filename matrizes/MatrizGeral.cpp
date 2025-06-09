#include "MatrizGeral.hpp"

MatrizGeral::MatrizGeral(int linhas, int colunas)
    : linhas(linhas),
      colunas(colunas),
      dados(linhas, std::vector<double>(colunas, 0.0)) {}

MatrizGeral MatrizGeral::operator+(const MatrizGeral &outra) const {
  if (linhas != outra.linhas || colunas != outra.colunas) {
    throw std::invalid_argument(
        "Matrizes de tamanhos diferentes não podem ser somadas.");
  }
  MatrizGeral resultado(linhas, colunas);
  for (int i = 0; i < linhas; ++i) {
    for (int j = 0; j < colunas; ++j) {
      resultado.dados[i][j] = dados[i][j] + outra.dados[i][j];
    }
  }
  return resultado;
}

MatrizGeral MatrizGeral::operator-(const MatrizGeral &outra) const {
  if (linhas != outra.linhas || colunas != outra.colunas) {
    throw std::invalid_argument(
        "Matrizes são de tamanhos diferentes e não pode ser subtraídas.");
  }

  MatrizGeral resultado(linhas, colunas);
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      resultado.dados[i][j] = dados[i][j] - outra.dados[i][j];
    }
  }
  return resultado;
}

MatrizGeral MatrizGeral::transposta() const {
  MatrizGeral resultado(colunas, linhas);
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      resultado.dados[j][i] = dados[i][j];
    }
  }
  return resultado;
}

MatrizGeral MatrizGeral::operator*(double escalar) const {
  MatrizGeral resultado(linhas, colunas);
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      resultado.dados[i][j] = dados[i][j] * escalar;
    }
  }
  return resultado;
}

MatrizGeral MatrizGeral::operator*(const MatrizGeral &outra) const {
  if (this->colunas != outra.linhas) {
    throw std::invalid_argument(
        "Número de colunas da primeira matriz deve ser igual ao número de "
        "linhas da segunda matriz para multiplicação.");
  }

  MatrizGeral resultado(this->linhas, outra.colunas);

  for (int i = 0; i < this->linhas; ++i) {
    for (int j = 0; j < outra.colunas; ++j) {
      double soma_produto = 0.0;
      for (int k = 0; k < this->colunas; ++k) {
        soma_produto += this->get(i, k) * outra.get(k, j);
      }
      resultado.set(i, j, soma_produto);
    }
  }
  return resultado;
}