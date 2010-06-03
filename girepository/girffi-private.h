/* GObject introspection: Private helper functions for ffi integration
 *
 * Copyright (C) 2008, 2009 Red Hat, Inc
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GIRFFI_PRIVATE_H__
#define __GIRFFI_PRIVATE_H__

#include "girffi.h"

G_BEGIN_DECLS

ffi_type *    g_ir_ffi_get_ffi_type               (GITypeTag type_tag, gboolean is_pointer);

G_END_DECLS

#endif /* __GIRFFI_PRIVATE_H__ */
