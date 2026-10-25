@echo off
@rem Copyright 2025-present Alexandre Gomiero de Oliveira
@rem SPDX-License-Identifier: Apache-2.0
@rem See LICENSE in the repository root.


@rem Screenshot generator using Chrome Headless

@rem === CONFIGS ===
@set "PAGE_WIDTH=1280"
@set "PAGE_HEIGHT=16384"
@set "CHROME_EXE=%USERPROFILE%\AppData\Local\Google\Chrome\Application\chrome.exe"

@rem === ARGUMENTS ===
@set "OUTPUT_FILE=%~1"
@set "TARGET_URL=%~2"
@set "SCRIPT_DIR=%~dp1"

@rem === DEBUG ===
echo Output: %OUTPUT_FILE%
echo URL: %TARGET_URL%
echo Dir: %SCRIPT_DIR%

@rem === BUILD CHROME COMMAND ===
@set "CHROME_ARGS=--headless --disable-cloud-import --disable-background-networking --no-first-run --disable-gpu --enable-logging --hide-scrollbars --window-size=%PAGE_WIDTH%,%PAGE_HEIGHT% --screenshot="%SCRIPT_DIR%%OUTPUT_FILE%" "%TARGET_URL%""

@rem === EXECUTE ===
@pushd "%SCRIPT_DIR%"
"%CHROME_EXE%" %CHROME_ARGS% 2>nul
@popd
