/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  Authors: Michael Zucchi <notzed@ximian.com>
 *
 *  Copyright 2004 Novell Inc. (www.novell.com)
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

#include <string.h>
#include <gtk/gtkimage.h>

#include "e-info-label.h"
#include <gtk/gtklabel.h>

#include <e-util/e-icon-factory.h>

static GtkHBoxClass *el_parent;

static void
el_init(GObject *o)
{
	/*EInfoLabel *el = (EInfoLabel *)o;*/
}

static void
el_finalise(GObject *o)
{
	((GObjectClass *)el_parent)->finalize(o);
}

static void
el_destroy (GtkObject *o)
{
	((EInfoLabel *)o)->location = NULL;
	((EInfoLabel *)o)->info = NULL;

	((GtkObjectClass *)el_parent)->destroy(o);
}

static int
el_expose_event(GtkWidget *w, GdkEventExpose *event)
{
	int x = ((GtkContainer *)w)->border_width;

	/* This seems a hack to me, but playing with styles wouldn't affect the background */
	gtk_paint_flat_box(w->style, w->window,
			   GTK_STATE_ACTIVE, GTK_SHADOW_NONE,
			   &event->area, w, "EInfoLabel",
			   w->allocation.x+x, w->allocation.y+x,
			   w->allocation.width-x*2, w->allocation.height-x*2);

	return ((GtkWidgetClass *)el_parent)->expose_event(w, event);
}

static int
get_text_full_width (GtkWidget *label)
{
	PangoLayout *layout;
	PangoRectangle rect;
	int width;

	g_return_val_if_fail (GTK_IS_LABEL (label), 0);

	layout = gtk_label_get_layout (GTK_LABEL (label));

	if (!layout)
		return 0;

	width = pango_layout_get_width (layout);
	pango_layout_set_width (layout, -1);
	pango_layout_get_extents (layout, NULL, &rect);
	pango_layout_set_width (layout, width);

	return PANGO_PIXELS (rect.width);
}

static void
el_size_allocate (GtkWidget *widget, GtkAllocation *pallocation)
{
	EInfoLabel *el;
	GtkAllocation allocation;
	int full_loc, full_nfo;
	gint diff;

	/* let calculate parent class first, and then just make it not divide evenly */
	((GtkWidgetClass *)el_parent)->size_allocate (widget, pallocation);

	g_return_if_fail (widget!= NULL);

	el = (EInfoLabel*) widget;

	if (!el->location)
		return;

	full_loc = get_text_full_width (el->location) + 1;
	full_nfo = get_text_full_width (el->info) + 1;

	/* do not know the width of text, thus return */
	if (full_loc == 1 && full_nfo == 1)
		return;

	if (el->location->allocation.width + el->info->allocation.width >= full_loc + full_nfo) {
		/* allocate for location only as many pixels as it requires to not ellipsize
		   and keep rest for the info part */
		diff = el->location->allocation.width - full_loc;
	} else {
		/* make both shorter, but based on the ratio of its full widths */
		gint total_have = el->location->allocation.width + el->info->allocation.width;
		gint total_full = full_loc + full_nfo;

		diff = el->location->allocation.width - full_loc * total_have / total_full;
	}

	if (!diff)
		return;

	allocation = el->location->allocation;
	allocation.width -= diff;
	gtk_widget_size_allocate (el->location, &allocation);

	allocation = el->info->allocation;
	allocation.x -= diff;
	allocation.width += diff;
	gtk_widget_size_allocate (el->info, &allocation);
}

static void
el_class_init(GObjectClass *klass)
{
	klass->finalize = el_finalise;

	((GtkObjectClass *)klass)->destroy = el_destroy;
	((GtkWidgetClass *)klass)->expose_event = el_expose_event;
	((GtkWidgetClass *)klass)->size_allocate = el_size_allocate;
}

GType
e_info_label_get_type(void)
{
	static GType type = 0;

	if (type == 0) {
		static const GTypeInfo info = {
			sizeof(EInfoLabelClass),
			NULL, NULL,
			(GClassInitFunc)el_class_init,
			NULL, NULL,
			sizeof(EInfoLabel), 0,
			(GInstanceInitFunc)el_init
		};
		el_parent = g_type_class_ref(gtk_hbox_get_type());
		type = g_type_register_static(gtk_hbox_get_type(), "EInfoLabel", &info, 0);
	}

	return type;
}

/**
 * e_info_label_new:
 * @icon:
 *
 * Create a new info label widget.  @icon is the name of the icon
 * (from the icon theme) to use for the icon image.
 *
 * Return value:
 **/
GtkWidget *
e_info_label_new(const char *icon)
{
	EInfoLabel *el = g_object_new(e_info_label_get_type(), NULL);
	GtkWidget *image;
	char *name = e_icon_factory_get_icon_filename (icon, E_ICON_SIZE_MENU);

	image = gtk_image_new_from_file(name);
	g_free(name);
	gtk_misc_set_padding((GtkMisc *)image, 6, 6);
	gtk_box_pack_start((GtkBox *)el, image, FALSE, TRUE, 0);
	gtk_widget_show(image);

	gtk_container_set_border_width((GtkContainer *)el, 3);

	return (GtkWidget *)el;
}

/**
 * e_info_label_set_info:
 * @el:
 * @location:
 * @info:
 *
 * Set the information to show on the label.  @location is some
 * context about the current view.  e.g. the folder name.  If the
 * label is too wide, this will be truncated.
 *
 * @info is some info about this location.
 **/
void
e_info_label_set_info(EInfoLabel *el, const char *location, const char *info)
{
	gchar *markup;

	if (el->location == NULL) {
		el->location = gtk_label_new (NULL);
		el->info = gtk_label_new (NULL);

		gtk_label_set_ellipsize (GTK_LABEL (el->location), PANGO_ELLIPSIZE_END);
		gtk_misc_set_alignment (GTK_MISC (el->location), 0.0, 0.0);
		gtk_misc_set_padding (GTK_MISC (el->location), 0, 6);

		gtk_label_set_ellipsize (GTK_LABEL (el->info), PANGO_ELLIPSIZE_MIDDLE);
		gtk_misc_set_alignment (GTK_MISC (el->info), 1.0, 1.0);
		gtk_misc_set_padding (GTK_MISC (el->info), 0, 6);

		gtk_widget_show (el->location);
		gtk_widget_show (el->info);

		gtk_box_pack_start (
			GTK_BOX (el), GTK_WIDGET (el->location),
			TRUE, TRUE, 0);
		gtk_box_pack_end (
			GTK_BOX (el), GTK_WIDGET (el->info),
			TRUE, TRUE, 6);
		gtk_widget_set_state (GTK_WIDGET (el), GTK_STATE_ACTIVE);
	}

	markup = g_markup_printf_escaped ("<b>%s</b>", location);
	gtk_label_set_markup (GTK_LABEL (el->location), markup);
	g_free (markup);

	markup = g_markup_printf_escaped ("<small>%s</small>", info);
	gtk_label_set_markup (GTK_LABEL (el->info), markup);
	g_free (markup);
}

