@echo off
echo Cleaning project ...
rmdir /S /Q .\Bin             2>> nul
rmdir /S /Q .\Bin             2>> nul

del .\Lib\uVision\*.uvgui.*   2>> nul
del .\Lib\uVision\*.bin       2>> nul

del .\Lib\EmBitz\*.bin        2>> nul
del .\Lib\EmBitz\*.elay       2>> nul
del .\Lib\EmBitz\*.eds        2>> nul
del .\Lib\EmBitz\*.ebd        2>> nul

del ~image.bin                2>> nul

echo done.