#include <stdexcept>

class MatrizGeral {
protected:
    int linhas,colunas;
    double **dados;
public:
    MatrizGeral(int linha,int coluna);
    ~MatrizGeral();

    MatrizGeral operator+(const MatrizGeral& outra)const;

    MatrizGeral operator-(const MatrizGeral& outra) const;

    MatrizGeral operator*(double escalar) const;
};