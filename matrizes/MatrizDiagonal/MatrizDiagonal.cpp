#include "MatrizDiagonal.hpp"

#include <iomanip>
#include <stdexcept>

MatrizDiagonal::MatrizDiagonal(int tamanho) : MatrizQuadrada(tamanho) {
  diagonal.resize(tamanho, 0.0);
}

MatrizDiagonal::~MatrizDiagonal() {}

double MatrizDiagonal::get(int i, int j) const {
  if (i < 0 || i >= linhas || j < 0 || j >= colunas) {
    throw std::out_of_range("Índices fora dos limites da matriz.");
  }
  if (i == j) {
    return diagonal[i];
  }
  return 0.0;
}

void MatrizDiagonal::set(int i, int j, double valor) {
  if (i < 0 || i >= linhas || j < 0 || j >= colunas) {
    throw std::out_of_range("Índices fora dos limites da matriz.");
  }

  if (i == j) {
    diagonal[i] = valor;
  } else {
    if (valor != 0.0) {
      throw std::invalid_argument(
          "Não é possível definir um valor diferente de zero fora da diagonal "
          "em uma MatrizDiagonal.");
    }
  }
}

MatrizDiagonal MatrizDiagonal::operator+(const MatrizDiagonal& outra) const {
  if (linhas != outra.linhas) {
    throw std::invalid_argument(
        "Matrizes de tamanhos diferentes não podem ser somadas.");
  }

  MatrizDiagonal resultado(linhas);
  for (int i = 0; i < linhas; ++i) {
    resultado.diagonal[i] = this->diagonal[i] + outra.diagonal[i];
  }
  return resultado;
}

MatrizDiagonal MatrizDiagonal::operator-(const MatrizDiagonal& outra) const {
  if (linhas != outra.linhas) {
    throw std::invalid_argument(
        "Matrizes de tamanhos diferentes não podem ser subtraídas.");
  }

  MatrizDiagonal resultado(linhas);
  for (int i = 0; i < linhas; ++i) {
    resultado.diagonal[i] = this->diagonal[i] - outra.diagonal[i];
  }
  return resultado;
}

MatrizDiagonal MatrizDiagonal::operator*(double escalar) const {
  MatrizDiagonal resultado(linhas);
  for (int i = 0; i < linhas; ++i) {
    resultado.diagonal[i] = this->diagonal[i] * escalar;
  }
  return resultado;
}

MatrizDiagonal MatrizDiagonal::transposta() const { return *this; }

MatrizGeral MatrizDiagonal::operator*(const MatrizGeral& outra) const {
  if (this->colunas != outra.getLinhas()) {
    throw std::invalid_argument(
        "Número de colunas da primeira matriz deve ser igual ao número de "
        "linhas da segunda matriz para multiplicação.");
  }

  MatrizGeral resultado(this->linhas, outra.getColunas());

  for (int i = 0; i < this->linhas; ++i) {
    for (int j = 0; j < outra.getColunas(); ++j) {
      resultado.set(i, j, this->diagonal[i] * outra.get(i, j));
    }
  }
  return resultado;
}

MatrizDiagonal MatrizDiagonal::operator*(const MatrizDiagonal& outra) const {
  if (this->colunas != outra.linhas) {
    throw std::invalid_argument(
        "Matrizes de tamanhos diferentes não podem ser multiplicadas.");
  }
  MatrizDiagonal resultado(linhas);
  for (int i = 0; i < linhas; ++i) {
    resultado.diagonal[i] = this->diagonal[i] * outra.diagonal[i];
  }
  return resultado;
}

std::ostream& operator<<(std::ostream& os, const MatrizDiagonal& matriz) {
  for (int i = 0; i < matriz.getLinhas(); ++i) {
    for (int j = 0; j < matriz.getColunas(); ++j) {
      os << std::fixed << std::setprecision(2) << matriz.get(i, j) << "\t";
    }
    os << std::endl;
  }
  return os;
}