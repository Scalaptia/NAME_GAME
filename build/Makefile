# Detectar el sistema operativo
ifeq ($(OS),Windows_NT)
    RM := del /Q
    EXECUTABLE := Name.exe
    LIBS := -lraylib -lopengl32 -lgdi32 -lwinmm
else
    RM := rm -f
    EXECUTABLE := Name
    LIBS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Compilador y banderas del compilador
CXX := g++
CXXFLAGS := -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/

# Archivos fuente
SRC := ../src/main.cpp

# Target por defecto
all: $(EXECUTABLE)

# Compilar y enlazar los archivos fuente
$(EXECUTABLE): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Limpiar archivos generados
clean:
	$(RM) $(EXECUTABLE)
