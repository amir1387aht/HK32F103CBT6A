@echo off
REM 删除当前目录的文件夹及子目录的文件夹
for /f "delims=" %%a in ('dir /b/s/ad') do (
    REM 以下用于删除KEIL创建的文件夹
    if "%%~na"=="DebugConfig" rd /s /q "%%a" 2>nul
    if "%%~na"=="Listings" rd /s /q "%%a" 2>nul
    if "%%~na"=="Objects" rd /s /q "%%a" 2>nul
    
    REM 以下用于删除IAR创建的文件夹
    if "%%~na"=="Debug" rd /s /q "%%a" 2>nul
    if "%%~na"=="settings" rd /s /q "%%a" 2>nul
)

REM 当前目录及子目录的对应后缀名的文件
for /f "delims=" %%i in ('dir /b /a-d /s "*.bak"') do del /a/f/q "%%i"
for /f "delims=" %%i in ('dir /b /a-d /s "*.plg"') do del /a/f/q "%%i"
for /f "delims=" %%i in ('dir /b /a-d /s "*.dep"') do del /a/f/q "%%i"
for /f "delims=" %%i in ('dir /b /a-d /s "*.scvd"') do del /a/f/q "%%i"
for /f "delims=" %%i in ('dir /b /a-d /s "*.ini"') do del /a/f/q "%%i"
for /f "delims=" %%i in ('dir /b /a-d /s "*.uvguix.*"') do del /a/f/q "%%i"
for /f "delims=" %%i in ('dir /b /a-d /s "*.txt"') do del /a/f/q "%%i"

针对IAR多工程删除多创建的文件夹
for /D %%i in ("../EWARM/*") do (
	rd /s /q "%%i"
)

exit