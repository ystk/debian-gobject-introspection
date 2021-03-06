
#include "girepository.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void test_constructor_return_type(GIBaseInfo* object_info);

void
test_constructor_return_type(GIBaseInfo* object_info)
{
  GIFunctionInfo* constructor;
  GITypeInfo* return_type;
  GIBaseInfo *return_info;
  const gchar* class_name;
  const gchar* return_name;

  class_name = g_registered_type_info_get_type_name ((GIRegisteredTypeInfo*) object_info);
  g_assert (class_name);

  constructor = g_object_info_find_method((GIObjectInfo*)object_info, "new");
  g_assert (constructor);

  return_type = g_callable_info_get_return_type ((GICallableInfo*)constructor);
  g_assert (return_type);
  g_assert (g_type_info_get_tag (return_type) == GI_TYPE_TAG_INTERFACE);

  return_info = g_type_info_get_interface (return_type);
  g_assert (return_info);

  return_name = g_registered_type_info_get_type_name ((GIRegisteredTypeInfo*) return_info);
  g_assert (strcmp (class_name, return_name) == 0);
}


int
main(int argc, char **argv)
{
  GIRepository *repo;
  GTypelib *ret;
  GError *error = NULL;
  GIBaseInfo *info;
  GType gtype;
  char *girdir;

  g_type_init ();

  repo = g_irepository_get_default ();

  girdir = g_build_filename (g_getenv ("top_builddir"), "gir", NULL);
  g_irepository_prepend_search_path (girdir);
  g_free (girdir);

  ret = g_irepository_require (repo, "Gio", NULL, 0, &error);
  g_assert (ret);
  g_assert (error == NULL);

  info = g_irepository_find_by_name (repo, "Gio", "Cancellable");
  g_assert (info != NULL);
  g_assert (g_base_info_get_type (info) == GI_INFO_TYPE_OBJECT);

  gtype = g_registered_type_info_get_g_type ((GIRegisteredTypeInfo *)info);
  g_assert (g_type_is_a (gtype, G_TYPE_OBJECT));

  info = g_irepository_find_by_gtype (repo, g_type_from_name ("GCancellable"));
  g_assert (info != NULL);

  g_print ("Successfully found GCancellable\n");

  test_constructor_return_type (info);

  info = g_irepository_find_by_name (repo, "Gio", "ThisDoesNotExist");
  g_assert (info == NULL);

  /* vfunc tests */
  {
    GIVFuncInfo *vfunc;
    GIFunctionInfo *invoker;

    /* Test vfunc with invoker on interface */
    info = g_irepository_find_by_name (repo, "Gio", "File");
    g_assert (info != NULL);

    vfunc = g_interface_info_find_vfunc ((GIInterfaceInfo*)info, "read_async");
    g_assert (vfunc != NULL);

    invoker = g_vfunc_info_get_invoker (vfunc);
    g_assert (invoker != NULL);

    g_assert (strcmp (g_base_info_get_name ((GIBaseInfo*)invoker), "read_async") == 0);

    /* Test vfunc with no known invoker on object */
    info = g_irepository_find_by_name (repo, "GObject", "Object");
    g_assert (info != NULL);

    vfunc = g_object_info_find_vfunc ((GIObjectInfo*)info, "dispose");
    g_assert (vfunc != NULL);

    /* Ok, maybe we should mark g_object_run_dispose as the invoker for
     * dispose, but...eh.  It's pretty special however you cut it.
     */
    invoker = g_vfunc_info_get_invoker (vfunc);
    g_assert (invoker == NULL);

    /* Test vfunc with invoker on object */
    info = g_irepository_find_by_name (repo, "Gio", "AppLaunchContext");
    g_assert (info != NULL);

    vfunc = g_object_info_find_vfunc ((GIObjectInfo*)info, "get_display");
    g_assert (vfunc != NULL);

    invoker = g_vfunc_info_get_invoker (vfunc);
    g_assert (invoker != NULL);
    g_assert (strcmp (g_base_info_get_name ((GIBaseInfo*)invoker), "get_display") == 0);

    /* And let's be sure we can find the method directly */

    invoker = g_object_info_find_method ((GIObjectInfo*)info, "get_display");
    g_assert (invoker != NULL);
    g_assert (strcmp (g_base_info_get_name ((GIBaseInfo*)invoker), "get_display") == 0);
  }

  exit(0);
}
