### Compile a lib for Emscripten

find . -name '*.cpp' > file_list.txt
em++ -c -std=c++2a -O2 -I./include/ $(<file_list.txt)
emar rcs libbox2d.a *.o

### FFMpeg

### Emscripten
emconfigure ../configure --cc=emcc --enable-cross-compile --target-os=none --arch=x86_32 --cpu=generic --disable-asm --disable-debug --disable-doc --disable-ffplay --disable-ffprobe --disable-network --disable-pthreads --disable-x86asm --disable-runtime-cpudetect --disable-iconv --disable-programs --disable-everything --enable-avformat --enable-avcodec --enable-avfilter --enable-swresample --enable-swscale --prefix=./ffmpeg_install --libdir=./ffmpeg_libs
emmake make -j8
emranlib *.a

### Linux
../configure --prefix=./ffmpeg_linux_install --disable-debug --disable-doc --disable-ffplay --disable-ffprobe --disable-network --enable-shared --enable-avformat --disable-programs --enable-avcodec --enable-avfilter --enable-swresample --enable-swscale
