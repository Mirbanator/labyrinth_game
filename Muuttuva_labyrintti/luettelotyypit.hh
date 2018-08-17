#ifndef JULKINEN_LUETTELOTYYPIT_HH
#define JULKINEN_LUETTELOTYYPIT_HH

/**
 *	\version $Id: pelirajapinta.hh 1844 2011-02-13 22:10:37Z salone58 $
 *	\file luettelotyypit.hh
 *	\brief Pelirajapinta-luokan esittely. ($Revision: 1844 $)
 *	\author ©2011 Eero Salonen <eero.j.salonen@tut.fi> 
 */

/// \namespace Julkinen
namespace Julkinen
{
	/**
	 *	\brief Pelaajan liikumissuunnat
	 */
	enum Suunta
	{
		/**
		 *	\brief Pelaaja liikuu alaspäin
		 */	
		ALAS,
		/**
		 *	\brief Pelaaja liikuu automaattisesti kohti seuraavaa palkintoa
		 *	
		 *	Pelaaja liikkuu ensisijaisesti siihen suuntaan missä matka
		 *	palkintoon on pidempi, jos siihen suuntaan ei voi liikkua,
		 *	niin pelaaja liikuu siihen suuntaa, missä matka palkintoon
		 *	on lyhyempi. Jos pelaaja ei pysty liikumaan kumpaankaan
		 *	suuntaan, niin pelaaja pysyy paikallaan.
		 *
		 *	Pelaaja ei ikinä liiku pois päin palkinnosta, paitsi jos
		 *	hänen poimimansa esineet aiheuttavat moisen siirtymän.
		 */
		AUTOMAATTI,
		/**
		 *	\brief Pelaaja liikuu oikealle
		 */			
		OIKEALLE,
		/**
		 *	\brief Pelaaja liikuu vasemmalle
		 */	
		VASEMMALLE,
		/**
		 *	\brief Pelaaja liikuu ylöspäin
		 */	
		YLOS,
		/**
		 *	\brief Pelaaja pysyy paikallaan
		 */	
		PAIKALLAAN
	};
			
	/**
	 *	\brief Esineiden tyyppitieto
	 */
 
//	enum EsineTyyppi
//	{
		/**
		 *	\brief Esine on palkinto esine
		 */	
//		PALKINTO
		/**
		 *	\brief Esine on teleportti käärö
		 */	
//		TELEPORTTI,
		/**
		 *	\brief Esine on kirottu poimiva pelaaja menettää vuoron
		 */	
//		KIROTTU,
		/**
		 *	\brief Esine on siunattu pelaaja saa ylimääräisen vuoron
		 */	
//		SIUNATTU
//	};

   /**
    *  \brief Erikoispalojen tyyppitieto
    */
   enum ErikoispalaTyyppi
   {
      /**
       * \brief Pala on normaali, jolla ei ole erikoistoiminnallisuutta.
       */
      NORMAALI,
        /**
         * \brief Pala on Teleporti
         */
        TELEPORTTI,
        /**
         * \brief Pala on siunattu, astuva pelaaja saa ylimääräisen vuoron
         */
        SIUNATTU,
        /**
         * \brief Pala on kirottu, astuva pelaaja menettää vuoron
         */
        KIROTTU
   };
   
	/**
	 *	\brief Tieto millainen pelaaja on kyseessä
	 */
	enum PelaajaTyyppi
	{
		/**
		 *	\brief Pelaaja on ihmispelaaja
		 */	
		IHMINEN,
		/**
		 *	\brief Pelaaja on tietokonepelaaja
		 */	
		TIETOKONE
				
	};
			
	/**
	 *	\brief Tieto siitä minkämuotoinen pala on kyseessä
	 */
	enum PalaTyyppi
	{
		/**
		 *	\brief Pala on suorakäytävä
		 */	
		IPALA,
		/**
		 *	\brief Pala on mutka
		 */	
		LPALA,
		/**
		 *	\brief Pala on T-risteys
		 */	
		TPALA
	};
			
	/**
	 *	\brief Tieto mille reunalle irtopala työnnettiin
	 */
	enum Reuna
	{
		/**
	 	 *	\brief Pala työnnettiin kartan alalaitaan.
		 */	
		ALA,
		/**
		 *	\brief Pala työnnettiin kartan oikeanaanlaitaan.
		 */
		OIKEA,
		/**
		 *	\brief Pala työnnettiin kartan vasempaan laitaan.
		 */
		VASEN,
		/**
		 *	\brief Pala työnnettiin kartan ylälaitaan.
		 */
		YLA,
		/**
		 *	\brief Pala työnnettiin tuntemattomaan paikkaan.
		 */
		EIOLE
	};
}

#endif // JULKINEN_LUETTELOTYYPIT
