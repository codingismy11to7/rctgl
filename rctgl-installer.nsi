; example2.nsi
;
; This script is based on example1.nsi, but it remember the directory, 
; has uninstall support and (optionally) installs start menu shortcuts.
;
; It will install makensisw.exe into a directory that the user selects,

;--------------------------------

; The name of the installer
Name "RCTGL"

; The file to write
OutFile "SetupRCTGL.exe"

; The default installation directory
InstallDir $PROGRAMFILES\RCTGL

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\RCTGL" ""

;--------------------------------

; Pages

Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "RCTGL (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File ".\rctgl.exe"
  File ".\SERPNTB.TTF"
  File ".\corona.dll"
  File ".\CpwDLL.dll"
  File ".\rctColors.dat"

  SetOutPath $INSTDIR\surfaces
  File ".\surfaces\*.tga"
  File ".\surfaces\*.png"

  SetOutPath $INSTDIR\edges
  File ".\edges\*.tga"

  SetOutPath $INSTDIR\paths
  File ".\paths\*.tga"

  SetOutPath $INSTDIR
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\RCTGL "Path" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RCTGL" "DisplayName" "RCTGL"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RCTGL" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RCTGL" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RCTGL" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\RCTGL"
  CreateShortCut "$SMPROGRAMS\RCTGL\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\RCTGL\RCTGL.lnk" "$INSTDIR\rctgl.exe" "" "$INSTDIR\rctgl.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\RCTGL"
  DeleteRegKey HKLM SOFTWARE\RCTGL

  ; Remove files and uninstaller
  Delete $INSTDIR\rctgl.exe
  Delete $INSTDIR\SERPNTB.TTF
  Delete $INSTDIR\corona.dll
  Delete $INSTDIR\CpwDLL.dll
  Delete $INSTDIR\rctColors.dat
  Delete $INSTDIR\uninstall.exe

  Delete "$INSTDIR\edges\*.*"
  RMDir $INSTDIR\edges

  Delete "$INSTDIR\surfaces\*.*"
  RMDir $INSTDIR\surfaces

  Delete "$INSTDIR\paths\*.*"
  RMDir $INSTDIR\paths

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\RCTGL\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\RCTGL"
  RMDir "$INSTDIR"

SectionEnd