#include "MatrizTriangularInferior.hpp"

MatrizTriangularInferior::MatrizTriangularInferior(size_t tamanho)
    : MatrizQuadrada(tamanho), tamanho(tamanho), dados(tamanho) {
  for (size_t i = 0; i < tamanho; i++) {
    dados[i].assign(i + 1, 0.0);
  }
}

MatrizTriangularInferior::MatrizTriangularInferior(const MatrizGeral& outra)
    : MatrizQuadrada(outra.getLinhas()), tamanho(outra.getLinhas()) {
  if (outra.getLinhas() != outra.getColunas()) {
    throw std::invalid_argument(
        "Erro de conversão: A MatrizGeral de origem deve ser quadrada.");
  }

  for (int i = 0; i < outra.getLinhas(); ++i) {
    for (int j = i + 1; j < outra.getColunas(); ++j) {
      if (outra.get(i, j) != 0.0) {
        throw std::invalid_argument(
            "Erro de conversão: A MatrizGeral contém elementos não-nulos acima "
            "da diagonal principal.");
      }
    }
  }

  this->dados.resize(this->tamanho);

  for (size_t i = 0; i < this->tamanho; ++i) {  // i).
    for (size_t j = 0; j <= i; ++j) {
      this->dados[i].push_back(outra.get(i, j));
    }
  }
}

std::ostream& operator<<(std::ostream& os,
                         const MatrizTriangularInferior& matriz) {
  for (size_t i = 0; i < matriz.tamanho; i++) {
    for (double val : matriz.dados[i]) {
      os << val << " ";
    }
    os << std::endl;
  }
  return os;
}

MatrizTriangularInferior MatrizTriangularInferior::operator+(
    const MatrizTriangularInferior& outra) const {
  if (tamanho != outra.tamanho) {
    throw std::invalid_argument("Matrizes de tamanhos diferentes");
  }

  MatrizTriangularInferior resultado(tamanho);
  for (size_t i = 0; i < tamanho; i++) {
    resultado.dados[i].clear();

    auto it1 = dados[i].begin();
    auto it2 = outra.dados[i].begin();

    for (size_t j = 0; j <= i; j++) {
      resultado.dados[i].push_back(*it1 + *it2);
      ++it1;
      ++it2;
    }
  }
  return resultado;
}

MatrizTriangularInferior MatrizTriangularInferior::operator-(
    const MatrizTriangularInferior& outra) const {
  if (tamanho != outra.tamanho) {
    throw std::invalid_argument(
        "Matrizes de tamanhos diferentes não podem ser "
        "somadas.");
  }

  MatrizTriangularInferior resultado(tamanho);
  for (size_t i = 0; i < tamanho; i++) {
    auto it1 = dados[i].begin();
    auto it2 = outra.dados[i].begin();
    for (size_t j = 0; j <= i; j++) {
      resultado.dados[i].push_back(*it1 - *it2);
      ++it1;
      ++it2;
    }
  }
  return resultado;
}

MatrizTriangularInferior MatrizTriangularInferior::operator*(
    double escalar) const {
  MatrizTriangularInferior resultado(tamanho);

  for (size_t i = 0; i < tamanho; i++) {
    resultado.dados[i].clear();

    for (double val : dados[i]) {
      resultado.dados[i].push_back(val * escalar);
    }
  }
  return resultado;
}

// MatrizTriangularSuperior MatrizTriangularInferior::transposta() const {
//   MatrizTriangularSuperior resultado(tamanho);
//   for (size_t i = 0; i < tamanho; ++i) {
//     auto it = dados[i].begin();
//     for (size_t j = i; j < tamanho; ++j, ++it) {
//       resultado.set(j, i, *it);  // A(i,j) → At(j,i)
//     }
//   }

//   return resultado;
// }

double MatrizTriangularInferior::determinante() const {
  if (tamanho == 0) {
    return 1.0;
  }

  double determinante = 1.0;
  for (size_t i = 0; i < tamanho; ++i) {
    auto it = dados[i].begin();
    std::advance(it, i);
    determinante *= *it;
  }

  return determinante;
}

MatrizGeral MatrizTriangularInferior::operator*(
    const MatrizGeral& outra) const {
  if (this->colunas != outra.getLinhas()) {
    throw std::invalid_argument(
        "Número de colunas da primeira matriz deve ser igual ao número de "
        "linhas da segunda matriz para multiplicação.");
  }

  MatrizGeral resultado(this->linhas,
                        outra.getColunas());  // Resultado é sempre MatrizGeral

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

MatrizTriangularInferior MatrizTriangularInferior::operator*(
    const MatrizTriangularInferior& outra) const {
  if (this->colunas != outra.linhas) {
    throw std::invalid_argument(
        "Número de colunas da primeira matriz deve ser igual ao número de "
        "linhas da segunda matriz para multiplicação.");
  }

  MatrizTriangularInferior resultado(this->linhas);

  for (int i = 0; i < this->linhas; ++i) {
    for (int j = 0; j < outra.colunas; ++j) {
      if (i >= j) {
        double soma_produto = 0.0;
        for (int k = 0; k <= i; ++k) {
          if (k >= j) {
            soma_produto += this->get(i, k) * outra.get(k, j);
          }
        }
        resultado.set(i, j, soma_produto);
      }
    }
  }
  return resultado;
}