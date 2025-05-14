@echo off
echo %cd%
%ORB%\Tools\Flash\DfuSe\DfuSeCommand -c -d --v --fn %1
pause
exit
