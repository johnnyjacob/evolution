/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 *  Authors: Rodrigo Moya <rodrigo@novell.com>
 *           Philip Van Hoof <pvanhoof@gnome.org>
 *
 *  Copyright 2004 Novell, Inc. (www.novell.com)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of version 2 of the GNU General Public
 *  License as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <glib.h>
#include <glib/gi18n.h>
#include <gtk/gtkfilechooser.h>
#include <gtk/gtkfilechooserdialog.h>
#include <gtk/gtkmessagedialog.h>
#include <gtk/gtkstock.h>
#include <gtk/gtk.h>
#include <libedataserver/e-source.h>
#include <libedataserverui/e-source-selector.h>
#include <libecal/e-cal.h>
#include <libecal/e-cal-util.h>
#include <calendar/gui/e-cal-popup.h>
#include <calendar/common/authentication.h>
#include <string.h>

#include "format-handler.h"
#include "e-util/e-error.h"

static void
display_error_message (GtkWidget *parent, const char *message)
{
	GtkWidget *dialog;

	dialog = gtk_message_dialog_new (GTK_WINDOW (parent), 0, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", message);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

typedef struct {
	GHashTable *zones;
	ECal *ecal;
} CompTzData;

static void
insert_tz_comps (icalparameter *param, void *cb_data)
{
	const char *tzid;
	CompTzData *tdata = cb_data;
	icaltimezone *zone = NULL;
	icalcomponent *tzcomp;
	GError *error = NULL;

	tzid = icalparameter_get_tzid (param);

	if (g_hash_table_lookup (tdata->zones, tzid))
		return;

	if (!e_cal_get_timezone (tdata->ecal, tzid, &zone, &error)) {
		g_warning ("Could not get the timezone information for %s :  %s \n", tzid, error->message);
		g_error_free (error);
		return;
	}

	tzcomp = icalcomponent_new_clone (icaltimezone_get_component (zone));
	g_hash_table_insert (tdata->zones, (gpointer) tzid, (gpointer) tzcomp);
}

static void
append_tz_to_comp (gpointer key, gpointer value, icalcomponent *toplevel)
{
	icalcomponent_add_component (toplevel, (icalcomponent *) value);
}

static void
do_save_calendar_ical (FormatHandler *handler, EPlugin *ep, ECalPopupTargetSource *target, ECalSourceType type, char *dest_uri)
{
	ESource *primary_source;
	ECal *source_client;
	GError *error = NULL;
	GList *objects;
	icalcomponent *top_level = NULL;

	primary_source = e_source_selector_peek_primary_selection (target->selector);

	if (!dest_uri)
		return;

	/* open source client */
	source_client = (ECal*) auth_new_cal_from_source (primary_source, type);
	if (!e_cal_open (source_client, TRUE, &error)) {
		display_error_message (gtk_widget_get_toplevel (GTK_WIDGET (target->selector)), error->message);
		g_object_unref (source_client);
		g_error_free (error);
		return;
	}

	/* create destination file */
	top_level = e_cal_util_new_top_level ();

	error = NULL;
	if (e_cal_get_object_list (source_client, "#t", &objects, &error)) {
		CompTzData tdata;
		GOutputStream *stream;

		tdata.zones = g_hash_table_new (g_str_hash, g_str_equal);
		tdata.ecal = source_client;

		while (objects != NULL) {
			icalcomponent *icalcomp = objects->data;

			icalcomponent_foreach_tzid (icalcomp, insert_tz_comps, &tdata);
			icalcomponent_add_component (top_level, icalcomp);

			/* remove item from the list */
			objects = g_list_remove (objects, icalcomp);
		}

		g_hash_table_foreach (tdata.zones, (GHFunc) append_tz_to_comp, top_level);

		g_hash_table_destroy (tdata.zones);
		tdata.zones = NULL;

		/* save the file */
		stream = open_for_writing (GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (target->selector))), dest_uri, &error);

		if (stream) {
			char *ical_str = icalcomponent_as_ical_string (top_level);

			g_output_stream_write_all (stream, ical_str, strlen (ical_str), NULL, NULL, &error);
			g_output_stream_close (stream, NULL, NULL);

			g_object_unref (stream);
			g_free (ical_str);
		}
	}

	if (error) {
		display_error_message (gtk_widget_get_toplevel (GTK_WIDGET (target->selector)), error->message);
		g_error_free (error);
	}

	/* terminate */
	g_object_unref (source_client);
	icalcomponent_free (top_level);
}

FormatHandler *ical_format_handler_new (void)
{
	FormatHandler *handler = g_new (FormatHandler, 1);

	handler->isdefault = TRUE;
	handler->combo_label = _("iCalendar format (.ics)");
	handler->filename_ext = ".ics";
	handler->options_widget = NULL;
	handler->save = do_save_calendar_ical;
	handler->data = NULL;

	return handler;
}
