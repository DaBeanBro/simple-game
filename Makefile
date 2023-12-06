print-%:; @echo $($*)

CC = gcc
LD = gcc

# library paths
PATH_LIB = lib
PATH_SDL = $(PATH_LIB)/SDL

INCFLAGS = -Isrc -Iinclude


CCFLAGS  = -std=c2x
CCFLAGS += -O2
CCFLAGS += -g
CCFLAGS += -fbracket-depth=1024
CCFLAGS += -fmacro-backtrace-limit=0
CCFLAGS += -Wall
CCFLAGS += -Wextra
CCFLAGS += -Wpedantic
CCFLAGS += -Wfloat-equal
CCFLAGS += -Wstrict-aliasing
CCFLAGS += -Wswitch-default
CCFLAGS += -Wformat=2
CCFLAGS += -Wno-newline-eof
CCFLAGS += -Wno-unused-parameter
CCFLAGS += -Wno-strict-prototypes
CCFLAGS += -Wno-fixed-enum-extension
CCFLAGS += -Wno-int-to-void-pointer-cast
CCFLAGS += -Wno-gnu-statement-expression
CCFLAGS += -Wno-gnu-compound-literal-initializer
CCFLAGS += -Wno-gnu-zero-variadic-macro-arguments
CCFLAGS += -Wno-gnu-empty-struct
CCFLAGS += -Wno-gnu-auto-type
CCFLAGS += -Wno-gnu-empty-initializer
CCFLAGS += -Wno-gnu-pointer-arith
CCFLAGS += -Wno-c99-extensions
CCFLAGS += -Wno-c11-extensions

LDFLAGS = -lm

BIN = bin
SRC = $(shell find src -name "*.c")
OBJ = $(SRC:%.c=$(BIN)/%.o)
DEP = $(SRC:%.c=$(BIN)/%.d)
OUT = $(BIN)/main

-include $(DEP)

UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
    SDL2_PREFIX := $(shell brew --prefix sdl2)
    INCFLAGS += -I$(SDL2_PREFIX)/include/SDL2
    LDFLAGS += -L$(SDL2_PREFIX)/lib -lSDL2
else ifeq ($(UNAME),Linux)
    LDFLAGS += -lSDL2
endif

$(BIN):
	mkdir -p $@

dirs: $(BIN)
	rsync -a --include '*/' --exclude '*' "src" "bin"

$(OBJ): $(BIN)/%.o: %.c
	$(CC) -o $@ -MMD -c $(CCFLAGS) $(INCFLAGS) $<

main: dirs $(OBJ)
	$(LD) -o $(OUT) $(OBJ) $(LDFLAGS)

all: dirs main

clean:
	rm -rf bin
