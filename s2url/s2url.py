# -*- coding: utf-8-unix -*-

# Copyright 2025-present Alexandre Gomiero de Oliveira
# SPDX-License-Identifier: Apache-2.0
# See LICENSE in the repository root.


import sys
import urllib.parse

if len(sys.argv) < 2:
	print("s2url - v1.0")
	print()
	print("By Gomiero (c) 2025-2025")
	print("Licensed under the Apache License, Version 2.0.")
	print()
	print("Converte uma string para URLENCODE")
	print()
	print("s2url [string]")
	print()
	sys.exit(1)


s = sys.argv[1]
r = urllib.parse.urlencode({"a": s})[2:]
print(r)

