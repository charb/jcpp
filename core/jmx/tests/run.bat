mkdir assembly
copy ..\..\..\native\windows\target\nar\native-windows-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\native-windows-1.0.dll assembly
copy ..\..\..\native\include\target\nar\native-include-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\native-include-1.0.dll assembly
copy ..\..\..\native\api\target\nar\native-api-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\native-api-1.0.dll assembly
copy ..\..\..\core\lang\target\nar\core-lang-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\core-lang-1.0.dll assembly
copy ..\..\..\core\util-concurrent\target\nar\core-util-concurrent-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\core-util-concurrent-1.0.dll assembly
copy ..\..\..\core\jcpp-exe\target\nar\jcpp-exe-1.0-amd64-Windows-msvc-executable\bin\amd64-Windows-msvc\jcpp-exe.exe assembly
copy ..\..\..\core\util-concurrent-tests\target\nar\core-util-concurrent-tests-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\core-util-concurrent-tests-1.0.dll assembly
copy ..\..\..\core\rmi\target\nar\core-rmi-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\core-rmi-1.0.dll assembly
copy ..\..\..\core\gc\target\nar\core-gc-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\core-gc-1.0.dll assembly
copy ..\..\..\junit\target\nar\jcpp-junit-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\jcpp-junit-1.0.dll assembly
copy ..\..\..\cli\target\nar\jcpp-cli-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\jcpp-cli-1.0.dll assembly
copy ..\..\..\core\jmx\server\target\nar\jmx-server-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\jmx-server-1.0.dll assembly
copy target\nar\jmx-tests-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\jmx-tests-1.0.dll assembly
cd assembly
jcpp-exe -classpath=jcpp-cli-1.0.dll;core-lang-1.0.dll;jcpp-junit-1.0.dll;core-util-concurrent-1.0.dll;core-rmi-1.0.dll;jmx-tests-1.0.dll;jmx-server-1.0.dll -classname=junit.textui.TestRunner jcpp.jmx.tests.ServerTestSuite
cd ..