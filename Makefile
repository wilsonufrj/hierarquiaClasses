# Nome do executável final
TARGET = calculadora_matrizes

# Compilador C++
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic

SRCS = \
	matrizes/MatrizDiagonal/MatrizDiagonal.cpp \
	matrizes/MatrizQuadrada/MatrizQuadrada.cpp \
	matrizes/MatrizGeral.cpp \
	matrizes/MatrizTriangular/MatrizTriangularInferior.cpp \
	matrizes/MatrizTriangular/MatrizTriangularSuperior.cpp \
	Reader/MatrizReader.cpp \
	Writer/MatrizWriter.cpp \
	main.cpp

# Arquivos objeto (.o) correspondentes aos arquivos fonte
OBJS = $(SRCS:.cpp=.o)

# Regra padrão: compila o executável
all: $(TARGET)

# Regra para vincular (linkar) os arquivos objeto no executável final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Regra para compilar cada arquivo .cpp em um arquivo .o
# $<: o primeiro pré-requisito (o arquivo .cpp)
# $@: o nome do alvo (o arquivo .o)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados pela compilação
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
