
#ifndef EM_MESSAGE_BROWSER_H
#define EM_MESSAGE_BROWSER_H

#include <gtk/gtkwidget.h>
#include "em-folder-view.h"

/* Standard GObject macros */
#define EM_TYPE_MESSAGE_BROWSER \
	(em_message_browser_get_type ())
#define EM_MESSAGE_BROWSER(obj) \
	(G_TYPE_CHECK_INSTANCE_CAST \
	((obj), EM_TYPE_MESSAGE_BROWSER, EMMessageBrowser))
#define EM_MESSAGE_BROWSER_CLASS(cls) \
	(G_TYPE_CHECK_CLASS_CAST \
	((cls), EM_TYPE_MESSAGE_BROWSER, EMMessageBrowserClass))
#define EM_IS_MESSAGE_BROWSER(obj) \
	(G_TYPE_CHECK_INSTANCE_TYPE \
	((obj), EM_TYPE_MESSAGE_BROWSER))
#define EM_IS_MESSAGE_BROWSER_CLASS(cls) \
	(G_TYPE_CHECK_CLASS_TYPE \
	((cls), EM_TYPE_MESSAGE_BROWSER))
#define EM_MESSAGE_BROWSER_GET_CLASS(obj) \
	(G_TYPE_INSTANCE_GET_CLASS \
	((obj), EM_TYPE_MESSAGE_BROWSER, EMMessageBrowserClass))

G_BEGIN_DECLS

typedef struct _EMMessageBrowser EMMessageBrowser;
typedef struct _EMMessageBrowserClass EMMessageBrowserClass;
typedef struct _EMMessageBrowserPrivate EMMessageBrowserPrivate;

struct _EMMessageBrowser {
	EMFolderView parent;

	/* container, if setup */
	GtkWidget *window;

	EMMessageBrowserPrivate *priv;
};

struct _EMMessageBrowserClass {
	EMFolderViewClass parent_class;
};

GType		em_message_browser_get_type	(void);

GtkWidget *     em_message_browser_new		(void);

/* Also sets up a bonobo container window w/ docks and so on. */
GtkWidget *     em_message_browser_window_new	(void);

G_END_DECLS

#endif /* EM_MESSAGE_BROWSER_H */
