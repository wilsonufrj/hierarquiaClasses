#include <iostream>
#include <stdexcept>
#include <vector>

#include "MatrizGeral.hpp"

bool compararMatrizes(const MatrizGeral &m1, const MatrizGeral &m2,
                      double tolerancia = 1e-9) {
  if (m1.getLinhas() != m2.getLinhas() || m1.getColunas() != m2.getColunas()) {
    return false;
  }
  for (int i = 0; i < m1.getLinhas(); ++i) {
    for (int j = 0; j < m1.getColunas(); ++j) {
      if (std::abs(m1.get(i, j) - m2.get(i, j)) > tolerancia) {
        return false;
      }
    }
  }
  return true;
}

void testConstrutorGetSet() {
  std::cout << "--- Teste: Construtor, get e set ---" << std::endl;
  MatrizGeral m(2, 3);
  if (m.getLinhas() == 2 && m.getColunas() == 3) {
    std::cout << "Construtor (tamanho): PASSOU" << std::endl;
  } else {
    std::cout << "Construtor (tamanho): FALHOU" << std::endl;
  }

  m.set(0, 0, 1.0);
  m.set(1, 2, 5.5);

  if (std::abs(m.get(0, 0) - 1.0) < 1e-9 &&
      std::abs(m.get(1, 2) - 5.5) < 1e-9) {
    std::cout << "Get e Set: PASSOU" << std::endl;
  } else {
    std::cout << "Get e Set: FALHOU" << std::endl;
  }
  std::cout << std::endl;
}

void testOperadorSoma() {
  std::cout << "--- Teste: Operador + (Soma) ---" << std::endl;
  MatrizGeral m1(2, 2);
  m1.set(0, 0, 1.0);
  m1.set(0, 1, 2.0);
  m1.set(1, 0, 3.0);
  m1.set(1, 1, 4.0);

  MatrizGeral m2(2, 2);
  m2.set(0, 0, 5.0);
  m2.set(0, 1, 6.0);
  m2.set(1, 0, 7.0);
  m2.set(1, 1, 8.0);

  MatrizGeral resultadoEsperado(2, 2);
  resultadoEsperado.set(0, 0, 6.0);
  resultadoEsperado.set(0, 1, 8.0);
  resultadoEsperado.set(1, 0, 10.0);
  resultadoEsperado.set(1, 1, 12.0);

  try {
    MatrizGeral mSoma = m1 + m2;
    if (compararMatrizes(mSoma, resultadoEsperado)) {
      std::cout << "Soma de matrizes (tamanhos iguais): PASSOU" << std::endl;
    } else {
      std::cout << "Soma de matrizes (tamanhos iguais): FALHOU" << std::endl;
    }
  } catch (const std::invalid_argument &e) {
    std::cout
        << "Soma de matrizes (tamanhos iguais): FALHOU (Exceção inesperada: "
        << e.what() << ")" << std::endl;
  }

  MatrizGeral m3(2, 3);
  try {
    m1 + m3;
    std::cout
        << "Soma de matrizes (tamanhos diferentes): FALHOU (Não lançou exceção)"
        << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cout
        << "Soma de matrizes (tamanhos diferentes): PASSOU (Lançou exceção: "
        << e.what() << ")" << std::endl;
  }
  std::cout << std::endl;
}

void testOperadorSubtracao() {
  std::cout << "--- Teste: Operador - (Subtração) ---" << std::endl;
  MatrizGeral m1(2, 2);
  m1.set(0, 0, 10.0);
  m1.set(0, 1, 8.0);
  m1.set(1, 0, 6.0);
  m1.set(1, 1, 4.0);

  MatrizGeral m2(2, 2);
  m2.set(0, 0, 1.0);
  m2.set(0, 1, 2.0);
  m2.set(1, 0, 3.0);
  m2.set(1, 1, 4.0);

  MatrizGeral resultadoEsperado(2, 2);
  resultadoEsperado.set(0, 0, 9.0);
  resultadoEsperado.set(0, 1, 6.0);
  resultadoEsperado.set(1, 0, 3.0);
  resultadoEsperado.set(1, 1, 0.0);

  try {
    MatrizGeral mSubtracao = m1 - m2;
    if (compararMatrizes(mSubtracao, resultadoEsperado)) {
      std::cout << "Subtração de matrizes (tamanhos iguais): PASSOU"
                << std::endl;
    } else {
      std::cout << "Subtração de matrizes (tamanhos iguais): FALHOU"
                << std::endl;
    }
  } catch (const std::invalid_argument &e) {
    std::cout << "Subtração de matrizes (tamanhos iguais): FALHOU (Exceção "
                 "inesperada: "
              << e.what() << ")" << std::endl;
  }

  MatrizGeral m3(2, 3);
  try {
    m1 - m3;
    std::cout << "Subtração de matrizes (tamanhos diferentes): FALHOU (Não "
                 "lançou exceção)"
              << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cout << "Subtração de matrizes (tamanhos diferentes): PASSOU (Lançou "
                 "exceção: "
              << e.what() << ")" << std::endl;
  }
  std::cout << std::endl;
}

void testOperadorMultiplicacaoEscalar() {
  std::cout << "--- Teste: Operador * (Multiplicação por Escalar) ---"
            << std::endl;
  MatrizGeral m(2, 2);
  m.set(0, 0, 1.0);
  m.set(0, 1, 2.0);
  m.set(1, 0, 3.0);
  m.set(1, 1, 4.0);

  double escalar = 2.0;
  MatrizGeral resultadoEsperado(2, 2);
  resultadoEsperado.set(0, 0, 2.0);
  resultadoEsperado.set(0, 1, 4.0);
  resultadoEsperado.set(1, 0, 6.0);
  resultadoEsperado.set(1, 1, 8.0);

  MatrizGeral mMultiplicada = m * escalar;
  if (compararMatrizes(mMultiplicada, resultadoEsperado)) {
    std::cout << "Multiplicação por escalar: PASSOU" << std::endl;
  } else {
    std::cout << "Multiplicação por escalar: FALHOU" << std::endl;
  }
  std::cout << std::endl;
}

void testTransposta() {
  std::cout << "--- Teste: Transposta ---" << std::endl;
  MatrizGeral m(2, 3);
  m.set(0, 0, 1.0);
  m.set(0, 1, 2.0);
  m.set(0, 2, 3.0);
  m.set(1, 0, 4.0);
  m.set(1, 1, 5.0);
  m.set(1, 2, 6.0);

  MatrizGeral resultadoEsperado(3, 2);
  resultadoEsperado.set(0, 0, 1.0);
  resultadoEsperado.set(0, 1, 4.0);
  resultadoEsperado.set(1, 0, 2.0);
  resultadoEsperado.set(1, 1, 5.0);
  resultadoEsperado.set(2, 0, 3.0);
  resultadoEsperado.set(2, 1, 6.0);

  MatrizGeral mTransposta = m.transposta();
  if (compararMatrizes(mTransposta, resultadoEsperado)) {
    std::cout << "Transposta: PASSOU" << std::endl;
  } else {
    std::cout << "Transposta: FALHOU" << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  testConstrutorGetSet();
  testOperadorSoma();
  testOperadorSubtracao();
  testOperadorMultiplicacaoEscalar();
  testTransposta();

  std::cout << "Todos os testes concluídos!" << std::endl;

  return 0;
}