# -*- coding: utf-8-unix -*-

# Copyright 2025-present Alexandre Gomiero de Oliveira
# SPDX-License-Identifier: Apache-2.0
# See LICENSE in the repository root.


import sys

digits = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]

def convert(num, base):
  ret = ""
  n = num
  while (True):
    (n, r) = divmod(n, base)
    ret += digits[r]
    if (n < 1):
      break
  return "".join(reversed(ret))

if len(sys.argv) != 3:
    print("Usage:")
    print()
    print(f"{sys.argv[0]} [base] numero")
    exit(1)
(b, n) = sys.argv[1:3]

b = int(b)
n = int(n)

if b <= 1:
    print(f"base must be bigger than 1")
    exit(2)

if b > len(digits):
    print(f"base too big: {b} max digits is: {len(digits)}")
    exit(2)
    
res = convert(n, b)
print(res)

