/*
 * utils/gtk.c - GTK utils
 *
 * copyright (c) 2018 alexandros theodotou
 *
 * this file is part of zrythm
 *
 * zrythm is free software: you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation, either version 3 of the license, or
 * (at your option) any later version.
 *
 * zrythm is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * gnu general public license for more details.
 *
 * you should have received a copy of the gnu general public license
 * along with zrythm.  if not, see <https://www.gnu.org/licenses/>.
 */

#include "gui/accel.h"
#include "utils/gtk.h"
#include "utils/resources.h"

/**
 * NOTE: bumps reference, must be decremented after calling.
 */
void
z_gtk_container_remove_all_children (GtkContainer * container)
{
  GList *children, *iter;

  children =
    gtk_container_get_children (GTK_CONTAINER (container));
  for (iter = children;
       iter != NULL;
       iter = g_list_next (iter))
    {
      g_object_ref (GTK_WIDGET (iter->data));
      gtk_container_remove (
        container,
        GTK_WIDGET (iter->data));
    }
  g_list_free (children);
}

void
z_gtk_container_destroy_all_children (GtkContainer * container)
{
  GList *children, *iter;

  children =
    gtk_container_get_children (GTK_CONTAINER (container));
  for (iter = children;
       iter != NULL;
       iter = g_list_next (iter))
    gtk_widget_destroy (GTK_WIDGET (iter->data));
  g_list_free (children);
}

void
z_gtk_button_set_icon_name (GtkButton * btn,
                            const char * name)
{
  GtkWidget * img =
    gtk_image_new_from_icon_name (
      name,
      GTK_ICON_SIZE_BUTTON);
  gtk_widget_set_visible (img, 1);
  gtk_container_add (GTK_CONTAINER (btn),
                     img);
}

/**
 * Creates a button with the given icon name.
 */
GtkButton *
z_gtk_button_new_with_icon (const char * name)
{
  GtkButton * btn = GTK_BUTTON (gtk_button_new ());
  z_gtk_button_set_icon_name (btn,
                              name);
  gtk_widget_set_visible (GTK_WIDGET (btn),
                          1);
  return btn;
}

/**
 * Creates a button with the given resource name as icon.
 */
GtkButton *
z_gtk_button_new_with_resource (IconType  icon_type,
                                const char * name)
{
  GtkButton * btn = GTK_BUTTON (gtk_button_new ());
  resources_add_icon_to_button (btn,
                                icon_type,
                                name);
  gtk_widget_set_visible (GTK_WIDGET (btn),
                          1);
  return btn;
}

GtkMenuItem *
z_gtk_create_menu_item (gchar *     label_name,
                  gchar *         icon_name,
                  IconType        resource_icon_type,
                  gchar *         resource,
                  int             is_toggle,
                  const char *    action_name)
{
  GtkWidget *box =
    gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
  GtkWidget *icon = NULL;
  if (icon_name)
    icon =
      gtk_image_new_from_icon_name (icon_name,
                                    GTK_ICON_SIZE_MENU);
  else if (resource)
    icon =
      resources_get_icon (resource_icon_type,
                          resource);
  GtkWidget *label = gtk_accel_label_new (label_name);
  GtkWidget * menu_item;
  if (is_toggle)
    menu_item = gtk_check_menu_item_new ();
  else
    menu_item = gtk_menu_item_new ();

  if (icon)
    gtk_container_add (GTK_CONTAINER (box), icon);

  gtk_label_set_use_underline (GTK_LABEL (label), TRUE);
  gtk_label_set_xalign (GTK_LABEL (label), 0.0);

  gtk_actionable_set_action_name (
    GTK_ACTIONABLE (menu_item),
    action_name);
  accel_set_accel_label_from_action (
    GTK_ACCEL_LABEL (label),
    action_name);

  gtk_box_pack_end (GTK_BOX (box), label, TRUE, TRUE, 0);

  gtk_container_add (GTK_CONTAINER (menu_item), box);

  gtk_widget_show_all (menu_item);

  return GTK_MENU_ITEM (menu_item);
}
