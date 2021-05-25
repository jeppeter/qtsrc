

set "srcpath=%~dp0"
set "configure=%srcpath%qtbase\configure.bat"
set "util=%srcpath%utils.py"
set INCLUDE_PATH=D:\opengles\include
set LIB_PATH=D:\opengles\x86-64

python.exe "%util%" checkenvpath INCLUDE "%INCLUDE_PATH%"  && goto check_libpath

set INCLUDE=%INCLUDE%;%INCLUDE_PATH%
echo "INCLUDE [%INCLUDE%]"

:check_libpath
python.exe "%util%" checkenvpath LIBPATH "%LIB_PATH%" && goto check_lib

set LIBPATH=%LIBPATH%;%LIB_PATH%
echo "LIBPATH [%LIBPATH%]"

:check_lib

python.exe "%util%" checkenvpath LIB "%LIB_PATH%" && goto run_configure
set LIB=%LIB%;%LIB_PATH%
echo "LIB [%LIB%]"

:run_configure
"%configure%" -opensource -confirm-license