include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard library/*.asm)
SOURCES_LIBRARY=$(wildcard library/*.c)
SOURCES_USER=$(wildcard userProgram/*.C)

OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_LIBRARY=$(SOURCES_LIBRARY:.asm=.o)
OBJECTS_USER=$(SOURCES_USER:.asm=.o)

all: $(MODULE)


$(MODULE): $(SOURCES) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_LIBRARY) $(OBJECTS_USER)
	$(LD) -T sampleCodeModule.ld _loader.o $(OBJECTS)  $(OBJECTS_ASM) $(OBJECTS_LIBRARY) $(OBJECTS_USER) -o ../$(MODULE)


%.o:%.c
	$(GCC) $(GCCFLAGS) -I./include -c _loader.c  $(SOURCES)

%.o:%.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o asm/*.o

.PHONY: all clean print

