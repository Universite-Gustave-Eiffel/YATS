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
#include "SourceSim.h"
#define PI 3.14159265

SourceSim::SourceSim(SDL_Surface * iWillBeOn, string n, float x1, float y1, float angleInclinaison)
{
	countVehicleLaunch= 0;
	name = n;
	whereIAmBlit = iWillBeOn;
	angle=angleInclinaison;

	// placement du point de controle visuelle des coordonnées
	coordonne.setX(x1);
	coordonne.setY(y1);
	coordonneMyVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,3,3,32,0,0,0,0);
	SDL_FillRect(coordonneMyVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,20,120,255));
	coordonneMyVisualPosition.x= coordonne.getX();
	coordonneMyVisualPosition.y= coordonne.getY();
	SDL_BlitSurface(coordonneMyVisualSurface,NULL,whereIAmBlit,&coordonneMyVisualPosition);

	SDL_FreeSurface(coordonneMyVisualSurface);

}// fin Ctor
//-----------------------------------------------------------------------------------------------------------------------------------
SourceSim::~SourceSim(void)
{
}// fib Dtor
//-----------------------------------------------------------------------------------------------------------------------------------
void SourceSim::myRoutine()
{
	/*majSurfaceRoute();
	majPtEntre();
	majPtSortie();*/
}// fin my routine
//-----------------------------------------------------------------------------------------------------------------------------------
Vehicle* SourceSim::popVehicle()
{
	string newVehicleName;
	newVehicleName = "VEHICLE ";
	newVehicleName += convertINTtoSTR(countVehicleLaunch);
	newVehicleName += " FROM ";
	newVehicleName += name;
	countVehicleLaunch++;

	Vehicle* aVehicleIsBorn = new Vehicle(coordonne.getX(),coordonne.getY(),whereIAmBlit,angle,newVehicleName );


	// TODO REBUILD HERE
	VueEnvSim * v = new VueEnvSim();
	v->setRoad(whereILaunchCar);
	v->setNode(whereILaunchCar->getExitNode());
	v->setRoadLink( v->getNodeSim()->getRandomRoadLink(v->getRoad()->getName()) );
	aVehicleIsBorn->setMyVue(v);
	aVehicleIsBorn->afterLaunch();

	return aVehicleIsBorn;
}// fin pop vehicle
//-----------------------------------------------------------------------------------------------------------------------------------
void SourceSim::printMe()
{
	cout << "- DISPLAY - " << name << " // type : Source // ( " << coordonne.getX() <<
		" ; " << coordonne.getY() << " ) " <<  endl
		<< "     Exit Road : " << whereILaunchCar->getName() << endl;
}// fin print me
//-----------------------------------------------------------------------------------------------------------------------------------
string SourceSim::getName()
{
	return name;
}// fin get name
//-----------------------------------------------------------------------------------------------------------------------------------
PointSim SourceSim::getCoordonnee()
{
	return coordonne;
}// fin get P sortie
//-----------------------------------------------------------------------------------------------------------------------------------
void SourceSim::setRoad(Road * r)
{
	whereILaunchCar = r;
}// fin set Road
//-----------------------------------------------------------------------------------------------------------------------------------
