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
#ifndef _FILELIST_CTRL_DROP_TARGET_HEADER_H_INCLUDED_
#define _FILELIST_CTRL_DROP_TARGET_HEADER_H_INCLUDED_

// app
#include "rapidsvn_drop_target.hpp"

class FolderBrowser;
class FileListCtrl;

class FileListCtrlDropTarget : public RapidSvnDropTarget
{
public:
  FileListCtrlDropTarget(FolderBrowser * browser,
                         FileListCtrl * parent);

  virtual
  ~FileListCtrlDropTarget() {}

  virtual wxString
  GetDestinationPath(const wxPoint & point);

private:
  FolderBrowser * m_browser;
  FileListCtrl * m_parent;
};

#endif
/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */
