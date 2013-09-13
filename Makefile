CPP_U_TEST_MAKEFILE="MakefileCppUTest.mk"
HARDWARE_MAKEFILE="myenergia.mk"

all: codeCppUTest codeMsp430

clean: cleanCodeCppUTest cleanCodeMsp430

prog: upload

upload: codeMsp430
	make -i -f $(HARDWARE_MAKEFILE) upload

codeCppUTest: CppUTest CppUTestExt version
	make -i -f $(CPP_U_TEST_MAKEFILE) 

codeMsp430: version
	make -i -f $(HARDWARE_MAKEFILE)

cleanCodeCppUTest:
	make -i -f $(CPP_U_TEST_MAKEFILE) clean

cleanCodeMsp430:
	make -i -f $(HARDWARE_MAKEFILE) clean

CppUTest: CppUTest/lib/libCppUTest.a

CppUTest/lib/libCppUTest.a:
	pwd
	make -i -C CppUTest

CppUTestExt: CppUTest/lib/libCppUTestExt.a

CppUTest/lib/libCppUTestExt.a:
	make -i -C CppUTest extensions

version:
	./generate_version.sh

.PHONY:
	version



##		# this is set up to by default to make the top level and test with CppUTest
##		#all: codeUnity
##		all: codeCppUTest
##
##		#clean: cleanCodeUnity
##		clean: cleanCodeCppUTest
##
##		cleanCode: cleanCodeCppUTest cleanCodeUnity
##
##		code: codeCppUTest codeUnity
##
##		codeCppUTest: CppUTest CppUTestExt
##			make -i -f MakefileCppUTest.mk 
##
##		codeUnity:
##			make -i -f MakefileUnity.mk
##
##		cleanCodeCppUTest:
##			make -i -f MakefileCppUTest.mk clean
##			
##		cleanCodeUnity:
##			make -i -f MakefileUnity.mk clean
##			
##		everything: CppUTest CppUTestExt
##			make -i -C CppUTest all extensions
##			make -i -C t0
##			make -i -C t1
##			make -i -C t2
##			make -i -C t3
##			make -i -C SandBox
##			make -i -f MakefileCppUTest.mk 
##			make -i -f MakefileUnity.mk
##
##		cleaneverything:
##			make -i -C t0 clean
##			make -i -C t1 clean
##			make -i -C t2 clean
##			make -i -C t3 clean
##			make -i -C SandBox clean
##			make -i -f MakefileCppUTest.mk clean
##			make -i -f MakefileUnity.mk clean
##			make -i -C CppUTest
##
##		#-- if CppUTestExt gives you any problems, t1 is really the only project depending on it.
##		t1: CppUTestExt
##
##		CppUTest: CppUTest/lib/libCppUTest.a
##
##		CppUTestExt: CppUTest/lib/libCppUTestExt.a
##
##		CppUTest/lib/libCppUTest.a:
##			pwd
##			make -i -C CppUTest
##
##		CppUTest/lib/libCppUTestExt.a:
##			make -i -C CppUTest extensions
