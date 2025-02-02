/*
 * Copyright (C) 2021 Alexandros Theodotou <alex at zrythm dot org>
 *
 * This file is part of Zrythm
 *
 * Zrythm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zrythm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Zrythm.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include "audio/foldable_track.h"
#include "audio/track.h"
#include "utils/arrays.h"
#include "gui/backend/event.h"
#include "gui/backend/event_manager.h"
#include "project.h"
#include "utils/flags.h"
#include "utils/mem.h"
#include "utils/objects.h"
#include "zrythm.h"
#include "zrythm_app.h"

void
foldable_track_init (
  Track * self)
{
  if (self->type == TRACK_TYPE_FOLDER)
    {
      gdk_rgba_parse (&self->color, "#dddddd");
      self->icon_name =
        g_strdup ("fluentui-folder-regular");
    }
}

/**
 * Used to check if soloed/muted/etc.
 */
bool
foldable_track_is_status (
  Track *                  self,
  FoldableTrackMixerStatus status)
{
  g_return_val_if_fail (
    self->is_project, false);
  bool all_soloed = self->size > 1;
  for (int i = 1; i < self->size; i++)
    {
      int pos = self->pos + i;
      Track * child =
        tracklist_get_track (TRACKLIST, pos);
      g_return_val_if_fail (
        IS_TRACK_AND_NONNULL (child), false);
      switch (status)
        {
        case FOLDABLE_TRACK_MIXER_STATUS_MUTED:
          if (!track_get_muted (child))
            return false;
          break;
        case FOLDABLE_TRACK_MIXER_STATUS_SOLOED:
          if (!track_get_soloed (child))
            return false;
          break;
        case FOLDABLE_TRACK_MIXER_STATUS_IMPLIED_SOLOED:
          if (!track_get_implied_soloed (child))
            return false;
          break;
        case FOLDABLE_TRACK_MIXER_STATUS_LISTENED:
          if (!track_get_listened (child))
            return false;
          break;
        }
    }
  return all_soloed;
}
