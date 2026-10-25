# Copyright 2025-present Alexandre Gomiero de Oliveira
# SPDX-License-Identifier: Apache-2.0
# See LICENSE in the repository root.

CC = gcc
CFLAGS ?= -O2 -Wall -Wextra -std=c11

ifeq ($(OS),Windows_NT)
TARGET = gtime.exe
else
TARGET = gtime
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): gtime.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

clean:
	$(RM) gtime gtime.exe
