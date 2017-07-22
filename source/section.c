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
/*                                   SECTION.C                                */
/******************************************************************************/

#include "style.h"

#include "as.h"
#include "section.h"

/******************************************************************************/

#define MAGIC  (89201129L) /* Magic number detects uninitialized sections.    */
#define SECMAX    (30000L) /* Maximum value of a single level's section num.  */

/******************************************************************************/

LOCAL void sn_chk P_((p_sn_t));
LOCAL void sn_chk(p_sn)
/* Checks that the given section object has a legal internal state.           */
p_sn_t p_sn;
{
 ubyte i;

 as_cold(p_sn->sn_magic==MAGIC,"sn_chk: Section has bad magic number.");
 as_cold(p_sn->sn_lev<=SECLEV_MAX,
         "sn_chk: Section has bad level number.");
 for (i=1;i<=p_sn->sn_lev;i++)
    as_cold(p_sn->sn_num[i]>0,
            "sn_chk: Section has zero hierarchical number.");
}

/******************************************************************************/

EXPORT void sn_ini(p_sn)
p_sn_t p_sn;
{
 p_sn->sn_magic = MAGIC;
 p_sn->sn_lev   = 0;
}

/******************************************************************************/

EXPORT void sn_set(p_sn,level)
p_sn_t p_sn;
ubyte  level;
{
 ubyte i;
 sn_chk(p_sn);
 as_cold(level>0 && level<=SECLEV_MAX,
         "sn_set: Specified level is too high.");
 p_sn->sn_lev=level;
 for(i=1;i<=level;i++)
    p_sn->sn_num[i]=1;
}

/******************************************************************************/

EXPORT void sn_inc (p_sn,lev)
p_sn_t p_sn;
ubyte  lev;
{
 sn_chk(p_sn);

 /* Check the parameter level. */
 as_cold(1<=lev && lev<=SECLEV_MAX,"sn_inc: Bad level number specified.");

 /* Check that we are not skipping a hierarchical level. */
 as_cold(lev<=p_sn->sn_lev+1,"sn_inc: Discountinuous level increment.");

 /* Actually increment the section. */
 if (lev==p_sn->sn_lev+1) p_sn->sn_num[lev]=0;
 p_sn->sn_lev=lev;
 p_sn->sn_num[lev]++;

 /* Check that the section number hasn't got too big. */
 as_cold(p_sn->sn_num[lev]<=SECMAX,"sn_inc: Section number is too large.");
}

/******************************************************************************/

EXPORT ubyte sn_lev(p_sn)
p_sn_t p_sn;
{
 sn_chk(p_sn);
 return p_sn->sn_lev;
}

/******************************************************************************/

EXPORT void sn_str(p_sn,s)
p_sn_t p_sn;
char   *s;
{
 char   t[20];
 ubyte  i;

 sn_chk(p_sn);

 s[0]=EOS;
 for (i=1;i<=p_sn->sn_lev;i++)
    {
     if (i>1) strcat(s,".");
     sprintf(t,"%u",(unsigned) p_sn->sn_num[i]);
     strcat(s,t);
    }
}

/******************************************************************************/
/*                               End of SECTION.C                             */
/******************************************************************************/

