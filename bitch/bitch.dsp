# Microsoft Developer Studio Project File - Name="bitch" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=bitch - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bitch.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bitch.mak" CFG="bitch - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bitch - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "bitch - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bitch - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
Bbitch32=bbitchmake.exe
# ADD BASE Bbitch32 /nologo
# ADD Bbitch32 /nologo
Rbitch=rc.exe
# ADD BASE Rbitch /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD Rbitch /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR /YX /FD /c
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419
BSC32=bscmake.exe
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /map /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "bitch - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
Bbitch32=bbitchmake.exe
# ADD BASE Bbitch32 /nologo
# ADD Bbitch32 /nologo
Rbitch=rc.exe
# ADD BASE Rbitch /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD Rbitch /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x419
# ADD RSC /l 0x419
BSC32=bscmake.exe
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /map /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "bitch - Win32 Release"
# Name "bitch - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bitch.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\crash_exception_attacher.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\crash_exception_handler.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\crash_version_mini.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\crash_version_windows.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\file.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\file_walker.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\mmf.cpp
# End Source File
# Begin Source File

SOURCE=..\Shared\search_bmh.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Shared\crash_exception_handler.h
# End Source File
# Begin Source File

SOURCE=..\Shared\crash_version_mini.h
# End Source File
# Begin Source File

SOURCE=..\Shared\crash_version_windows.h
# End Source File
# Begin Source File

SOURCE=..\Shared\file.h
# End Source File
# Begin Source File

SOURCE=..\Shared\file_walker.h
# End Source File
# Begin Source File

SOURCE=..\Shared\mmf.h
# End Source File
# Begin Source File

SOURCE=..\Shared\search_bmh.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\Shared\DbgHelp.Lib
# End Source File
# End Target
# End Project
