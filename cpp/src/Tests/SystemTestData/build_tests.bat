rem I:\Trentino\trentino\Binaries\trentino_x86_windows_0.2-pa
set TRENTINO_HOME=I:\Trentino\trentino\Binaries\trentino_x86_windows_0.2-pa
rem ..\..\..\..\..\Binaries\trentino_x86_windows_0.2-pa
echo Trentino home is %TRENTINO_HOME%

rem build basiccalculator
:call_functions
echo using Trentino home %TRENTINO_HOME%
rem call::build_project BasicCalculatorRemote
rem call::build_project LocalCallDataExchange
rem call::build_project BasicCalculator
rem call::build_project BasicCalculatorThrowError
rem call::build_project SCAReferenceExample
rem call::build_project BasicCalculatorReturnVoid
rem call::build_project Builder
rem call::build_project LocalCallDataExchangeExtended



goto:eof



:build_project
rmdir /s /q %~1Gen_Build
rmdir /s /q %~1Gen
rmdir /s /q %~1
echo
echo ##########################%~1############################
echo create the Source project
echo create a build directory
mkdir %~1_Build
cd %~1_Build
echo call CMake
cmake -G "Visual Studio 10" ..\%~1_Source
echo call MSBUILD on install target
msbuild INSTALL.vcxproj

echo
echo
rem delete the Build dir
cd ..
echo delete build directory %~1_Build
rem rmdir /s /q %~1_Build

rem now run trengen
echo using Trentino home %TRENTINO_HOME%
mkdir %~1Gen
%TRENTINO_HOME%\bin\Trengen.exe -cont %~1 -rtdir %TRENTINO_HOME%
if errorlevel 1 goto error_tregen
rem copy proxy and wrappers to be reused by integration tests
copy /y %~1Gen\*_TrentinoGenProxiesWrappers.* ProxiesAndWrappers
rem now compile generated code
mkdir %~1Gen_Build
cd %~1Gen_Build
cmake  -G "Visual Studio 10" ..\%~1Gen
msbuild INSTALL.vcxproj
if ERRORLEVEL 1 goto error_gen
cd ..
rem rmdir /s /q %~1Gen_Build
rem rmdir /s /q %~1Gen
echo %~1 build sucessfully
echo ########################## END %~1 ############################
goto:eof
:error_gen
echo build of generated file failed. Please load in visual studio and check cause
cd ..
goto:eof
:error_tregen
echo error during Tregen validation. see output for more details
goto:eof




