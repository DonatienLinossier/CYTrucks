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
#    |-- Shell.sh	
#    |-- Makefile
#    |-- README.md



DATA_DIR = data
C_DIR = progc
	SRC_DIR = $(C_DIR)/src
	INCLUDE_DIR = $(C_DIR)/include
	BUILD_DIR = $(C_DIR)/build
	BIN_DIR = $(C_DIR)/bin

GNU_DIR = gnuplot
TEMP_DIR = temp
IMAGES_DIR = images
DEMO_DIR = demo

createDirs:
	mkdir -p $(DATA_DIR) $(BUILD_DIR) $(BIN_DIR) $(TEMP_DIR) $(IMAGES_DIR) $(DEMO_DIR)


cleanAll : cleanData cleanBuild cleanBin cleanTemp cleanImages cleanDemo

#Clean
cleanData : 
	rm -f $(DATA_DIR)/*

cleanBuild : 
	rm -f $(BUILD_DIR)/*

cleanBin : 
	rm -f $(BIN_DIR)/*

cleanTemp : 
	rm -f $(TEMP_DIR)/*

cleanImages :
# on copie le dossier images dans demo 
# question enregistre t-on plusieurs demos ??
	rm -f $(IMAGES_DIR)/*

cleanDemo : 
	rm -f $(DEMO_DIR)/*






