#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>

class MatrizGeral {
 protected:
  int linhas, colunas;
  std::vector<std::vector<double>> dados;

 public:
  MatrizGeral(int linha, int coluna);
  virtual ~MatrizGeral() = default;

  MatrizGeral operator+(const MatrizGeral &outra) const;

  MatrizGeral operator-(const MatrizGeral &outra) const;

  MatrizGeral operator*(double escalar) const;
  MatrizGeral operator*(const MatrizGeral &outra) const;

  MatrizGeral transposta() const;

  double get(int i, int j) const { return dados[i][j]; }

  void set(int i, int j, double valor) { dados[i][j] = valor; }

  int getLinhas() const { return linhas; }
  int getColunas() const { return colunas; }
};