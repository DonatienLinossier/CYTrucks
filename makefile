#    project_name/
#    |-- progc/
#    |   |-- src/
#    |   |   |-- main.c
#    |   |   |-- module1.c
#    |   |   |-- module2.c
#    |   |
#    |   |-- include/
#    |   |   |-- project_name.h
#    |   |   |-- module1.h
#    |   |   |-- module2.h
#    |   |
#    |   |-- build/
#    |   |   |-- (Generated build artifacts go here)
#    |   |
#    |   |-- bin/
#    |       |-- (Executable file goes here after compilation)
#    |
#    |-- plot/
#    |   |-- (Scripts for GNUPlot rendering)
#    |
#    |-- data/
#    |   |-- (Data files go here | Input )
#    |
#    |-- temp/
#    |   |-- (Temporary files go here | tmp )
#    |
#    |-- images/
#    |   |-- (Image files go here | Output)
#    |
#    |-- demo/
#    |   |-- (Demo files go here | last executions)
#    |
#    |-- constant.sh
#    |-- ShellD.sh	
#    |-- truckAnalyse.sh	
#    |-- Makefile
#    |-- README.md

.PHONY: moveImagesToDemo cleanCompilation cleanTemp cleanDemo cleanImg clean createDir createCompDir createDataDir


# Compiler
CC=gcc

# Compiler flags
CFLAGS= -lm #-wall

PROGC=progc
SRCDIR=$(PROGC)/src
OBJDIR=$(PROGC)/build
BINDIR=$(PROGC)/bin

DATADIR=data
DEMODIR=demo
IMGDIR=images
TEMPDIR=temp


# Source files
SRCS=$(wildcard $(SRCDIR)/*.c)

# Object files
OBJS=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Executable name
EXEC=$(BINDIR)/main

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)

# Compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

createCompDir: $(OBJDIR) $(BINDIR)

createDir: $(IMGDIR) $(TEMPDIR) $(DEMODIR)

createDataDir: $(DATADIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(DEMODIR):
	mkdir -p $(DEMODIR)

$(IMGDIR):
	mkdir -p $(IMGDIR)

$(DATADIR):
	mkdir -p $(DATADIR)

$(TEMPDIR):
	mkdir -p $(TEMPDIR)




cleanCompilation:
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*

cleanTemp : 
	rm -rf $(TEMPDIR)/*

cleanDemo :
	rm -rf $(DEMODIR)/*

cleanImg :
	rm -rf $(IMGDIR)/*

clean: cleanCompilation cleanTemp cleanTemp cleanImg cleanDemo

moveImagesToDemo:
	@echo "Moving files from last execution to $(DEMODIR)/OutputX"
	@if [ -n "$$(ls -A $(IMGDIR))" ]; then \
		number=$$(ls -l $(DEMODIR) | grep "^d" | wc -l); \
		output="$(DEMODIR)/Output$$number"; \
		mkdir -p "$$output"; \
		mv images/* "$$output"; \
		echo "  Files from $(IMGDIR) moved to $$output"; \
	else \
		echo "  No files from last execution. No files moved."; \
    fi
