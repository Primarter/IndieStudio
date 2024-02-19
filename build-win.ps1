#Requires -Version 7
echo "`e[1;42mCreating build folder if it doesn't exist`e[0m"
mkdir ./build
echo "`e[1;42mStarting build`e[0m"
cd ./build && cmake ../ -G "MinGW Makefiles" && cmake --build .
cd ../