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

#include "Road.h"
using namespace std;

class SourceSim
{
public:
	SourceSim(SDL_Surface * iWillBeOn, string n, float x1, float y1, float angleInclinaison);
	~SourceSim(void);

	// display
	void printMe();

	// get & set
	string getName();
	PointSim getCoordonnee();
	void setRoad(Road * r);

	// processing 
	void myRoutine();
	Vehicle* popVehicle();

	// inline processing
	inline string convertINTtoSTR(int n)
	{	std::ostringstream oss;
		oss << n;
		std::string result = oss.str();
		return result;}

private:
	int countVehicleLaunch;

	Road * whereILaunchCar;

	string name;

	float aD1;
	float bD1;

	float angle;

	SDL_Surface *whereIAmBlit;

	PointSim coordonne;
	SDL_Rect coordonneMyVisualPosition;
	SDL_Surface *coordonneMyVisualSurface;


};

