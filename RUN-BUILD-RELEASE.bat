cd build
cmake ..
cmake --build . --config Release --clean-first
cd ..
start %~dp0\build\Release\Calculator.exe
exit 0