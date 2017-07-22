/*##############################################################################

FUNNNELWEB COPYRIGHT
====================
FunnelWeb is a literate-programming macro preprocessor.
The FunnelWeb web is at http://www.ross.net/funnelweb/

Copyright (c) Ross N. Williams 1992. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of Version 2 of the GNU General Public License as
published by the Free Software Foundation (http://www.gnu.org/).

This program is distributed WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See Version 2 of the GNU General Public License for more details.

You should have received a copy of Version 2 of the GNU General Public
License along with this program. If not, you can obtain a copy as follows:
   ftp://prep.ai.mit.edu/pub/gnu/COPYING-2.0
or write to:
    Free Software Foundation, Inc.,
    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

Section 2a of the license requires that all changes to this file be
recorded prominently in this file. Please record all changes here.

Programmers:
   RNW  Ross N. Williams (ross@ross.net)

Changes:
   07-May-1992  RNW  Program prepared for release under GNU GPL V2.

##############################################################################*/


/******************************************************************************/
/*                                  TEXHEAD.H                                 */
/******************************************************************************/
/*                                                                            */
/* TEX HEADER PACKAGE                                                         */
/* ==================                                                         */
/* This package contains a single function that writes the TeX header         */
/* (containing all the Weave macros) to the specified stream. The package     */
/* consists of:                                                               */
/*                                                                            */
/* texhead.tex - The header file ("source code" for texhead.ctx).             */
/* texhead.ctx - C code automatically generated by texhead.tex.               */
/* texhead.h   - This file, containing a function definition.                 */
/* texhead.c   - Contains a function body.                                    */
/*                                                                            */
/* The first version of FunnelWeb (1986) generated TeX output files that used */
/* a collection of macros to neaten and simplify the bulk of the TeX output   */
/* file. For example, the macro \fwbtx provided a simple way to specify       */
/* verbatim text. This system worked extremely well, the only inconvenience   */
/* being that each FunnelWeb TeX output file had to "\input" the TeX header   */
/* file containing all the macros. At the time, this seemed a sensible        */
/* factorization of the macros, and, within the limited environment in which  */
/* FunnelWeb was operating, worked well.                                      */
/*                                                                            */
/* In NEW, IMPROVED FunnelWeb, "\input"ing the header file has the potential  */
/* to cause lots of problems, the major ones being:                           */
/*                                                                            */
/* - The header file would have to be installed as part of the FunnelWeb      */
/*   system. Currently this means that it would be the ONLY other file        */
/*   necessary apart from the FunnelWeb executable. It would be far more      */
/*   desirable to avoid having to install the header file.                    */
/*                                                                            */
/* - The header file would have to be referred to somehow by the TeX file.    */
/*   As it makes sense to have only one copy of the header file on a machine, */
/*   TeX files would have to refer to that copy. This would require one of a  */
/*   number of messy machine-specific mechanisms such as (VMS) logical name   */
/*   translation or environment variable translation.                         */
/*                                                                            */
/* - TeX files could not be easily moved to other machines (particularly      */
/*   those not running FunnelWeb themselves) without also sending the header  */
/*   file.                                                                    */
/*                                                                            */
/* - If FunnelWeb and the header file were ever jointly modified, the dynamic */
/*   binding of old TeX files would mean that they may no longer be printable.*/
/*                                                                            */
/* For all these reasons, the decision was made to write the library of TeX   */
/* macros at the start of each TeX output file, thus making each TeX output   */
/* file entirely self-contained. To do this, the header file had to be        */
/* converted into a sequence of C output statments. To this end, a new        */
/* FunnelWeb shell command CODIFY was added that performs this transformation.*/
/* CODIFY could have been a separate utility program, but if it was, it might */
/* somehow be separated from the rest of FunnelWeb during distribution. By    */
/* building CODIFY into FunnelWeb itself, this possibility is eliminated.     */
/*                                                                            */
/* This package encapsulates the automatically generated C code. This header  */
/* file defines a function that writes it to a specified stream. The package  */
/* body texhead.c contains the body of the function which consists mainly of  */
/* a #include of the automatically generated C code in texhead.ctx.           */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_TEXH
#define DONE_TEXH

/******************************************************************************/

#include "style.h"

#include "writfile.h"

/******************************************************************************/

EXPORT void tex_head P_((p_wf_t));
/* Writes the FunnelWeb TeX header block to the argument stream. */

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                             End of TEXHEAD.H                               */
/******************************************************************************/
