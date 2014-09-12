  /* ----------------------------------------------------------------------
   * YATS (http://github.com/Ifsttar/YATS). This file is part of YATS.
   *
   * YATS (Yet Another Traffic Simulation) is a simple and efficient
   * Traffic Simulator used for reasearch purpose
   * Copyright (C) 2013-2014 - IFSTTAR - Julien Saunier and Julien Gagneux
 
   * YATS is free software; you can redistribute it and/or modify
   * it under the terms of the GNU General Public License as published by
   * the Free Software Foundation; either version 3 of the License, or
   * (at your option) any later version.
   * 
   * YATS is distributed in the hope that it will be useful,
   * but WITHOUT ANY WARRANTY; without even the implied warranty of
   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   * GNU General Public License for more details.
   * 
   * You should have received a copy of the GNU General Public License
   * along with this program; if not, write to the Free Software Foundation,
   * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA or 
   * see <http://ww.gnu.org/licenses/>
   *
   * For more information, please consult: <http://github.com/Ifsttar/YATS> or 
   * send an email to scientific.computing@ifsttar.fr
   *
   * To contact Ifsttar, write to Ifsttar, 14-20 Boulevard Newton
   * Cité Descartes, Champs sur Marne F-77447 Marne la Vallée Cedex 2 FRANCE
   * or write to scientific.computing@ifsttar.fr
   * ----------------------------------------------------------------------*/
   
   
#include "yats.h"
#include "InitialScreen.h"
//#include <>

using namespace std;

#define PI 3.14159265
#define DEG2RAD (PI/180)

//Le nombre de frames par seconde
const int FRAMES_PER_SECOND = 40;

//#define TEMPS       30 

