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
#include "EnvironmentSim.h"


EnvironmentSim::EnvironmentSim(void)
{
}// fin CTor
//-----------------------------------------------------------------------------------------------------------------------------------
EnvironmentSim::~EnvironmentSim(void)
{
}// fin DTor
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::addRoadToTheList(Road * r)
{
	listOfRoad.push_back(r);
}// fin add road to the list
//-----------------------------------------------------------------------------------------------------------------------------------
int EnvironmentSim::getListOfRoadSize()
{
	return listOfRoad.size();
}// fin get List Of RoadSize ()
//-----------------------------------------------------------------------------------------------------------------------------------
Road * EnvironmentSim::getRoadAt(int i)
{
	return listOfRoad.at(i);
}// fin get Road at(i)
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::printRoadList()
{
	cout << endl ;
	cout << "- Display - printing Road list : " << endl; 
	for(unsigned int i(0); i<listOfRoad.size(); i++)
	{
		listOfRoad.at(i)->printMe();
	}// fin for i
	cout << endl ;

}// fin print RoadList
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::printVehicleList()
{
	cout << endl ;
	for(unsigned int i(0); i<listOfVehicle.size(); i++)
	{
		//listOfVehicle.at(i)->printMe();
	}// fin for i
	cout << endl ;
}
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::printNodeList()
{
	cout << endl ;
	cout << "- Display - printing Node list : " << endl; 
	for(unsigned int i(0); i<listOfNode.size(); i++)
	{
		listOfNode.at(i)->displayMe();
	}// fin for i
	cout << endl ;
}
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::printSourceList()
{
	cout << endl ;
	cout << "- Display - printing Source list : " << endl; 
	for(unsigned int i(0); i<listOfSource.size(); i++)
	{
		listOfSource.at(i)->printMe();
	}// fin for i
	cout << endl ;
}
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::addNodeToTheList(NodeSim * n)
{
	listOfNode.push_back(n);
}// fin addNodeToTheList
//-----------------------------------------------------------------------------------------------------------------------------------
int EnvironmentSim::getListOfNodeSize()
{
	return listOfNode.size();
}// fin get List Of Node Size
//-----------------------------------------------------------------------------------------------------------------------------------
NodeSim * EnvironmentSim::getNodeAt(int i)
{
	return listOfNode.at(i);
}// fin getNodeAt(i)
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::addSourceToTheList(SourceSim * s)
{
	listOfSource.push_back(s);
}// fin Add sourceToTheList
//-----------------------------------------------------------------------------------------------------------------------------------
int EnvironmentSim::getListOfSourceSize()
{
	return listOfSource.size();
}// fin get list of Source Size
//-----------------------------------------------------------------------------------------------------------------------------------
SourceSim * EnvironmentSim::getSourceAt(int i)
{
	return listOfSource.at(i);
}// fin get Source At(i)
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::addVehicleToTheList(Vehicle * v)
{
	listOfVehicle.push_back(v);
}// fin add Vehicle to the list
//-----------------------------------------------------------------------------------------------------------------------------------
int EnvironmentSim::getListOfVehicleSize()
{
	return listOfVehicle.size();
}// fin get list of Vehicle.size
//-----------------------------------------------------------------------------------------------------------------------------------
Vehicle * EnvironmentSim::getVehicleAt(int i)
{
	return listOfVehicle.at(i);
}// fin get Vehicle at(i)
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::linkingRoadToNode()
{
	// pour tout les noeuds
	for(unsigned int i(0); i<listOfNode.size(); i++)
	{
		//si le l'exitpoint de la road == false prendre chaque point d'entrée du noeud puis le mettre en entrée de la road en question
		for(int j(0); j<listOfNode.at(i)->getListExitPointSize();j++)
		{
			if(listOfNode.at(i)->getTheRoadExitAt(j)->isEntryNodeSet() == false)
			{listOfNode.at(i)->getTheRoadExitAt(j)->setEntryNode(listOfNode.at(i));}
			
		}//fin for j

		for(int j(0); j<listOfNode.at(i)->getListEntryPointSize();j++)
		{
			if(listOfNode.at(i)->getTheRoadEntryAt(j)->isExitNodeSet() == false)
			{listOfNode.at(i)->getTheRoadEntryAt(j)->setExitNode(listOfNode.at(i));}
			
		}//fin for j

	}// fin for i
}//fin linking road to node()
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::myRoutine()
{	

	for(unsigned int i(0) ; i < listOfVehicle.size() ; i++)
	{
		if(listOfVehicle.at(i)->getIfIWannaBeDelete() == true )
		{	cout<< "- System - Deleting Vehicle : " << listOfVehicle.at(i)->getName() <<endl;
			delete listOfVehicle.at(i);
			listOfVehicle.erase(listOfVehicle.begin()+i);}
		else
		{
			listOfVehicle.at(i)->myRoutine();
			}
	}
}// fin My Routine
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::createAllRoadLink()
{
	for(unsigned int i(0); i<listOfNode.size();i++)
	{
		//cout << " creating RoadLinkList For " << listOfNode.at(i)->getName() << endl;
		listOfNode.at(i)->createAllRoadLink();
	}// fin for all node
}// fin create all road Link
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::moveEnvironnment(int x, int y)
{
	/* RAPPEL : 
	vector<Vehicle *> listOfVehicle;          -> done
	vector<SourceSim *> listOfSource;		  -> apparently no need 
	vector<Road *> listOfRoad;				  -> done
	vector<NodeSim *> listOfNode;			  -> done without Manual Maj RoadLink..
	vector<VueEnvSim *> listVueEnvSim;        -> apparently no need  */ 

	//////////////////////////
	// MAJ VEHICLE POSITION //
	//////////////////////////
	for(unsigned int i(0);i<listOfVehicle.size();i++)
	{
		listOfVehicle.at(i)->setCoord( 
			/* x */ listOfVehicle.at(i)->getCoord().getX()+ x ,
			/* y */ listOfVehicle.at(i)->getCoord().getY()+ y );
	}// fin for i 

	///////////////////////
	// MAJ ROAD POSITION //
	///////////////////////
	for(unsigned int i(0);i<listOfRoad.size();i++)
	{
		listOfRoad.at(i)->setCoordPE( 
			/* x */ listOfRoad.at(i)->getCoordPE().getX()+ x ,
			/* y */ listOfRoad.at(i)->getCoordPE().getY()+ y );

		listOfRoad.at(i)->setCoordPS( 
			/* x */ listOfRoad.at(i)->getCoordPS().getX()+ x ,
			/* y */ listOfRoad.at(i)->getCoordPS().getY()+ y );

		listOfRoad.at(i)->myRoutine();
	}// fin for i 

	///////////////////////
	// MAJ NODE POSITION //
	///////////////////////
	for(unsigned int i(0);i<listOfNode.size();i++)
	{
		listOfNode.at(i)->setCoord( 
			/* x */ listOfNode.at(i)->getNodePoint().getX()+ x ,
			/* y */ listOfNode.at(i)->getNodePoint().getY()+ y );
	}// fin for i 
}// fin move Environment
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::setSurfaceFontScreen( SDL_Surface * iWillBeOn )
{
	whereIAmBlit = iWillBeOn;
}// fin setSurfaceFontScreen( SDL_Surface * iWillBeOn )
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::postMoveEnv()
{
	float correctZoomLvl = listOfRoad.at(0)->getZoomLVL();

	for(unsigned int i(0);i<listOfNode.size();i++)
	{
		listOfNode.at(i)->circle(listOfNode.at(i)->getNodePoint().getX(),
								 listOfNode.at(i)->getNodePoint().getY(),
								 13*correctZoomLvl,whereIAmBlit,156,156,156);
	}// fin for i 
}// fin postMoveEnv()
//-----------------------------------------------------------------------------------------------------------------------------------
void EnvironmentSim::zoomEnv(float r)
{/* r -> facteur de zoom */
	
	/* Cursor */
	int cursorPlaceX , cursorPlaceY;
	SDL_GetMouseState(&cursorPlaceX, &cursorPlaceY);
	
	/* Wanna more théory ? GOTOsee : http://fr.wikipedia.org/wiki/Homoth%C3%A9tie */

	///////////////////////
	// MAJ ROAD POSITION //
	///////////////////////
	//cout<<listOfRoad.at(4)->getLongueur()<<endl;
	for(unsigned int i(0);i<listOfRoad.size();i++)
	{
		listOfRoad.at(i)->setZoomLVL(r);

		listOfRoad.at(i)->setCoordPE( 
			/* x */ ( r * ( listOfRoad.at(i)->getCoordPE().getX() - cursorPlaceX ) + cursorPlaceX ),
			/* y */ ( r * ( listOfRoad.at(i)->getCoordPE().getY() - cursorPlaceY ) + cursorPlaceY )  );

		listOfRoad.at(i)->setCoordPS( 
			/* x */ ( r * ( listOfRoad.at(i)->getCoordPS().getX() - cursorPlaceX ) + cursorPlaceX ),
			/* y */ ( r * ( listOfRoad.at(i)->getCoordPS().getY() - cursorPlaceY ) + cursorPlaceY )  );

		listOfRoad.at(i)->myRoutine();
	}// fin for i 

	float correctZoomLvl = listOfRoad.at(0)->getZoomLVL();
	cout<<"zoom = " << correctZoomLvl*100 <<endl;

	//////////////////////////
	// MAJ VEHICLE POSITION //
	//////////////////////////
	//listOfVehicle.at(0)->printMe();
	for(unsigned int i(0);i<listOfVehicle.size();i++)
	{
		listOfVehicle.at(i)->setCoord( 
			/* x */ ( r * ( listOfVehicle.at(i)->getCoord().getX() - cursorPlaceX ) + cursorPlaceX ),
			/* y */ ( r * ( listOfVehicle.at(i)->getCoord().getY() - cursorPlaceY ) + cursorPlaceY )  );

		listOfVehicle.at(i)->setZoomLVL(r);
	}// fin for i 

	///////////////////////
	// MAJ NODE POSITION //
	///////////////////////
	//listOfNode.at(2)->getRoadLinkAt(0)->DisplyMe();
	for(unsigned int i(0);i<listOfNode.size();i++)
	{		listOfNode.at(i)->setCoord( 
			/* x */ ( r * ( listOfNode.at(i)->getNodePoint().getX() - cursorPlaceX ) + cursorPlaceX ),
			/* y */ ( r * ( listOfNode.at(i)->getNodePoint().getY() - cursorPlaceY ) + cursorPlaceY )  );

			listOfNode.at(i)->circle(listOfNode.at(i)->getNodePoint().getX(),
								 listOfNode.at(i)->getNodePoint().getY(),
								 13*correctZoomLvl,whereIAmBlit,156,156,156);

			listOfNode.at(i)->setTheCorrectRoadLinkZoomLvl(r);

	}// fin for i 

}// fin zoom environnement
//-----------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------------
