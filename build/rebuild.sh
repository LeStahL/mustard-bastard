rm mustard-bastard.exe
if [ "$1" -gt "-f" ]
  then rm CMakeCache.txt; cmake ..
fi
cmake --build . --config Release && ./Release/mustard-bastard.exe