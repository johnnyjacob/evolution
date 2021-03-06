/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* e-html-utils.c */
/*
 * Copyright (C) 2000  Ximian, Inc.
 * Author: Dan Winship <danw@ximian.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __E_HTML_UTILS__
#define __E_HTML_UTILS__

#include <glib.h>

#define E_TEXT_TO_HTML_PRE               (1 << 0)
#define E_TEXT_TO_HTML_CONVERT_NL        (1 << 1)
#define E_TEXT_TO_HTML_CONVERT_SPACES    (1 << 2)
#define E_TEXT_TO_HTML_CONVERT_URLS      (1 << 3)
#define E_TEXT_TO_HTML_MARK_CITATION     (1 << 4)
#define E_TEXT_TO_HTML_CONVERT_ADDRESSES (1 << 5)
#define E_TEXT_TO_HTML_ESCAPE_8BIT       (1 << 6)
#define E_TEXT_TO_HTML_CITE              (1 << 7)

char *e_text_to_html_full (const char *input, unsigned int flags, guint32 color);
char *e_text_to_html      (const char *input, unsigned int flags);

#endif /* __E_HTML_UTILS__ */
