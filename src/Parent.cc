// ext3grep -- An ext3 file system investigation and undelete tool
//
//! @file Parent.cc This file contains the implementation of class Parent.
//
// Copyright (C) 2008, by
// 
// Carlo Wood, Run on IRC <carlo@alinoe.com>
// RSA-1024 0x624ACAD5 1997-01-26                    Sign & Encrypt
// Fingerprint16 = 32 EC A7 B6 AC DB 65 A6  F6 F6 55 DD 1C DC FF 61
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef USE_PCH
#include "sys.h"
#include <string>
#include <sstream>
#endif

#include "Parent.h"
#include "directories.h"

std::string Parent::dirname(bool show_inodes) const
{
  if (!M_dir_entry)
    return std::string();
  std::string path(M_dir_entry->name, M_dir_entry->name_len);
  if (show_inodes)
  {
    std::ostringstream tmp;
    tmp << '(' << M_dir_entry->inode << ')';
    path += tmp.str();
    for (Parent const* lparent = M_parent; lparent->M_dir_entry; lparent = lparent->M_parent)
    {
      tmp.str("");
      tmp << std::string(lparent->M_dir_entry->name, lparent->M_dir_entry->name_len) << '(' << lparent->M_dir_entry->inode << ')';
      path = tmp.str() + '/' + path;
    }
  }
  else
  {
    for (Parent const* lparent = M_parent; lparent->M_dir_entry; lparent = lparent->M_parent)
      if (lparent->M_dir_entry->name_len > 0)
	path = std::string(lparent->M_dir_entry->name, lparent->M_dir_entry->name_len) + '/' + path;
  }
  return path;
}
