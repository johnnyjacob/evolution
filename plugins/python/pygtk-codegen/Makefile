#Place holder
CC=gcc
CFLAGS=`pkg-config --cflags gtk+-2.0 pygtk-2.0` `python-config --include` -I.    
LDFLAGS=`pkg-config --libs gtk+-2.0 pygtk-2.0`
DEFS=`pkg-config --variable=defsdir pygtk-2.0`

e-plugin.c: e-plugin.defs e-plugin.override            
	pygtk-codegen-2.0 --prefix e-plugin --register $(DEFS)/gdk-types.defs --register $(DEFS)/gtk-types.defs --override e-plugin.override e-plugin.defs > $@                              

defs:
	python /usr/share/pygtk/2.0/codegen/h2def.py ../../../e-util/e-plugin.h > e-plugin.defs
clean:
	rm e-plugin.c
	rm eplugin.so

eplugin.so: eplugin.o ../../../e-util/.libs/e-plugin.o epluginmodule.o e-plugin.c
	$(CC) $(LDFLAGS) -shared $^ -o $@

all: e-plugin.so
