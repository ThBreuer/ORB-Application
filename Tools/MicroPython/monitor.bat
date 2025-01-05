echo.

echo ### Compiling
echo Directory: %cd%
echo Program: %1

"%ORB%\Tools\MicroPython\mpy-build.exe" -f "%~1.py" -o "%~1.bin"

rmdir /S /Q .\Bin     2>>nul

echo ### Starting Monitor

if exist "%cd%\%~1.keys.txt" (
    set keyfile="%cd%\%~1.keys.txt"
) else (
    set keyfile="%cd%\ORB-Monitor-Tasten.txt"
)
start "" "%ORB%\Tools\ORB-Monitor\ORB-Monitor.exe" -prog "%cd%\%~1.bin" -title "%cd%" -keys %keyfile%

echo ### Finished
