mkdir assembly
copy ..\..\native\windows\target\nar\native-windows-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\native-windows-1.0.dll assembly
copy ..\..\native\include\target\nar\native-include-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\native-include-1.0.dll assembly
copy ..\..\native\api\target\nar\native-api-1.0-amd64-Windows-msvc-shared\lib\amd64-Windows-msvc\shared\native-api-1.0.dll assembly
copy ..\..\native\tests\target\test-nar\bin\amd64-Windows-msvc\NativeThreadTest.exe assembly
cd assembly
NativeThreadTest.exe
cd ..