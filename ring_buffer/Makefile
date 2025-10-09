# ===============================
# Makefile for Ring Buffer Library
# ===============================

# Compiler and flags
CC = gcc
CFLAGS = -Iring_buffer_lib/include -Iring_buffer_source/test -Wall -O2

# Archiver for static library
AR = ar
ARFLAGS = rcs

# Source files and object files
SRC = ring_buffer_source/src/ring_buffer.c
OBJ = ring_buffer_source/obj/ring_buffer.o

# Static library
LIB = ring_buffer_lib/lib/ring_buffer.a

# Test files
TEST_SRC = ring_buffer_source/test/test.c
TEST_OBJ = ring_buffer_source/obj/test.o

# Executable (add .exe for Windows if needed)
EXE_EXT =
TEST_EXE = ring_buffer_source/build/tests$(EXE_EXT)

# ===============================
# Configuration
# ===============================
BUFFER_SIZE ?= 16
VOLATILE ?= 0

# Inject configuration into compiler flags
CFLAGS += -DRB_VOLATILE_SIZE=$(BUFFER_SIZE)
ifeq ($(VOLATILE), 1)
	CFLAGS += -DRB_VOLATILE_SET
endif

# ===============================
# Phony targets
# ===============================
.PHONY: all lib test clean clean-lib clean-test

# ===============================
# Default target
# ===============================
all: $(LIB) $(TEST_EXE)

# ===============================
# Ensure directories exist
# ===============================
$(OBJ): | ring_buffer_source/obj
$(TEST_OBJ): | ring_buffer_source/obj
$(TEST_EXE): | ring_buffer_source/build
$(LIB): | ring_buffer_lib

ring_buffer_source/obj:
	mkdir -p $@

ring_buffer_source/build:
	mkdir -p $@

ring_buffer_lib:
	mkdir -p $@

# ===============================
# Build object files
# ===============================
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJ): $(TEST_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# ===============================
# Build library
# ===============================
$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

# ===============================
# Build test executable
# ===============================
$(TEST_EXE): $(TEST_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# ===============================
# Shortcuts for building individual targets
# ===============================
lib: $(LIB)
test: $(TEST_EXE)

# ===============================
# Clean targets
# ===============================
clean-lib:
	rm -f $(OBJ) $(LIB)

clean-test:
	rm -f $(TEST_OBJ) $(TEST_EXE)

# Clean everything
clean: clean-lib clean-test
