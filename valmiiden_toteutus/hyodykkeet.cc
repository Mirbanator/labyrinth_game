#ifndef JULKINEN_TOT_HYODYKKEET_CC
#define JULKINEN_TOT_HYODYKKEET_CC


/**
 *  \file hyodykkeet.cc
 *  \brief Apufunktioiden toteutukset.
 *  \author ©2010 Jarmo Jaakkola <jarmo.jaakkola@tut.fi>,
 *      TTY Ohjelmistotekniikka
 */
#include "hyodykkeet.hh"




template<typename CharT, typename T>
bool
muunnaMerkkijono(std::basic_string<CharT> const& lahde, T& kohde)
{
    bool paluuarvo(true);

    std::basic_istringstream<CharT> virta(lahde);
    virta >> kohde;

    if (!virta || !virta.eof())
    {
        paluuarvo = false;
    }

    return paluuarvo;
}

template<typename CharT>
std::tr1::shared_ptr<CharT>
cMerkkijonoksi(std::basic_string<CharT> const& merkkijono)
{
    // Muistetaan tila myös lopun null-merkille.
    TaulukonTuhoaja<CharT> tuhoaja;
    std::tr1::shared_ptr<CharT> paluuarvo(
            new CharT[merkkijono.size() + 1],
            tuhoaja
          );

    // Seuraava toimii, koska c_str() on aina null-loppuinen.
    CharT* kohde(paluuarvo.get());
    CharT const* lahde(merkkijono.c_str());
    CharT const rajoitinMerkki = CharT();
    while ((*kohde++ = *lahde++) != rajoitinMerkki)
    {
    }

    return paluuarvo;
}

template<typename T1, typename T2>
T2
muunna(
        T1 muunnettava,
        std::map<T1, T2> const& muuntaja,
        T1 tunnistamaton
      )
{
    typename std::map<T1, T2>::const_iterator kohta(
            muuntaja.find(muunnettava)
          );

    if (muuntaja.end() != kohta)
    {
        return kohta->second;
    }

    kohta = muuntaja.find(tunnistamaton);
    if (muuntaja.end() != kohta)
    {
        return kohta->second;
    }

    return T2();
}

#endif  // JULKINEN_TOT_HYODYKKEET_ICC
