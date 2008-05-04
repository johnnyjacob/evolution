#Johnny Jacob <jjohnny@novell.com>

E_UTIL_CFLAGS = -DORBIT2=1 -pthread -D_REENTRANT -I/home/jjohnny/src/git/e-trunk/opt//include/evolution-data-server-2.22 -I/home/jjohnny/src/opt/gnome/include/libbonoboui-2.0 -I/home/jjohnny/src/opt/gnome/include/orbit-2.0 -I/home/jjohnny/src/opt/gnome/include/libxml2 -I/home/jjohnny/src/opt/gnome/include/gnome-vfs-2.0 -I/home/jjohnny/src/opt/gnome/lib/gnome-vfs-2.0/include -I/home/jjohnny/src/opt/gnome/include/glib-2.0 -I/home/jjohnny/src/opt/gnome/lib/glib-2.0/include -I/home/jjohnny/src/opt/gnome/include/libbonobo-2.0 -I/home/jjohnny/src/opt/gnome/include/libgnomecanvas-2.0 -I/home/jjohnny/src/opt/gnome/include/libgnome-2.0 -I/home/jjohnny/src/opt/gnome/include/gconf/2 -I/home/jjohnny/src/opt/gnome/include/bonobo-activation-2.0 -I/home/jjohnny/src/opt/gnome/include/pango-1.0 -I/home/jjohnny/src/opt/gnome/include/gail-1.0 -I/home/jjohnny/src/opt/gnome/include/libart-2.0 -I/home/jjohnny/src/opt/gnome/include/gtk-2.0 -I/home/jjohnny/src/opt/gnome/include -I/home/jjohnny/src/opt/gnome/include/atk-1.0 -I/home/jjohnny/src/opt/gnome/lib/gtk-2.0/include -I/home/jjohnny/src/opt/gnome/include/cairo -I/home/jjohnny/src/opt/gnome/include/pixman-1 -I/home/jjohnny/src/opt/gnome/include/libglade-2.0 -I/home/jjohnny/src/opt/gnome/include/libgnomeui-2.0 -I/home/jjohnny/src/opt/gnome/include/gnome-keyring-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/lib/pkgconfig/../../include/mono-1.0   $(WERROR)  -I/usr/include/nspr4/  

E_UTIL_LIBS = -pthread -L/home/jjohnny/src/git/e-trunk/opt//lib -L/home/jjohnny/src/opt/gnome/lib -L/usr/lib/pkgconfig/../../lib -lgnomeui-2 -lSM -lICE -lbonoboui-2 -lgnomevfs-2 -lgnomecanvas-2 -lart_lgpl_2 -ledataserverui-1.2 -lglade-2.0 -lebook-1.2 -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lpangocairo-1.0 -lpango-1.0 -lcairo -lgnome-2 -lpopt -lcamel-1.2 -ledataserver-1.2 -lxml2 -lgconf-2 -lbonobo-2 -lbonobo-activation -lgmodule-2.0 -lORBit-2 -lgobject-2.0 -lmono -ldl -lpthread -lm -lgthread-2.0 -lrt -lglib-2.0   -lpthread -L/usr/lib -ldl -lplc4 -lplds4 -lnspr4 -lpthread -lX11  

all : bindings

bindings : python_module
	swig -python eplugin.i

python_module:
	gcc -c ../../../e-util/e-plugin.c eplugin_wrap.c -I../../../ -I/usr/include/python2.5 $(E_UTILS_CFLAGS) $(E_UTILS_LIBS) 
	ld -shared eplugin_wrap.o -o _eplugin.so 
