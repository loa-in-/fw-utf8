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
/*                                      AS.H                                  */
/******************************************************************************/
/*                                                                            */
/* ASSERTION PACKAGE                                                          */
/* =================                                                          */
/* This package contains macros and functions that support assertions. An     */
/* assertion is a boolean condition that is supposed always to be true at a   */
/* particular point during program execution. An assertion statement tests    */
/* such a condition and bombs the program if it is false; better to be        */
/* alerted to such a condition rather than suffer and erroneous execution.    */
/*                                                                            */
/* Standard C supports asertions with the <assert.h> header file providing    */
/* the "assert" macro. Unfortunately, this does not meet the needs of         */
/* FunnelWeb for two reasons:                                                 */
/*                                                                            */
/* 1) Portability is emphasised in FunnelWeb and the assert macro is fairly   */
/*    recent. Its only argument is the boolean condition, which means that    */
/*    without the ANSI macros __FILE__ and __LINE__, the macro would be       */
/*    unable to indicate where an assertion failure occurred, in a non-ANSI   */
/*    environment.                                                            */
/*                                                                            */
/* 2) There is only one assert macro and it can be either on or off, the      */
/*    implication being that in production code, it should be turned off. In  */
/*    contrast, the execution speed of the assert macro will usually matter   */
/*    only in a small portion of the code as, in most programs, a small       */
/*    portion of the code accounts for most of the execution time. By having  */
/*    two categories of assertion, we can leave most of the assertions turned */
/*    on in the production program.                                           */
/*                                                                            */
/* This reasoning leads to the slightly different assertion facilty provided  */
/* by this package. Here, there are two assertion routines/macros, HOT        */
/* assertions for HOT code (code in a program hot spot) and COLD assertions   */
/* for COLD code (not in a hot spot). Only the HOT assertions can be turned   */
/* off.                                                                       */
/*                                                                            */
/******************************************************************************/

/* Ensure that the body of this header file is included at most once.         */
#ifndef DONE_AS
#define DONE_AS

/******************************************************************************/

#include "style.h"

/******************************************************************************/

/* The following #define determines whether hot assertions are to be turned   */
/* on or off. Set to 0 for OFF and 1 for ON.                                  */
/* Note: I have left hot assertions on in the production version as FunnelWeb */
/*       doesn't go slowly enough to make me want to turn it off.             */
#define AS_DOHOT 1

/******************************************************************************/

EXPORT void as_bomb P_((char *));
/* This function writes out its argument string and then bombs the program.   */
/* It should be called at any point where it has been determined that an      */
/* illegal condition has been detected. The other assertion routines/macros   */
/* call this function.                                                        */

/* The following two macros define hot and cold assertions. Be sure never to  */
/* call them with arguments with side effects!                                */
#define as_cold(e,s) {if (!(e)) as_bomb(s);}

#if AS_DOHOT
#define as_hot(e,s)    {if (!(e)) as_bomb(s);}
#define AS_HCODE(CODE) {CODE}
#else
#define as_hot(e,s)    ((void) 0)
#define AS_HCODE(CODE) ((void) 0)
#endif

/******************************************************************************/

/* For #ifndef preventing multiple inclusion of the body of this header file. */
#endif

/******************************************************************************/
/*                                     AS.H                                   */
/******************************************************************************/
