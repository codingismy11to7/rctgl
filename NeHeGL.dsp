# Microsoft Developer Studio Project File - Name="NeHeGL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=NeHeGL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NeHeGL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NeHeGL.mak" CFG="NeHeGL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NeHeGL - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "NeHeGL - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NeHeGL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"RCTGL.exe"

!ELSEIF  "$(CFG)" == "NeHeGL - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"RCTGL.exe" /pdbtype:sept
# SUBTRACT LINK32 /debug

!ENDIF 

# Begin Target

# Name "NeHeGL - Win32 Release"
# Name "NeHeGL - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Example.cpp
# End Source File
# Begin Source File

SOURCE=.\glfont.cpp
# End Source File
# Begin Source File

SOURCE=.\guicon.cpp
# End Source File
# Begin Source File

SOURCE=.\NeHeGL.cpp
# End Source File
# Begin Source File

SOURCE=.\NeheResource.rc
# End Source File
# Begin Source File

SOURCE=.\rctgl.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceIO.cpp
# End Source File
# Begin Source File

SOURCE=.\skyDome.cpp
# End Source File
# Begin Source File

SOURCE=.\tga1.cpp
# End Source File
# Begin Source File

SOURCE=.\tga2.cpp
# End Source File
# Begin Source File

SOURCE=".\vr-atmospheres.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-audio.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-carride.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-display.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-elements.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-entrances.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-file.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-font.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-ghosttrain.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-init.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-input.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-invertedrollercoaster.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-landscape.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-logflume.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-menu.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-minetrain.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-monorail.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-observationtower.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-paths.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-railroad.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-rapids.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-rides.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-riverride.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-rotodrop.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-singlerailrollercoaster.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-skyway.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-slc.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-spaceshot.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-steelcorkscrewrollercoaster.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-steelmini.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-steelrollercoaster.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-steeltwisterrollercoaster.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-steelwildmouse.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-suspendedsinglerail.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-tracks.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-trees1.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-virginiareel.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-walls.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-wildmouse.cpp"
# End Source File
# Begin Source File

SOURCE=".\vr-woodenrollercoaster.cpp"
# End Source File
# Begin Source File

SOURCE="H:\program files\Microsoft Visual Studio\VC98\Lib\GLU32.LIB"
# End Source File
# Begin Source File

SOURCE="H:\program files\Microsoft Visual Studio\VC98\Lib\GLAUX.LIB"
# End Source File
# Begin Source File

SOURCE="H:\program files\Microsoft Visual Studio\VC98\Lib\OPENGL32.LIB"
# End Source File
# Begin Source File

SOURCE=.\corona.lib
# End Source File
# Begin Source File

SOURCE=.\basictemplate\CpwDLL.lib
# End Source File
# Begin Source File

SOURCE=..\..\DXSDK\lib\dxguid.lib
# End Source File
# Begin Source File

SOURCE=..\..\DXSDK\lib\dinput8.lib
# End Source File
# Begin Source File

SOURCE=..\..\DXSDK\lib\dsetup.lib
# End Source File
# Begin Source File

SOURCE=..\..\DXSDK\lib\dinput.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\GLFont.h
# End Source File
# Begin Source File

SOURCE=.\guicon.h
# End Source File
# Begin Source File

SOURCE=.\NeHeGL.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ResourceIO.h
# End Source File
# Begin Source File

SOURCE=".\vr-font.h"
# End Source File
# Begin Source File

SOURCE=.\vr3d.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\nehe.bmp
# End Source File
# End Group
# Begin Source File

SOURCE="H:\program files\Microsoft Visual Studio\VC98\Lib\WINMM.LIB"
# End Source File
# Begin Source File

SOURCE=..\..\fmod\api\lib\fmodvc.lib
# End Source File
# End Target
# End Project
