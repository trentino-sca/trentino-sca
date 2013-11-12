rem I:\Trentino\trentino\Binaries\trentino_x86_windows_0.2-pa
set TRENTINO_SOURCE=C:\DEV\871-z002ttbb-Ver

echo Trentino home is %TRENTINO_HOME%

rem build basiccalculator
:call_functions
echo using Trentino home %TRENTINO_HOME%
echo using Source directory %TRENTINO_SOURCE%
rem cd %TRENTINO_HOME%/bin
start /d %TRENTINO_HOME%\bin TrentinoConsole -install %TRENTINO_SOURCE%/cpp/src/Tests/SystemTestData/PerformanceTest_BasicCalculator/BasicCalculatorRemote
start /d %TRENTINO_HOME%\bin TrentinoConsole -install %TRENTINO_SOURCE%/cpp/src/Tests/SystemTestData/PerformanceTest_BasicCalculator/BasicCalculatorRemoteClient
start /d %TRENTINO_HOME%\bin TrentinoConsole -install %TRENTINO_SOURCE%/cpp/src/Tests/SystemTestData/PerformanceTest_BasicCalculator/BasicCalculatorRemoteClient
start /d %TRENTINO_HOME%\bin TrentinoConsole -install %TRENTINO_SOURCE%/cpp/src/Tests/SystemTestData/PerformanceTest_BasicCalculator/BasicCalculatorRemoteClient
start /d %TRENTINO_HOME%\bin TrentinoConsole -install %TRENTINO_SOURCE%/cpp/src/Tests/SystemTestData/PerformanceTest_BasicCalculator/BasicCalculatorRemoteClient
start /d %TRENTINO_HOME%\bin TrentinoConsole -install %TRENTINO_SOURCE%/cpp/src/Tests/SystemTestData/PerformanceTest_BasicCalculator/BasicCalculatorRemoteClient
start /d %TRENTINO_HOME%\bin TrentinoConsole -install %TRENTINO_SOURCE%/cpp/src/Tests/SystemTestData/PerformanceTest_BasicCalculator/BasicCalculatorRemoteClient
start /d %TRENTINO_HOME%\bin TrentinoConsole -install %TRENTINO_SOURCE%/cpp/src/Tests/SystemTestData/PerformanceTest_BasicCalculator/BasicCalculatorRemoteClient
start /d %TRENTINO_HOME%\bin TrentinoConsole -install %TRENTINO_SOURCE%/cpp/src/Tests/SystemTestData/PerformanceTest_BasicCalculator/BasicCalculatorRemoteClient
