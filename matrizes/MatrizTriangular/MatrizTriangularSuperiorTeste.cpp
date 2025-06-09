#include <cassert>
#include <iostream>

#include "MatrizTriangularInferior.hpp"
#include "MatrizTriangularSuperior.hpp"

void testarConstrutorEImpressao() {
  std::cout << "=== Teste Construtor e Impressão ===" << std::endl;
  MatrizTriangularSuperior A(3);
  std::cout << A << std::endl;
}

void testarSoma() {
  std::cout << "=== Teste Soma ===" << std::endl;
  MatrizTriangularSuperior A(2), B(2);

  // Matriz A:
  // [1, 2]
  // [0, 3]
  A.set(0, 0, 1.0);
  A.set(0, 1, 2.0);
  A.set(1, 1, 3.0);

  // Matriz B:
  // [4, 5]
  // [0, 6]
  B.set(0, 0, 4.0);
  B.set(0, 1, 5.0);
  B.set(1, 1, 6.0);

  MatrizTriangularSuperior C = A + B;

  assert(C.get(0, 0) == 5.0);
  assert(C.get(0, 1) == 7.0);
  assert(C.get(1, 1) == 9.0);

  std::cout << "Soma passou!\n" << std::endl;
}

void testarSubtracao() {
  std::cout << "=== Teste Subtração ===" << std::endl;
  MatrizTriangularSuperior A(2);
  A.set(0, 0, 4.0);
  A.set(0, 1, 5.0);
  A.set(1, 1, 6.0);

  MatrizTriangularSuperior B(2);
  B.set(0, 0, 1.0);
  B.set(0, 1, 2.0);
  B.set(1, 1, 3.0);

  MatrizTriangularSuperior C = A - B;

  assert(C.get(0, 0) == 3.0);
  assert(C.get(0, 1) == 3.0);
  assert(C.get(1, 1) == 3.0);

  std::cout << "Subtração passou!\n" << std::endl;
}

void testarMultiplicacaoEscalar() {
  std::cout << "=== Teste Multiplicação por Escalar ===" << std::endl;
  MatrizTriangularSuperior A(2);
  A.set(0, 0, 1.0);
  A.set(0, 1, 2.0);
  A.set(1, 1, 3.0);

  MatrizTriangularSuperior B = A * 2.0;

  assert(B.get(0, 0) == 2.0);
  assert(B.get(0, 1) == 4.0);
  assert(B.get(1, 1) == 6.0);

  std::cout << "Multiplicação passou!\n" << std::endl;
}

void testarDeterminante() {
  std::cout << "=== Teste Determinante ===" << std::endl;
  MatrizTriangularSuperior A(3);
  A.set(0, 0, 2.0);  // Linha 0: [2.0, 3.0, 1.0]
  A.set(0, 1, 3.0);
  A.set(0, 2, 1.0);
  A.set(1, 1, 4.0);  // Linha 1: [4.0, 5.0]
  A.set(1, 2, 5.0);
  A.set(2, 2, 6.0);  // Linha 2: [6.0]

  // O determinante deve ser 2.0 * 4.0 * 6.0 = 48.0
  double det = A.determinante();
  std::cout << "Determinante calculado: " << det << std::endl;
  assert(std::abs(det - 48.0) < 1e-9);

  std::cout << "Determinante passou!\n" << std::endl;
}

// void testarTransposta() {
//   std::cout << "=== Teste Transposta ===" << std::endl;
//   MatrizTriangularSuperior A(3);
//   A.set(0, 0, 1.0);
//   A.set(0, 1, 2.0);
//   A.set(0, 2, 3.0);
//   A.set(1, 1, 4.0);
//   A.set(1, 2, 5.0);
//   A.set(2, 2, 6.0);

//   MatrizTriangularInferior At = A.transposta();

//   assert(At.get(0, 0) == 1.0);
//   assert(At.get(1, 0) == 2.0);
//   assert(At.get(1, 1) == 4.0);
//   assert(At.get(2, 0) == 3.0);
//   assert(At.get(2, 1) == 5.0);
//   assert(At.get(2, 2) == 6.0);

//   std::cout << "Transposta passou!\n" << std::endl;
// }

int main() {
  testarConstrutorEImpressao();
  testarSoma();
  testarSubtracao();
  testarMultiplicacaoEscalar();
  testarDeterminante();
  // testarTransposta();
  std::cout << "Todos os testes passaram com sucesso!" << std::endl;
  return 0;
}
