INCLUDES = 						\
	$(EVOLUTION_CALENDAR_CFLAGS)			\
	-I .						\
	-I$(top_srcdir)	                                \
	-DCALDAV_GLADEDIR=\""$(gladedir)"\"		

@EVO_PLUGIN_RULE@

plugin_DATA = org-gnome-evolution-caldav.eplug
plugin_LTLIBRARIES = liborg-gnome-evolution-caldav.la

liborg_gnome_evolution_caldav_la_SOURCES =        \
	caldav-source.c

liborg_gnome_evolution_caldav_la_LIBADD = 	\
	$(EVOLUTION_CALENDAR_LIBS)		\
	$(EPLUGIN_LIBS)		

liborg_gnome_evolution_caldav_la_LDFLAGS = -module -avoid-version $(NO_UNDEFINED)

EXTRA_DIST =				\
	org-gnome-evolution-caldav.eplug.xml

CLEANFILES = org-gnome-evolution-caldav.eplug
