@echo off
REM *****************************************************************
REM CMNVARS.BAT - common environment variables
REM *****************************************************************
REM NOTE: All batch files to set the environment must call this batch
REM       file at the end.

REM Set the version numbers
set OWBLDVER=20
set OWBLDVERSTR=2.0
set OWBLDVERTOOL=1300

REM Set up default path information variables
if not "%OWDEFPATH%" == "" goto defpath_set
set OWDEFPATH=%PATH%;
set OWDEFINCLUDE=%INCLUDE%
set OWDEFWATCOM=%WATCOM%
:defpath_set

REM Subdirectory to be used for building OW build tools
if "%OWOBJDIR%" == "" set OWOBJDIR=binbuild

REM Subdirectory to be used for build binaries
set OWBINDIR=%OWROOT%\build\%OWOBJDIR%

REM Subdirectory containing OW sources
set OWSRCDIR=%OWROOT%\bld

REM Subdirectory containing documentation sources
set OWDOCSDIR=%OWROOT%\docs

REM Set environment variables
set PATH=%OWBINDIR%;%OWROOT%\build;%OWDEFPATH%
set INCLUDE=%OWDEFINCLUDE%
set WATCOM=%OWDEFWATCOM%

REM Set the toolchain version to OWTOOLSVER variable
set OWTOOLSVER=0
if not '%OWTOOLS%' == 'WATCOM' goto no_watcom
echo set OWTOOLSVER=__WATCOMC__>getversi.gc
wcc386 -p getversi.gc >getversi.bat
call getversi.bat
del getversi.*
:no_watcom

REM OS specifics

REM setup right COMSPEC for non-standard COMSPEC setting on NT based systems
if not '%OS%' == 'Windows_NT' goto no_windows_nt
if '%NTDOS%' == '1' goto no_windows_nt
set COMSPEC=%WINDIR%\system32\cmd.exe
set COPYCMD=/y
:no_windows_nt

echo Open Watcom build environment
