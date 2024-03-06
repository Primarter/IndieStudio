echo "\033[1;42mCreating build folder if it doesn't exist\033[0m"
mkdir ./build
echo "\033[1;42mStarting build\033[0m"
cd ./build && cmake ../ -G "Unix Makefiles" && cmake --build .
cd ../