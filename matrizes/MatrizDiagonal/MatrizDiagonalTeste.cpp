#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "MatrizDiagonal.hpp"

bool compararMatrizesDiagonais(const MatrizDiagonal &m1,
                               const MatrizDiagonal &m2,
                               double tolerancia = 1e-9) {
  if (m1.getLinhas() != m2.getLinhas()) {
    return false;
  }
  for (int i = 0; i < m1.getLinhas(); ++i) {
    if (std::abs(m1.get(i, i) - m2.get(i, i)) > tolerancia) {
      return false;
    }
  }
  return true;
}

void testConstrutorGetSet() {
  std::cout << "--- Teste: Construtor, get e set ---" << std::endl;
  MatrizDiagonal m(3);

  if (m.getLinhas() == 3 && m.getColunas() == 3) {
    std::cout << "Construtor (tamanho): PASSOU" << std::endl;
  } else {
    std::cout << "Construtor (tamanho): FALHOU" << std::endl;
  }

  m.set(0, 0, 1.0);
  m.set(1, 1, 5.5);
  m.set(2, 2, 10.0);

  if (std::abs(m.get(0, 0) - 1.0) < 1e-9 &&
      std::abs(m.get(1, 1) - 5.5) < 1e-9 &&
      std::abs(m.get(2, 2) - 10.0) < 1e-9) {
    std::cout << "Get e Set (diagonal): PASSOU" << std::endl;
  } else {
    std::cout << "Get e Set (diagonal): FALHOU" << std::endl;
  }

  if (std::abs(m.get(0, 1) - 0.0) < 1e-9 &&
      std::abs(m.get(2, 0) - 0.0) < 1e-9) {
    std::cout << "Get (fora da diagonal): PASSOU" << std::endl;
  } else {
    std::cout << "Get (fora da diagonal): FALHOU" << std::endl;
  }

  try {
    m.set(0, 1, 99.0);
    std::cout
        << "Set (fora da diagonal, valor != 0): FALHOU (Não lançou exceção)"
        << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cout << "Set (fora da diagonal, valor != 0): PASSOU (Lançou exceção: "
              << e.what() << ")" << std::endl;
  } catch (...) {
    std::cout << "Set (fora da diagonal, valor != 0): FALHOU (Lançou exceção "
                 "incorreta)"
              << std::endl;
  }

  try {
    m.set(0, 1, 0.0);
    if (std::abs(m.get(0, 1) - 0.0) < 1e-9) {
      std::cout << "Set (fora da diagonal, valor == 0): PASSOU" << std::endl;
    } else {
      std::cout << "Set (fora da diagonal, valor == 0): FALHOU (Valor alterado "
                   "inesperadamente)"
                << std::endl;
    }
  } catch (const std::exception &e) {
    std::cout << "Set (fora da diagonal, valor == 0): FALHOU (Lançou exceção "
                 "inesperada: "
              << e.what() << ")" << std::endl;
  }

  std::cout << std::endl;
}

void testOperadorSoma() {
  std::cout << "--- Teste: Operador + (Soma) ---" << std::endl;
  MatrizDiagonal m1(2);
  m1.set(0, 0, 1.0);
  m1.set(1, 1, 4.0);

  MatrizDiagonal m2(2);
  m2.set(0, 0, 5.0);
  m2.set(1, 1, 8.0);

  MatrizDiagonal resultadoEsperado(2);
  resultadoEsperado.set(0, 0, 6.0);
  resultadoEsperado.set(1, 1, 12.0);

  try {
    MatrizDiagonal mSoma = m1 + m2;
    if (compararMatrizesDiagonais(mSoma, resultadoEsperado)) {
      std::cout << "Soma de matrizes diagonais (tamanhos iguais): PASSOU"
                << std::endl;
    } else {
      std::cout << "Soma de matrizes diagonais (tamanhos iguais): FALHOU"
                << std::endl;
    }
  } catch (const std::invalid_argument &e) {
    std::cout << "Soma de matrizes diagonais (tamanhos iguais): FALHOU "
                 "(Exceção inesperada: "
              << e.what() << ")" << std::endl;
  }

  MatrizDiagonal m3(3);
  try {
    m1 + m3;
    std::cout << "Soma de matrizes diagonais (tamanhos diferentes): FALHOU "
                 "(Não lançou exceção)"
              << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cout << "Soma de matrizes diagonais (tamanhos diferentes): PASSOU "
                 "(Lançou exceção: "
              << e.what() << ")" << std::endl;
  } catch (...) {
    std::cout << "Soma de matrizes diagonais (tamanhos diferentes): FALHOU "
                 "(Lançou exceção incorreta)"
              << std::endl;
  }
  std::cout << std::endl;
}

