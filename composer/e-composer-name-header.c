/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * Copyright (C) 2008 Novell, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU Lesser General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "e-composer-name-header.h"

#include <glib/gi18n.h>

/* XXX Temporary kludge */
#include "addressbook/gui/contact-editor/e-contact-editor.h"
#include "addressbook/gui/contact-list-editor/e-contact-list-editor.h"

#define E_COMPOSER_NAME_HEADER_GET_PRIVATE(obj) \
	(G_TYPE_INSTANCE_GET_PRIVATE \
	((obj), E_TYPE_COMPOSER_NAME_HEADER, EComposerNameHeaderPrivate))

/* Convenience macro */
#define E_COMPOSER_NAME_HEADER_GET_ENTRY(header) \
	(E_NAME_SELECTOR_ENTRY (E_COMPOSER_HEADER (header)->input_widget))

enum {
	PROP_0,
	PROP_NAME_SELECTOR
};

struct _EComposerNameHeaderPrivate {
	ENameSelector *name_selector;
	guint destination_index;
};

static gpointer parent_class;

static void
composer_name_header_clicked_cb (EComposerNameHeader *header)
{
	ENameSelectorDialog *dialog;

	dialog = e_name_selector_peek_dialog (header->priv->name_selector);
	e_name_selector_dialog_set_destination_index (
		dialog, header->priv->destination_index);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_hide (GTK_WIDGET (dialog));
}

static void
composer_name_header_entry_changed_cb (ENameSelectorEntry *entry,
                                       EComposerNameHeader *header)
{
	g_signal_emit_by_name (header, "changed");
}

static gboolean
composer_name_header_entry_query_tooltip_cb (GtkEntry *entry,
                                             gint x,
                                             gint y,
                                             gboolean keyboard_mode,
                                             GtkTooltip *tooltip)
{
	const gchar *text;

	text = gtk_entry_get_text (entry);

	if (keyboard_mode || text == NULL || *text == '\0')
		return FALSE;

	gtk_tooltip_set_text (tooltip, text);

	return TRUE;
}

static GObject *
composer_name_header_constructor (GType type,
                                  guint n_construct_properties,
                                  GObjectConstructParam *construct_properties)
{
	EComposerNameHeaderPrivate *priv;
	ENameSelectorModel *model;
	ENameSelectorEntry *entry;
	GObject *object;
	gchar *label;

	/* Chain up to parent's constructor() method. */
	object = G_OBJECT_CLASS (parent_class)->constructor (
		type, n_construct_properties, construct_properties);

	priv = E_COMPOSER_NAME_HEADER_GET_PRIVATE (object);
	g_assert (E_IS_NAME_SELECTOR (priv->name_selector));

	model = e_name_selector_peek_model (priv->name_selector);
	label = e_composer_header_get_label (E_COMPOSER_HEADER (object));
	g_assert (label != NULL);

	/* XXX Peeking at private data. */
	priv->destination_index = model->sections->len;
	e_name_selector_model_add_section (model, label, label, NULL);

	e_composer_header_set_title_tooltip (
		E_COMPOSER_HEADER (object),
		_("Click here for the address book"));

	entry = E_NAME_SELECTOR_ENTRY (
		e_name_selector_peek_section_list (
		priv->name_selector, label));
	e_name_selector_entry_set_contact_editor_func (
		entry, e_contact_editor_new);
	e_name_selector_entry_set_contact_list_editor_func (
		entry, e_contact_list_editor_new);
	g_signal_connect (
		entry, "changed",
		G_CALLBACK (composer_name_header_entry_changed_cb), object);
	g_signal_connect (
		entry, "query-tooltip",
		G_CALLBACK (composer_name_header_entry_query_tooltip_cb),
		NULL);
	E_COMPOSER_HEADER (object)->input_widget = g_object_ref_sink (entry);

	g_signal_connect (
		object, "clicked",
		G_CALLBACK (composer_name_header_clicked_cb), NULL);

	return object;
}

