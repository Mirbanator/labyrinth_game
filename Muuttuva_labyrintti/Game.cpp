#include "Game.h"
#include "debug.hh"
#include "vaittama.hh"

Game::Game() :
mGameMode(false), mScreen(nullptr), alueenKoko(0), mActivePlayer(0)
{}


Game::~Game()
{
	DEBUG_OUTPUT("Game destructor" << std::endl);

	system("PAUSE");
}
bool Game::onkoAlustustilassa() const{
	return !mGameMode;
}
void Game::lisaaNaytto(Julkinen::Nayttorajapinta* naytto){
	DEBUG_OUTPUT("lisaaNaytto()" << std::endl);

	// Perform checks
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, onkoAlustustilassa(), "onkoAlustustilassa", "Game.cpp", 23, "lisaaNaytto");

	// Add the screen
	mScreen = dynamic_cast<Naytto*>(naytto);
	mScreen->komentoAloitaRakennus();
}
void Game::maaritaPelialueenKoko(Julkinen::Koordinaatti const& koko){
	// Perform checks
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, mScreen != nullptr, "mScreen != nullptr", "Game.cpp", 31, "maaritaPelialueenKoko");

	// Define game area size
	alueenKoko = koko.haeXkoordinaatti();
}
void Game::lisaaPelaaja(Julkinen::PelaajaTyyppi tyyppi, std::string const& nimi, char lyhenne, Julkinen::Koordinaatti const& sijainti){
	DEBUG_OUTPUT("lisaaPelaaja()" << std::endl);

	// Perform checks
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, onkoAlustustilassa(), "onkoAlustustilassa", "Game.cpp", 36, "lisaaPelaaja");
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, alueenKoko > 0, "mAreaSize > 0", "Game.cpp", 37, "lisaaPelaaja");

	try{
		if (!sijainti.onkoIrtopala()){
			if ((int)sijainti.haeXkoordinaatti() < 1 || (int)sijainti.haeXkoordinaatti() > alueenKoko || (int)sijainti.haeYkoordinaatti() < 1 || (int)sijainti.haeXkoordinaatti() > alueenKoko)
				throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);
		}
		std::vector<Player>::iterator player = Pelaajat.end();
		player = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&sijainti](Player p){
			return sijainti == p.getLocation();
		});
		if (player != Pelaajat.end())
			throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe("There is already a player on the given coordinate."));
	}
	catch (Julkinen::Alustusvirhe& av){
		av.tulosta(std::cout);
		std::cout << std::endl;
	}

	// Add the piece
	Pelaajat.push_back(Player(tyyppi, nimi, lyhenne, sijainti));
}
void Game::lisaaPala(Julkinen::PalaTyyppi pala, unsigned int rotaatio, Julkinen::Koordinaatti const& sijainti){
	DEBUG_OUTPUT("lisaaPala()" << std::endl);
	// Perform checks
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, onkoAlustustilassa(), "onkoAlustustilassa", "Game.cpp", 50, "lisaaPala");
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, alueenKoko > 0, "mAreaSize > 0", "Game.cpp", 51, "lisaaPala");
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, vapaaPala(sijainti), "freePieceSlot", "Game.cpp", 52, "lisaaPala");

	try{
		if (!sijainti.onkoIrtopala()){
			if ((int)sijainti.haeXkoordinaatti() < 1 || (int)sijainti.haeXkoordinaatti() > alueenKoko || (int)sijainti.haeYkoordinaatti() < 1 || (int)sijainti.haeXkoordinaatti() > alueenKoko)
				throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);
		}
		if (rotaatio < 1 || rotaatio > 4)
			throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_ROTAATIO);
	}
	catch (Julkinen::Alustusvirhe& av){
		av.tulosta(std::cout);
		std::cout << std::endl;
	}


	// Add the piece
	Palat.push_back(Piece(sijainti, pala, rotaatio));
}
void Game::lisaaEsine(char merkki, Julkinen::Koordinaatti const& sijainti, std::string const& pelaaja){
	DEBUG_OUTPUT("lisaaEsine()" << std::endl);

	// Perform checks
	try{
		std::vector<Player>::iterator player = Pelaajat.end();
		player = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&pelaaja](Player p){
			return p.getName() == pelaaja;
		});
		if (player == Pelaajat.end())
			throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe("Player does not exist."));

		if (!sijainti.onkoIrtopala()){
			if ((int)sijainti.haeXkoordinaatti() < 1 || (int)sijainti.haeXkoordinaatti() > alueenKoko || (int)sijainti.haeYkoordinaatti() < 1 || (int)sijainti.haeXkoordinaatti() > alueenKoko)
				throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);
		}
	}
	catch (Julkinen::Alustusvirhe& av){
		av.tulosta(std::cout);
		std::cout << std::endl;
	}


	// Find piece where this item belongs and add it
	for (int i = 0; i < (int)Palat.size(); i++){
		if (Palat.at(i).getLocation() == sijainti)
			Palat.at(i).setItem(merkki);
	}

	// Find player whose target this item is and add it
	for (int i = 0; i < (int)Pelaajat.size(); i++){
		if (Pelaajat.at(i).getName() == pelaaja){
			Pelaajat.at(i).addTargetItem(merkki);
		}
	}
}
void Game::asetaPalanTyyppi(Julkinen::ErikoispalaTyyppi tyyppi, Julkinen::Koordinaatti const& sijainti, Julkinen::Koordinaatti const& kohde){
	DEBUG_OUTPUT("asetaPalanTyyppi()" << std::endl);

	// Perform checks
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, onkoAlustustilassa(), "onkoAlustustilassa", "Game.cpp", 57, "asetaPalanTyyppi");

	try{
		if (!sijainti.onkoIrtopala()){
			if ((int)sijainti.haeXkoordinaatti() < 1 || (int)sijainti.haeXkoordinaatti() > alueenKoko || (int)sijainti.haeYkoordinaatti() < 1 || (int)sijainti.haeXkoordinaatti() > alueenKoko)
				throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);
		}
		if (!kohde.onkoIrtopala()){
			if ((int)kohde.haeXkoordinaatti() < 1 || (int)kohde.haeXkoordinaatti() > alueenKoko || (int)kohde.haeYkoordinaatti() < 1 || (int)kohde.haeXkoordinaatti() > alueenKoko)
				throw Julkinen::Alustusvirhe(Julkinen::Alustusvirhe::VIRHEELLINEN_SIJAINTI);
		}
	}
	catch (Julkinen::Alustusvirhe& av)
	{
		av.tulosta(std::cout);
		std::cout << std::endl;
	}


	std::vector<Piece>::iterator currentPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
		return piece.getLocation() == sijainti;
	});
	currentPiece->setSpecialType(tyyppi);
	currentPiece->setTarget(kohde);
}
void Game::alustusLopeta(){
	DEBUG_OUTPUT("alustusLopeta()" << std::endl);

	paivita();
	mScreen->komentoLopetaRakennus();
	mGameMode = true;
	mScreen->ilmoitusVuorossa(Pelaajat.at(mActivePlayer).getName());
}
bool Game::onkoPelitilassa() const{
	return mGameMode;
}
void Game::komentoTyonna(Julkinen::Reuna reuna, unsigned int paikka, unsigned int rotaatio){
	DEBUG_OUTPUT("komentoTyonna()" << std::endl);

	// Perform checks
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, onkoPelitilassa(), "onkoPelitilassa", "Game.cpp", 80, "komentoTyonna");

	try{
		if (mPlayerActionStatus.isPushed()){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAA_ON_JO_TYONNETTY);
		}

		if ((int)paikka < 1 || (int)paikka > alueenKoko){
			throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_OLEMATON_PAIKKA);
		}
		if (rotaatio < 1 || rotaatio > 4){
			throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_VIRHEELLINEN_ROTAATIO);
		}
	}
	catch (Julkinen::Toimintovirhe& tv){
		tv.tulosta(std::cout);
		std::cout << std::endl;
		mScreen->ilmoitusVuorossa(Pelaajat.at(mActivePlayer).getName());
		return;
	}
	catch (Julkinen::Komentovirhe& kv){
		kv.tulosta(std::cout);
		return;
	}



	// Begin construction mode
	mScreen->komentoAloitaRakennus();
	mGameMode = false;

	// Get iterator to piece of opposite edge
	int x, y;
	switch (reuna){
	case Julkinen::ALA:
		y = 1;
		x = paikka;
		break;
	case Julkinen::YLA:
		y = alueenKoko;
		x = paikka;
		break;
	case Julkinen::OIKEA:
		x = 1;
		y = paikka;
		break;
	case Julkinen::VASEN:
		x = alueenKoko;
		y = paikka;
		break;
	}
	std::vector<Piece>::iterator irrotaPala = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
		return piece.getLocation() == Julkinen::Koordinaatti(x, y);
	});

	// Move pieces & players
	std::vector<Piece>::iterator liikutaPalaa;
	std::vector<Player>::iterator liikutaPelaajaa = Pelaajat.end(); 
	switch (reuna){
	case Julkinen::ALA:
		for (y += 1; y < alueenKoko + 1; y++){
			liikutaPalaa = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
				return piece.getLocation() == Julkinen::Koordinaatti(x, y);
			});
			liikutaPelaajaa = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
				return player.getLocation() == Julkinen::Koordinaatti(x, y);
			});
			liikutaPalaa->setLocation(Julkinen::Koordinaatti(x, y - 1));
			if (liikutaPelaajaa != Pelaajat.end()){
				if (y > 1)
					liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(x, y - 1));
				else
					liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(x, alueenKoko));
			}
			liikutaPelaajaa = Pelaajat.end();
		}
		liikutaPelaajaa = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
			return player.getLocation() == Julkinen::Koordinaatti(x, 1);
		});
		if (liikutaPelaajaa != Pelaajat.end())
			liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(x, alueenKoko));
		y--;
		break;
	case Julkinen::YLA:
		for (y -= 1; y > 0; y--){
			liikutaPalaa = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
				return piece.getLocation() == Julkinen::Koordinaatti(x, y);
			});
			liikutaPelaajaa = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
				return player.getLocation() == Julkinen::Koordinaatti(x, y);
			});
			liikutaPalaa->setLocation(Julkinen::Koordinaatti(x, y + 1));
			if (liikutaPelaajaa != Pelaajat.end()){
				if (y < alueenKoko)
					liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(x, y + 1));
				else
					liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(x, 1));
			}
			liikutaPelaajaa = Pelaajat.end();
		}
		liikutaPelaajaa = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
			return player.getLocation() == Julkinen::Koordinaatti(x, alueenKoko);
		});
		if (liikutaPelaajaa != Pelaajat.end())
			liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(x, 1));
		y++;
		break;
	case Julkinen::OIKEA:
		for (x += 1; x < alueenKoko + 1; x++){
			liikutaPalaa = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
				return piece.getLocation() == Julkinen::Koordinaatti(x, y);
			});
			liikutaPelaajaa = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
				return player.getLocation() == Julkinen::Koordinaatti(x, y);
			});
			liikutaPalaa->setLocation(Julkinen::Koordinaatti(x - 1, y));
			if (liikutaPelaajaa != Pelaajat.end()){
				if (x > 1)
					liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(x - 1, y));
				else
					liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(alueenKoko, y));
			}
			liikutaPelaajaa = Pelaajat.end();
		}
		liikutaPelaajaa = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
			return player.getLocation() == Julkinen::Koordinaatti(1, y);
		});
		if (liikutaPelaajaa != Pelaajat.end())
			liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(alueenKoko, y));
		x--;
		break;
	case Julkinen::VASEN:
		for (x -= 1; x > 0; x--){
			liikutaPalaa = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
				return piece.getLocation() == Julkinen::Koordinaatti(x, y);
			});
			liikutaPelaajaa = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
				return player.getLocation() == Julkinen::Koordinaatti(x, y);
			});
			liikutaPalaa->setLocation(Julkinen::Koordinaatti(x + 1, y));
			if (liikutaPelaajaa != Pelaajat.end()){
				if (x < alueenKoko)
					liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(x + 1, y));
				else
					liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(1, y));
			}
			liikutaPelaajaa = Pelaajat.end();
		}
		liikutaPelaajaa = std::find_if(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
			return player.getLocation() == Julkinen::Koordinaatti(alueenKoko, y);
		});
		if (liikutaPelaajaa != Pelaajat.end())
			liikutaPelaajaa->setLocation(Julkinen::Koordinaatti(1, y));
		x++;
		break;
	}

	// Move current detached piece to empty slot
	std::vector<Piece>::iterator attachPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
		return piece.getLocation() == Julkinen::Koordinaatti();
	});
	attachPiece->setLocation(Julkinen::Koordinaatti(x, y));
	attachPiece->setRotation(rotaatio);

	// Set original piece of opposite edge as new detached piece
	irrotaPala->setLocation(Julkinen::Koordinaatti());

	mPlayerActionStatus.setPushed();

	paivita();

	mScreen->komentoLopetaRakennus();
	mScreen->ilmoitusVuorossa(Pelaajat.at(mActivePlayer).getName());
	mGameMode = true;
}
void Game::komentoLiiku(Julkinen::Suunta suunta, unsigned int maara){
	DEBUG_OUTPUT("komentoLiiku()" << std::endl);

	// Perform checks
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, onkoPelitilassa(), "onkoPelitilassa", "Game.cpp", 242, "komentoLiiku");

	if (suunta == Julkinen::AUTOMAATTI){
		tietokone();
		// CPU actions handled, no reason to continue in method
		return;
	}

	try{
		if (!mPlayerActionStatus.isPushed()){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_IRTOPALAA_EI_OLE_TYONNETTY);
		}
		if ((int)maara < 0){
			throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_TUNNISTAMATON_PARAMETRI);
		}
		if (maara == 0 && suunta != Julkinen::Suunta::PAIKALLAAN){
			throw Julkinen::Komentovirhe(Julkinen::Komentovirhe::VIRHE_TUNNISTAMATON_PARAMETRI);
		}
		if (tormays(suunta, maara)){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_EI_VOITU_LIIKKUA_ANNETTUA_MAARAA);
		}
	}
	catch (Julkinen::Toimintovirhe& tv){
		tv.tulosta(std::cout);
		std::cout << std::endl;
		// At the moment, if player performs Toimintovirhe, he is NOT asked for a new command.
		mPlayerActionStatus.setMoved();
		return;
	}
	catch (Julkinen::Komentovirhe& kv){
		kv.tulosta(std::cout);
		std::cout << std::endl;
		// At the moment, if player performs Toimintovirhe, he is NOT asked for a new command.
		mPlayerActionStatus.setMoved();
		return;
	}

	if (suunta == Julkinen::PAIKALLAAN){
		Pelaajat.at(mActivePlayer).setLastCommand(std::string("paikallaan"));
		mPlayerActionStatus.setMoved();
		// Player does not want to move, no reason to continue in method
		return;
	}

	// If got to this point, it is safe to move player.
	Liiku(maara, suunta);
	Pelaajat.at(mActivePlayer).setLastCommand(std::string("liiku " + directionChar(suunta) + " " + std::to_string(maara)));
	mPlayerActionStatus.setMoved();

}
bool Game::vaihdaVuoro(){
	DEBUG_OUTPUT("vaihdaVuoro()" << std::endl);

	// Perform checks
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, onkoPelitilassa(), "onkoPelitilassa", "Game.cpp", 344, "vaihdaVuoro");
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, mPlayerActionStatus.actionsDone(), "mPlayerActionStatus.actionsDone()", "Game.cpp", 345, "vaihdaVuoro");

	try{
		if (!mPlayerActionStatus.isMoved()){
			throw Julkinen::Toimintovirhe(Julkinen::Toimintovirhe::VIRHE_PELAAJA_EI_OLE_LIIKKUNUT);
		}
	}
	catch (Julkinen::Toimintovirhe& tv){
		tv.tulosta(std::cout);
		std::cout << std::endl;
		return true;
	}


	// Check if someone won game
	for (int i = 0; i < (int)Pelaajat.size(); i++){
		if (Pelaajat.at(i).isWinner())
		{
			return false;
		}
	};

	// Do things
	mScreen->komentoAloitaRakennus();
	mGameMode = false;

	paivita();

	mScreen->komentoLopetaRakennus();
	mGameMode = true;

	if (mActivePlayer == Pelaajat.size() - 1)
		mActivePlayer = 0;
	else
		mActivePlayer++;
	DEBUG_OUTPUT("Active Player:" << mActivePlayer << std::endl);

	mScreen->ilmoitusVuorossa(Pelaajat.at(mActivePlayer).getName());
	mPlayerActionStatus.reset();
	return true;
}
Julkinen::PelaajaTyyppi Game::haeVuorossa(){
	// Perform checks
	Julkinen::vaittamaToteutus(Julkinen::ESIEHTOVAITTAMA, onkoPelitilassa(), "onkoPelitilassa", "Game.cpp", 314, "haeVuorossa");

	return Pelaajat.at(mActivePlayer).getType();
}

