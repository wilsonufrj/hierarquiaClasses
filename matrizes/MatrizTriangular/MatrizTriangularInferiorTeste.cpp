#include <cassert>
#include <iostream>
#include <limits>

#include "MatrizTriangularInferior.hpp"

void testarConstrutor() {
  std::cout << "=== Teste Construtor ===" << std::endl;

  // Caso normal
  MatrizTriangularInferior pequena(3);
  assert(pequena.getLinhas() == 3);

  // Caso limite (potencialmente válido)
  try {
    size_t grande_but_possivel = 10;  // Ajuste conforme seu sistema
    MatrizTriangularInferior grande(grande_but_possivel);
    std::cout << "Criada matriz com " << grande_but_possivel << " linhas"
              << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Alocação falhou: " << e.what()
              << " (pode ser normal em sistemas com pouca memória)"
              << std::endl;
  }

  // Caso inválido (forçando erro)
  try {
    size_t impossivel = std::numeric_limits<size_t>::max();
    MatrizTriangularInferior invalida(impossivel);
    assert(false);
  } catch (const std::length_error& e) {
    std::cout << "Erro de tamanho capturado (esperado): " << e.what()
              << std::endl;
  } catch (const std::bad_alloc& e) {
    std::cout << "Falta de memória (esperado em alguns casos): " << e.what()
              << std::endl;
  }

  std::cout << "OK!" << std::endl << std::endl;
}

void testarAcessoElementos() {
  std::cout << "=== Teste Acesso a Elementos ===" << std::endl;
  MatrizTriangularInferior mat(3);

  // Preenche valores
  mat.set(0, 0, 1.0);
  mat.set(1, 0, 2.0);
  mat.set(1, 1, 3.0);
  mat.set(2, 0, 4.0);
  mat.set(2, 1, 5.0);
  mat.set(2, 2, 6.0);

  // Verifica valores
  assert(mat.get(0, 0) == 1.0);
  assert(mat.get(1, 1) == 3.0);
  assert(mat.get(2, 0) == 4.0);

  // Elementos acima da diagonal devem ser zero
  assert(mat.get(0, 1) == 0.0);
  assert(mat.get(1, 2) == 0.0);

  std::cout << "Matriz criada:" << std::endl << mat << std::endl;
  std::cout << "OK!" << std::endl << std::endl;
}

void testarSoma() {
  std::cout << "=== Teste Soma de Matrizes ===" << std::endl;
  MatrizTriangularInferior A(2), B(2);

  A.set(0, 0, 1.0);
  A.set(1, 0, 2.0);
  A.set(1, 1, 3.0);

  B.set(0, 0, 4.0);
  B.set(1, 0, 5.0);
  B.set(1, 1, 6.0);

  MatrizTriangularInferior C = A + B;

  assert(C.get(0, 0) == 5.0);
  assert(C.get(1, 1) == 9.0);

  std::cout << "Matriz A:" << std::endl << A << std::endl;
  std::cout << "Matriz B:" << std::endl << B << std::endl;
  std::cout << "Resultado A+B:" << std::endl << C << std::endl;
  std::cout << "OK!" << std::endl << std::endl;
}

void testarMultiplicacaoEscalar() {
  std::cout << "=== Teste Multiplicação por Escalar ===" << std::endl;
  MatrizTriangularInferior A(2);

  A.set(0, 0, 1.0);
  A.set(1, 0, 2.0);
  A.set(1, 1, 3.0);

  MatrizTriangularInferior B = A * 2.5;

  assert(B.get(0, 0) == 2.5);
  assert(B.get(1, 1) == 7.5);

  std::cout << "Matriz original:" << std::endl << A << std::endl;
  std::cout << "Após multiplicar por 2.5:" << std::endl << B << std::endl;
  std::cout << "OK!" << std::endl << std::endl;
}

void testarDeterminante() {
  std::cout << "=== Teste Determinante ===" << std::endl;

  // Caso 1: Matriz 1x1
  MatrizTriangularInferior A(1);
  A.set(0, 0, 5.0);
  assert(A.determinante() == 5.0);

  // Caso 2: Matriz 2x2
  MatrizTriangularInferior B(2);
  B.set(0, 0, 2.0);
  B.set(1, 0, 1.0);
  B.set(1, 1, 3.0);
  assert(B.determinante() == 6.0);  // 2 * 3 = 6

  // Caso 3: Matriz 3x3 com zero na diagonal
  MatrizTriangularInferior C(3);
  C.set(0, 0, 1.0);
  C.set(1, 0, 2.0);
  C.set(1, 1, 0.0);  // Determinante deve ser zero
  C.set(2, 0, 3.0);
  C.set(2, 1, 4.0);
  C.set(2, 2, 5.0);
  assert(C.determinante() == 0.0);

  // Caso 4: Matriz vazia
  MatrizTriangularInferior D(0);
  assert(D.determinante() == 1.0);

  std::cout << "Todos os testes de determinante passaram!\n" << std::endl;
}

// void testarTransposta() {
//   std::cout << "=== Teste Transposta ===" << std::endl;

//   // Caso 1: Matriz 2x2
//   MatrizTriangularInferior A(2);
//   A.set(0, 0, 1.0);
//   A.set(1, 0, 2.0);
//   A.set(1, 1, 3.0);

//   MatrizTriangularInferior At = A.transposta();

//   std::cout << "Matriz original:\n" << A << std::endl;
//   std::cout << "Matriz transposta:\n" << At << std::endl;

//   assert(At.get(0, 0) == 1.0);
//   assert(At.get(0, 1) == 2.0);  // Elemento que estava em (1,0)
//   assert(At.get(1, 1) == 3.0);

//   // Caso 2: Matriz 3x3
//   MatrizTriangularInferior B(3);
//   B.set(0, 0, 1.0);
//   B.set(1, 0, 2.0);
//   B.set(1, 1, 3.0);
//   B.set(2, 0, 4.0);
//   B.set(2, 1, 5.0);
//   B.set(2, 2, 6.0);

//   MatrizTriangularInferior Bt = B.transposta();

//   assert(Bt.get(0, 0) == 1.0);
//   assert(Bt.get(0, 1) == 2.0);
//   assert(Bt.get(0, 2) == 4.0);
//   assert(Bt.get(1, 1) == 3.0);
//   assert(Bt.get(1, 2) == 5.0);
//   assert(Bt.get(2, 2) == 6.0);

//   std::cout << "Todos os testes de transposta passaram!\n" << std::endl;
// }

int main() {
  testarConstrutor();
  testarAcessoElementos();
  testarSoma();
  testarMultiplicacaoEscalar();
  testarDeterminante();
  // testarTransposta();
  std::cout << "=== Todos os testes passaram! ===" << std::endl;
  return 0;
}