void testOperadorSubtracao() {
  std::cout << "--- Teste: Operador - (Subtração) ---" << std::endl;
  MatrizDiagonal m1(2);
  m1.set(0, 0, 10.0);
  m1.set(1, 1, 8.0);

  MatrizDiagonal m2(2);
  m2.set(0, 0, 1.0);
  m2.set(1, 1, 4.0);

  MatrizDiagonal resultadoEsperado(2);
  resultadoEsperado.set(0, 0, 9.0);
  resultadoEsperado.set(1, 1, 4.0);

  try {
    MatrizDiagonal mSubtracao = m1 - m2;
    if (compararMatrizesDiagonais(mSubtracao, resultadoEsperado)) {
      std::cout << "Subtração de matrizes diagonais (tamanhos iguais): PASSOU"
                << std::endl;
    } else {
      std::cout << "Subtração de matrizes diagonais (tamanhos iguais): FALHOU"
                << std::endl;
    }
  } catch (const std::invalid_argument &e) {
    std::cout << "Subtração de matrizes diagonais (tamanhos iguais): FALHOU "
                 "(Exceção inesperada: "
              << e.what() << ")" << std::endl;
  }

  MatrizDiagonal m3(3);
  try {
    m1 - m3;
    std::cout << "Subtração de matrizes diagonais (tamanhos diferentes): "
                 "FALHOU (Não lançou exceção)"
              << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cout << "Subtração de matrizes diagonais (tamanhos diferentes): "
                 "PASSOU (Lançou exceção: "
              << e.what() << ")" << std::endl;
  } catch (...) {
    std::cout << "Subtração de matrizes diagonais (tamanhos diferentes): "
                 "FALHOU (Lançou exceção incorreta)"
              << std::endl;
  }
  std::cout << std::endl;
}

void testOperadorMultiplicacaoEscalar() {
  std::cout << "--- Teste: Operador * (Multiplicação por Escalar) ---"
            << std::endl;
  MatrizDiagonal m(2);
  m.set(0, 0, 1.0);
  m.set(1, 1, 4.0);

  double escalar = 2.0;
  MatrizDiagonal resultadoEsperado(2);
  resultadoEsperado.set(0, 0, 2.0);
  resultadoEsperado.set(1, 1, 8.0);

  MatrizDiagonal mMultiplicada = m * escalar;
  if (compararMatrizesDiagonais(mMultiplicada, resultadoEsperado)) {
    std::cout << "Multiplicação por escalar: PASSOU" << std::endl;
  } else {
    std::cout << "Multiplicação por escalar: FALHOU" << std::endl;
  }
  std::cout << std::endl;
}

void testTransposta() {
  std::cout << "--- Teste: Transposta ---" << std::endl;
  MatrizDiagonal m(3);
  m.set(0, 0, 1.0);
  m.set(1, 1, 5.0);
  m.set(2, 2, 10.0);

  MatrizDiagonal resultadoEsperado = m;

  MatrizDiagonal mTransposta = m.transposta();
  if (compararMatrizesDiagonais(mTransposta, resultadoEsperado)) {
    std::cout << "Transposta: PASSOU" << std::endl;
  } else {
    std::cout << "Transposta: FALHOU" << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  std::cout << "Executando testes para MatrizDiagonal:" << std::endl;
  std::cout << "-------------------------------------" << std::endl
            << std::endl;

  testConstrutorGetSet();
  testOperadorSoma();
  testOperadorSubtracao();
  testOperadorMultiplicacaoEscalar();
  testTransposta();

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Todos os testes para MatrizDiagonal concluídos!" << std::endl;

  return 0;
}