CPPUTEST_MAKEFILE="MakefileCppUTest.mk"
CPPUTEST_HOME = /usr/local
HARDWARE_MAKEFILE="myenergia.mk"

all: codeCppUTest codeMsp430

clean: cleanCodeCppUTest cleanCodeMsp430

prog: upload

upload: codeMsp430
	make -i -f $(HARDWARE_MAKEFILE) upload

codeCppUTest: CppUTest CppUTestExt version
	make -i -f $(CPPUTEST_MAKEFILE)

codeMsp430: version
	make -i -f $(HARDWARE_MAKEFILE)

cleanCodeCppUTest:
	make -i -f $(CPPUTEST_MAKEFILE) clean

cleanCodeMsp430:
	make -i -f $(HARDWARE_MAKEFILE) clean

CppUTest: $(CPPUTEST_HOME)/lib/libCppUTest.a

CppUTestExt: $(CPPUTEST_HOME)/lib/libCppUTestExt.a

version:
	./generate_version.sh

.PHONY:
	version
