cd org.trentino.trengen.parent
call mvn install
cd ..\org.trentino.trengen.tools
call  mvn assembly:single
cd target
copy /Y Trengen.jar I:\Trentino\trentino\Binaries\trentino_x86_windows_0.7-r\bin
copy /Y Trengen.jar I:\SmartGrid\SharedLibraries\cpp_mp\x86\Windows\tools\trentino\Debug\bin
copy /Y Trengen.jar I:\SmartGrid\Pea_mp\StorageSystem\installed\TrentinoRuntime\bin
copy /Y Trengen.jar ..\..\dist
copy /Y Trengen.jar  ..\..\..\cpp_build\build\x86Windows\Debug
copy /Y Trengen.jar  ..\..\..\cpp_build\build\x86Windows\Release
cd ..\..