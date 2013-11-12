rem I:\Trentino\trentino\Binaries\trentino_x86_windows_0.2-pa

call::build_project BasicCalculatorRemote
call::build_project BasicCalculatorRemoteClient
call::build_project BasicCalculator
call::build_project BasicCalculatorRemoteNotEnclosedTypes
call::build_project HelloWorldRemote\HelloWorldRemote
call::build_project HelloWorldRemote\HelloWorldRemoteClient
call::build_project BasicCalculatorWithLifeCycle_Test\BasicCalculatorWithLifeCycle
call::build_project BasicPrinter
call::build_project BasicPrinterClient
call::build_project LocalDataExchange



goto:eof



:build_project
rmdir /s /q %~1Gen_Build
rmdir /s /q %~1Gen
rmdir /s /q %~1_Build
rmdir /s /q %~1
