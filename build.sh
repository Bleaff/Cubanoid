mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..  # или Debug
make -j4 # использовать 4 ядра для сборки

make clean

make rebuild_cache