InitialScreen::InitialScreen(void)
{
	// variable relatifs a la gestion du temps
	int frame =0 ;	
	//Ce qui va nous servir a activer/desactiver le regulateur
	bool cap = true;
	// bool utiliser pour déplacer l'image.
	bool isLeftMouseButtonPressed = false; // bool isLeftMouseButtonMove = false;
	int lastX, lastY;


	// INDISPENSABLE, initialise la SDL
	initMyScreen();

	// asking for user task
	askingUserForFile();
	
	// M.A.J de l'ecran
	SDL_Flip(pWindowSurface);

	char mustContinue = 1; // Indicateur boolean pour la boucle principale

	//Timer utilise pour calculer le nombre de frames par seconde 
	TimerSDL fps; 	 

	applyFontScreen();

	// mis en place du system de log
	logIt();


	SDL_Event event;
	SDL_EnableKeyRepeat(1000, 1000);


	// Boucle principale
	while ( mustContinue )
	{
		//On demarre le timer fps 
		fps.start();
		
		SDL_PollEvent(&event);

        // re coloration de l'ecran de fond
		SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 0, 0, 0));

		/* a rajouter */
		SDL_BlitSurface(copyOfPWindowsSurface,NULL,pWindowSurface,&posOfCopy);
		

		screenRoutine();
	
		SDL_Flip(pWindowSurface);

		switch(event.type)
        {
			// Detecte si on clique sur la croix
            case SDL_QUIT:
                mustContinue = 0;
                break;

			case SDL_MOUSEBUTTONDOWN:

			//////////////////////////////
			// DEPLACEMENT - click Down // 
			//////////////////////////////
            if (event.button.button == SDL_BUTTON_LEFT)// si clique souris gauche
    	        {	SDL_GetMouseState(&lastX, &lastY); 
					isLeftMouseButtonPressed = true;}

			if (event.button.button == SDL_BUTTON_RIGHT)// si clique souris gauche
    	        {
					//myVehicle->setObjectifToFalse();
    	        }

			//////////
			// ZOOM // 
			//////////
			if (event.button.button == SDL_BUTTON_WHEELUP)// si clique souris gauche
    	        {
					if(m_Env.getRoadAt(0)->getZoomLVL()<1.70){
					SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 0, 0, 0));
					m_Env.zoomEnv(1.1);
					SDL_FreeSurface(copyOfPWindowsSurface);
					if((SDL_SaveBMP(pWindowSurface, whereIPrintRsx.c_str())) != 0)
						exit(EXIT_FAILURE); 
					copyOfPWindowsSurface = copie_surface(pWindowSurface);}
    	        }

			////////////
			// DEZOOM // 
			////////////
			if (event.button.button == SDL_BUTTON_WHEELDOWN)// si clique souris gauche
    	        {
					if(m_Env.getRoadAt(0)->getZoomLVL()>0.25){
					SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 0, 0, 0));					
					m_Env.zoomEnv(0.9);
					SDL_FreeSurface(copyOfPWindowsSurface);
					if((SDL_SaveBMP(pWindowSurface, whereIPrintRsx.c_str())) != 0)
						exit(EXIT_FAILURE); 
					copyOfPWindowsSurface = copie_surface(pWindowSurface);}
    	        }

    	    break;

			////////////////////////////
			// DEPLACEMENT - click up // 
			////////////////////////////
			case SDL_MOUSEBUTTONUP:

				if (event.button.button == SDL_BUTTON_LEFT)// si clique souris gauche
    	        {
					if(isLeftMouseButtonPressed==true){
					// re coloration de l'ecran de fond en noir
					SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 0, 0, 0));
					
					int xrel = 0;
					int yrel = 0;
					m_Env.moveEnvironnment(xrel,yrel);
					m_Env.postMoveEnv();
					SDL_FreeSurface(copyOfPWindowsSurface);
					if((SDL_SaveBMP(pWindowSurface, whereIPrintRsx.c_str())) != 0)
						exit(EXIT_FAILURE); 
					copyOfPWindowsSurface = copie_surface(pWindowSurface);

					SDL_Flip(pWindowSurface);
					}
					isLeftMouseButtonPressed = false;
					//isLeftMouseButtonMove = false; 
					//m_Env.postMoveEnv();
    	        }
			break;

			/////////////////////////////
			// DEPLACEMENT - Mouvement // 
			/////////////////////////////
			case SDL_MOUSEMOTION:
				if(isLeftMouseButtonPressed==true){
					//isLeftMouseButtonMove = true;

					// re coloration de l'ecran de fond en noir
					SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 0, 0, 0));
					
					int xrel = -(lastX-event.motion.x);
					int yrel = -(lastY-event.motion.y);
					m_Env.moveEnvironnment(xrel,yrel);
					lastX=event.motion.x;
					lastY=event.motion.y;

					SDL_FreeSurface(copyOfPWindowsSurface);
					if((SDL_SaveBMP(pWindowSurface, whereIPrintRsx.c_str())) != 0)
						exit(EXIT_FAILURE); 
					copyOfPWindowsSurface = copie_surface(pWindowSurface);
					   }
			break;/* fin SED_MouseMotion */


			case SDL_KEYDOWN:
				
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						mustContinue = 0;
						break;
						
						
					default: //prevent enumeration of wSwitch
						break;

				}// fin switch 2
				break; // fin case SDL_KeyDown
			
        }// fin switch 1

	//On incremente le compteur de frames
	frame++;

	//Si nous voulons reguler le frame rate
    if( cap == true )
    {
        //Tant que le timer fps n'est pas assez haut
        while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //On attend...
        }
    }// fin if

	}// fin While
}// fin Ctor
//-----------------------------------------------------------------------------------------------------------------------------------
InitialScreen::~InitialScreen(void)
{

}// fin Dtor
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::initMyScreen()
{// all function i don't wanna put in the CTor

	posOfCopy.x=0;
	posOfCopy.y=0;

	fprintf(stderr,"- System - Lancement de l'ecran principal \n");

	char init[] = "SDL_VIDEO_WINDOW_POS=800,100";

	putenv(init); //pour placer en x,y sur l'ecran

	pWindowSurface = NULL; // Ecran principal
	

	if ( SDL_Init(SDL_INIT_VIDEO) == -1 ) // initialisation de la video
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL\n");
		exit(EXIT_FAILURE);
    }// fin if

	//Une chaine de caracteres temporaire
    char caption[ 64 ];

    //On calcule le nombre de frames par seconde et on cree la chaine de caracteres
	sprintf( caption, "Frames Par Seconde: %i", FRAMES_PER_SECOND );

	// Titre de la fenetre
	SDL_WM_SetCaption(caption, NULL);


	/* Chargement de l'icône AVANT SDL_SetVideoMode */
    SDL_WM_SetIcon(SDL_LoadBMP("simIcon.bmp"), NULL);

	// Creer la fenetre
    pWindowSurface = SDL_SetVideoMode(1200,900,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
	if ( pWindowSurface == NULL )
	{
	    fprintf(stderr,"Erreur lors de l'ouverture de la fenetre\n");
	    SDL_Quit();
	}

	// Coloration en noir pour la surface de fond
	SDL_FillRect(pWindowSurface,NULL,SDL_MapRGB(pWindowSurface->format,0,0,0));

	// envoi de la surface de base a l'environnement.
	m_Env.setSurfaceFontScreen(pWindowSurface);

}// fin init my screen
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::askingUserForFile()
{
	// my actual test file : 
	// C:\DotSim\EveryFilesYouNeed.txt

	/* composition of a listFile 
	PARAMETERS the_parameters_file
	ROADMAP the_roadmap_file
	SOURCESPARAMETERS the_source_parameters_file
	TAGS the_tag_file
    */ 

	//fprintf(stderr,"- System - Please : enter the String of the absolut path file for your reference file list. \n");
	//cin >> fichierListFile;
	//cout << "- System - the Absolut path of your file is : " + fichierListFile + "\n";

	////////////
	// VIRGIN //
	////////////
	// fichierListFile = "../DotSimSampleFiles/ViginDotSim/EveryFilesYouNeed.txt";
	// fichierListFile = "../DotSimSampleFiles/TestDotSim/EveryFilesYouNeed.txt";
	// fichierListFile = "../DotSimSampleFiles/SingleRoad/EveryFilesYouNeed.txt";	
	// fichierListFile = "../DotSimSampleFiles/TwoRoads/EveryFilesYouNeed.txt";

	/////////////////////////////
	// Graphical features Test //
	/////////////////////////////
	// fichierListFile = "../DotSimSampleFiles/TestOnRoadInclinaison/EveryFilesYouNeed.txt";



	///////////////
	// Carrefour //
	///////////////
	// fichierListFile = "/home/julien/YATS/DotSimSampleFiles/ClassicalCarrefour/EveryFilesYouNeed.txt";
	// fichierListFile = "../DotSimSampleFiles/ClassicalCarrefourStrange/EveryFilesYouNeed.txt";
	// fichierListFile = "../DotSimSampleFiles/ClassicalCarrefourForOnlyOneDriver/EveryFilesYouNeed.txt";

	//////////
	// LOOP //
	//////////
	// fichierListFile = "../DotSimSampleFiles/HellLoop/EveryFilesYouNeed.txt";
	// fichierListFile = "../DotSimSampleFiles/WorkOnCornerTriangle60/EveryFilesYouNeed.txt";

	//////////
	// TURN //
	//////////
	// fichierListFile = "../DotSimSampleFiles/TwoTurnSingleRoad/EveryFilesYouNeed.txt";
	// fichierListFile = "../DotSimSampleFiles/WorkOnCorner/EveryFilesYouNeed.txt";
	// fichierListFile = "../DotSimSampleFiles/TestOnMyWayCircuit/EveryFilesYouNeed.txt";

	/////////////
	// COMPLEX //
	/////////////
	// fichierListFile = "../DotSimSampleFiles/FourWayRoundaboutSingleCentralRoad/EveryFilesYouNeed.txt";
	// fichierListFile = "../DotSimSampleFiles/OneDirverFourWayRoundaboutSingleCentralRoad/EveryFilesYouNeed.txt";

	////////////
	// SOURCE //
	////////////
	// fichierListFile = "../DotSimSampleFiles/TestOnSourceSimClass/EveryFilesYouNeed.txt";
	// fichierListFile = "../DotSimSampleFiles/HellSourceLoop/EveryFilesYouNeed.txt";
	
	/////////////
	// Big Map //
	/////////////
	 fichierListFile = "../DotSimSampleFiles/FirstBigMap/EveryFilesYouNeed.txt";

	// chargement de listFile
	loadListFile();    

}// fin asking User For File
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::loadListFile()
{
	ifstream fichier(fichierListFile.c_str());
 
	string quickStringManip = fichierListFile;
	bool finish = false;
	while(finish==false)
	{
		if(quickStringManip.at(quickStringManip.length()-1)=='/' || quickStringManip.at(quickStringManip.length()-1)=='\\')
		{
			finish=true;
		}else{
			quickStringManip.erase(quickStringManip.end()-1);
		}// fin else finish == true
	}// fin while finish == false
	//cout << quickStringManip << endl;
	localFileSystem = quickStringManip;
	parametersFile = quickStringManip;
	roadMapFile = quickStringManip;
	sourceParametersFile = quickStringManip;
	tagsFile= quickStringManip;

   if(fichier)
   {
      //L'ouverture s'est bien passée, on peut donc lire
	fprintf(stderr,"- System - Loading the list of file. \n");
      string ligne; //Une variable pour stocker les lignes lues
 
      while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
      {
		  if(ligne.compare(0,10,"PARAMETERS") == 0)
		  {
			  //cout << "enter PARAMETTERS" << endl ;
			  ligne.erase(0,11);
			  ligne.erase(ligne.end()-1);
			  parametersFile.append(ligne);
			  //cout << parametersFile << endl;
			  loadPARAMETERS();
 		  }// fin if PARAMETERS

		  if(ligne.compare(0,7,"ROADMAP") == 0)
		  {
			  //cout << "enter ROADMAP" << endl ;
			  ligne.erase(0,8);
			  ligne.erase(ligne.end()-1);
			  roadMapFile.append(ligne);
			  //cout << "roadmapfile- " << roadMapFile << endl;
			  loadROADMAP();
		  }// fin if roadmap

		  if(ligne.compare(0,17,"SOURCESPARAMETERS") == 0)
		  {
			  //cout << "enter SOURCESPARAMETERS" << endl ;
			  ligne.erase(0,18);
			  ligne.erase(ligne.end()-1);
			  sourceParametersFile.append(ligne);
			  //cout << sourceParametersFile << endl;
			  loadSOURCESPARAMETTERS();
		  }// fin if SOURCESPARAMETERS

		  if(ligne.compare(0,4,"TAGS") == 0)
		  {
			  //cout << "enter TAGS" << endl ;
			  ligne.erase(0,5);
			  ligne.erase(ligne.end()-1);
			  tagsFile.append(ligne);
			  //cout << tagsFile << endl;
			  loadTAGS();
		  }// fin if TAGS
         //cout << ligne << endl;
      }// fin while
   }// fin if 
   else
   {
      fprintf(stderr,"- ERROR - cannot open the file : listFile in read mode \n");
   }// fin else

}// fin Load file List
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::loadPARAMETERS()
{
	fprintf(stderr,"- System - Loading Parameters File. \n");
}// fin load 
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::loadROADMAP()
{
	ifstream fichierRoadmap(roadMapFile.c_str());

		
	if (!fichierRoadmap.is_open()){
		perror("error while opening file");
		cout << roadMapFile << endl;
	}
	
	
	
	string name;
	string type;
	string sx1,sx2,sy1,sy2;	

	string pointOfAnotherSegment1; 
	bool ifSeg1=false;
	string pointOfAnotherSegment2;
	bool ifSeg2=false;
	bool fromAnotherSegment=true;
	bool writeOrNot=false;

	string laRelou;
	
	if(fichierRoadmap)
   {
	  fprintf(stderr,"- System - Loading Road Map File \n");
      string ligne; //Une variable pour stocker les lignes lues
      while(getline(fichierRoadmap, ligne)) //Tant qu'on n'est pas à la fin, on lit
      {
		  int myNumberToClassMyInfo=0;
		  int mySecondFocus=0;
		  for(unsigned int i(0);i<ligne.length();i++)
		  {
			  // 32 = space
			  // 40 = (
			  // 41 = )
			  // 59 = ;
			  if(ligne.at(i) == 40 )
			  {
				  for(unsigned int j(i+1);j<ligne.length();j++)
				  {
					  if(ligne.at(j) == 41 )
					  {
						  writeOrNot=true;
					  }

					  if(writeOrNot == false )
					  {
						  laRelou+=ligne.at(j);
					  }

				  }// fin for j

				  //cout << laRelou << endl;

				for(unsigned int k(0);k<laRelou.length();k++)
					  {
						  if(laRelou.at(k)==59)
						  {
							  fromAnotherSegment=false;
							  //cout<<"enter another segm == false "<<endl;
						  }// fin if ;
						  else
						  {
							  //cout<<"enter another segm == true "<<endl;

						  }//fin else
					  }// fin for k
					  
				if(fromAnotherSegment==true)
				{
					mySecondFocus++;
					//cout<<mySecondFocus<<endl;
				
				//cout << mySecondFocus << endl;

				switch(mySecondFocus)
				{
					case 1 :
						if(ifSeg1==false)
						{
						pointOfAnotherSegment1 = laRelou;
						//cout << pointOfAnotherSegment1 << endl;
						ifSeg1=true;
						}
					break;

					case 2 : 
						pointOfAnotherSegment2 = laRelou;
						//cout << pointOfAnotherSegment2 << endl;
						ifSeg2=true;
					break;
				}
				}// fin if seg == true
				if(fromAnotherSegment==false)
				{
					mySecondFocus++;
				}

			  }// fin if ( & )

			  //cout << laRelou << endl;

			  

			  if(ligne.at(i) == 32 || ligne.at(i) == 40 || ligne.at(i) == 41 || ligne.at(i) == 59)
			  {
				  //fprintf(stderr,"- test - here we have a space \n");
				  if(ifSeg1==true && myNumberToClassMyInfo==3)
				  {
				  myNumberToClassMyInfo++;
				  }
				  myNumberToClassMyInfo++;
			  }// fin if space
			  else
			  {
				  switch(myNumberToClassMyInfo)
				  {
						case 0 : 
							name+=ligne.at(i);
						break;

						case 1 : 
							type+=ligne.at(i);
						break;

						case 3 : 
							sx1+=ligne.at(i);
						break;

						case 4 : 
							sy1+=ligne.at(i);
						break;

						case 7 : 
							sx2+=ligne.at(i);
						break;

						case 8 : 
							sy2+=ligne.at(i);
						break;
				  }
			  }// fin else space

			  writeOrNot=false;
			  laRelou="";
			  fromAnotherSegment=true;

			//////////////
		  }// fin for i
			//////////////

		  if(ifSeg1==true)
		  {
			  for( int l(0);l<m_Env.getListOfRoadSize();l++)
			  {
				  if(m_Env.getRoadAt(l)->getName().compare(pointOfAnotherSegment1)==0)
				  {
					  //cout << "enter if seg1 " << endl;

					  sx1=convertFLtoSTR( m_Env.getRoadAt(l)->getPSortie().getX() );
					  sy1=convertFLtoSTR( m_Env.getRoadAt(l)->getPSortie().getY() );
				  }// fin if same name Road
			  }// fin forl 
			  // fin if seg1==true
		  }

		  if(ifSeg2==true)
		  {
			for(int l(0);l<m_Env.getListOfRoadSize();l++)
			  {
				  if(m_Env.getRoadAt(l)->getName().compare(pointOfAnotherSegment2)==0)
				  {
					  //cout << "enter if seg2 " << endl;

					  sx2=convertFLtoSTR( m_Env.getRoadAt(l)->getPEntre().getX() );
					  sy2=convertFLtoSTR( m_Env.getRoadAt(l)->getPEntre().getY() );
				  }// fin if same nam 
			  }// fin forl 
			  // fin if seg1==true
		  }

		  // true true
		  if(ifSeg1==true && ifSeg2==true)
		  {
			  if(type.compare(0,6,"ROAD") == 0)
			  {
				Road * sim = new Road(pWindowSurface, name, 
					convertSTRtoFL(sx1), 
					convertSTRtoFL(sy1), 
					convertSTRtoFL(sx2), 
					convertSTRtoFL(sy2));
				m_Env.addRoadToTheList(sim);
				//listOfRoad.push_back(sim);
				//sim->printMe();
			  }// fin if type = source
		  }// fin if(ifSeg1==true && ifSeg2==true)

		  // true False
		  if(ifSeg1==true && ifSeg2==false)
		  {
			  if(type.compare(0,6,"ROAD") == 0)
			  {
				Road * sim = new Road(pWindowSurface, name, 
					convertSTRtoFL(sx1), 
					convertSTRtoFL(sy1), 
					convertINTMetersToIntPIX(convertSTRtoFL(sx2)), 
					convertINTMetersToIntPIX(convertSTRtoFL(sy2)));
				m_Env.addRoadToTheList(sim);
				//listOfRoad.push_back(sim);
				//sim->printMe();
			  }// fin if type = source
		  }// fin if(ifSeg1==true && ifSeg2==true
		  
		  // false true
		  if(ifSeg1==false && ifSeg2==true)
		  {
			  if(type.compare(0,6,"ROAD") == 0)
			  {
				Road * sim = new Road(pWindowSurface, name, 
					convertINTMetersToIntPIX(convertSTRtoFL(sx1)), 
					convertINTMetersToIntPIX(convertSTRtoFL(sy1)), 
					convertSTRtoFL(sx2), 
					convertSTRtoFL(sy2));
				m_Env.addRoadToTheList(sim);
				//listOfRoad.push_back(sim);
				//sim->printMe();
			  }// fin if type = source
		  }// fin if(ifSeg1==true && ifSeg2==true))

		  // false false
		  if(ifSeg1==false && ifSeg2==false)
		  {
			  if(type.compare(0,6,"ROAD") == 0)
			  {
				Road * sim = new Road(pWindowSurface, name, 
					convertINTMetersToIntPIX(convertSTRtoFL(sx1)), 
					convertINTMetersToIntPIX(convertSTRtoFL(sy1)), 
					convertINTMetersToIntPIX(convertSTRtoFL(sx2)), 
					convertINTMetersToIntPIX(convertSTRtoFL(sy2)));
				m_Env.addRoadToTheList(sim);
				//listOfRoad.push_back(sim);
				//sim->printMe();
			  }// fin if type = source
		  }// fin if(ifSeg1==false && ifSeg2==false)
		  

		 
		pointOfAnotherSegment1=""; 
		ifSeg1=false;
		string pointOfAnotherSegment2=""; 
		ifSeg2=false;
		fromAnotherSegment=true;
		writeOrNot=false;
		mySecondFocus=0;

		name="";
		type="";
		sx1="";sy1="";
		sx2="";sy2="";

      }// fin while
   }// fin if 
   else
   {
      fprintf(stderr,"- ERROR - cannot open the file : ROADMAP in read mode \n");
   }// fin else

   //m_Env.printRoadList(); /*vérifié*/

}// fin load ROADMAP
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::loadSOURCESPARAMETTERS()
{
	fprintf(stderr,"- System - Loading Sources Parameters File \n");
}// fin load SOURCESPARAMETERS
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::loadTAGS()
{
	fprintf(stderr,"- System - Loading Tags File \n");
}// fin load TAGS
//----------------------------------------------------------------------------------------------------------------------------------
string InitialScreen::convertFLtoSTR(float myStringToConvert)
{
	 // créer un flux de sortie
    std::ostringstream oss;
    // écrire un nombre dans le flux
    oss << myStringToConvert;
    // récupérer une chaîne de caractères
    std::string result = oss.str();

	return result;
}// fin convert fl to str
//----------------------------------------------------------------------------------------------------------------------------------
float InitialScreen::convertSTRtoFL(string myStringToConvert)
{
	float nombre(0);

	// créer un flux à partir de la chaîne à convertir
    std::istringstream iss( myStringToConvert );
    // convertir en un int
    
    iss >> nombre; // nombre vaut 10

	return nombre;
}// fin convert str to int
//-----------------------------------------------------------------------------------------------------------------------------------
float InitialScreen::convertINTMetersToIntPIX(float n)
{
	float result(0);
	result = (n*100) / 14;
	return result;
}// fin convert int metters to int Pix
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::screenRoutine()
{
	m_Env.myRoutine();
}// fin screenRoutine
//-----------------------------------------------------------------------------------------------------------------------------------
SDL_Surface* InitialScreen::copie_surface(SDL_Surface *surface_a_copier)
{
    SDL_Surface *surface_copiee = NULL;
    surface_copiee = SDL_CreateRGBSurface(SDL_HWSURFACE, surface_a_copier->w, surface_a_copier->h, surface_a_copier->format->BitsPerPixel, surface_a_copier->format->Rmask, surface_a_copier->format->Gmask, surface_a_copier->format->Bmask, surface_a_copier->format->Amask);
 
    if(surface_copiee == NULL || surface_a_copier == NULL)
        return NULL;
 
    SDL_FreeSurface(surface_copiee);   // pour libérer la surface
    surface_copiee = NULL;
 
    return SDL_DisplayFormatAlpha(surface_a_copier);
}// fin copie surface
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::applyFontScreen()
{//copyOfPWindowsSurface = SDL_LoadBMP ("../DotSimSampleFiles/VirginDotSim/testFile.bmp");

	// affichage des road sur la map.
	for(int w(0);w<m_Env.getListOfRoadSize();w++)
		{
			m_Env.getRoadAt(w)->myRoutine();
		}

	//////////////////////
	// Building NodeSim //
	//////////////////////

	for(int i(0);i<m_Env.getListOfRoadSize();i++)
	{ 
		/////////////////
		// GET P ENTRE //
		/////////////////
		float x = m_Env.getRoadAt(i)->getPEntre().getX();
		float y = m_Env.getRoadAt(i)->getPEntre().getY();
		bool isItHere = false;

		for(int j(0);j<m_Env.getListOfNodeSize();j++)
		{
			if(isEqual(m_Env.getNodeAt(j)->getNodePoint().getX(), x) == true && isEqual(m_Env.getNodeAt(j)->getNodePoint().getY(),y) == true)
				{
					isItHere = true;
					if(m_Env.getNodeAt(j)->existInExitList(m_Env.getRoadAt(i)->getName())==false)
					{
						m_Env.getNodeAt(j)->addExitPoint(m_Env.getRoadAt(i));
					}
				}
		}// fin for j
		
		if(isItHere==false)
		{
			NodeSim* s = new NodeSim(x,y);
			s->addExitPoint(m_Env.getRoadAt(i));
			m_Env.addNodeToTheList(s);//listOfNode.push_back(s);
			s->circle(x,y,12.5,pWindowSurface,156,156,156);
		}// fin isItHere = false

		//////////////////
		// GET P SORTIE //
		//////////////////
		 x = m_Env.getRoadAt(i)->getPSortie().getX();
		 y = m_Env.getRoadAt(i)->getPSortie().getY();
		 isItHere = false;

		for(int j(0);j<m_Env.getListOfNodeSize();j++)
		{
				if(isEqual(m_Env.getNodeAt(j)->getNodePoint().getX(), x) == true && isEqual(m_Env.getNodeAt(j)->getNodePoint().getY(),y) == true)
				{
					isItHere = true;
					if(m_Env.getNodeAt(j)->existInEntryList(m_Env.getRoadAt(i)->getName())==false)
					{
						m_Env.getNodeAt(j)->addEntryPoint(m_Env.getRoadAt(i));
					}
				}
		}// fin for j
		
		if(isItHere==false)
		{
			NodeSim* s = new NodeSim(x,y);
			s->addEntryPoint(m_Env.getRoadAt(i));
			m_Env.addNodeToTheList(s);//listOfNode.push_back(s);
			s->circle(x,y,12.5,pWindowSurface,156,156,156);
		}// fin isItHere = false

		isItHere=false;
		
	}// fin for i 

	for(int w(0);w<m_Env.getListOfNodeSize();w++)
	{
		m_Env.getNodeAt(w)->setName("Node" + convertINTtoSTR(w) );
	}// fin for w

	m_Env.printNodeList();

	////////////////////////
	// Building SourceSim //
	////////////////////////
	for(int w(0);w<m_Env.getListOfNodeSize();w++)
	{
		if(m_Env.getNodeAt(w)->getListEntryPointSize() == 0)
		{	
			for(int z(0); z < m_Env.getNodeAt(w)->getListExitPointSize() ; z++)
			{
				/* 1 ) creation des sources */
				std::string newSourceName;
				newSourceName = "generiqueSource FOR ";
				newSourceName += m_Env.getNodeAt(w)->getTheRoadExitAt(z)->getName();
				SourceSim * newSourceSim = new SourceSim(pWindowSurface,newSourceName, 
													m_Env.getNodeAt(w)->getNodePoint().getX(),
													m_Env.getNodeAt(w)->getNodePoint().getY(),
													m_Env.getNodeAt(w)->getTheRoadExitAt(z)->getAngle());
				/* 2 ) ajout de la route a la sources */
				newSourceSim->setRoad(m_Env.getNodeAt(w)->getTheRoadExitAt(z));
				/* 3) ajout de la source dans l'environnement */
				m_Env.addSourceToTheList(newSourceSim);//listOfSource.push_back(newSourceSim);
			}/// fin for z
		}// fin if ( listOfNode.at(w)->getListEntryPointSize() == 0)
	}// fin for all Node

	m_Env.printSourceList();

	 m_Env.linkingRoadToNode();

	 m_Env.printRoadList(); /*vérifié*/

	 cout << "- Display - Creating RoadLink Begin" << endl;
	 m_Env.createAllRoadLink(); /* creation de la liste des RoadLink de chaque Node */
	 cout << "- Display - Creating RoadLink End" << endl;
	//////////////////////
	// Building WellSim //
	////////////////////// not yet ...

	// applying trics to incrise the frame rate
	whereIPrintRsx = localFileSystem + "testFile.bmp";
	cout << "- System - Saving the RoadMap picture in : " << endl << "            " << whereIPrintRsx << endl;
	//  const char *file
	if((SDL_SaveBMP(pWindowSurface, whereIPrintRsx.c_str())) != 0)
		exit(EXIT_FAILURE); 
	copyOfPWindowsSurface = copie_surface(pWindowSurface);

	// TEST !!  lancement de vehicle sur les sources
	for(int i(0); i< m_Env.getListOfSourceSize() ; i++ ) 
	{
		m_Env.addVehicleToTheList(m_Env.getSourceAt(i)->popVehicle());
	}// fin for i 

}// fin appl font screen
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::logIt()
{
	// creation du dossier et initialisation des variables 
	buildLogFolder();
	// creation des fichiers logs correspondant a leur items
	buildRoadLogFile();
	buildNodeLogFile();

}// fin logIt()
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::buildLogFolder()
{
	yearMonthDayHourMinSec =  currentDateTime();
	logFolder = localFileSystem + "log_" + yearMonthDayHourMinSec;
	//if( _mkdir( logFolder.c_str() ) == 0 )// si le repertoire n'existe pas il est creer 
   if (boost::filesystem::create_directory( logFolder.c_str() ) == 0 ){ // os neutre
      //printf( "Directory '\\testtmp' was successfully created\n" )
	   cout << "- System - Creation of the log folder " << endl;
   }
   else // sinon rien il existe deja 
      //printf( "Problem creating directory '\\testtmp'\n" ); 
	  cout << "- System - Log folder already exist " << endl;
}// fin buildLogFolder
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::buildRoadLogFile()
{
	string const nomFichier(logFolder + "/logROAD.txt");
    ofstream monFlux(nomFichier.c_str());
 
    if(monFlux)   
    {
		cout << "- Display - Writting of : " << nomFichier << endl;
		for(int i(0); i < m_Env.getListOfRoadSize() ; i++){
			monFlux << "- ROAD : " << m_Env.getRoadAt(i)->getName() << endl;
			monFlux << "            COORD (" << m_Env.getRoadAt(i)->getCoordPE().getX() <<  ";" << m_Env.getRoadAt(i)->getCoordPE().getY() << 
				") // (" << m_Env.getRoadAt(i)->getCoordPS().getX() << ";" << m_Env.getRoadAt(i)->getCoordPS().getY() << ")" << endl; 
			monFlux << "            ANGLE : "<< m_Env.getRoadAt(i)->getAngle() << endl;
			monFlux << "            LONGUEUR : "<< m_Env.getRoadAt(i)->getLongueur() << " ( pix )"  << endl;
			//monFlux << "            LONGUEUR : "<< Road::convertMetterToPIX(m_Env.getRoadAt(i)->getLongueur()) << " ( Metters )"  << endl;
			if(m_Env.getRoadAt(i)->isEntryNodeSet()==true)
			{monFlux << "            ENTRY NODE : "<< m_Env.getRoadAt(i)->getEntryNode()->getName() << endl;}
			if(m_Env.getRoadAt(i)->isExitNodeSet()==true)
			{monFlux << "            EXIT NODE : "<< m_Env.getRoadAt(i)->getExitNode()->getName() << endl;}}// fin for i 
	}
    else
    {
        cout << "- ERROR - cannot open the file : " << nomFichier << endl;
    }
}// fin build road log file
//-----------------------------------------------------------------------------------------------------------------------------------
void InitialScreen::buildNodeLogFile()
{

	string const nomFichier(logFolder + "/logNODE.txt");
    ofstream monFlux(nomFichier.c_str());
 
    if(monFlux)   
    {
		for(int i(0); i < m_Env.getListOfNodeSize() ; i++){
			monFlux << "Node : " << m_Env.getNodeAt(i)->getName() << "( " << m_Env.getNodeAt(i)->getNodePoint().getX() << " ; " << m_Env.getNodeAt(i)->getNodePoint().getY() << " ) " << endl;
				
				monFlux << "     Entry : ";
				for(int j(0); j < m_Env.getNodeAt(i)->getListEntryPointSize() ; j++ ) 
				{
					monFlux << m_Env.getNodeAt(i)->getTheRoadEntryAt(j)->getName() << ", ";
				}
				monFlux << endl;

				monFlux << "     Exit : ";
				for(int k(0); k < m_Env.getNodeAt(i)->getListExitPointSize() ; k++ ) 
				{
					monFlux << m_Env.getNodeAt(i)->getTheRoadExitAt(k)->getName() << ", ";
				}
				monFlux << endl;

			for(int l(0);l<m_Env.getNodeAt(i)->getListRoadLinkSize() ; l++){
			monFlux << "          LinkRoad : " << m_Env.getNodeAt(i)->getRoadLinkAt(l)->getIDRoadLink() << endl;
			monFlux << "               entry : " << m_Env.getNodeAt(i)->getRoadLinkAt(l)->getEntryRoad()->getName() << endl;
			monFlux << "               exit  : " << m_Env.getNodeAt(i)->getRoadLinkAt(l)->getExitRoad()->getName() << endl;
			monFlux << "               Angle : " << m_Env.getNodeAt(i)->getRoadLinkAt(l)->getAngle() << endl;
			monFlux << "               gap : " << m_Env.getNodeAt(i)->getRoadLinkAt(l)->getGap() << endl;
			monFlux << "               max speed : " << m_Env.getNodeAt(i)->getRoadLinkAt(l)->getDesiredSpeed() << endl;
			monFlux << endl;}// fin for l

		}// fin for i
	}
    else
    {
        cout << "- ERROR - cannot open the file : " << nomFichier << endl;
    }
}// fin buildNodeLogFile()
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------
