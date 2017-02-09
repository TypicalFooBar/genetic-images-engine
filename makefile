LDFLAGS=-std=c++14 -O2
DEBUGLDFLAGS=-std=c++14 -g

INCLUDES=\
	-I /usr/local/boost-1.63.0/include \
	-I /Users/derek/Development/projects/skia/include/core \
	-I /Users/derek/Development/projects/skia/include/config \
	-I /Users/derek/Development/projects/skia/include/codec \
	-I /Users/derek/Development/projects/skia/include/gpu \
	-I /Users/derek/Development/projects/skia/include/utils

LDLIBS=\
	-L /usr/local/boost-1.63.0/lib -l boost_system -l boost_filesystem -l boost_thread \
	-L /Users/derek/Development/projects/skia/out/Static -l skia \
	-framework CoreFoundation -framework CoreGraphics -framework CoreText -framework CoreServices -framework OpenGL -framework GLUT

SRCS=main.cpp src/*.cpp
OUTPUTDIR=bin

build: clean prepare
# Compile
	g++ $(SRCS) $(DEBUGLDFLAGS) -o $(OUTPUTDIR)/main.exe $(INCLUDES) $(LDLIBS)
# Copy libs to output directory
	cp /usr/local/boost-1.63.0/lib/libboost_system.dylib bin/
	cp /usr/local/boost-1.63.0/lib/libboost_filesystem.dylib bin/
	cp /usr/local/boost-1.63.0/lib/libboost_thread.dylib bin/
prepare:
# Create the output directory
	mkdir $(OUTPUTDIR)
	cp kelsey.png $(OUTPUTDIR)
	cp blue-x.png $(OUTPUTDIR)
	cp quotes.png $(OUTPUTDIR)
	cp sonic32x32.png $(OUTPUTDIR)
clean:
# Delete the output directory
	rm -rf $(OUTPUTDIR)