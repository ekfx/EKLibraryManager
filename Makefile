# variaveis
CXX = x86_64-w64-mingw32-g++
C = gcc
CFLAGS = -c
CXXFLAGS = -Iinclude -MMD -MP -O0 -g0 -pipe -ID:/vcpkg/packages/curl_x64-windows/include
LDFLAGS = -Llib-mingw-w64 -lwinmm -mconsole -LD:/vcpkg/packages/curl_x64-windows/lib
LDLIBS = -lz -lcurl
OUT = build/eklm.exe
MKDIR = if not exist build mkdir build
RM = rmdir /s /q build
RUN = $(OUT)
RUN_DEBUG = $(OUT) -debug

# pega todos arquivos fonte
SOURCES = $(wildcard src/*.cpp) $(wildcard src/*.c)

# Gera lista de objetos: cada .cpp ou .c vira um .o na pasta build, com o mesmo nome base
OBJECTS = $(addprefix build/, $(notdir $(SOURCES:.cpp=.o)))
OBJECTS := $(OBJECTS:.c=.o)

# Dependências automáticas
DEPENDS = $(OBJECTS:.o=.d)

all: build_dir compile copy_assets

run_debug:
	$(RUN_DEBUG)

run:
	$(RUN)

build_dir:
	$(MKDIR)

# Regra genérica para .cpp -> .o
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: src/%.c
	$(C) $(CFLAGS) -c $< -o $@

# Inclui dependências
-include $(DEPENDS)

compile: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(OUT)

clean:
	$(RM)

.PHONY: all clean copy_assets