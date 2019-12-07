# Makefile


all		: httpheaders.c httpheaders.h keys.c keys.h httpheaders.py		
		python httpheaders.py build


install		:
		cp ./build/lib*/httpheaders.so ./../

clean		:
		rm -rf build
		rm -f httpheaders.so
