//*******************************************************************
/*!
\file   entry.cpp
\author Thomas Breuer
\date   22.11.2023
*/

//*******************************************************************
#include "Common/Src/ORBlocal.h"

//*******************************************************************
int Main( BYTE para, ORBlocal &orb );

//*******************************************************************
int foo( BYTE para, ORBlocal &orb )
{
  int y = -1;
  y = Main(para, orb);
  return(y);
}

//*******************************************************************
#if defined _KEIL
/// Keil 5:
 unsigned x2 __attribute__((at( 0x8020000))) = (unsigned )foo; /* RO */

// Keil armclang 6:
//  unsigned x2 __attribute__((section( ".ARM.__at_0x8020000"	))) = (unsigned )foo; /* RO */
#elif defined _GCC
  int __attribute__((section(".startAppSection"))) x2 = (unsigned )foo; /* RO */
#endif
