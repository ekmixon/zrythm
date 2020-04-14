/*
 * Copyright (C) 2019 Alexandros Theodotou <alex at zrythm dot org>
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

/**
 * \file
 *
 * Code related to Carla plugins.
 */

#include "config.h"

#ifdef HAVE_CARLA

#ifndef __PLUGINS_CARLA_NATIVE_PLUGIN_H__
#define __PLUGINS_CARLA_NATIVE_PLUGIN_H__

#include <CarlaNativePlugin.h>
#include <CarlaUtils.h>

typedef struct PluginDescriptor PluginDescriptor;
typedef void * CarlaPluginHandle;

/**
 * @addtogroup plugins
 *
 * @{
 */

/**
 * The type of the Carla plugin.
 */
typedef enum CarlaPluginType
{
  CARLA_PLUGIN_NONE,
  CARLA_PLUGIN_RACK,
  CARLA_PLUGIN_PATCHBAY,
  CARLA_PLUGIN_PATCHBAY16,
  CARLA_PLUGIN_PATCHBAY32,
  CARLA_PLUGIN_PATCHBAY64,
} CarlaPluginType;

typedef struct CarlaNativePlugin
{
  NativePluginHandle       native_plugin_handle;
  NativeHostDescriptor     native_host_descriptor;
  const NativePluginDescriptor * native_plugin_descriptor;

  CarlaHostHandle          host_handle;

  uint32_t                 num_midi_events;
  NativeMidiEvent          midi_events[200];
  NativeTimeInfo           time_info;

  /** Pointer back to Plugin. */
  Plugin *                 plugin;

  /** Plugin ID inside carla engine. */
  unsigned int             carla_plugin_id;

} CarlaNativePlugin;

/**
 * Creates an instance of a CarlaNativePlugin inside
 * the given Plugin.
 *
 * The given Plugin must have its descriptor filled
 * in.
 */
void
carla_native_plugin_new_from_descriptor (
  Plugin * plugin);

/**
 * Returns a filled in descriptor from the
 * given binary path.
 */
PluginDescriptor *
carla_native_plugin_get_descriptor_from_path (
  const char * path,
  PluginType   type);

/**
 * Returns a filled in descriptor from the
 * CarlaCachedPluginInfo.
 */
PluginDescriptor *
carla_native_plugin_get_descriptor_from_cached (
  const CarlaCachedPluginInfo * info,
  PluginType              type);

/**
 * Wrapper to get param count.
 */
static inline uint32_t
carla_native_plugin_get_param_count (
  CarlaNativePlugin * self)
{
  return
    self->native_plugin_descriptor->get_parameter_count (
      self->native_plugin_handle);
}

/**
 * Wrapper to get param info at given index.
 */
static inline const NativeParameter *
carla_native_plugin_get_param_info (
  CarlaNativePlugin * self,
  uint32_t            index)
{
  return
    self->native_plugin_descriptor->get_parameter_info (
      self->native_plugin_handle, index);
}

/**
 * Instantiates the plugin.
 *
 * @ret 0 if no errors, non-zero if errors.
 */
int
carla_native_plugin_instantiate (
  CarlaNativePlugin * self);

/**
 * Processes the plugin for this cycle.
 */
void
carla_native_plugin_proces (
  CarlaNativePlugin * self,
  const long          g_start_frames,
  const nframes_t     nframes);

/**
 * Shows or hides the UI.
 */
void
carla_native_plugin_open_ui (
  CarlaNativePlugin * self,
  bool                show);

/**
 * Returns the plugin Port corresponding to the
 * given parameter.
 */
Port *
carla_native_plugin_get_port_from_param (
  CarlaNativePlugin *     self,
  const NativeParameter * param);

/**
 * Deactivates, cleanups and frees the instance.
 */
void
carla_native_plugin_free (
  CarlaNativePlugin * self);

/**
 * @}
 */

#endif

#endif // HAVE_CARLA
