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
#ifndef _MODIFICATION_MGR_H_INCLUDED_
#define _MODIFICATION_MGR_H_INCLUDED_

// wxWidgets
#include "wx/string.h"

namespace svn
{
  class Context;
}

/**
 * This class manages modified sub-items of various parent-paths within the current bookmark.
 *
 */
class ModificationManager
{
public:
  /** Default constructor */
  ModificationManager();


  /** Destructor */
  virtual ~ ModificationManager();



  /**
   * Query modification data for a certain parent path.
   * The path will be scanned for modifications recursively,
   * which may take some time depending on the working copy's size.
   * Call this before getting modification status
   * for individual child items (GetStatus()).
   *
   * @param parentPath Parent path to scan
   */
  void
  QueryPath(svn::Client & client, const wxString & parentPath);


  /**
   * Gets modification status of (children) of the
   * item (file or folder), which is directly
   * contained in the given parentPath.
   * Note: Before calling this, QueryPath() must be called.
   *
   * @param parentPath Parent path of the item
   * @param item Name of the item
   * @return Number of modified subitems
   */
  int
  GetStatus(const wxString & parentPath,
            const wxString & item) const;


  /**
   * Call this method to ensure all data is cleared.
   */
  void
  Cleanup();

  /**
   * Call this when a bookmark must be refreshed.
   * All previously stored data below the given path is cleared.
   */
  void
  Cleanup(const wxString & parentPath);


private:
  struct Data;

  Data * m;

  /** disallow copy constructor */
  ModificationManager(const ModificationManager &);


  /** disallow assignment operator */
  ModificationManager & operator = (const ModificationManager &);
};

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */
