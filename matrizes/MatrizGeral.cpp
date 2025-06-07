#include<MatrizGeral.hpp>
#include <stdexcept>
#include <iostream>

MatrizGeral::MatrizGeral(int linhas,int colunas) : linhas(linhas), colunas(colunas) {
    if (linhas <= 0 || colunas <= 0) {
        throw std::invalid_argument("Número de linhas e colunas deve ser maior que zero.");
    }
    dados = new double*[linhas];
    for (int i = 0; i < linhas; ++i) {
        dados[i] = new double[colunas]();
    }
}

MatrizGeral::~MatrizGeral() {
    for (int i = 0; i < linhas; ++i) {
        delete[] dados[i];
    }
    delete[] dados;
}

MatrizGeral MatrizGeral::operator+(const MatrizGeral& outra)const{
        if (linhas != outra.linhas || colunas != outra.colunas) {
            throw std::invalid_argument("Matrizes de tamanhos diferentes não podem ser somadas.");
        }
        MatrizGeral resultado(linhas, colunas);
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                resultado.dados[i][j] = dados[i][j] + outra.dados[i][j];
            }
        }
        return resultado;
    }

MatrizGeral MatrizGeral::operator-(const MatrizGeral& outra) const{
    if(linhas != outra.linhas || colunas != outra.colunas){
        throw std::invalid_argument("Matrizes são de tamanhos diferentes e não pode ser subtraídas.");
    }
    
    MatrizGeral resultado(linhas,colunas);
    for(int i=0;i<linhas;i++){
        for(int j=0;j<colunas;j++){
            resultado.dados[i][j] = dados[i][j] - outra.dados[i][j];
        }
    }
    return resultado;
}

MatrizGeral MatrizGeral::operator*(double escalar) const{
    MatrizGeral resultado(linhas,colunas);
    for(int i=0;i<linhas;i++){
        for(int j=0;j<colunas;j++){
            resultado.dados[i][j] = dados[i][j]*escalar;
        }
    }
    return resultado;
}