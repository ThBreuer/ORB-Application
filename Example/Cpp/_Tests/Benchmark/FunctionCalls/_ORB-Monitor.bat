@echo off
set p=%cd%\%1
start "" /B "%ORB%\Tools\ORB-Monitor\ORB-Monitor.exe" -prog %p%Bin\main.hex -k %p%Src\ORB-Monitor-Tasten.txt -t "<%cd%>"

