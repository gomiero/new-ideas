# -*- coding: utf-8-unix -*-

# Copyright 2025-present Alexandre Gomiero de Oliveira
# SPDX-License-Identifier: Apache-2.0
# See LICENSE in the repository root.


import binascii
import struct
import sys


# convert a bitcoin private key from hexadecimal to decimal

if len(sys.argv) < 2:
    print(f"Usage: python {sys.argv[0]} <str hex 256>")
    exit(1)

numstr = sys.argv[1]
if len(numstr) != 64:
    print("Chave invalida (64 bytes). Verifique zeros a esquerda")
    exit(1)
numbytes = binascii.unhexlify(numstr)
n1,n2,n3,n4 = struct.unpack(">QQQQ", numbytes)
result = n1 << 192 | n2 << 128 | n3 << 64 | n4
print(result)
