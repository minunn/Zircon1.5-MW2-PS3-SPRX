@echo off
cd /d %~dp0
WinSCP.com /script=upload.txt
if %ERRORLEVEL% neq 0 goto error
exit 0

:error
exit 0