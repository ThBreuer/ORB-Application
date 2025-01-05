@echo off

set pfad=%cd%

echo.

for /R /D %%f in (*.*) do (
    cd %%f
    echo cleaning %%f
    del *.bin 2> nul
    cd %pfad%
)
