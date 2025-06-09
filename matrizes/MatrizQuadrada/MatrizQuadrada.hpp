#pragma once

#include "../MatrizGeral.hpp"

class MatrizQuadrada : public MatrizGeral {
 public:
  MatrizQuadrada(int tamanho);
  ~MatrizQuadrada();
  double traco() const;
};