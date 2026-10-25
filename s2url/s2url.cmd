@echo off
@rem Copyright 2025-present Alexandre Gomiero de Oliveira
@rem SPDX-License-Identifier: Apache-2.0
@rem See LICENSE in the repository root.


@IF /I [%1]==[] (
    @echo:By Gomiero ^(c^) 2025-present - Apache License 2.0
    @echo:
    @echo Converts a string to urlencode and, optionally, send it to clipboard
    @echo:    
    @echo s2url "[string]"
    @echo s2url -c "[string]"
    @echo:
    @echo  -c copy to clipboard
    @echo: 
    goto :END
)

@IF /I [%1] EQU [-c] (
    @IF "%~2" == "" (
        @echo:
        @echo:usage:
        @echo:
        @echo:s2url -c a+b
        @echo:
        goto :END
    ) ELSE (
        @python %~dp0\s2url.py %~2 | clip
        goto :END
    )
) ELSE (
    @python %~dp0\s2url.py %~1
)

:END
