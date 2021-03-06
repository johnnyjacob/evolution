/* Evolution internal utilities - Glade dialog widget utilities
 *
 * Copyright (C) 2000 Ximian, Inc.
 * Copyright (C) 2000 Ximian, Inc.
 *
 * Author: Federico Mena-Quintero <federico@ximian.com>
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
 */

#ifndef E_DIALOG_WIDGETS_H
#define E_DIALOG_WIDGETS_H

#include <time.h>
#include <glade/glade.h>



void e_dialog_editable_set (GtkWidget *widget, const char *value);
char *e_dialog_editable_get (GtkWidget *widget);

void e_dialog_radio_set (GtkWidget *widget, int value, const int *value_map);
int e_dialog_radio_get (GtkWidget *widget, const int *value_map);

void e_dialog_toggle_set (GtkWidget *widget, gboolean value);
gboolean e_dialog_toggle_get (GtkWidget *widget);

void e_dialog_spin_set (GtkWidget *widget, double value);
double e_dialog_spin_get_double (GtkWidget *widget);
int e_dialog_spin_get_int (GtkWidget *widget);

void e_dialog_option_menu_set (GtkWidget *widget, int value, const int *value_map);
int e_dialog_option_menu_get (GtkWidget *widget, const int *value_map);

void e_dialog_combo_box_set (GtkWidget *widget, int value, const int *value_map);
int e_dialog_combo_box_get (GtkWidget *widget, const int *value_map);

void e_dialog_dateedit_set (GtkWidget *widget, time_t t);
time_t e_dialog_dateedit_get (GtkWidget *widget);

gboolean e_dialog_widget_hook_value (GtkWidget *dialog, GtkWidget *widget,
				     gpointer value_var, gpointer info);

void e_dialog_get_values (GtkWidget *dialog);

gboolean e_dialog_xml_widget_hook_value (GladeXML *xml, GtkWidget *dialog, const char *widget_name,
					 gpointer value_var, gpointer info);



#endif
