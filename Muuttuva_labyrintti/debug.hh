#ifndef JULKINEN_DEBUG_HH
#define JULKINEN_DEBUG_HH


/**
 *  \file debug.hh
 *  \brief Debuggauksen apumakro
 *  \author ©2011 Matti Rintala <bitti@cs.tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include <iostream>

extern bool debug_output; // Globaali muuttuja, hyi!

    /**
     *  \brief Makro, jolla voi tulostaa debug-tulosteita.
     * 
     * <b>Tämän makron toteutus on vielä kesken!</b>
     *
     *  Käytetään seuraavasti:
     *  \code
     *      DEBUG_OUTPUT("Kääk" << std::endl);
     *  \endcode
     *
     *  \post Jos ohjelma on käännetty debug-tilassa, tulostus tulostuu
     *    ruudulle. Muussa tapauksessa mitään ei tapahdu.
     */
#define DEBUG_OUTPUT(stuff) if (debug_output) { std::cerr << stuff; }

#endif  // JULKINEN_DEBUG_HH
