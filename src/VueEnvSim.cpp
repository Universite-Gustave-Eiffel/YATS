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

VueEnvSim::VueEnvSim(/*int n*/)
{
	//b=n;
}// fin Ctor
//-----------------------------------------------------------------------------------------------------------------------------------
VueEnvSim::~VueEnvSim(void)
{
}// fin DTor
//-----------------------------------------------------------------------------------------------------------------------------------
void VueEnvSim::setRoad(Road * r)
{
	m_road = r;
}// fin set Road
//-----------------------------------------------------------------------------------------------------------------------------------
void VueEnvSim::setNode(NodeSim * n)
{
	m_node = n;
}// fin set Node
//-----------------------------------------------------------------------------------------------------------------------------------
Road * VueEnvSim::getRoad()
{
	return m_road;
}// fin get Road
//-----------------------------------------------------------------------------------------------------------------------------------
NodeSim * VueEnvSim::getNodeSim()
{
	return m_node;
}// fin get NodeSim
//-----------------------------------------------------------------------------------------------------------------------------------
void VueEnvSim::setRoadLink(RoadLink * r)
{
	m_RoadLink = r;
}// fin set Road Link
//-----------------------------------------------------------------------------------------------------------------------------------
RoadLink * VueEnvSim::getRoadLink()
{
	return m_RoadLink;
}// fin get Road Link
//-----------------------------------------------------------------------------------------------------------------------------------
bool VueEnvSim::isNextRoadLinkSet()
{
	if(m_NextRoadLink==NULL)
	{return false;}else{return true;}
}// fin choose next road link
//-----------------------------------------------------------------------------------------------------------------------------------
RoadLink * VueEnvSim::getNextRoadLink()
{
	return m_NextRoadLink;
}// fin choose next road link
//-----------------------------------------------------------------------------------------------------------------------------------
void VueEnvSim::chooseNextRoadLink()
{
	if(m_RoadLink->getExitRoad()->getExitNode()->getRandomRoadLink(m_RoadLink->getExitRoad()->getName())!=NULL && isNextRoadLinkSet()==false)
	{m_NextRoadLink=m_RoadLink->getExitRoad()->getEntryNode()->getRandomRoadLink(m_RoadLink->getExitRoad()->getName());}
}// fin choose next road link
//-----------------------------------------------------------------------------------------------------------------------------------
int VueEnvSim::getMyWaySize()
{
	return myWay.size();
}// fin if get my way size
//-----------------------------------------------------------------------------------------------------------------------------------
RoadLink * VueEnvSim::getMyWayItemAt(int i)
{
	return myWay.at(i);
}// fin getMyWayItemAt(int i)
//-----------------------------------------------------------------------------------------------------------------------------------
void VueEnvSim::setMyWayLastItem(RoadLink * rl)
{
	myWay.push_back(rl);
}// fin setMyWayLastItem(RoadLink * rl)
//-----------------------------------------------------------------------------------------------------------------------------------
float VueEnvSim::getDistToBeAtDesiredSpeed(float actualVehicleSpeed, RoadLink * r,float accelr)
{
	/* definition */ 
	float dist = r->getGap() , accel = accelr , tempSpeed = actualVehicleSpeed , deltaT = 0.025;

	/* processing */
	//if( tempSpeed > r->getDesiredSpeed() )
	//{
		while(tempSpeed>r->getDesiredSpeed() )
		{
		dist += tempSpeed;
		tempSpeed = (tempSpeed + ( -accel * deltaT ) ) ;
		}// fin while
	//}// fin if 
	//else{return 0;}
	return dist;
}// fin get Dist to be at desired speed
//-----------------------------------------------------------------------------------------------------------------------------------
void VueEnvSim::printingMyWyList()
{
	cout<<"- DISPLAY - MyWay (size) : "<< myWay.size() <<endl;
	for(unsigned int i(0); i<myWay.size() ; i++)
	{
		myWay.at(i)->DisplyMe();
	}// fin for i
	cout<<endl;
}// fin printing may Way List
//-----------------------------------------------------------------------------------------------------------------------------------
void VueEnvSim::supAndDecalFistItemOfMyWay()
{
	myWay.erase(myWay.begin());
}// fin supAndDecalFistItemOfMyWay()
//-----------------------------------------------------------------------------------------------------------------------------------
