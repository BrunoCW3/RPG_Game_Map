CC     = gcc
CFLAGS = -Wall -std=c99
LIBS   = -lm
TARGET = rpg.exe
SRCS   = main.c matrizes.c revelador.c movimentacao.c

all: $(TARGET)

$(TARGET): $(SRCS) matrizes.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	del /Q $(TARGET) 2>NUL || rm -f $(TARGET)
