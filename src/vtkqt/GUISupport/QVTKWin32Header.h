/*=========================================================================

  Program:   Visualization Toolkit
  Module:    QVTKWin32Header.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*-------------------------------------------------------------------------
  Copyright 2008 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------*/
#ifndef __QVTKWin32Header_h
#define __QVTKWin32Header_h

#if 1
// Added by LLNL. We don't care about exposing these classes outside of
# if __GNUC__ >= 4
#   define QVTK_EXPORT __attribute__ ((visibility("hidden")))
# else
#   define QVTK_EXPORT /* hidden by default */
# endif

#else

#include "vtkSystemIncludes.h"
#include "vtkABI.h"

#if defined(VTK_BUILD_SHARED_LIBS)
# if defined(QVTK_EXPORTS) || defined(QVTKWidgetPlugin_EXPORTS)
#  define QVTK_EXPORT VTK_ABI_EXPORT
# else
#  define QVTK_EXPORT VTK_ABI_IMPORT
# endif
#else
# define QVTK_EXPORT
#endif

#endif

#endif /*__QVTKWin32Header_h*/