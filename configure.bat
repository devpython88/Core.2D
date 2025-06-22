@echo off
setlocal

REM === Argument checks ===
IF "%~1"=="" (
    echo No dist directory name provided [arg 1]
    exit /b 1
)
SET "DIST_DIR=%~1"

IF "%~2"=="" (
    echo No cmake generator provided [arg 2]
    exit /b 1
)
SET "BUILD_GEN=%~2"

IF "%~3"=="" (
    echo No build system executable provided [arg 3]
    exit /b 1
)
SET "BUILD_SYS=%~3"

REM === Configure and build ===
IF NOT EXIST build (
    mkdir build
)

cd build

cmake -G "%BUILD_GEN%" ..
IF ERRORLEVEL 1 (
    echo cmake configuration failed.
    exit /b 1
)

"%BUILD_SYS%"
IF ERRORLEVEL 1 (
    echo build failed.
    exit /b 1
)

mkdir "%DIST_DIR%\lib" 2>nul
mkdir "%DIST_DIR%\include" 2>nul

REM === Copy .a and .lib files to dist/lib ===
copy /Y .\*.a "%DIST_DIR%\lib\" >nul 2>&1
copy /Y .\*.lib "%DIST_DIR%\lib\" >nul 2>&1

REM === Copy headers to dist/include ===
copy /Y ..\src\*.h "%DIST_DIR%\include\" >nul 2>&1

echo Distribution prepared in "%DIST_DIR%"
