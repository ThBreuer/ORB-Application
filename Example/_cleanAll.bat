@echo off

set pfad=%cd%

echo cleaning all %pfad%
echo.

for /R /D %%f in (*.*) do (
  if exist %%f\_clean.bat (
    cd %%f
    echo cleaning %%f
    call _clean.bat 
    cd %pfad%
  )
)
