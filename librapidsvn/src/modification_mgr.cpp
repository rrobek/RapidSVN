/*
 * ====================================================================
 * Copyright (c) 2002-2018 The RapidSVN Group.  All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (in the file GPL.txt).
 * If not, see <http://www.gnu.org/licenses/>.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://rapidsvn.tigris.org/.
 * ====================================================================
 */

// stl
#include <map>

// libsvncpp
#include "svncpp/context.hpp"
#include "svncpp/client.hpp"
#include "svncpp/status.hpp"

// wxWidgets
#include "wx/wx.h"
#include "wx/string.h"
#include "wx/confbase.h"
#include "wx/debug.h"
#include "wx/time.h"
#include "wx/filename.h"

// app
#include "modification_mgr.hpp"
#include "utils.hpp"

/** Time after which a parent path will be refreshed. This setting should be made configurable. */
#define MODIFICATION_REFRESH_TIME_MILLIS 5000


typedef std::map<wxString, int> ModificationStatusMap;

/**
 * modification data per parent path
 */
struct ModificationData
{
public:
  ModificationData() : updateTime(wxGetUTCTimeMillis())
  {
  }

  wxLongLong updateTime;
  ModificationStatusMap data;
};

/** maps from parent path to associated data. */
typedef std::map<wxString, ModificationData> ModificationMap;

/**
 * structure that hides implementation details from
 * modification_mgr.hpp
 */
struct ModificationManager::Data
{
public:
  /** Contains data for all parent paths */
  ModificationMap data;

  /** default constructor */
  Data()
  {
  }
};






ModificationManager::ModificationManager()
  : m(new Data())
{
}


ModificationManager::~ModificationManager()
{
  delete m;
}

void ModificationManager::Cleanup(const wxString &parentPath)
{
  for (ModificationMap::iterator iter = m->data.begin(); iter != m->data.end(); /**/) {
    if (iter->first.StartsWith(parentPath))
      iter = m->data.erase(iter);
    else
      ++iter;
  }
}

void ModificationManager::QueryPath(svn::Client &client, const wxString &parentPath)
{
  ModificationMap::iterator iter = m->data.find(parentPath);
  if (iter == m->data.end() || iter->second.updateTime < wxGetUTCTimeMillis() - MODIFICATION_REFRESH_TIME_MILLIS)
  {
    //printf("Retrieving data for %s...\n", (const char*) parentPath.c_str()); fflush(stdout);
    // fetch new:
    ModificationData newData;

    svn::Path parentPathUtf8(PathUtf8(parentPath));

    // Only get interesting entries
    svn::StatusFilter modifiedFilter;
    modifiedFilter.showUnversioned = false;
    modifiedFilter.showUnmodified = false;
    modifiedFilter.showModified = true;
    modifiedFilter.showConflicted = true;
    modifiedFilter.showExternals = false;
    svn::StatusEntries modifiedEntries;
    client.status(parentPathUtf8.c_str(), modifiedFilter, true, false,
                  modifiedEntries);
    wxChar pathSeparator = wxFileName::GetPathSeparator();
    size_t parentLength = parentPath.Length() + 1; //+1 = path separator

    svn::StatusEntries::const_iterator it;
    for (it = modifiedEntries.begin(); it != modifiedEntries.end(); it++)
    {
      const svn::Path modifiedPath((*it).path());
      wxString path(PathToNative(modifiedPath).Mid(parentLength));
      int separatorPos = path.Find(pathSeparator);

      // we have to check, wether the entry we wanna add contains
      // modified entries or is modified itself (in this case this
      // counts) or if the modifications are deeper in the tree
      // (in that case we only mark it as modified)
      bool hasModifiedSubChildren = false;
      if (wxNOT_FOUND != separatorPos)
      {
        wxString restPath(path.Mid(separatorPos+1));
        path = path.Left(separatorPos);

        if (wxNOT_FOUND != restPath.Find(pathSeparator))
          hasModifiedSubChildren = true;
      }

      int modified_count = 0;
      ModificationStatusMap::const_iterator iter = newData.data.find(path);
      if (iter != newData.data.end())
        modified_count = iter->second;
      if (hasModifiedSubChildren)
      {
        if (0 == modified_count)
          newData.data[path] = -1;
      }
      else if (modified_count < 0)
        newData.data[path] = 1;
      else
        newData.data[path]++;
    }
    // insert
    m->data[parentPath] = newData;
  }
  else {
    //printf("Reusing data for %s.\n", (const char*) parentPath.c_str()); fflush(stdout);
  }
}

int ModificationManager::GetStatus(const wxString &parentPath, const wxString &item) const
{
  ModificationMap::const_iterator iter = m->data.find(parentPath);
  if (iter == m->data.end()) {
    //printf("ParentPath %s is not available!\n", (const char*) parentPath.c_str()); fflush(stdout);
    return 0; // data is not available
  }
  const ModificationData& d = iter->second;
  ModificationStatusMap::const_iterator iter2 = d.data.find(item);
  if (iter2 == d.data.end()) {
    //printf("Item %s is not available!\n", (const char*) item.c_str()); fflush(stdout);
    return 0; // no data for item is available (should not happen actually)
  }
  // Found requested data
  return iter2->second;
}

void ModificationManager::Cleanup()
{
  m->data.clear();
}

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */
