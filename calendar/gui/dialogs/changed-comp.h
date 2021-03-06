/* Evolution calendar - Changed calendar component dialog
 *
 * Copyright (C) 2001 Ximian, Inc.
 *
 * Author: JP Rosevear <jpr@ximian.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef CHANGED_COMP_H
#define CHANGED_COMP_H

#include <glib.h>
#include <gtk/gtkwindow.h>
#include <libecal/e-cal-component.h>

gboolean changed_component_dialog (GtkWindow *window, ECalComponent *comp, gboolean deleted, gboolean changed);

#endif
