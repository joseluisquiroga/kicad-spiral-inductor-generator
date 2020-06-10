
BUILD_DIR := ./build
TARGET_DIR := ./

HL_CURR_DIR := $(shell pwd)

CXX_BASE_FLAGS := -Wall -std=c++17

BMETAL_CFLAGS := -Wall -std=gnu11 -ffreestanding -nostdlib -nostartfiles -fno-default-inline 

BMETAL_CXXFLAGS_P1 := -nostdlib -fno-exceptions -fno-unwind-tables -fno-extern-tls-init
BMETAL_CXXFLAGS_P2 := -fno-rtti -fno-default-inline -fno-threadsafe-statics -fno-elide-constructors
BMETAL_CXXFLAGS := ${CXX_BASE_FLAGS} ${BMETAL_CXXFLAGS_P1} ${BMETAL_CXXFLAGS_P2}

SG_DBG_FLAG := -DFULL_DEBUG

SG_BASE_DIR := .

# -------------------------------------------------------------------------------------------


TARGET := spiral_gen

TGT_LDFLAGS := -rdynamic -pthread

TGT_LDLIBS := -lgmpxx -lgmp

TGT_POSTMAKE := printf "====================================\nFinished building "$(TARGET)"\n\n\n"

SRC_CFLAGS := ${BMETAL_CFLAGS} ${SG_DBG_FLAG} -pthread
SRC_CXXFLAGS := ${CXX_BASE_FLAGS} ${SG_DBG_FLAG} -pthread

SRC_INCDIRS := ${SG_BASE_DIR}/util

SOURCES := \
	${SG_BASE_DIR}/util/sg_dbg_util.cpp \
	${SG_BASE_DIR}/spiral_gen.cpp \


