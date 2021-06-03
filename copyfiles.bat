echo off

REM to make the copy files

set scrdir=%~dp0
set dstdir=%scrdir%msvc2010_64

call :copy_directory bin
call :copy_directory doc
call :copy_directory include
call :copy_directory lib
call :copy_directory mkspecs
call :copy_directory plugins

goto :exit_out

:copy_directory

set curd=%~1
set curdst=%dstdir%\%curd%
set cursrc=%scrdir%%curd%

if exist %curdst% (
	rd /s /q %curdst%
)
md %curdst%

xcopy /s /e %cursrc% %curdst%

exit /b 0

:exit_out