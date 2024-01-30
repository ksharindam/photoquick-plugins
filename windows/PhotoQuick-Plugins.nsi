; HM NIS Edit Wizard helper defines
!define PROG_NAME "PhotoQuick Plugins"
!define PROG_VERSION "1.1.0"
!define PROG_PUBLISHER "Arindamsoft"
!define PROG_ICON "photoquick-plugins.ico"
!define ICON_PATH "${PROG_ICON}"
!define LICENSE_PATH "..\LICENSE.txt"

!define PRODUCT_DIR_REGKEY "Software\${PROG_NAME}"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PROG_NAME}"

; Get installation directory of main Photoquick program
InstallDir "$PROGRAMFILES\PhotoQuick"
InstallDirRegKey HKLM "Software\PhotoQuick" ""

Name "${PROG_NAME}"
OutFile "${PROG_NAME}-${PROG_VERSION}.exe"
SetCompressor lzma

; Required Plugins
!include "Sections.nsh"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${ICON_PATH}"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; MUI pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "${LICENSE_PATH}"
;!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES
; Language files
!insertmacro MUI_LANGUAGE "English"
; MUI end ------

; This shows version info in installer, VIFileVersion and VIProductVersion must be in x.x.x.x format
VIProductVersion "${PROG_VERSION}.0"
VIFileVersion "${PROG_VERSION}.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "PhotoQuick Plugins"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "PhotoQuick Image Viewer Plugins"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Arindamsoft Co."
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${PROG_VERSION}.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Arindam Chaudhuri <ksharindam@gmail.com>"


!define BUILDDIR      "..\src"

Function .onInit
  ReadRegStr $0 HKLM "Software\PhotoQuick" ""
  ${IF} $0 == ""
    Messagebox MB_ICONSTOP|MB_OK "PhotoQuick not installed. Please install PhotoQuick first"
    Abort
  ${ENDIF}
FunctionEnd

; Components

Section "Main Components" SecMain
  SectionIn RO ; Read only, always installed
  SetOutPath "$INSTDIR\plugins"
  SetOverwrite try
  File "${ICON_PATH}"
SectionEnd

Section "Grayscale Local" SecGrayLoc
  File "${BUILDDIR}\grayscale-local.dll"
SectionEnd

Section "Stretch Histogram" SecStHist
  File "${BUILDDIR}\stretch-histogram.dll"
SectionEnd

Section "Photo Frame" SecPhotoFrame
  File "${BUILDDIR}\photo-frame.dll"
SectionEnd

Section "Kuwahara" SecKuwahara
  File "${BUILDDIR}\kuwahara.dll"
SectionEnd

Section "Tone Mapping" SecTonMap
  File "${BUILDDIR}\tone-mapping.dll"
SectionEnd

Section "Barcode Generator" SecBarcodeGen
  File "${BUILDDIR}\barcode-generator.dll"
SectionEnd

Section "Histogram Viewer" SecHistView
  File "${BUILDDIR}\histogram-viewer.dll"
SectionEnd

Section "Pixart Scaler" SecPixartScale
  File "${BUILDDIR}\pixart-scaler.dll"
SectionEnd


Section -Post
  WriteUninstaller "$INSTDIR\plugins\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\plugins\${PROG_ICON}"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PROG_VERSION}"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "Publisher" "${PROG_PUBLISHER}"
  WriteRegStr HKLM "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\plugins\uninst.exe"
SectionEnd


Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Do you really want to completely remove $(^Name)?" IDYES +2
  Abort
FunctionEnd

; Here INSTDIR is PhotoQuick\plugins , i.e same directory where uninst.exe exists
Section Uninstall
  ; Must remove uninstaller first
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\grayscale-local.dll"
  Delete "$INSTDIR\stretch-histogram.dll"
  Delete "$INSTDIR\photo-frame.dll"
  Delete "$INSTDIR\kuwahara.dll"
  Delete "$INSTDIR\tone-mapping.dll"
  Delete "$INSTDIR\histogram-viewer.dll"
  Delete "$INSTDIR\barcode-generator.dll"
  Delete "$INSTDIR\pixart-scaler.dll"
  Delete "$INSTDIR\${PROG_ICON}"
  RMDir "$INSTDIR"

  DeleteRegKey HKLM "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd
