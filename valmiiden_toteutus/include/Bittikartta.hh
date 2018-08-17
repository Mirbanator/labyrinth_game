/**
 *	\version $Id: Bittikartta.hh 1800 2011-02-05 06:54:47Z salone58 $
 *  \file  Bittikartta.hh
 *  \brief Labyrintti-pelin tulostuksen apuluokka ($Revision: 1800 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi> 
 */
#ifndef BITTIKARTTA_HH
#define BITTIKARTTA_HH

#include <string>
#include <iosfwd>

/**
 * Dimensiotyyppi Bittikartta-luokan koordinaateille.
 */
typedef unsigned long int Dim;

/**
 * Bittikartta-luokka mahdollistaa tulostusten tekemisen vaiheittain
 * Bittikartta-luokan olioon ja vasta lopuksi tulostamisen ruudulle.
 *
 * \b Huom! Bittikartta-luokan origo (0,0) on <em>vasemmassa yl‰nurkassa</em>
 * ja y-suunta kasvaa alasp‰in.
 */
class Bittikartta
{

public:

  /**
   * \param leveys piirtoalueen leveys
   * \param korkeus piirtoalueen korkeus
   */
   Bittikartta(Dim leveys, Dim korkeus);

  /**
   * Purkaja
   */
   ~Bittikartta();

  /**
   * Kirjoittaa alueelle vaakatekstin, joka alkaa koordinaateista (x, y).
   * Viimeinen merkki tulee pisteeseen (x + tekstin pituus, y).
   * Bittikartta-luokan origo (0,0) on <em>vasemmassa yl‰nurkassa</em>
   * ja y-suunta kasvaa alasp‰in.
   * \param x alkupisteen x-koordinaatti
   * \param y alkupisteen y-koordinaatti
   * \param teksti kirjoitettava teksti
   */
   void vaakateksti(Dim x, Dim y, std::string const& teksti);

  /**
   * Kirjoittaa alueelle pystytekstin, joka alkaa koordinaateista (x, y).
   * Viimeinen merkki tulee pisteeseen (x, y + tekstin pituus).
   * Bittikartta-luokan origo (0,0) on <em>vasemmassa yl‰nurkassa</em>
   * ja y-suunta kasvaa alasp‰in.
   * \param x alkupisteen x-koordinaatti
   * \param y alkupisteen y-koordinaatti
   * \param teksti kirjoitettava teksti
   */
   void pystyteksti(Dim x, Dim y, std::string const& teksti);

  /**
   * Piirt‰‰ suorakaiteen, jonka vasen yl‰kulma on pisteess‰ (x, y). Reunat
   * piirret‰‰n annetulla merkill‰.
   * Bittikartta-luokan origo (0,0) on <em>vasemmassa yl‰nurkassa</em>
   * ja y-suunta kasvaa alasp‰in.
   * \param x alkupisteen x-koordinaatti
   * \param y alkupisteen y-koordinaatti
   * \param lev suorakaiteen leveys
   * \param kork suorakaiteen korkeus
   * \param merkki alueen ‰‰riviivojen piirt‰miseen k‰ytett‰v‰ merkki
   */
   void suorakaide(Dim x, Dim y, Dim lev, Dim kork, char merkki);

  /**
   * Pyyhkii piirtoalueen eli korvaa kaikki piirretyt merkit v‰lilyˆnneill‰.
   */
   void tyhjenna();

  /**
   * Tulostaa bittikartan sis‰llˆn annettuun virtaan.
   * \param virta virta, johon bittikartta tulostetaan
   */
   void tulosta(std::ostream& virta) const;

  /**
   * Piirt‰‰ horisontaalisen viivan eli vaakaviivan.
   * Bittikartta-luokan origo (0,0) on <em>vasemmassa yl‰nurkassa</em>
   * ja y-suunta kasvaa alasp‰in.
   * \param x alkupisteen x-koordinaatti
   * \param y alkupisteen y-koordinaatti
   * \param lev viivan leveys
   * \param merkki viivan piirtoon k‰ytett‰v‰ merkki
   */
   void vaakaviiva(Dim x, Dim y, Dim lev, char merkki);

  /**
   * Piirt‰‰ vertikaalisen viivan eli pystyviivan.
   * Bittikartta-luokan origo (0,0) on <em>vasemmassa yl‰nurkassa</em>
   * ja y-suunta kasvaa alasp‰in.
   * \param x alkupisteen x-koordinaatti
   * \param y alkupisteen y-koordinaatti
   * \param kork viivan korkeus
   * \param merkki viivan piirtoon k‰ytett‰v‰ merkki
   */
   void pystyviiva(Dim x, Dim y, Dim kork, char merkki);

private:


   inline Dim indeksi(Dim x, Dim y) const;
   void suorakaide( Dim x, Dim y, Dim lev, Dim kork,
                    char k, /// Yhden merkin kaide
                    char v, char kv, char o, /// Vaakaviiva
                    char yy, char kp, char a, /// Pystyviiva
                    char vy, char yv, char oy, char vp, char op,
                    char va, char av, char oa /// Suorakaide
                  );

  Dim x_;
  Dim y_;
  std::string kartta_;

  Bittikartta(Bittikartta const&); /// Estetty
  Bittikartta& operator =(Bittikartta const&); /// Estetty
};

#endif // BITTIKARTTA_HH

