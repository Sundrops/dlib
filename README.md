# dlib for mingw_5.3
由于mingw_5.3对C++11支持不足，std::thread,std::mutex等不能使用，所以利用mingw-std-threads来补充。(https://github.com/Sundrops/mingw-std-threads)

# build for windows
下载cmake，利用cmake-gui生成makefile，具体config选择mingw makefile，然后直接generate
cd build
mingw32-make

# build for linux(不变)
cd build
cmake ..
cmake --build . --config Release


