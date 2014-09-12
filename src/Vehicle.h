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

#include <algorithm> 
#include "VueEnvSim.h"

class Vehicle
{

public:
	// Ctor & DTor
	Vehicle(int a, int b, SDL_Surface * iWillBeOn);
	Vehicle(float a, float b, SDL_Surface * iWillBeOn, float angleInitial,std::string n);
	~Vehicle(void);

	// get & set
	void setMyVue(VueEnvSim * v);
	bool getIfIWannaBeDelete();
	void setName(std::string n);
	std::string getName();
	float getDistance(PointSim a, PointSim b);
	PointSim getPointForState(int actionForState);
	float getDistanceToStop();
	void setCoord(float abs, float ord);
	PointSim getCoord();
	void setZoomLVL(float r);

	// Display
	void printMe();
	void displaySpec();

	// processing
	void moveFoward();
	void stopSmooth();
	void turnLeft();
	void turnRigth();
	void nextPosition();
	void printMyLinearEquation();
	void myRoutine();
	void decide();
	void setPointFocal(int x , int y);
	void setObjectifToFalse();
	void putMyControlPoint();
	void putMyFocalPoint();
	void afterLaunch();
	
	/// inline processing
	inline bool isEqual(float x, float y)
	{
	  const double epsilon = 0.000001/* some small number such as 1e-5 */;
	  return std::abs(x - y) <= epsilon * std::abs(x);
	}

	inline bool isEqualLigth(float x, float y)
	{
	  const double epsilon = 0.01/* some small number such as 1e-5 */;
	  return std::abs(x - y) <= epsilon * std::abs(x);
	}

	// test 
	void setAutomaticalSpeed();

private:
	// referencement
	std::string name;

	// attribut pour le deplacement du vehicule
	float accel;
	float deltaT;
	float aD1;
	float aD2;
	float bD1;
	float bD2;
	float vitesseMAX;
	float vitesseVehicle;
	float vitessePrecedente;
	float targetSpeed;

	float angleBraquage;
	float angleBraquageMax;
	float angle;

	float zoomLVL;

	// brain privilege 
	VueEnvSim * m_Vue;

	// attributs permettans de visualiser le vehicule
	SDL_Surface *whereIAmBlit;
	SDL_Surface *myVisualSurface;
	SDL_Surface *rotation;
	SDL_Rect myVisualPosition;

	// attribut pour l'ia du vehicule
	PointSim pointA; /* Coord du vehicule TODO renomer */
	PointSim pointFocal;
	bool haveObjectif;

	// attribut pour le placement d'un point de centre de vehicule
	SDL_Surface *myPointVisualSurface;
	SDL_Rect myPointVisualPosition;

	// attribut pour le placement d'un point de focalisation
	SDL_Surface *myPointFocalVisualSurface;
	SDL_Rect myPointFocalVisualPosition;

	// test
	//int lastbraquage;
	int alignCount;

	bool deleteMe;
};

