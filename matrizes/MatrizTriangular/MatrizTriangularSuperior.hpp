#pragma once

#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

#include "../MatrizQuadrada/MatrizQuadrada.hpp"
#include "MatrizTriangularInferior.hpp"

class MatrizTriangularSuperior : public MatrizQuadrada {
 protected:
  size_t tamanho;
  std::vector<std::list<double>> dados;

 public:
  explicit MatrizTriangularSuperior(const MatrizGeral& outra);

  MatrizTriangularSuperior(size_t tamanho);

  friend std::ostream& operator<<(std::ostream& os,
                                  const MatrizTriangularSuperior& matriz);

  MatrizTriangularSuperior operator+(
      const MatrizTriangularSuperior& outra) const;

  MatrizTriangularSuperior operator-(
      const MatrizTriangularSuperior& outra) const;

  MatrizTriangularSuperior operator*(double escalar) const;

  MatrizGeral operator*(const MatrizGeral& outra) const;

  MatrizTriangularSuperior operator*(
      const MatrizTriangularSuperior& outra) const;

  // MatrizTriangularInferior transposta() const;

  double determinante() const;

  double get(size_t i, size_t j) const {
    if (i >= tamanho || j >= tamanho) {
      throw std::out_of_range("Índices fora da matriz");
    }
    if (j < i) {
      return 0.0;
    }
    auto it = dados[i].begin();
    std::advance(it, j - i);
    return *it;
  }

  void set(size_t i, size_t j, double valor) {
    if (i >= tamanho || j >= tamanho) {
      throw std::out_of_range("Índices fora da matriz");
    }
    if (j < i) {
      throw std::invalid_argument(
          "Não pode setar elementos abaixo da diagonal");
    }
    auto it = dados[i].begin();
    std::advance(it, j - i);
    *it = valor;
  }

  size_t getLinhas() const { return tamanho; }
  size_t getColunas() const { return tamanho; }
};