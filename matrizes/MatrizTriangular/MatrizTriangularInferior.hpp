#pragma once
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

#include "../MatrizQuadrada/MatrizQuadrada.hpp"
#include "MatrizTriangularSuperior.hpp"

class MatrizTriangularInferior : public MatrizQuadrada {
 private:
  size_t tamanho;
  std::vector<std::list<double>> dados;

 public:
  explicit MatrizTriangularInferior(const MatrizGeral& outra);

  MatrizTriangularInferior(size_t tamanho);

  friend std::ostream& operator<<(std::ostream& os,
                                  const MatrizTriangularInferior& matriz);

  MatrizTriangularInferior operator+(
      const MatrizTriangularInferior& outra) const;

  MatrizTriangularInferior operator-(
      const MatrizTriangularInferior& outra) const;

  MatrizTriangularInferior operator*(double escalar) const;

  MatrizGeral operator*(const MatrizGeral& outra) const;

  MatrizTriangularInferior operator*(
      const MatrizTriangularInferior& outra) const;

  // MatrizTriangularSuperior transposta() const;
  double determinante() const;

  double get(size_t i, size_t j) const {
    if (i >= tamanho || j >= tamanho) {
      throw std::out_of_range("Índices fora da matriz");
    }
    if (j > i) {  // Acima da diagonal
      return 0.0;
    }
    auto it = dados[i].begin();
    std::advance(it, j);
    return *it;
  }

  void set(size_t i, size_t j, double valor) {
    if (i >= tamanho || j >= tamanho) {
      throw std::out_of_range("Índices fora da matriz");
    }
    if (j > i) {
      throw std::invalid_argument("Não pode setar elementos acima da diagonal");
    }
    auto it = dados[i].begin();
    std::advance(it, j);
    *it = valor;
  }

  size_t getLinhas() const { return tamanho; }
  size_t getColunas() const { return tamanho; }
};