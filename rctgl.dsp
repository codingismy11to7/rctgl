# Microsoft Developer Studio Project File - Name="rctgl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=rctgl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rctgl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rctgl.mak" CFG="rctgl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rctgl - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "rctgl - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rctgl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "TIXML_USE_STL" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "rctgl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "TIXML_USE_STL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"rctgl.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "rctgl - Win32 Release"
# Name "rctgl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\debugLog.cpp
# End Source File
# Begin Source File

SOURCE=.\guicon.cpp
# End Source File
# Begin Source File

SOURCE=".\rctgl-camera.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-frustum.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-globals.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-init.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-input.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-landscape.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-menu.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-park.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-path.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-poly.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-texman.cpp"
# End Source File
# Begin Source File

SOURCE=".\rctgl-vertex.cpp"
# End Source File
# Begin Source File

SOURCE=.\rctgl.cpp
# End Source File
# Begin Source File

SOURCE=.\depend\tinyxml\tinyxml.cpp
# End Source File
# Begin Source File

SOURCE=.\depend\tinyxml\tinyxmlerror.cpp
# End Source File
# Begin Source File

SOURCE=.\depend\tinyxml\tinyxmlparser.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\depend\corona\corona.h
# End Source File
# Begin Source File

SOURCE=.\debugLog.h
# End Source File
# Begin Source File

SOURCE=".\rctgl-camera.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-displaymodes.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-frustum.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-init.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-input.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-landscape.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-menu.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-park.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-path.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-poly.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-rgb.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-texman.h"
# End Source File
# Begin Source File

SOURCE=".\rctgl-vertex.h"
# End Source File
# Begin Source File

SOURCE=.\rctgl.h
# End Source File
# Begin Source File

SOURCE=.\depend\tinyxml\tinyxml.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
