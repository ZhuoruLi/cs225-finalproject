EXE = main
RELEASE = ../releases/solution
TEST = test

# Add all object files needed for the compiling.
EXE_OBJ = main.o
OBJS = main.o graph.o route.o airport.o \
	  		stickers/StickerSheet.o stickers/Image.o

# bfs specific
CPP_FILES += $(wildcard bfs/*.cpp)
OBJS += $(CPP_FILES:.cpp=.o)

# Generated files
CLEAN_RM = *.o *.d tests/*.o tests/*.d \
				csv_parser/*.o csv_parser/*.d 

# Use the makefile template:
include cs225/make/cs225.mk