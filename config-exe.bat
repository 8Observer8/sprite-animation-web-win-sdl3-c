cmake -G "MinGW Makefiles" -S . -B dist/win ^
-DSDL3_DIR=H:/libs/sdl-3.1.6-prefix/win/lib/cmake/SDL3 ^
-DSDL3_image_DIR=H:/libs/sdl3_image-3.1.0-prefix/win/lib/cmake/SDL3_image ^
-DCMAKE_BUILD_TYPE=Debug
