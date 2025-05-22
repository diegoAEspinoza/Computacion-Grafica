# Compiler and flags
CXX      = g++
CXXFLAGS = -Wall -g $(shell pkg-config --cflags glfw3 glew)
LDFLAGS  = $(shell pkg-config --libs glfw3 glew glut) -lGL

# Directorios donde se encuentran los archivos .cpp
SOURCES_DIRS = Semana7


# Buscar todos los archivos .cpp en los directorios
CPP_FILES = $(foreach dir, $(SOURCES_DIRS), $(wildcard $(dir)/*.cpp))

# Crear una lista de los nombres de los ejecutables basados en los archivos .cpp
TARGETS = $(CPP_FILES:.cpp=)

# Default target
all: $(TARGETS)

# Regla para compilar cada archivo .cpp en su respectivo ejecutable
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

# Clean up build artifacts
clean:
	rm -f $(TARGETS)
