mkdir assembly
copy ..\..\native\windows\target\nar\native-windows-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\native-windows-1.0.dll assembly
copy ..\..\native\include\target\nar\native-include-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\native-include-1.0.dll assembly
copy ..\..\native\api\target\nar\native-api-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\native-api-1.0.dll assembly
copy ..\..\core\lang\target\nar\core-lang-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\core-lang-1.0.dll assembly
copy ..\..\core\jcpp-exe\target\nar\jcpp-exe-1.0-amd64-Windows-msvc-executable\bin\amd64-Windows-msvc\jcpp-exe.exe assembly
copy ..\..\junit\target\nar\jcpp-junit-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\jcpp-junit-1.0.dll assembly
copy ..\..\cli\target\nar\jcpp-cli-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\jcpp-cli-1.0.dll assembly
copy ..\..\core\tests\target\nar\core-tests-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\core-tests-1.0.dll assembly
copy ..\..\core\gc\target\nar\core-gc-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\core-gc-1.0.dll assembly
cd assembly
jcpp-exe -Dk1=v1 -Dk2=v2 -Dk3=v3 -classpath=jcpp-junit-1.0.dll;core-tests-1.0.dll -classname=junit.textui.TestRunner jcpp.lang.info.MyTestSuite 
cd ..