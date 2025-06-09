#pragma once

#include <vector>

#include "../MatrizQuadrada/MatrizQuadrada.hpp"

class MatrizDiagonal : public MatrizQuadrada {
 private:
  int tamanho;
  std::vector<double> diagonal;

 public:
  MatrizDiagonal(int tamanho);
  ~MatrizDiagonal();

  friend std::ostream& operator<<(std::ostream& os,
                                  const MatrizDiagonal& matriz);

  virtual double get(int i, int j) const;

  virtual void set(int i, int j, double valor);

  MatrizDiagonal operator+(const MatrizDiagonal& outra) const;

  MatrizDiagonal operator-(const MatrizDiagonal& outra) const;

  MatrizDiagonal operator*(double escalar) const;

  MatrizGeral operator*(const MatrizGeral& outra) const;
  MatrizDiagonal operator*(const MatrizDiagonal& outra) const;

  MatrizDiagonal transposta() const;
};