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

#ifndef ROAD_H
#define ROAD_H

#include "NodeSim.h"

using namespace std;
class NodeSim;
class Road
{
public:

	// DTor & CTor
	Road(SDL_Surface * iWillBeOn, string n, float x1, float y1, float x2, float y2);
	~Road(void);

	// Display
	void printMe();

	// Get & Set
	string getName();
	PointSim getPEntre();
	PointSim getPSortie();
	float getAngle();
	bool isEntryNodeSet();
	bool isExitNodeSet();
	void setEntryNode(NodeSim * n);
	void setExitNode(NodeSim * n);
	NodeSim * getExitNode();
	NodeSim * getEntryNode();
	float getDistance(PointSim a, PointSim b);
	float getLongueur();
	float convertMetterToPIX(float f);
	void setZoomLVL(float zoom);
	float getZoomLVL();

	// test 
	PointSim getCoordPE();
	void setCoordPE(float abs, float ord);
	PointSim getCoordPS();
	void setCoordPS(float abs, float ord);

	// processing
	void myRoutine();
	void majPtEntre();
	void majPtSortie();
	void majSurfaceRoute();

private:

	string name;
	float longueur;
	float zoomLVL;

	float aD1;
	float bD1;

	float angle;
	PointSim inTheMiddle;

	NodeSim * entryNode;
	bool m_isEntryNodeSet;
	NodeSim * exitNode;
	bool m_isExitNodeSet;

	// apparament inutile ^^
	//float pente;
	//float angleInclinaison;

	SDL_Surface *whereIAmBlit;
	SDL_Surface *myVisualSurface;
	SDL_Surface *rotation;
	SDL_Rect myVisualPosition;

	PointSim pointEntre;
	SDL_Rect pointEntreMyVisualPosition;
	SDL_Surface *pointEntreMyVisualSurface;

	PointSim pointSortie;
	SDL_Rect pointSortieMyVisualPosition;
	SDL_Surface *pointSortieMyVisualSurface;

};

#endif
