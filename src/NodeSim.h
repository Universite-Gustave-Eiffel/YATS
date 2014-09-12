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

#ifndef NODE_SIM_H
#define NODE_SIM_H


#include "Road.h"
#include "RoadLink.h"

class Road;
class RoadLink;

class NodeSim
{
public:

	// CTor & DTor
	NodeSim(float a,float b);
	~NodeSim(void);

	// Display
	void displayMe();

	// Get & Set
	void addEntryPoint(Road * nameEntry);
	bool existInEntryList(std::string candidateEntryList);
	void addExitPoint(Road * nameexit);
	bool existInExitList(std::string candidateEntryList);
	PointSim getNodePoint();
	int getListEntryPointSize();
	int getListExitPointSize();
	int getListRoadLinkSize();
	Road* getTheRoadExitAt(int i);
	Road* getTheRoadEntryAt(int i);
	std::string getName();
	void setName(std::string n);
	RoadLink * getRandomRoadLink(std::string s);
	void setCoord(float abs, float ord);
	void setTheCorrectRoadLinkZoomLvl(float r);
	RoadLink * getRoadLinkAt(int i);

	// Processing
	void circle(int x, int y, int radius, SDL_Surface *thescreen, int r, int g, int b); /* building a circle to complet the empy space in every road node */ 
	void createAllRoadLink();


private : 

	std::string name;

	std::vector<Road *> listEntryPoint;
	std::vector<Road *> listExitPoint;
	std::vector<RoadLink *> listOfRoadLink;

	PointSim nodePoint;
	SDL_Rect nodeVisualPosition;
	SDL_Surface *nodeVisualSurface;
	
};

#endif

