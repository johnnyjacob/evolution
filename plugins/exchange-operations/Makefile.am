INCLUDES = -I .						\
	-I$(top_srcdir)	                                \
	-I$(top_srcdir)/widgets				\
	-I$(top_srcdir)/calendar			\
	-I$(top_builddir)/composer			\
	-I$(top_builddir)/mail				\
	$(CAMEL_EXCHANGE_CFLAGS)                        \
	$(EVOLUTION_MAIL_CFLAGS)			\
	-DEVOLUTION_GLADEDIR=\""$(gladedir)"\"          \
	-DCONNECTOR_GLADEDIR=\""$(gladedir)"\"


@EVO_PLUGIN_RULE@

plugin_DATA = org-gnome-exchange-operations.eplug 	\
	org-gnome-folder-permissions.xml		\
	org-gnome-folder-subscription.xml		\
	org-gnome-exchange-tasks-subscription.xml	\
	org-gnome-exchange-cal-subscription.xml		\
	org-gnome-exchange-ab-subscription.xml

plugin_LTLIBRARIES = liborg-gnome-exchange-operations.la

liborg_gnome_exchange_operations_la_SOURCES = 		\
	exchange-operations.c				\
	exchange-operations.h				\
	exchange-config-listener.c			\
	exchange-config-listener.h			\
	exchange-calendar.c				\
	exchange-contacts.c				\
	exchange-change-password.c			\
	exchange-change-password.h			\
	exchange-delegates-user.c			\
	exchange-delegates-user.h			\
	exchange-delegates.c				\
	exchange-delegates.h				\
	exchange-user-dialog.c				\
	exchange-user-dialog.h				\
	exchange-folder-size-display.c			\
	exchange-folder-size-display.h			\
	exchange-account-setup.c			\
	exchange-permissions-dialog.c			\
	exchange-permissions-dialog.h			\
	exchange-folder-permission.c			\
	exchange-folder-subscription.c			\
	exchange-folder-subscription.h			\
	exchange-folder.c				\
	exchange-mail-send-options.c			\
	exchange-send-options.c				\
	exchange-send-options.h

liborg_gnome_exchange_operations_la_LIBADD = 			\
	$(top_builddir)/e-util/libeutil.la 			\
	$(top_builddir)/widgets/misc/libemiscwidgets.la		\
	$(top_builddir)/calendar/gui/libevolution-calendar.la 	\
	$(top_builddir)/mail/libevolution-mail.la 		\
	$(top_builddir)/addressbook/gui/component/libevolution-addressbook.la \
	$(CAMEL_EXCHANGE_LIBS)					\
	$(EVOLUTION_MAIL_LIBS)

liborg_gnome_exchange_operations_la_LDFLAGS = -module -avoid-version $(NO_UNDEFINED)

glade_DATA =							\
	exchange-change-password.glade				\
	exchange-delegates.glade				\
	exchange-folder-tree.glade				\
	exchange-permissions-dialog.glade			\
	e-foreign-folder-dialog.glade				\
	exchange-passwd-expiry.glade				\
	exchange-oof.glade					\
	exchange-send-options.glade

error_DATA = org-gnome-exchange-operations.error
errordir = $(privdatadir)/errors

EXTRA_DIST = 							\
	org-gnome-exchange-operations.eplug.xml			\
	org-gnome-exchange-operations.error.xml			\
	org-gnome-folder-permissions.xml			\
	org-gnome-folder-subscription.xml			\
	org-gnome-exchange-tasks-subscription.xml		\
	org-gnome-exchange-cal-subscription.xml			\
	org-gnome-exchange-ab-subscription.xml			\
	$(glade_DATA)						

BUILT_SOURCES = $(error_DATA) org-gnome-exchange-operations.eplug 

CLEANFILES = $(BUILT_SOURCES)
