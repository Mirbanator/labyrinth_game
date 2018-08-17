/**
 *	\version $Id: labyrintti.cc 1802 2011-02-07 09:17:58Z salone58 $
 *  \file labyrintti.cc
 *  \brief Labyrintti pelin pﾃ､ﾃ､ohjelma ($Revision: 1802 $)
 *  \author ﾂｩ2011 Eero Salonen <eero.j.salonen@tut.fi>
 */

#include "include/include.hh"

const unsigned int MAX_PARAMETREJA = 4;
std::string lueArgumentit(std::deque<std::string> parametrit);

/**
 * \brief Globaali debug-lippu
 *
 * Pﾃ､ﾃ､ohjelma asettaa tﾃ､mﾃ､n lipun, jos ohjelma on kﾃ､ynnistetty debug-optiolla
 */
bool debug_output = false;

bool debug_naytto = false;

/**
 *	\brief Labyrintti-pelin pﾃ､ﾃ､ohjelma.
 *
 *	Kﾃ､yttﾃｶjﾃ､rjestelmﾃ､ kutsuu tﾃ､tﾃ､ funktiota ja kﾃ､ynnistﾃ､ﾃ､ labyrintti-pelin.
 *
 *	\param argc komentorivi argumenttien mﾃ､ﾃ､rﾃ､.
 *	\param argv komentorivi argumentit.
 *
 *	\return Tiedon onnistuiko ohjelman suoritus vai epﾃ､onnistuiko se.
 */
int main(int argc, char** argv)
{
	std::string tiedosto = "";
	std::deque<std::string> parametrit(argv, argv + argc);

	DEBUG_OUTPUT(argv << std::endl;);

   //Luetaan parametrit
	try
	{
		
		tiedosto = lueArgumentit(parametrit);
	}
	catch(Julkinen::Alustusvirhe virhe)
	{
		//Jos debug tilassa heitetään virhe eteenpäin
		if(debug_output)
		{ 
			DEBUG_OUTPUT(virhe << std::endl);
			throw;
		}
		else
		{	std::cerr << virhe << std::endl;
			return EXIT_FAILURE;
		}
	}
	catch(...)
	{
		//Jos debug tilassa heitetään virhe eteenpäin
		if(debug_output)
		{ 
			DEBUG_OUTPUT("VIRHE: Parametrien lukeminen epännistui"
				<< std::endl;);
			throw;
		}
		else
		{
			std::cerr
				<< "VIRHE: Parametrien lukeminen epännistui"
				<< std::endl;
			return EXIT_FAILURE;
		}
	}

	try
	{
		Julkinen::Koordinaatti koko(5,5);
		//Luodaan osoitin n艙ttnn.
		std::shared_ptr<Naytto> naytto(
			new Naytto(koko , 25, 20, debug_naytto));
		//Luodaan osoitin peliin
		
        std::shared_ptr<Game> peli(Julkinen::luoPeli());
		
		peli->lisaaNaytto(naytto.get());
		//Luodaan osoitin rakentajaan

        Rakentaja rakentaja(peli, koko,
                             tiedosto, naytto);
           
		//Alustetaan peli
		try
		{
	
			rakentaja.lueTiedosto();
	
			rakentaja.lisaaPalat();
	
			rakentaja.lisaaIrtopala();
	
			rakentaja.lisaaPelaajat();
	
			rakentaja.lisaaEsineet();
			peli->alustusLopeta();
        

		}
		catch(Julkinen::Virhe virhe)
		{
			//Jos debug tilassa heitetﾃ､ﾃ､n virhe eteenpﾃ､in
			if(debug_output)
			{ 
				DEBUG_OUTPUT(virhe << std::endl);
				throw;
			}
			else
			{
				std::cerr << virhe << std::endl;
				return EXIT_FAILURE;
			}
		}
		catch(...)
		{
			//Jos debug tilassa heitetﾃ､ﾃ､n virhe eteenpäin
			if(debug_output)
			{ 
				DEBUG_OUTPUT("VIRHE: Alustus epaonnistui" << std::endl);
				throw;
			}
			else
			{
				std::cerr << "VIRHE: Alustus epaonnistui" << std::endl;
				return EXIT_FAILURE;
			}
		}
		
		try
		{
			//Luodaan komentotulkki osoitin
			std::shared_ptr<Komentotulkki> komentotulkki(
				Komentotulkki::uusiKomentotulkki(naytto));
			//Kﾃ､ynnistetﾃ､ﾃ､n komentotulkki
			komentotulkki->kaynnistaKomentotulkki(peli);

		}
		catch(Julkinen::Virhe virhe)
		{
			//Jos debug tilassa heitetﾃ､ﾃ､n virhe eteenpﾃ､in
			if(debug_output)
			{ 
				DEBUG_OUTPUT(virhe << std::endl);
				throw;
			}
			else
			{
				std::cerr << virhe << std::endl;
				return EXIT_FAILURE;
			}
		}
		catch(...)
		{
			//Jos debug tilassa heitetﾃ､ﾃ､n virhe eteenpﾃ､in
			if(debug_output)
			{ 
				DEBUG_OUTPUT("VIRHE: Kaynnistys epaonnistui" << std::endl);
				throw;
			}
			else
			{
				std::cerr << "VIRHE: Kaynnistys epaonnistui" << std::endl;
				return EXIT_FAILURE;
			}
		}

	}
	catch(Julkinen::Virhe virhe)
	{
		//Jos debug tilassa heitetﾃ､ﾃ､n virhe eteenpﾃ､in
		if(debug_output)
		{ 
			DEBUG_OUTPUT(virhe << std::endl);
			throw;
		}
		else
		{
			std::cerr << virhe << std::endl;
			return EXIT_FAILURE;
		}
	}
	
	catch(...)
	{
		//Jos debug tilassa heitetﾃ､ﾃ､n virhe eteenpﾃ､in
		if(debug_output)
		{ 
			DEBUG_OUTPUT("VIRHE: Tuntematon virhe" << std::endl);
			throw;
		}
		else
		{
			std::cerr << "VIRHE: Tuntematon virhe" << std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;

}

std::string lueArgumentit(std::deque<std::string> parametrit)
{
   //Apumuuttuja alustustiedoston nime・varten
   std::string palaute;
   //Käydään parametrit läpi
   for(unsigned int i = 1; i < parametrit.size(); i++)
   {
      //Jos parametrina -d laitetaan ohjelma debug tilaan.
      if(parametrit[i] == "-d")
      {
         debug_output = true;
      }
      else if ( parametrit[i] == "-n" )
      {
         debug_naytto = true;
      }
                 
      else
      {
         palaute = parametrit[i];
      }
   }
   
   // Jos liikaa parametreja niin heitetään poikkeus.
   if(parametrit.size() > MAX_PARAMETREJA)
   {
      throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHE_LIIKAA_PARAMETREJA);
   }
   
   return palaute;
}
