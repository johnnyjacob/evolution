/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*-
 * e-shell-view.c
 *
 * Copyright (C) 2004 Novell Inc.
 *
 * Author(s): Michael Zucchi <notzed@ximian.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * Helper class for evolution shells to setup a view
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>

#include <gtk/gtkwindow.h>
#include <glib/gi18n.h>

#include "e-shell-view.h"
#include "e-shell-window.h"
#include "e-util/e-icon-factory.h"

static BonoboObjectClass *parent_class = NULL;

struct _EShellViewPrivate {
	int dummy;
};

static void
impl_ShellView_setTitle(PortableServer_Servant _servant, const CORBA_char *id, const CORBA_char * title, CORBA_Environment * ev)
{
	EShellView *esw = (EShellView *)bonobo_object_from_servant(_servant);
	/* To translators: This is the window title and %s is the
	component name. Most translators will want to keep it as is. */
	char *tmp = g_strdup_printf(_("%s - Evolution"), title);

	e_shell_window_set_title(esw->window, id, tmp);
	g_free(tmp);
}

static void
impl_ShellView_setComponent(PortableServer_Servant _servant, const CORBA_char *id, CORBA_Environment * ev)
{
	EShellView *esw = (EShellView *)bonobo_object_from_servant(_servant);

	e_shell_window_switch_to_component(esw->window, id);
}

struct change_icon_struct {
	const char *component_name;
	GdkPixbuf *icon;
};

static gboolean
change_button_icon_func (EShell *shell, EShellWindow *window, gpointer user_data)
{
	struct change_icon_struct *cis = (struct change_icon_struct*)user_data;

	g_return_val_if_fail (window != NULL, FALSE);
	g_return_val_if_fail (cis != NULL, FALSE);

	e_shell_window_change_component_button_icon (window, cis->component_name, cis->icon);

	return TRUE;
}

static void
impl_ShellView_setButtonIcon (PortableServer_Servant _servant, const CORBA_char *id, const CORBA_char * iconName, CORBA_Environment * ev)
{
	EShellView *esw = (EShellView *)bonobo_object_from_servant(_servant);
	EShell *shell = e_shell_window_peek_shell (esw->window);

	struct change_icon_struct cis;
	cis.component_name = id;
	cis.icon = NULL;

	if (iconName)
		cis.icon = e_icon_factory_get_icon (iconName, E_ICON_SIZE_BUTTON);

	e_shell_foreach_shell_window (shell, change_button_icon_func, &cis);

	if (cis.icon)
		g_object_unref (cis.icon);
}

static void
impl_dispose (GObject *object)
{
	/*EShellView *esv = (EShellView *)object;*/

	((GObjectClass *)parent_class)->dispose(object);
}

static void
impl_finalise (GObject *object)
{
	((GObjectClass *)parent_class)->finalize(object);
}

static void
e_shell_view_class_init (EShellViewClass *klass)
{
	GObjectClass *object_class;
	POA_GNOME_Evolution_ShellView__epv *epv;

	parent_class = g_type_class_ref(bonobo_object_get_type());

	object_class = G_OBJECT_CLASS (klass);
	object_class->dispose  = impl_dispose;
	object_class->finalize = impl_finalise;

	epv = & klass->epv;
	epv->setTitle = impl_ShellView_setTitle;
	epv->setComponent = impl_ShellView_setComponent;
	epv->setButtonIcon = impl_ShellView_setButtonIcon;
}

static void
e_shell_view_init (EShellView *shell)
{
}

EShellView *e_shell_view_new(struct _EShellWindow *window)
{
	EShellView *new = g_object_new (e_shell_view_get_type (), NULL);

	/* TODO: listen to destroy? */
	new->window = window;

	return new;
}

BONOBO_TYPE_FUNC_FULL (EShellView, GNOME_Evolution_ShellView, bonobo_object_get_type(), e_shell_view)

