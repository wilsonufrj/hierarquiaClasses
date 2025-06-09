#include "MatrizTriangularSuperior.hpp"
MatrizTriangularSuperior::MatrizTriangularSuperior(size_t tamanho)
    : MatrizQuadrada(tamanho), tamanho(tamanho), dados(tamanho) {
  for (size_t i = 0; i < tamanho; i++) {
    dados[i].assign(tamanho - i, 0.0);
  }
}

MatrizTriangularSuperior::MatrizTriangularSuperior(const MatrizGeral& outra)
    : MatrizQuadrada(outra.getLinhas()), tamanho(outra.getLinhas()) {
  if (outra.getLinhas() != outra.getColunas()) {
    throw std::invalid_argument(
        "Erro de conversão: A MatrizGeral de origem deve ser quadrada.");
  }
  for (int i = 0; i < outra.getLinhas(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (outra.get(i, j) != 0.0) {
        throw std::invalid_argument(
            "Erro de conversão: A MatrizGeral contém elementos não-nulos "
            "abaixo da diagonal principal.");
      }
    }
  }
  this->dados.resize(this->tamanho);

  for (size_t i = 0; i < this->tamanho; ++i) {
    for (size_t j = i; j < this->tamanho; ++j) {
      this->dados[i].push_back(outra.get(i, j));
    }
  }
}

std::ostream& operator<<(std::ostream& os,
                         const MatrizTriangularSuperior& matriz) {
  for (size_t i = 0; i < matriz.tamanho; i++) {
    for (double val : matriz.dados[i]) {
      os << val << " ";
    }
    os << std::endl;
  }
  return os;
}

MatrizTriangularSuperior MatrizTriangularSuperior::operator+(
    const MatrizTriangularSuperior& outra) const {
  if (tamanho != outra.tamanho) {
    throw std::invalid_argument("Matrizes de tamanhos diferentes");
  }

  MatrizTriangularSuperior resultado(tamanho);
  for (size_t i = 0; i < tamanho; i++) {
    resultado.dados[i].clear();
    auto it1 = dados[i].begin();
    auto it2 = outra.dados[i].begin();
    for (size_t j = i; j < tamanho; j++, ++it1, ++it2) {
      resultado.dados[i].push_back(*it1 + *it2);
    }
  }
  return resultado;
}

MatrizTriangularSuperior MatrizTriangularSuperior::operator-(
    const MatrizTriangularSuperior& outra) const {
  if (tamanho != outra.tamanho) {
    throw std::invalid_argument("Matrizes de tamanhos diferentes");
  }

  MatrizTriangularSuperior resultado(tamanho);
  for (size_t i = 0; i < tamanho; i++) {
    resultado.dados[i].clear();
    auto it1 = dados[i].begin();
    auto it2 = outra.dados[i].begin();
    for (size_t j = i; j < tamanho; j++, ++it1, ++it2) {
      resultado.dados[i].push_back(*it1 - *it2);
    }
  }
  return resultado;
}

MatrizTriangularSuperior MatrizTriangularSuperior::operator*(
    double escalar) const {
  MatrizTriangularSuperior resultado(tamanho);
  for (size_t i = 0; i < tamanho; i++) {
    resultado.dados[i].clear();
    for (double val : dados[i]) {
      resultado.dados[i].push_back(val * escalar);
    }
  }
  return resultado;
}

// MatrizTriangularInferior MatrizTriangularSuperior::transposta() const {
//   MatrizTriangularInferior resultado(colunas);
//   for (int i = 0; i < linhas; ++i) {
//     for (int j = 0; j < colunas; ++j) {
//       if (i <= j) {
//         resultado.set(j, i, this->get(i, j));
//       }
//     }
//   }
//   return resultado;
// }

double MatrizTriangularSuperior::determinante() const {
  if (tamanho == 0) return 1.0;

  double det = 1.0;
  for (size_t i = 0; i < tamanho; ++i) {
    det *= dados[i].front();
  }
  return det;
}

MatrizGeral MatrizTriangularSuperior::operator*(
    const MatrizGeral& outra) const {
  if (this->colunas != outra.getLinhas()) {
    throw std::invalid_argument(
        "Número de colunas da primeira matriz deve ser igual ao número de "
        "linhas da segunda matriz para multiplicação.");
  }

  MatrizGeral resultado(this->linhas, outra.getColunas());

  for (int i = 0; i < this->linhas; ++i) {
    for (int j = 0; j < outra.getColunas(); ++j) {
      double soma_produto = 0.0;
      for (int k = 0; k < this->colunas; ++k) {
        soma_produto += this->get(i, k) * outra.get(k, j);
      }
      resultado.set(i, j, soma_produto);
    }
  }
  return resultado;
}

MatrizTriangularSuperior MatrizTriangularSuperior::operator*(
    const MatrizTriangularSuperior& outra) const {
  if (this->colunas != outra.linhas) {
    throw std::invalid_argument(
        "Número de colunas da primeira matriz deve ser igual ao número de "
        "linhas da segunda matriz para multiplicação.");
  }

  MatrizTriangularSuperior resultado(this->linhas);

  for (int i = 0; i < this->linhas; ++i) {
    for (int j = 0; j < outra.colunas; ++j) {
      if (i <= j) {
        double soma_produto = 0.0;
        for (int k = i; k <= j && k < this->colunas; ++k) {
          soma_produto += this->get(i, k) * outra.get(k, j);
        }
        resultado.set(i, j, soma_produto);
      }
    }
  }
  return resultado;
}