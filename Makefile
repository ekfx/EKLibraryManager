CXX = g++
CXXFLAGS = -Iinclude -MMD -MP -O0 -g0 -pipe
LDFLAGS = -Llib-mingw-w64 -lwinmm -mconsole
OUT = build/EKLibraryManager.exe
MKDIR = if not exist build mkdir build
RM = rmdir /s /q build

# Arquivos fonte
SOURCES = $(wildcard src/*.cpp)

# Gera lista de objetos: cada .cpp ou .c vira um .o na pasta build, com o mesmo nome base
OBJECTS = $(addprefix build/, $(notdir $(SOURCES:.cpp=.o)))
OBJECTS := $(OBJECTS:.c=.o)

# Dependências automáticas
DEPENDS = $(OBJECTS:.o=.d)

all: build_dir compile copy_assets

build_dir:
	$(MKDIR)

# Regra genérica para .cpp -> .o
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Inclui dependências
-include $(DEPENDS)

compile: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $(OUT)

copy_assets:
	$(CP_ASSETS)

clean:
	$(RM)

.PHONY: all clean copy_assets