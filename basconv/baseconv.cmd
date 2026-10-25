@echo off
@rem Copyright 2025-present Alexandre Gomiero de Oliveira
@rem SPDX-License-Identifier: Apache-2.0
@rem See LICENSE in the repository root.


@set "SCRIPT=%~dp0baseconv.py"
@python %SCRIPT% %1 %2
