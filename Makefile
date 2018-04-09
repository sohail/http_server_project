# Makefile
# Written by, Sohail Qayum Malik[sqm@hackers.pk]

all		: http_headers argsv

argsv		:
		make -C argsv-CPython

http_headers	:		
		make -C http_headers_src

install		:
		make -C http_headers_src install
		make -C argsv-CPython install

clean		:
		make -C http_headers_src clean
		make -C argsv-CPython clean

