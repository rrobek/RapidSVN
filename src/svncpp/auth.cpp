#include "auth.h"

namespace svn
{

Auth::Auth ()
{
  auth_obj = (svn_client_auth_baton_t *) apr_pcalloc 
             (pool, sizeof (*auth_obj));

  auth_obj->prompt_callback = NULL;
  auth_obj->prompt_baton = NULL;
  auth_obj->store_auth_info = true;
  auth_obj->got_new_auth_info = true;
}

Auth::~Auth ()
{
}

void
Auth::username (const char *username)
{
  userName = username;
}

void
Auth::password (const char *password)
{
  passWord = password;
}

svn_client_auth_baton_t *
Auth::authenticate ()
{
  return auth_obj;
}

}
