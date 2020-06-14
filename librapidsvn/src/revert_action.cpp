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
// wxWidgets
#include "wx/wx.h"

// svncpp
#include "svncpp/client.hpp"

// app
#include "revert_action.hpp"
#include "revert_dlg.hpp"

/* Note that a recursive revert action might change the filesystem tree.
   As we don't know yet what kind of revert we will be, we have to be safe and
   update the tree in any case. */
RevertAction::RevertAction(wxWindow * parent)
  : Action(parent, _("Revert"), Action::UPDATE_TREE)
{
}

bool
RevertAction::Prepare()
{
  if (!Action::Prepare())
    return false;

  RevertDlg dlg(GetParent());

  if (dlg.ShowModal() != wxID_OK)
  {
    return false;
  }

  m_recursive = dlg.GetRecursive();

  return true;
}

bool
RevertAction::Perform()
{
  svn::Client client(GetContext());
  client.revert(GetTargets(), m_recursive);

  return true;
}

bool
RevertAction::CheckStatusSel(const svn::StatusSel & WXUNUSED(statusSel))
{
  return true;
}

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../rapidsvn-dev.el")
 * end:
 */
