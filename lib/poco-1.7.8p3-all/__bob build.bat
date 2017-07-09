rem buildwin.cmd 140 clean
rem buildwin.cmd 140 clean all both

rem buildwin.cmd 140 build static_mt both Win32 nosamples notests devenv
rem copy /lib/*.lib /_lib/
rem copy /lib/*.pdb /_lib/
rem buildwin.cmd 140 clean all both

cd CppUnit
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd Crypto
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd Data
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd Foundation
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd JSON
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd MongoDB
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd Net
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd NetSSL_OpenSSL
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd PageCompiler
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd Util
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd XML
del /S *.ilk *.pdb *.exe *.db *.obj
cd..

cd Zip
del /S *.ilk *.pdb *.exe *.db *.obj
cd..
pause