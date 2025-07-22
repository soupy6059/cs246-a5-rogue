# Simple Makefile for C++ projects
# Project structure:
# project/
# ├── src/        (source files)
# ├── inc/        (header files)
# ├── build/      (object files, created automatically)
# └── Makefile

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -O0
TARGET = main

# Compiler and flags
INCLUDES = -Iinc

# Directories
SRCDIR = src
INCDIR = inc
BUILDDIR = build

# Find all .cc files in src directory
SOURCES = $(wildcard $(SRCDIR)/*.cc)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cc=$(BUILDDIR)/%.o)

# Default target
all: $(TARGET)

# Build the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)
	@echo "Build complete: $(TARGET)"

# Compile source files to object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cc
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILDDIR) $(TARGET)
	@echo "Clean complete"

# Rebuild everything
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET) "assets/carter-level.txt"

# Debug build
debug: CXXFLAGS += -DDEBUG -g3 -O0
debug: $(TARGET)

# Declare phony targets
.PHONY: all clean rebuild install run debug release help
