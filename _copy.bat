@echo off

mkdir "..\..\Desktop\bob's game"
mkdir "..\..\Desktop\bob's game\data"
xcopy /v .\*.dll "..\..\Desktop\bob's game"
xcopy /v .\Release\bobsgame.exe "..\..\Desktop\bob's game"
xcopy /v .\bobsgame.bmp "..\..\Desktop\bob's game"
xcopy /v .\version.txt "..\..\Desktop\bob's game"
xcopy /v .\LICENSE "..\..\Desktop\bob's game"
xcopy /v /e .\data "..\..\Desktop\bob's game\data"

pause