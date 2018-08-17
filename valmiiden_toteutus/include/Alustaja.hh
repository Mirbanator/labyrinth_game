/**
 *	\version $Id: Alustaja.hh 1800 2011-02-05 06:54:47Z salone58 $
 *  \file  Alustaja.hh
 *  \brief Labyrintti-pelin alustuksen apuluokka ($Revision: 1800 $)
 *  \author ©2010 Eero Salonen <eero.j.salonen@tut.fi> 
 */

#ifndef ALUSTAJA_HH
#define ALUSTAJA_HH

#include "../../koordinaatti.hh"
#include <vector>

/**
 * Alustaja-luokka huolehtii alkutilanteen luomisesta peli‰ varten.
 *
 * \b Huom! Alustaja-luokan origo (0,0) on <em>vasemmassa alanurkassa</em>
 * ja y-suunta kasvaa ylˆsp‰in.
 */
class Alustaja {
public:
  //! M‰‰ritt‰‰ y-koordinaatin maksimiarvon
  static unsigned int const LABYRINTIN_KORKEUS = 5;
  //! M‰‰ritt‰‰ x-koordinaatin maksimiarvon
  static unsigned int const LABYRINTIN_LEVEYS = 5;

  //! Merkki, jonka annaKoordinaatinEsine palauttaa, kun ruudussa ei ole esinett‰
  static char const EI_ESINETTA = 'x';

  /**
   * M‰‰ritt‰‰ ruudun tyypin eri vaihtoehdot.
   */
  enum Ruututyyppi {
    I, /*!< Kyseess‰ on harjoitustyˆohjeen I-ruutu */
    L, /*!< Kyseess‰ on harjoitustyˆohjeen L-ruutu */
    T  /*!< Kyseess‰ on harjoitustyˆohjeen T-ruutu */
  };

  /**
   * \param pelaajia Peliss‰ mukana olevien pelaajien m‰‰r‰. Pit‰‰ olla v‰lill‰
   *                 2-4.
   */
  Alustaja(unsigned int pelaajia);
  /**
   * \param pelaajia Peliss‰ mukana olevien pelaajien m‰‰r‰. Pit‰‰ olla v‰lill‰
   *                 2-4.
   * \param siemen Satunnaislukugeneraattorille annettava alustusarvo.
   */
  Alustaja(unsigned int pelaajia, unsigned long int siemen);
  /**
   * Purkaja
   */
  ~Alustaja();

  /**
   * \return Palauttaa alkutilanteen irtopalan tyypin.
   */
  Ruututyyppi annaIrtopalanTyyppi() const;

  /**
   * Alustaja-luokan origo (0,0) on <em>vasemmassa alanurkassa</em>
   * ja y-suunta kasvaa ylˆsp‰in.
   *
   * \param x Labyrintin x-koordinaatti. Pit‰‰ olla v‰lill‰
   *          1-LABYRINTIN_LEVEYS.
   * \param y Labyrintin y-koordinaatti. Pit‰‰ olla v‰lill‰
   *          1-LABYRINTIN_KORKEUS.
   * \return Palauttaa labyrintin alkutilanteen ruudun (x, y) tyypin.
   */
  Ruututyyppi annaKoordinaatinRuututyyppi(unsigned int x,
					  unsigned int y) const;

  /**
   * Alustaja-luokan origo (0,0) on <em>vasemmassa alanurkassa</em>
   * ja y-suunta kasvaa ylˆsp‰in.
   *
   * \param x Labyrintin x-koordinaatti. Pit‰‰ olla v‰lill‰
   *          1-LABYRINTIN_LEVEYS.
   * \param y Labyrintin y-koordinaatti. Pit‰‰ olla v‰lill‰
   *          1-LABYRINTIN_KORKEUS.
   * \return Palauttaa labyrintin alkutilanteen ruudun (x, y) rotaation.
   *         Rotaatio on kokonaisluku v‰lill‰ 1-4.
   */
  unsigned int annaKoordinaatinRotaatio(unsigned int x,
					unsigned int y) const;

  /**
   * Alustaja-luokan origo (0,0) on <em>vasemmassa alanurkassa</em>
   * ja y-suunta kasvaa ylˆsp‰in.
   *
   * \param x Labyrintin x-koordinaatti. Pit‰‰ olla v‰lill‰
   *          1-LABYRINTIN_LEVEYS.
   * \param y Labyrintin y-koordinaatti. Pit‰‰ olla v‰lill‰
   *          1-LABYRINTIN_KORKEUS.
   * \return Palauttaa joko ruudussa olevaa esinett‰ vastaavan merkin v‰lilt‰
   *         a-l tai vaihtoehtoisesti vakion EI_ESINETTA, jos ruutu on tyhj‰.
   */
  char annaKoordinaatinEsine(unsigned int x, unsigned int y) const;

   char annaKoordinaatinErikoispala(unsigned int x, unsigned int y) const;
  /**
   * \param pelaaja Pelaajan numero. Pit‰‰ olla v‰lill‰ 0-(pelaajien_lkm-1).
   * \return Palauttaa pelaajan etsitt‰vien esineiden listan.
   */
  std::vector<char> annaPelaajanEsinelista(unsigned int pelaaja) const;

  /**
   * \return Palauttaa Alustajan satunnaislukugeneraattorin k‰ytt‰m‰n
   * siemenluvun.
   */
  unsigned long int annaSiemenluku() const;

   Julkinen::Koordinaatti annaSeuraavaKohde();
private:
  Alustaja(Alustaja const&);
  Alustaja & operator=(Alustaja const&);

  static unsigned long int const raakamax_ = 0x7FFFFFFFul;

  void arvoAlkutilanne();

  unsigned long int arvo(unsigned long int raja);
  unsigned long int raakaArvo();

  unsigned long int alkusiemen_;
  unsigned long int siemen1_;
  unsigned long int siemen2_;

  unsigned int erikoisesineidenmaara_;
  unsigned int pelaajia_;

  Ruututyyppi irtopala_;

  std::vector<Ruututyyppi> labyrintinRuudut;
  std::vector<unsigned int> labyrintinRotaatiot;
  std::vector<char> labyrintinEsineet;
  std::vector< std::vector<char> > pelaajienEsineet;
   std::vector<char> labyrintinErikoispalat;
   std::vector<unsigned int> kohdePalat;
   
   unsigned int annettuKohde;
};

#endif // ALUSTAJA_HH
