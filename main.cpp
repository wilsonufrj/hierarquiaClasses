#include <iostream>

void exibirMenu() {
    std::cout << "===== Menu da Calculadora de Matrizes =====\n";
    std::cout << "1. Imprimir uma, ou mais, matrizes da lista.\n";
    std::cout << "2. Inserir uma nova matriz lida do teclado ou de um arquivo que contenha somente uma matriz.\n";
    std::cout << "3. Inserir uma matriz identidade n x n.\n";
    std::cout << "4. Alterar ou remover uma, ou mais matrizes da lista.\n";
    std::cout << "5. Apresentar a lista de matrizes com a identificação das matrizes pelo seu TIPO, seu número de linhas e colunas, ou, alternativamente, por um nome dado pelo usuário quando de sua criação.\n";
    std::cout << "6. Gravar a lista com um nome diferente (backup).\n";
    std::cout << "7. Ler uma outra lista de matrizes, acrescentando à lista existente, ou a substituindo.\n";
    std::cout << "8. Zerar a lista de matrizes.\n";
    std::cout << "0. Sair\n";
    std::cout << "===========================================\n";
    std::cout << "Escolha uma opção: ";
}

int main() {
    int opcao;
    do {
        exibirMenu();
        std::cin >> opcao;
        switch(opcao) {
            case 1:
                // Imprimir matrizes
                break;
            case 2:
                // Inserir nova matriz
                break;
            case 3:
                // Inserir matriz identidade
                break;
            case 4:
                // Alterar ou remover matrizes
                break;
            case 5:
                // Apresentar lista de matrizes
                break;
            case 6:
                // Gravar lista (backup)
                break;
            case 7:
                // Ler outra lista de matrizes
                break;
            case 8:
                // Zerar lista de matrizes
                break;
            case 0:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }
        std::cout << std::endl;
    } while(opcao != 0);

    return 0;
}