static void
composer_name_header_set_property (GObject *object,
                                   guint property_id,
                                   const GValue *value,
                                   GParamSpec *pspec)
{
	EComposerNameHeaderPrivate *priv;

	priv = E_COMPOSER_NAME_HEADER_GET_PRIVATE (object);

	switch (property_id) {
		case PROP_NAME_SELECTOR:	/* construct only */
			g_assert (priv->name_selector == NULL);
			priv->name_selector = g_value_dup_object (value);
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}

static void
composer_name_header_get_property (GObject *object,
                                   guint property_id,
                                   GValue *value,
                                   GParamSpec *pspec)
{
	switch (property_id) {
		case PROP_NAME_SELECTOR:	/* construct only */
			g_value_set_object (
				value,
				e_composer_name_header_get_name_selector (
				E_COMPOSER_NAME_HEADER (object)));
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}

static void
composer_name_header_dispose (GObject *object)
{
	EComposerNameHeaderPrivate *priv;

	priv = E_COMPOSER_NAME_HEADER_GET_PRIVATE (object);

	if (priv->name_selector != NULL) {
		g_object_unref (priv->name_selector);
		priv->name_selector = NULL;
	}

	/* Chain up to parent's dispose() method. */
	G_OBJECT_CLASS (parent_class)->dispose (object);
}

static void
composer_name_header_class_init (EComposerNameHeaderClass *class)
{
	GObjectClass *object_class;

	parent_class = g_type_class_peek_parent (class);
	g_type_class_add_private (class, sizeof (EComposerNameHeaderPrivate));

	object_class = G_OBJECT_CLASS (class);
	object_class->constructor = composer_name_header_constructor;
	object_class->set_property = composer_name_header_set_property;
	object_class->get_property = composer_name_header_get_property;
	object_class->dispose = composer_name_header_dispose;

	g_object_class_install_property (
		object_class,
		PROP_NAME_SELECTOR,
		g_param_spec_object (
			"name-selector",
			NULL,
			NULL,
			E_TYPE_NAME_SELECTOR,
			G_PARAM_READWRITE |
			G_PARAM_CONSTRUCT_ONLY));
}

static void
composer_name_header_init (EComposerNameHeader *header)
{
	header->priv = E_COMPOSER_NAME_HEADER_GET_PRIVATE (header);
}

GType
e_composer_name_header_get_type (void)
{
	static GType type = 0;

	if (G_UNLIKELY (type == 0)) {
		static const GTypeInfo type_info = {
			sizeof (EComposerNameHeaderClass),
			(GBaseInitFunc) NULL,
			(GBaseFinalizeFunc) NULL,
			(GClassInitFunc) composer_name_header_class_init,
			(GClassFinalizeFunc) NULL,
			NULL,  /* class_data */
			sizeof (EComposerNameHeader),
			0,     /* n_preallocs */
			(GInstanceInitFunc) composer_name_header_init,
			NULL   /* value_table */
		};

		type = g_type_register_static (
			E_TYPE_COMPOSER_HEADER, "EComposerNameHeader",
			&type_info, 0);
	}

	return type;
}

EComposerHeader *
e_composer_name_header_new (const gchar *label,
                            ENameSelector *name_selector)
{
	g_return_val_if_fail (E_IS_NAME_SELECTOR (name_selector), NULL);

	return g_object_new (
		E_TYPE_COMPOSER_NAME_HEADER, "label", label,
		"button", TRUE, "name-selector", name_selector, NULL);
}

ENameSelector *
e_composer_name_header_get_name_selector (EComposerNameHeader *header)
{
	g_return_val_if_fail (E_IS_COMPOSER_NAME_HEADER (header), NULL);

	return header->priv->name_selector;
}

EDestination **
e_composer_name_header_get_destinations (EComposerNameHeader *header)
{
	EDestinationStore *store;
	EDestination **destinations;
	ENameSelectorEntry *entry;
	GList *list, *iter;
	gint ii = 0;

	g_return_val_if_fail (E_IS_COMPOSER_NAME_HEADER (header), NULL);

	entry = E_COMPOSER_NAME_HEADER_GET_ENTRY (header);
	store = e_name_selector_entry_peek_destination_store (entry);

	list = e_destination_store_list_destinations (store);
	destinations = g_new0 (EDestination *, g_list_length (list) + 1);

	for (iter = list; iter != NULL; iter = iter->next)
		destinations[ii++] = g_object_ref (iter->data);

	g_list_free (list);

	return destinations;  /* free with e_destination_freev() */
}

void
e_composer_name_header_set_destinations (EComposerNameHeader *header,
                                         EDestination **destinations)
{
	EDestinationStore *store;
	ENameSelectorEntry *entry;
	GList *list, *iter;
	gint ii;

	g_return_if_fail (E_IS_COMPOSER_NAME_HEADER (header));

	entry = E_COMPOSER_NAME_HEADER_GET_ENTRY (header);
	store = e_name_selector_entry_peek_destination_store (entry);

	/* Clear the destination store. */
	list = e_destination_store_list_destinations (store);
	for (iter = list; iter != NULL; iter = iter->next)
		e_destination_store_remove_destination (store, iter->data);
	g_list_free (list);

	if (destinations == NULL)
		return;

	for (ii = 0; destinations[ii] != NULL; ii++)
		e_destination_store_append_destination (
			store, destinations[ii]);
}
