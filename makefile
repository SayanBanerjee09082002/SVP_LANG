# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -O2

# Source files
SRCS = main.c string_datatype.c comment_remover.c lexical_analyzer/lexical_analyzer.c lexical_analyzer/keyword_analyzer.c lexical_analyzer/operator_analyzer.c

# Object files directory
OBJDIR = bin
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

# Header files
HDRS = string_datatype.h comment_remover.h lexical_analyzer/lexical_analyzer.h lexical_analyzer/keyword_analyzer.h lexical_analyzer/operator_analyzer.h lexical_analyzer/tokens.h

# Executable name
TARGET = executable

# Default target
all: $(TARGET)

# Create bin directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR) $(OBJDIR)/lexical_analyzer

# Link the object files to create the executable
$(TARGET): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c file into an object file
$(OBJDIR)/%.o: %.c $(HDRS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Phony targets
.PHONY: all clean
