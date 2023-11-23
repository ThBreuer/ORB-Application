@echo off

set pfad=%cd%

del __image.axf 2>>nul
rmdir /S /Q tmp 2>>nul

echo cleaning all %pfad%
echo.

for /R /D %%f in (*.*) do (
  if exist %%f\_clean.bat (
    echo ===============================================
    cd %%f
    call _clean.bat
    cd %pfad%
  )
)