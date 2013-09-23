#---- Outputs ----#
COMPONENT_NAME = BlinkTest

#--- Inputs ----#
CPPUTEST_USE_EXTENSIONS = Y
CPPUTEST_HOME = /usr/local
CPP_PLATFORM = Gcc
#CXX = clang

CPPFLAGS += -I(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

SRC_DIRS = \
	src \

TEST_SRC_DIRS = \
	tests \

INCLUDE_DIRS = \
	. \
	$(CPPUTEST_HOME)/include \
	include \

# MakefileWorker.mk was copied into CPPUTEST_HOME manually after running
# CppUTest's 'make install' command
include $(CPPUTEST_HOME)/build/MakefileWorker.mk
