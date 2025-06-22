# Compilador y flags
CXX      = g++
CXXFLAGS = -Wall -g -Iinclude $(shell pkg-config --cflags glfw3 glew)
LDFLAGS  = $(shell pkg-config --libs glfw3 glew glut) -lGL

# Directorios
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Archivos fuente y objeto
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Nombre del ejecutable final
TARGET = $(BIN_DIR)/main

# Regla por defecto
all: $(TARGET)

# Enlazar el ejecutable a partir de los objetos
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilar cada .cpp en su .o correspondiente
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar el programa
run: all
	./$(TARGET)

# Limpiar archivos objeto y ejecutables
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
