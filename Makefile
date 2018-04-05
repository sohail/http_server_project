# regedit/Makefile
# Written by, Sohail Qayum Malik[sqm@hackers.pk]

all		: http_headers

http_headers	:		
		make -C http_headers_src


install		:
		make -C http_headers_src install

clean		:
		make -C http_headers_src clean

