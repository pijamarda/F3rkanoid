@echo off
setlocal

set IMAGE=f3rkanoid-builder
set OUTPUT=dist\windows

where docker >nul 2>&1
if errorlevel 1 (
    echo ERROR: Docker not found. Make sure Docker Desktop is running.
    exit /b 1
)

echo =^> Building Docker image...
echo    First run compiles SFML from source ~5 min, subsequent runs use the cache.
docker build -f Dockerfile.build -t %IMAGE% .
if errorlevel 1 ( echo ERROR: Docker build failed. & exit /b 1 )

echo =^> Extracting artifacts from container...
for /f "tokens=*" %%i in ('docker create %IMAGE%') do set CONTAINER=%%i
if errorlevel 1 ( echo ERROR: docker create failed. & exit /b 1 )

if not exist %OUTPUT% mkdir %OUTPUT%
docker cp %CONTAINER%:/workspace/dist/. %OUTPUT%
docker rm %CONTAINER% >nul

echo.
echo =^> Done!  Distribution folder: %OUTPUT%
echo    Run the game:  %OUTPUT%\f3rkanoid.exe
