#ifndef JULKINEN_TOT_HYODYKKEET_HH
#define JULKINEN_TOT_HYODYKKEET_HH


/**
 *  \file hyodykkeet.hh
 *  \brief Apufunktioiden esittelyjä.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */


#include <cstring>      // std::strncpy
#include <map>          // std::map
#include <sstream>      // std::basic_ostringstream
#include <string>       // std::basic_string
/**
 *	Jos kääntäjä on GNUG pohjainen esim. gcc tai tutg++ käytetään tr1/memory
 *	kirjastoa.
 */
#	if defined(__GNUG__)

#include <tr1/memory>
/**
 *	Muussa tapauksessa käytetään memory kirjastoa ja toivotaan että kääntäjästä
 *	löytyy alustava tuki uudelle C++ standardille.
 *	Toimii esim. Visual Studio 2010.
 */
#	else
#include <memory>
#	endif


    /**
     *  \brief Tuhoaja-funktori taulukoiden säilömiseen
     *      std::tr1::shared_ptr:n päässä.
     *
     *  Rakentaja ja purkaja eivät voi heittää poikkeuksia, koska niillä
     *  ei ole mitään erikoista tehtävää.
     */
    template<typename T>
    class
    TaulukonTuhoaja
    {
        public:
            /**
             *  \brief Tuhoa annettu taulukkoosoitin taulukko-deletellä.
             */
            void
            operator()(T* p)
                const
            {
                delete[] p;
            }
    };

    /**
     *  \brief Lue merkkijono tyypin T olioon.
     *
     *  \tparam CharT Merkkijonon sisältämien merkkien tyyppi.
     *  \tparam T Luettavan tyypin arvo.
     *  \param lahde Merkkijono, josta arvo luetaan.
     *  \param kohde Olio, johon muunnettu arvo luetaan.  Täytyy olla
     *      luettavissa std::basic_ostream<char>-oliosta >>-operaattorilla.
     *  \return Arvo \c true jos ja vain jos arvon muuntaminen onnistui
     *      sen lukeminen kulutti \em koko merkkijonon.
     */
    template<typename CharT, typename T>
    bool
    muunnaMerkkijono(std::basic_string<CharT> const& lahde, T& kohde);

    /**
     *  \brief Varaa dynaamisesti C-merkkijono ja sijoita siihen
     *      merkkijonon arvo.
     *
     *  \tparam CharT Merkkijonon sisältämien merkkien tyyppi.
     *  \param merkkijono Merkkijono, jonka sisältö kopioidaan.
     *  \return Dynaamisesti varattu C-merkkijono.
     */
    template<typename CharT>
    std::tr1::shared_ptr<CharT>
    cMerkkijonoksi(std::basic_string<CharT> const& merkkijono);

    /**
     *  \brief Muunna arvo toiseksi std::mapin avulla.
     *
     *  \tparam T1 Muunnoksen lähtötyyppi.
     *  \tparam T2 Muunnoksen kohdetyyppi.
     *  \param muunnettava Muunnettava arvo.
     *  \param muuntaja Muunnos tehdään tätä hyväksi käyttäen.
     *  \param tunnistamaton Arvo, jota mapista haetaan, jos \p muunnettava
     *      ei sieltä löytynyt.
     *  \returns Haettua vastaava arvo, jos se löytyy.  Jos ei löydy, niin
     *      tunnistamatonta arvoa vastaava.  Jos sitäkään ei löydy niin,
     *      T2().
     */
    template<typename T1, typename T2>
    T2
    muunna(
            T1 muunnettava,
            std::map<T1, T2> const& muuntaja,
            T1 tunnistamaton
          );


	#include "hyodykkeet.cc"



#endif  // JULKINEN_TOT_HYODYKKEET_HH
