/*
 * e-cell-date.h - Date item for e-table.
 * Copyright 2001, Ximian, Inc.
 *
 * Authors:
 *   Chris Lahey <clahey@ximian.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License, version 2, as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef _E_CELL_DATE_H_
#define _E_CELL_DATE_H_

#include <table/e-cell-text.h>

G_BEGIN_DECLS

#define E_CELL_DATE_TYPE        (e_cell_date_get_type ())
#define E_CELL_DATE(o)          (G_TYPE_CHECK_INSTANCE_CAST ((o), E_CELL_DATE_TYPE, ECellDate))
#define E_CELL_DATE_CLASS(k)    (G_TYPE_CHECK_CLASS_CAST((k), E_CELL_DATE_TYPE, ECellDateClass))
#define E_IS_CELL_DATE(o)       (G_TYPE_CHECK_INSTANCE_TYPE ((o), E_CELL_DATE_TYPE))
#define E_IS_CELL_DATE_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), E_CELL_DATE_TYPE))

typedef struct {
	ECellText base;
} ECellDate;

typedef struct {
	ECellTextClass parent_class;
} ECellDateClass;

GType      e_cell_date_get_type (void);
ECell     *e_cell_date_new      (const char *fontname, GtkJustification justify);

G_END_DECLS

#endif /* _E_CELL_DATE_H_ */