void Game::paivita(){

	std::for_each(Palat.begin(), Palat.end(), [&](Piece piece){
		mScreen->palaLaudalle(piece.getType(), Julkinen::ErikoispalaTyyppi(), piece.getRotation(), piece.getLocation(), Julkinen::Koordinaatti());
		// Check that there is an item on piece
		if (piece.getItem() != 'x')
			mScreen->esineLaudalle(piece.getItem(), piece.getLocation());
	});
	std::for_each(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
		mScreen->pelaajaLaudalle(player.getAbbr(), player.getLocation());
	});
	std::for_each(Pelaajat.begin(), Pelaajat.end(), [&](Player player){
		mScreen->tulostaPelaajantiedot(player.getName(), player.getCollectedItems(), player.getTargetItems(), player.getLastCommand());
	});
}
bool Game::tormays(const Julkinen::Suunta& direction, const unsigned& amount){

	// If direction is PAIKALLAAN or AUTOMAATTI, no reason to continue in method
	if (direction == Julkinen::PAIKALLAAN || direction == Julkinen::AUTOMAATTI)
		return false;

	// Get iterator to player
	std::vector<Player>::iterator player = Pelaajat.begin() + mActivePlayer;

	// Get player location
	int x = player->getLocation().haeXkoordinaatti();
	int y = player->getLocation().haeYkoordinaatti();

	switch (direction){
	case Julkinen::ALAS:
		// check if out of game area
		if ((y + (int)amount) > alueenKoko) return true;
		// check for collision
		for (int i = 0; i < (int)amount; i++){

			std::vector<Piece>::iterator currentPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
				return piece.getLocation() == Julkinen::Koordinaatti(x, y);
			});

			Julkinen::PalaTyyppi startType = currentPiece->getType();
			unsigned int startRotation = currentPiece->getRotation();

			if ((startType == Julkinen::IPALA && startRotation == 2)
				|| (startType == Julkinen::IPALA && startRotation == 4)
				|| (startType == Julkinen::LPALA && startRotation == 1)
				|| (startType == Julkinen::LPALA && startRotation == 4)
				|| (startType == Julkinen::TPALA && startRotation == 3)
				) return true;

			if (y < alueenKoko){
				std::vector<Piece>::iterator nextPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
					return piece.getLocation() == Julkinen::Koordinaatti(x, y + 1);
				});

				Julkinen::PalaTyyppi destType = nextPiece->getType();
				unsigned int destRotation = nextPiece->getRotation();

				if ((destType == Julkinen::IPALA && destRotation == 2)
					|| (destType == Julkinen::IPALA && destRotation == 4)
					|| (destType == Julkinen::LPALA && destRotation == 2)
					|| (destType == Julkinen::LPALA && destRotation == 3)
					|| (destType == Julkinen::TPALA && destRotation == 1)
					) return true;
			}
			y++;
		}
		if (tormaysPelaajaan(x, y))
			return true;
		break;
	case Julkinen::YLOS:
		// check if out of game area
		if ((y - (int)amount) < 1) return true;
		// check for collision
		for (unsigned i = 0; i < amount; i++){

			std::vector<Piece>::iterator currentPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
				return piece.getLocation() == Julkinen::Koordinaatti(x, y);
			});

			Julkinen::PalaTyyppi startType = currentPiece->getType();
			unsigned int startRotation = currentPiece->getRotation();

			if ((startType == Julkinen::IPALA && startRotation == 2)
				|| (startType == Julkinen::IPALA && startRotation == 4)
				|| (startType == Julkinen::LPALA && startRotation == 3)
				|| (startType == Julkinen::LPALA && startRotation == 3)
				|| (startType == Julkinen::TPALA && startRotation == 1)
				) return true;

			if (y > 1){
				std::vector<Piece>::iterator nextPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
					return piece.getLocation() == Julkinen::Koordinaatti(x, y - 1);
				});

				Julkinen::PalaTyyppi destType = nextPiece->getType();
				unsigned int destRotation = nextPiece->getRotation();

				if ((destType == Julkinen::IPALA && destRotation == 2)
					|| (destType == Julkinen::IPALA && destRotation == 4)
					|| (destType == Julkinen::LPALA && destRotation == 1)
					|| (destType == Julkinen::LPALA && destRotation == 4)
					|| (destType == Julkinen::TPALA && destRotation == 3)
					) return true;
			}
			y--;

		}
		if (tormaysPelaajaan(x, y))
			return true;
		break;
	case Julkinen::OIKEALLE:
		// check if out of game area
		if ((x + (int)amount) > alueenKoko) return true;
		// check for collision
		for (int i = 0; i < (int)amount; i++){

			std::vector<Piece>::iterator currentPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
				return piece.getLocation() == Julkinen::Koordinaatti(x, y);
			});

			Julkinen::PalaTyyppi startType = currentPiece->getType();
			unsigned int startRotation = currentPiece->getRotation();

			if ((startType == Julkinen::IPALA && startRotation == 1)
				|| (startType == Julkinen::IPALA && startRotation == 3)
				|| (startType == Julkinen::LPALA && startRotation == 3)
				|| (startType == Julkinen::LPALA && startRotation == 4)
				|| (startType == Julkinen::TPALA && startRotation == 2)
				) return true;

			if (x < alueenKoko){
				std::vector<Piece>::iterator nextPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
					return piece.getLocation() == Julkinen::Koordinaatti(x + 1, y);
				});

				Julkinen::PalaTyyppi destType = nextPiece->getType();
				unsigned int destRotation = nextPiece->getRotation();

				if ((destType == Julkinen::IPALA && destRotation == 1)
					|| (destType == Julkinen::IPALA && destRotation == 3)
					|| (destType == Julkinen::LPALA && destRotation == 1)
					|| (destType == Julkinen::LPALA && destRotation == 2)
					|| (destType == Julkinen::TPALA && destRotation == 4)
					) return true;
			}
			x++;
		}
		// Check for player collision
		if (tormaysPelaajaan(x, y))
			return true;
		break;
	case Julkinen::VASEMMALLE:
		// check if out of game area
		if ((x - (int)amount) < 1)
			return true;
		// check for collision
		for (int i = 0; i < (int)amount; i++){

			std::vector<Piece>::iterator currentPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
				return piece.getLocation() == Julkinen::Koordinaatti(x, y);
			});

			Julkinen::PalaTyyppi startType = currentPiece->getType();
			unsigned int startRotation = currentPiece->getRotation();

			if ((startType == Julkinen::IPALA && startRotation == 1)
				|| (startType == Julkinen::IPALA && startRotation == 3)
				|| (startType == Julkinen::LPALA && startRotation == 1)
				|| (startType == Julkinen::LPALA && startRotation == 2)
				|| (startType == Julkinen::TPALA && startRotation == 4)
				) return true;

			if (x > 1){
				std::vector<Piece>::iterator nextPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
					return piece.getLocation() == Julkinen::Koordinaatti(x - 1, y);
				});

				Julkinen::PalaTyyppi destType = nextPiece->getType();
				unsigned int destRotation = nextPiece->getRotation();

				if ((destType == Julkinen::IPALA && destRotation == 1)
					|| (destType == Julkinen::IPALA && destRotation == 3)
					|| (destType == Julkinen::LPALA && destRotation == 3)
					|| (destType == Julkinen::LPALA && destRotation == 4)
					|| (destType == Julkinen::TPALA && destRotation == 2)
					) return true;
			}
			x--;
		}
		if (tormaysPelaajaan(x, y))
			return true;
		break;
	}
	// If got to this point, no collisions detected
	return false;
}
bool Game::tormaysPelaajaan(const int& x, const int& y) const{
	for (int i = 0; i < (int)Pelaajat.size(); i++){
		if (Pelaajat.at(i).getLocation() == Julkinen::Koordinaatti(x, y) && Pelaajat.at(i).getName() != Pelaajat.at(mActivePlayer).getName()){
			return true;
		}
	};
	return false;
}
void Game::tietokone(){

	// Get CPU target coordinates
	Julkinen::Koordinaatti targetCoords;
	std::for_each(Palat.begin(), Palat.end(), [&](Piece piece){
		if (piece.getItem() == Pelaajat.at(mActivePlayer).nextItem())
			targetCoords = piece.getLocation();
	});

	// If current CPU target is on a detached piece, do nothing and return
	if (targetCoords.onkoIrtopala())
		return;

	DEBUG_OUTPUT("CPU Target coords: " << targetCoords.haeXkoordinaatti() << " " << targetCoords.haeYkoordinaatti() << std::endl);

	// Move to closest distance
	Julkinen::Koordinaatti playerCoords = Pelaajat.at(mActivePlayer).getLocation();
	int X, Y, moveDistance;
	Julkinen::Suunta priorityDirection;
	X = playerCoords.haeXkoordinaatti() - targetCoords.haeXkoordinaatti();
	Y = playerCoords.haeYkoordinaatti() - targetCoords.haeYkoordinaatti();
	// Calculate priority direction 
	if (std::abs(X) > std::abs(Y)){
		if (X > 0)
		{
			priorityDirection = Julkinen::VASEMMALLE;
			moveDistance = std::abs(X);
		}
		else if (X < 0)
		{
			priorityDirection = Julkinen::OIKEALLE;
			moveDistance = std::abs(X);
		}
	}
	else if (std::abs(Y) > std::abs(X)){
		if (Y > 0)
		{
			priorityDirection = Julkinen::YLOS;
			moveDistance = std::abs(Y);
		}
		else if (Y < 0)
		{
			priorityDirection = Julkinen::ALAS;
			moveDistance = std::abs(Y);
		}
	}
	// if there is no difference between diffY and diffX, move to random direction
	else{
		moveDistance = 1;
		priorityDirection = randomDirection();
	}

	// Test priority direction for collisions.
	// If test fails, reduce moveDistance by one and try again.
	bool safeToMove = false;
	while (moveDistance > 0){
		if (tormays(priorityDirection, moveDistance))
			moveDistance--;
		else{
			safeToMove = true;
			break;
		}

	}
	// If could not move, try move to random direction as far as possible
	if (!safeToMove){
		Julkinen::Suunta rndDirection = priorityDirection;

		// Find a direction other than current priority
		while (rndDirection == priorityDirection)
			rndDirection = randomDirection();

		// Set it as new priority direction
		priorityDirection = rndDirection;
		moveDistance = 1;

		// Check for collisions
		while (moveDistance > 0){
			if (tormays(priorityDirection, moveDistance))
				moveDistance--;
			else{
				safeToMove = true;
				break;
			}

		}
	}
	// Confirm that it is safe and move CPU.
	// If its still not safe, do not move at all.
	if (safeToMove)
		Liiku(moveDistance, priorityDirection);

	// Set CPU status flags
	mPlayerActionStatus.setMoved();
	mPlayerActionStatus.setPushed();
}
std::string Game::directionChar(const Julkinen::Suunta& direction) const{
	if (direction == Julkinen::ALAS)
		return std::string("a");
	else if (direction == Julkinen::YLOS)
		return std::string("y");
	else if (direction == Julkinen::VASEMMALLE)
		return std::string("v");
	else if (direction == Julkinen::OIKEALLE)
		return std::string("o");

	return std::string("");
}
void Game::Liiku(const int& distance, const Julkinen::Suunta& direction){
	// Get iterator to player
	std::vector<Player>::iterator player = Pelaajat.begin() + mActivePlayer;
	// Get players current coordinates
	int x = player->getLocation().haeXkoordinaatti();
	int y = player->getLocation().haeYkoordinaatti();
	switch (direction){
	case Julkinen::ALAS:
		// Loop all pieces in players path to collect items
		for (int limit = y + distance; y < limit + 1; y++){
			if (y <= alueenKoko){
				// Get iterator to piece under player
				std::vector<Piece>::iterator atPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
					return piece.getLocation() == Julkinen::Koordinaatti(x, y);
				});
				// Check if the piece under the player has an item or if it is a special piece
				// If stepOnPiece returns false, player has stepped on teleport. If so, return to stop movement.
				if (!astu(atPiece, player))
					return;
			}
		}
		y--;
		// Move player
		player->setLocation(Julkinen::Koordinaatti(x, y));
		break;
	case Julkinen::YLOS:
		// Loop all pieces in players path to collect items
		for (int limit = y - distance; y >= limit; y--){
			if (y > 0){
				// Get iterator to piece under player
				std::vector<Piece>::iterator atPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
					return piece.getLocation() == Julkinen::Koordinaatti(x, y);
				});
				// Check if the piece under the player has an item or if it is a special piece
				// If stepOnPiece returns false, player has stepped on teleport. If so, return to stop movement.
				if (!astu(atPiece, player))
					return;
			}
		}
		y++;
		// Move player
		player->setLocation(Julkinen::Koordinaatti(x, y));
		break;
	case Julkinen::OIKEALLE:
		// Loop all pieces in players path to collect items
		for (int limit = x + distance; x < limit + 1; x++){
			if (x <= alueenKoko){
				// Get iterator to piece under player
				std::vector<Piece>::iterator atPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
					return piece.getLocation() == Julkinen::Koordinaatti(x, y);
				});
				// Check if the piece under the player has an item or if it is a special piece
				// If stepOnPiece returns false, player has stepped on teleport. If so, return to stop movement.
				if (!astu(atPiece, player))
					return;
			}
		}
		x--;
		// Move player
		player->setLocation(Julkinen::Koordinaatti(x, y));
		break;
	case Julkinen::VASEMMALLE:
		// Loop all pieces in players path to collect items
		for (int limit = x - distance; x >= limit; x--){
			if (x > 0){
				// Get iterator to piece under player
				std::vector<Piece>::iterator atPiece = std::find_if(Palat.begin(), Palat.end(), [&](Piece piece){
					return piece.getLocation() == Julkinen::Koordinaatti(x, y);
				});
				// Check if the piece under the player has an item or if it is a special piece
				// If stepOnPiece returns false, player has stepped on teleport. If so, return to stop movement.
				if (!astu(atPiece, player))
					return;
			}
		}
		x++;
		// Move player
		player->setLocation(Julkinen::Koordinaatti(x, y));
		break;
	}
}
Julkinen::Suunta Game::randomDirection() const{
	srand((unsigned)time(NULL));
	int rnd = rand() % 4;
	switch (rnd){
	case 0:
		return Julkinen::YLOS;
	case 1:
		return Julkinen::ALAS;
	case 2:
		return Julkinen::VASEMMALLE;
	case 3:
		return Julkinen::OIKEALLE;
	default:
		return Julkinen::Suunta::PAIKALLAAN;
	}

}
bool Game::vapaaPala(const Julkinen::Koordinaatti& coord){
	std::vector<Piece>::iterator piece = Palat.end();
	std::find_if(Palat.begin(), Palat.end(), [&coord](Piece piece){
		return piece.getLocation() == coord;
	});
	if (piece == Palat.end())
		return true;

	return false;
}
bool Game::astu(std::vector<Piece>::iterator piece, std::vector<Player>::iterator player){
	// If piece has item that matches players next target, collect it
	if (piece->getItem() == player->nextItem()){
		player->collectItem();
		mScreen->ilmoitusEsinePoimittu(piece->getItem(), player->getName());
		piece->removeItem();
	}
	// If piece has special type of Teleport, do teleporting and return false
	if (piece->getSpecialType() == Julkinen::TELEPORTTI){
		player->setLocation(piece->getTarget());
		mScreen->ilmoitusErikoispalaanAstuttu(Julkinen::TELEPORTTI, player->getName());
		return false;
	}
	// If piece has any other special type, throw ToteuttamatonVirhe
	try{
		if (piece->getSpecialType() == Julkinen::KIROTTU)
			throw Julkinen::ToteuttamatonVirhe("Cursed piece has not been implemented.");
		if (piece->getSpecialType() == Julkinen::SIUNATTU)
			throw Julkinen::ToteuttamatonVirhe("Blessed piece has not been implemented.");
	}
	catch (Julkinen::ToteuttamatonVirhe& tv){
		if (debug_output){
			tv.tulosta(std::cout);
			std::cout << std::endl;
		}
	}

	return true;
}