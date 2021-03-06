/*
 * Copyright (c) 2012 BalaBit IT Ltd, Budapest, Hungary
 * Copyright (c) 2012 Gergely Nagy <algernon@balabit.hu>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "linux-kmsg-format.h"
#include "messages.h"
#include "plugin.h"
#include "plugin-types.h"

static MsgFormatHandler linux_kmsg_handler =
{
  .parse = &linux_kmsg_format_handler
};

static MsgFormatHandler *
linux_kmsg_format_construct(Plugin *self, GlobalConfig *cfg, gint plugin_type, const gchar *plugin_name)
{
  return &linux_kmsg_handler;
}

static Plugin linux_kmsg_format_plugin =
{
  .type = LL_CONTEXT_FORMAT,
  .name = "linux-kmsg",
  .construct = (gpointer (*)(Plugin *self, GlobalConfig *cfg, gint plugin_type, const gchar *plugin_name)) linux_kmsg_format_construct,
};

gboolean
linux_kmsg_format_module_init(GlobalConfig *cfg, CfgArgs *args)
{
  linux_msg_format_init();
  plugin_register(cfg, &linux_kmsg_format_plugin, 1);
  return TRUE;
}

const ModuleInfo module_info =
{
  .canonical_name = "linux-kmsg-format",
  .version = VERSION,
  .description = "The linux-kmsg-format module provides support for parsing linux 3.5+ /dev/kmsg-format messages.",
  .core_revision = SOURCE_REVISION,
  .plugins = &linux_kmsg_format_plugin,
  .plugins_len = 1,
};
