from distutils.core import setup, Extension
# argsv, module name
setup(name="httpheaders", version="1.0", 
		ext_modules=[
	           # Take help on Extension module		
	           # To toggle between cross compilation comment or uncomment
		   # the following lines
		   Extension("httpheaders", ["httpheaders.c", "keys.c"])]) 
		   #Extension("httpheaders", ["httpheaders.c"], extra_compile_args=["-m32"], extra_link_args=["--format=elf32-i386", "-m elf-i386", "-oformat elf32-i386"])])
