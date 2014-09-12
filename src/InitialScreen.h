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
   
   
#pragma once

using std::string;
using namespace std;

class InitialScreen
{
public:
	InitialScreen(void);
	~InitialScreen(void);
	// all function i don't wanna put in the CTor
	void initMyScreen();
	void screenRoutine();
	void applyFontScreen();

	// fonction utiliser pour le chargement de fichier source de la simulation
	void askingUserForFile();
	void loadListFile();
	void loadPARAMETERS();
	void loadROADMAP();
	void loadSOURCESPARAMETTERS();
	void loadTAGS();

	//fonction d'usage
	float convertSTRtoFL(string myStringToConvert);
	string convertFLtoSTR(float myStringToConvert);
	float convertINTMetersToIntPIX(float n);
	SDL_Surface* copie_surface(SDL_Surface *surface_a_copier);

	// only one Public attribut of program ! please, do not launch any rock in my face.
	SDL_Surface* pWindowSurface;
	SDL_Surface* copyOfPWindowsSurface;
	SDL_Rect posOfCopy;

	inline bool isEqual(float x, float y){
	  const double epsilon = 0.00001/* some small number such as 1e-5 */;
	  return std::abs(x - y) <= epsilon * std::abs(x);}

	inline bool isEqualLigth(float x, float y){
	  const double epsilon = 0.01/* some small number such as 1e-5 */;
	  return std::abs(x - y) <= epsilon * std::abs(x);}

	inline string convertINTtoSTR(int n){
		 // créer un flux de sortie
		std::ostringstream oss;
		// écrire un nombre dans le flux
		oss << n;
		// récupérer une chaîne de caractères
		std::string result = oss.str();
	return result;
	}

	inline const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://www.cplusplus.com/reference/clibrary/ctime/strftime/
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &tstruct);
	for(unsigned int i = 0;i<sizeof(buf);i++){if(buf[i]==':'){buf[i]='-';}}
    return buf;}

	// test For .log
	void logIt(); /* main of log */
	void buildLogFolder(); 
	void buildRoadLogFile();
	void buildNodeLogFile();


private:
	EnvironmentSim m_Env;

	// variable necessais a la construction de la simulation et au chargement de fichiers source.
	string localFileSystem;
	string fichierListFile;
	string parametersFile;
	string roadMapFile;
	string sourceParametersFile;
	string tagsFile;

	// where is the bmp file 
	string whereIPrintRsx;

	// log folder section
	string logFolder;
	string yearMonthDayHourMinSec;


};

