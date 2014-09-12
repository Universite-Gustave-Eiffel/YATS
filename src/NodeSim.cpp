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
#include "NodeSim.h"


#define PI 3.14159265
#define DEG2RAD (PI/180)

NodeSim::NodeSim(float a, float b)
{
	nodePoint.setX((float)a);
	nodePoint.setY((float)b);

	srand((unsigned)(time(0))); /* use to init the futur randomizator of exit road*/
}// frin CTor
//-----------------------------------------------------------------------------------------------------------------------------------
NodeSim::~NodeSim(void)
{
}// fin Dtor
//-----------------------------------------------------------------------------------------------------------------------------------
PointSim NodeSim::getNodePoint()
{
	return nodePoint;
}// fin GetNodPoint
//-----------------------------------------------------------------------------------------------------------------------------------
void NodeSim::addEntryPoint(Road * nameEntry)
{
	listEntryPoint.push_back(nameEntry);
}// fin add entry point
//-----------------------------------------------------------------------------------------------------------------------------------
void NodeSim::addExitPoint(Road * nameExit)
{	
	listExitPoint.push_back(nameExit);
}// fin addExitPoint
//-----------------------------------------------------------------------------------------------------------------------------------
bool NodeSim::existInEntryList(string candidateEntryList)
{
	bool existInList = false;
	for(unsigned int i(0);i<listEntryPoint.size();i++)
	{
		if(existInList==false)
		{
			if(listEntryPoint.at(i)->getName().compare(candidateEntryList)==0)
			{
				existInList =true;
			}// fin if compare
		}// fin if exist in list == false
	}// fin for i
	return existInList;
}// fin existInEntryList(string candidateEntryList)
//-----------------------------------------------------------------------------------------------------------------------------------
bool NodeSim::existInExitList(string candidateEntryList)
{
	bool existInList = false;
	for(unsigned int i(0);i<listExitPoint.size();i++)
	{
		if(existInList==false)
		{
			if(listExitPoint.at(i)->getName().compare(candidateEntryList)==0)
			{
				existInList=true;
			}// fin if compare
		}// fin if exist in list == false
	}// fin for i
	return existInList;
}// fin existInExitList
//-----------------------------------------------------------------------------------------------------------------------------------
void NodeSim::circle(int x, int y, int radius, SDL_Surface *thescreen, int r, int g, int b)
{
    float floatx, floaty, floatradius;
    SDL_Rect trect;

    trect.w = 1;
    trect.h = 1;

    floatx = static_cast <float> (x);
    floaty = static_cast <float> (y);
    floatradius = static_cast <float> (radius);

    float i;
	float j;

	for (j=0; j < radius; j+=(float)1)
    {
		floatradius=j;
		for (i=0; i < 360; i+= (float)1)
		{
			float degInRad =  i* (float)DEG2RAD;

			trect.x = static_cast <int> (floatx + cos(degInRad) * floatradius);
			trect.y = static_cast <int> (floaty + sin(degInRad)* floatradius);

			if(trect.x >= thescreen->clip_rect.x)
				if(trect.y >= thescreen->clip_rect.y)
					if((trect.x + trect.w) <= thescreen->clip_rect.w)
						if((trect.y + trect.h) <= thescreen->clip_rect.h)
							SDL_FillRect(thescreen, &trect, SDL_MapRGB( thescreen->format,r,g,b));
		}// fin for i 
	}// fin for j

}// fin the circle
//-----------------------------------------------------------------------------------------------------------------------------------
void NodeSim::displayMe()
{
	cout << "- DISPLAY - " << name << "( " << nodePoint.getX() << " ; " << nodePoint.getY() << " ) " << endl;
	for(unsigned int i(0); i < listEntryPoint.size() ; i++ ) 
	{
		cout << "     Entry : " << listEntryPoint.at(i)->getName() << endl;
	}
	for(unsigned int i(0); i < listExitPoint.size() ; i++ ) 
	{
		cout << "     Exit : " << listExitPoint.at(i)->getName() << endl;
	}
}// fin display me
//-----------------------------------------------------------------------------------------------------------------------------------
int NodeSim::getListEntryPointSize()
{
	return listEntryPoint.size();
}// fin get Entry Point size
//-----------------------------------------------------------------------------------------------------------------------------------
int NodeSim::getListExitPointSize()
{
	return listExitPoint.size() ;
}// fin get Entry Point size
//-----------------------------------------------------------------------------------------------------------------------------------
Road* NodeSim::getTheRoadExitAt(int i)
{
	return listExitPoint.at(i);
}// fin get The road exit at i
//-----------------------------------------------------------------------------------------------------------------------------------
Road* NodeSim::getTheRoadEntryAt(int i)
{
	return listEntryPoint.at(i);
}// fin get The road entry at i
//-----------------------------------------------------------------------------------------------------------------------------------
std::string NodeSim::getName()
{
	return name;
}
//-----------------------------------------------------------------------------------------------------------------------------------
void NodeSim::setName(std::string n)
{
	name = n;
}// fin set name
//-----------------------------------------------------------------------------------------------------------------------------------
RoadLink * NodeSim::getRandomRoadLink(std::string s)
{
	int randNumb = 0;

	vector<RoadLink *> cadidateRoadLink;
	for(unsigned int i(0);i<listOfRoadLink.size();i++)
	{
		if(s.compare(listOfRoadLink.at(i)->getEntryRoad()->getName())==0)
		{
			cadidateRoadLink.push_back(	listOfRoadLink.at(i) ) ;
		}// fin if
	}// fin for i

	if(cadidateRoadLink.size()>0)
	{randNumb = std::rand() % cadidateRoadLink.size();
	return cadidateRoadLink.at(randNumb);}
	else
	{ return NULL;}
}// fin get Random Road
//-----------------------------------------------------------------------------------------------------------------------------------
void NodeSim::createAllRoadLink()
{
	int k = 0;
	for(unsigned int i(0); i < listEntryPoint.size(); i++)
	{	for(unsigned int j (0); j< listExitPoint.size(); j++)
		{
			// TODO : pour chaque binome creaer un linkrpoad
			RoadLink * r = new RoadLink(listEntryPoint.at(i),listExitPoint.at(j));
			r->setIDRoadLink(k);
			k+=1;
			listOfRoadLink.push_back(r);
			//r->DisplyMe();
		}// fin for j 
	}// fin for i 

	for(unsigned int i(0); i<listOfRoadLink.size();i++)
	{
		listOfRoadLink.at(i)->DisplyMe();
	}// fin display roadLink.
}// fin create all roadLink
//-----------------------------------------------------------------------------------------------------------------------------------
void NodeSim::setCoord(float abs, float ord)
{
	nodePoint.setX(abs);
	nodePoint.setY(ord);
}// fin set coord
//-----------------------------------------------------------------------------------------------------------------------------------
void NodeSim::setTheCorrectRoadLinkZoomLvl(float r)
{
	for(unsigned int i(0);i<listOfRoadLink.size();i++)
	{
		//int g = listOfRoadLink.at(i)->getGap()*r;
		//cout<<g<<endl;
		listOfRoadLink.at(i)->setGap(listOfRoadLink.at(i)->getGap()*r);

		//float d = listOfRoadLink.at(i)->getDesiredSpeed();
		//cout<<d<<endl;
		listOfRoadLink.at(i)->setDesiredSpeed(listOfRoadLink.at(i)->getDesiredSpeed()*r);
	}//fin for i
}// fin setTheCorrectZoomLvl
//-----------------------------------------------------------------------------------------------------------------------------------
RoadLink * NodeSim::getRoadLinkAt(int i)
{
	return listOfRoadLink.at(i);
}// fin get road link at 
//-----------------------------------------------------------------------------------------------------------------------------------
int NodeSim::getListRoadLinkSize()
{
	return listOfRoadLink.size();
}// get list road link size 
//-----------------------------------------------------------------------------------------------------------------------------------
