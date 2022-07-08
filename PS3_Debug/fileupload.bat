@echo off
setlocal
cd /d %~dp0
echo user Shark> ftpcmd.dat
echo Admin>> ftpcmd.dat
echo bin>> ftpcmd.dat
echo cd /dev_hdd0/tmp>>ftpcmd.dat
echo put Vertigo.sprx>> ftpcmd.dat
echo quit>> ftpcmd.dat
ftp -n -s:ftpcmd.dat 192.168.0.75
del ftpcmd.dat