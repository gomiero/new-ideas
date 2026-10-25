# Copyright 2025-present Alexandre Gomiero de Oliveira
# SPDX-License-Identifier: Apache-2.0
# See LICENSE in the repository root.

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11

ifeq ($(OS),Windows_NT)
TARGET = gtime.exe
else
TARGET = gtime
endif

.PHONY: all debug clean FORCE

all: $(TARGET)

$(TARGET): gtime.c FORCE
	$(CC) $(CPPFLAGS) $(CFLAGS) -O3 -s $(LDFLAGS) -o $@ $< $(LDLIBS)

debug:
	$(CC) $(CPPFLAGS) $(CFLAGS) -O0 -g3 $(LDFLAGS) -o $(TARGET) gtime.c $(LDLIBS)

FORCE:

clean:
	$(RM) gtime gtime.exe
