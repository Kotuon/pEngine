; -- 64Bit.iss --
; Demonstrates installation of a program built for the x64 (a.k.a. AMD64)
; architecture.
; To successfully run this installation and the program it installs,
; you must have a "x64" edition of Windows.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]

AppId={{C061D781-F8DB-4E28-AB2E-C45E8BE048DC}}
AppName=pEngine
AppVersion=1.0

WizardStyle=modern
DefaultDirName={autopf}\pEngine
DefaultGroupName=pEngine
UninstallDisplayIcon={app}\pEngine.exe
Compression=lzma2
SolidCompression=yes
OutputDir=.\installer_ouput  
PrivilegesRequired=none
OutputBaseFilename=pEngine_Setup

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"

[Files]
Source: ".\game_directory\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: ".\installer_files\*"; DestDir: "{userdocs}\pEngine\"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\pEngine"; Filename: "{app}\pEngine.exe"; WorkingDir:{app}
Name: "{group}\{cm:UninstallProgram,pEngine}"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\pEngine.exe"; Description: "{cm:LaunchProgram,pEngine}"; Flags: nowait postinstall skipifsilent

[UninstallDelete]


