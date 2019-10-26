[Setup]
AppName=Licenser
AppVersion=0.11-2
WizardStyle=modern
DefaultDirName={autopf}\Licenser
DefaultGroupName=Licenser
UninstallDisplayIcon={app}\licenser.exe
Compression=lzma2
SolidCompression=yes
ChangesEnvironment=yes

[Files]
Source: "build\Release\licenser.exe"; DestDir: "{app}"; DestName: "licenser.exe"

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; \
    ValueType: expandsz; ValueName: "PATH"; ValueData: "{olddata};{app}"; \
    Check: NeedsAddPath('{app}')
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment";  ValueName: "PATH"; ValueData: "{app}";

[Code]
function NeedsAddPath(Param: string): boolean;
var
  OrigPath: string;
begin
  if not RegQueryStringValue(HKEY_LOCAL_MACHINE,
    'SYSTEM\CurrentControlSet\Control\Session Manager\Environment',
    'Path', OrigPath)
  then begin
    Result := True;
    exit;
  end;
  Result := Pos(';' + Param + ';', ';' + OrigPath + ';') = 0;
end;
const
  EnvironmentKey = 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment';

//procedure RemovePath(Path: string);
//var
//  Paths: string;
//  P: Integer;
//begin
//  if not RegQueryStringValue(HKEY_LOCAL_MACHINE, EnvironmentKey, 'Path', Paths) then
//  begin
//    Log('PATH not found');
//  end
//   else
//  begin
//    Log(Format('PATH is [%s]', [Paths]));
//
//    P := Pos(';' + Uppercase(Path) + ';', ';' + Uppercase(Paths) + ';');
//    if P = 0 then
//    begin
//      Log(Format('Path [%s] not found in PATH', [Path]));
//    end
//      else
//    begin
//      if P > 1 then P := P - 1;
//      Delete(Paths, P, Length(Path) + 1);
//      Log(Format('Path [%s] removed from PATH => [%s]', [Path, Paths]));
//
//      if RegWriteStringValue(HKEY_LOCAL_MACHINE, EnvironmentKey, 'Path', Paths) then
//      begin
//        Log('PATH written');
//      end
//        else
//      begin
//        Log('Error writing PATH');
//      end;
//    end;
//  end;
//end;
//
//procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
//begin
//  if CurUninstallStep = usUninstall then
//  begin
//    RemovePath(ExpandConstant('{app}'));
//  end;
//end;