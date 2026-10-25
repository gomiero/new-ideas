$(warning Start)

# Copyright 2025-present Alexandre Gomiero de Oliveira
# SPDX-License-Identifier: Apache-2.0
# See LICENSE in the repository root.



EXE_NAME=gtime

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

CC = gcc
CXX = g++
CFLAGS += -s -Wall -pedantic -Werror -O3

ifdef DEBUG
CFLAGS += -g -DDEBUG -D__DEBUG -D__DEBUG__
endif

CXXFLAGS += $(CFLAGS)

LDFLAGS= # -L./lib
LIBS = # -lm

EXE = $(subst .c,,$(SRC))

TARGET = $(EXE_NAME)


.PHONY: all clean

all:$(EXE_NAME)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

# $@ -> output
# $< -> input

clean:
	rm -rf *.o 

dist-clean:
	rm -rf *.o $(TARGET)
