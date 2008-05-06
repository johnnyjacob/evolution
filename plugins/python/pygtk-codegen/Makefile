#Place holder
DEFS=`pkg-config --variable=defsdir pygtk-2.0`

e-plugin.c: e-plugin.defs e-plugin.override            
	pygtk-codegen-2.0 --prefix e-plugin --register $(DEFS)/gdk-types.defs --register $(DEFS)/gtk-types.defs --override e-plugin.override e-plugin.defs > $@                              
all: e-plugin.c

defs:
	python /usr/share/pygtk/2.0/codegen/h2def.py ../../../e-util/e-plugin.h > e-plugin.defs
clean:
	rm e-plugin.c