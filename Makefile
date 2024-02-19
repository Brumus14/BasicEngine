CXX := g++
INCLUDE_DIRS := ./lib/bx/include ./lib/bimg/include ./lib/bgfx/include ./src
SRCS := ${shell find src -name "*.cpp"}
LIB_DIRS := ./lib/bgfx/.build/linux64_gcc/bin
LIBS := glfw bgfxDebug bimgDebug bxDebug dl GL pthread X11
DEFINES := BX_CONFIG_DEBUG=1
TARGET := tes

.PHONY: build run clean

build:
	@${CXX} ${addprefix -I, ${INCLUDE_DIRS}} ${SRCS} ${addprefix -L, ${LIB_DIRS}} ${addprefix -l, ${LIBS}} ${addprefix -D, ${DEFINES}} -o ${TARGET}

	@./lib/bgfx/.build/linux64_gcc/bin/shadercDebug -f res/shaders/fs_basic.sc -o res/shaders/fs_basic.bin -i ./lib/bgfx/src/ --platform linux -p 440 --type fragment --verbose
	@./lib/bgfx/.build/linux64_gcc/bin/shadercDebug -f res/shaders/vs_basic.sc -o res/shaders/vs_basic.bin -i ./lib/bgfx/src/ --platform linux -p 440 --type vertex --verbose

run:
	@./${TARGET}

clean:
	@rm ${TARGET}
