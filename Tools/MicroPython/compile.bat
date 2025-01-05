echo.

echo ### Compiling
echo Directory: %cd%
echo Program: %1

"%ORB%\Tools\MicroPython\mpy-build.exe" -f "%~1.py" -o "%~1.bin"

rmdir /S /Q .\Bin     2>>nul

echo ### Finished
