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
#include "Road.h"

#define PI 3.14159265

Road::Road(SDL_Surface * iWillBeOn, string n, float x1, float y1, float x2, float y2)
{
	//fprintf(stderr,"- System - Lancement d'une Source \n");
	name = n;
	whereIAmBlit = iWillBeOn;
	zoomLVL=1;

	m_isEntryNodeSet = false;
	m_isExitNodeSet = false;

	float dist_PE_PS(0);
/*
	// creation d'une surface (typeSurface, longeur, hauteur, type couleur , ?,?,?,?)
	myVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,35,20,32,0,0,0,0);

	// coloration de la surface
	SDL_FillRect(myVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,255,0,0));

	myVisualPosition.x=a-(myVisualSurface->w / 2);
	myVisualPosition.y=b-(myVisualSurface->h / 2);

	SDL_BlitSurface(myVisualSurface,NULL,whereIAmBlit,&myVisualPosition);
	*/
	// placement du point d'entrée
	pointEntre.setX(x1);
	pointEntre.setY(y1);
	pointEntreMyVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,3,3,32,0,0,0,0);
	SDL_FillRect(pointEntreMyVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,20,120,255));
	pointEntreMyVisualPosition.x= pointEntre.getX();
	pointEntreMyVisualPosition.y= pointEntre.getY();
	SDL_BlitSurface(pointEntreMyVisualSurface,NULL,whereIAmBlit,&pointEntreMyVisualPosition);

	// placement du point de sortie
	pointSortie.setX(x2);
	pointSortie.setY(y2);
	pointSortieMyVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,3,3,32,0,0,0,0);
	SDL_FillRect(pointSortieMyVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,20,120,255));
	pointSortieMyVisualPosition.x= pointSortie.getX();
	pointSortieMyVisualPosition.y= pointSortie.getY();
	SDL_BlitSurface(pointSortieMyVisualSurface,NULL,whereIAmBlit,&pointSortieMyVisualPosition);

	longueur = getDistance(pointEntre,pointSortie);

	// placement de la surtface route
	// 1 calcul de la distance entre les 2 points (entré & sortie)
	dist_PE_PS= sqrt((pointSortie.getX()-pointEntre.getX())*(pointSortie.getX()-pointEntre.getX())
		+(pointSortie.getY()-pointEntre.getY())*(pointSortie.getY()-pointEntre.getY()));
	//cout << dist_PE_PS << endl;
	aD1 = (pointSortie.getY()-pointEntre.getY())
		/(pointSortie.getX()-pointEntre.getX());
	bD1 = pointEntre.getY()-(aD1*pointEntre.getX());
	// RECENT BUG FIX on the angle
	if(pointEntre.getX()<=pointSortie.getX())
	{angle = -atan (aD1) * 180 / PI;}else{angle = (-atan (aD1) * 180 / PI )+180;}
	//angle = -atan (aD1) * 180 / PI; // FORMULE INITIALE
	inTheMiddle.setX( ( pointSortie.getX()+ pointEntre.getX() ) /2 );
	inTheMiddle.setY( ( pointSortie.getY()+ pointEntre.getY() ) /2 );
	//2 initialisation de la surface.
	whereIAmBlit = iWillBeOn;
	myVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,dist_PE_PS,25,32,0,0,0,0) ;
	SDL_FillRect(myVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,156,156,156));

	/* TEST */
	cout << "- TEST - Road : " << name << " // AD1 : " << aD1 << " // bd1 : " << bD1 << endl;
	if(angle<0){angle = angle + 360;}

	rotation = rotozoomSurface(myVisualSurface, angle, 1, 1);  //On transforme la surface image.

	SDL_SetColorKey(rotation, SDL_SRCCOLORKEY, SDL_MapRGB(rotation->format, 0, 0, 0));

	SDL_BlitSurface(rotation,NULL,whereIAmBlit,&myVisualPosition);

	//?
	myVisualPosition.x=inTheMiddle.getX()-(rotation->w/2);
	myVisualPosition.y=inTheMiddle.getY()-(rotation->h/2);

	//SDL_BlitSurface(myVisualSurface,NULL,whereIAmBlit,&myVisualPosition);

	SDL_FreeSurface(rotation);
}// fin Ctor
//-----------------------------------------------------------------------------------------------------------------------------------
Road::~Road(void)
{
}// fib Dtor
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::myRoutine()
{
	//cout << pointEntre.getX() <<"/" ; 
	//cout << pointEntre.getY() << endl ; 

	// todo : changer ce truc la ! 
	// notament Maj Surface route mettre lmes dernieres modifications dans une autre fonction

	majSurfaceRoute();
	//majPtEntre();
	//majPtSortie();
}// fin my routine
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::majPtEntre()
{
	// pointEntre
	// SDL_Rect pointEntreMyVisualPosition;
	// SDL_Surface *pointEntreMyVisualSurface;

	//pointEntreMyVisualPosition.x= pointEntre.getX();
	//pointEntreMyVisualPosition.y= pointEntre.getY();

	//SDL_BlitSurface(pointEntreMyVisualSurface,NULL,whereIAmBlit,&pointEntreMyVisualPosition);
}// fin maj Pt Entre
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::majPtSortie()
{
	// pointSortie
	// SDL_Rect pointSortieMyVisualPosition;
	// SDL_Surface *pointSortieMyVisualSurface;

	//pointSortieMyVisualPosition.x= pointSortie.getX();
	//pointSortieMyVisualPosition.y= pointSortie.getY();

	//SDL_BlitSurface(pointSortieMyVisualSurface,NULL,whereIAmBlit,&pointSortieMyVisualPosition);
}// fin maj pt sortie
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::majSurfaceRoute()
{
	float dist_PE_PS(0);

	// placement du point de Entré
	//pointEntreMyVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,3,3,32,0,0,0,0);
	//SDL_FillRect(pointEntreMyVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,20,120,255));
	//pointEntreMyVisualPosition.x = pointEntre.getX();
	//pointEntreMyVisualPosition.y = pointEntre.getY();
	//SDL_BlitSurface(pointEntreMyVisualSurface,NULL,whereIAmBlit,&pointEntreMyVisualPosition);

	// placement du point de sortie
	//pointSortieMyVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,3,3,32,0,0,0,0);
	//SDL_FillRect(pointSortieMyVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,20,120,255));
	//pointSortieMyVisualPosition.x= pointSortie.getX();
	//pointSortieMyVisualPosition.y= pointSortie.getY();
	//SDL_BlitSurface(pointSortieMyVisualSurface,NULL,whereIAmBlit,&pointSortieMyVisualPosition);

	longueur = getDistance(pointEntre,pointSortie);

	dist_PE_PS= sqrt((pointSortie.getX()-pointEntre.getX())*(pointSortie.getX()-pointEntre.getX())
		+(pointSortie.getY()-pointEntre.getY())*((double)pointSortie.getY()/*pointSortie.getY()*/ 
		/* strange thing but cannot be fix ?!? HA HA !! finaly fix by casting correct type*/ -pointEntre.getY()));

	if(dist_PE_PS<=1){dist_PE_PS=1;}

	aD1 = (pointSortie.getY()-pointEntre.getY())
		/(pointSortie.getX()-pointEntre.getX());
	bD1 = pointEntre.getY()-(aD1*pointEntre.getX());

	if(pointEntre.getX()<=pointSortie.getX())
	{angle = -atan (aD1) * 180 / PI;}else{angle = (-atan (aD1) * 180 / PI )+180;}

	inTheMiddle.setX( ( pointSortie.getX()+ pointEntre.getX() ) /2 );
	inTheMiddle.setY( ( pointSortie.getY()+ pointEntre.getY() ) /2 );
	//else{
		
	//}// fin else 1
	//2 initialisation de la surface.
	myVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,dist_PE_PS,25*zoomLVL,32,0,0,0,0) ;
	SDL_FillRect(myVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,156,156,156));

	if(angle<0){angle = angle + 360;}

	rotation = rotozoomSurface(myVisualSurface, angle, 1, 1);  //On transforme la surface image.

	SDL_SetColorKey(rotation, SDL_SRCCOLORKEY, SDL_MapRGB(rotation->format, 0, 0, 0));

	// don't take this out
	myVisualPosition.x=inTheMiddle.getX()-(rotation->w/2);
	myVisualPosition.y=inTheMiddle.getY()-(rotation->h/2);

	SDL_BlitSurface(rotation,NULL,whereIAmBlit,&myVisualPosition);

	SDL_FreeSurface(rotation);
	SDL_FreeSurface(myVisualSurface);
	//SDL_FreeSurface(pointEntreMyVisualSurface);
	//SDL_FreeSurface(pointSortieMyVisualSurface);

}// fin maj surface Route
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::printMe()
{
	cout << "- DISPLAY - " << name << " TYPE : ROAD " << endl;
	cout << "            COORD (" << pointEntre.getX() <<  ";" << pointEntre.getY() << ") // (" << pointSortie.getX() << ";" << pointSortie.getY() << ")" << endl; 
	cout << "            ANGLE : "<< angle << endl;
	cout << "            LONGUEUR : "<< longueur << " ( pix )"  << endl;
	cout << "            LONGUEUR : "<< convertMetterToPIX(longueur) << " ( Metters )"  << endl;
	if(m_isEntryNodeSet==true)
	{cout << "            ENTRY NODE : "<< entryNode->getName() << endl;}
	if(m_isExitNodeSet==true)
	{cout << "            EXIT NODE : "<< exitNode->getName() << endl;}

}// fin print me
//-----------------------------------------------------------------------------------------------------------------------------------
string Road::getName()
{
	return name;
}// fin get name
//-----------------------------------------------------------------------------------------------------------------------------------
PointSim Road::getPEntre()
{
	return pointEntre;
}// fin get P sortie
//-----------------------------------------------------------------------------------------------------------------------------------
PointSim Road::getPSortie()
{
	return pointSortie;
}// fin get P sortie
//-----------------------------------------------------------------------------------------------------------------------------------
float Road::getAngle()
{
	return angle;
}//fin get angle
//-----------------------------------------------------------------------------------------------------------------------------------
bool Road::isEntryNodeSet()
{
	return m_isEntryNodeSet;
}// fin bool isEntryNodeSet()
//-----------------------------------------------------------------------------------------------------------------------------------
bool Road::isExitNodeSet()
{
	return m_isExitNodeSet;
}// fin bool isExitNodeSet()
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::setEntryNode(NodeSim * n)
{
	entryNode = n;
	m_isEntryNodeSet=true;
}// fin set entry node
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::setExitNode(NodeSim * n)
{
	exitNode = n;
	m_isExitNodeSet=true;
}// fin set exit node
//-----------------------------------------------------------------------------------------------------------------------------------
NodeSim * Road::getExitNode()
{
	return exitNode;
}// fin get Exit Node
//-----------------------------------------------------------------------------------------------------------------------------------
NodeSim * Road::getEntryNode()
{
	return entryNode;
}// fin get Entry node
//-----------------------------------------------------------------------------------------------------------------------------------
float Road::getDistance(PointSim a, PointSim b)
{
	float dist = sqrtf( ( a.getX() - b.getX() ) * ( a.getX() - b.getX() ) 
					+	   ( a.getY() - b.getY() ) * ( a.getY() - b.getY() )
			)/* fin racine*/;
	return dist;
}// fin get distance
//-----------------------------------------------------------------------------------------------------------------------------------
float Road::getLongueur()
{
	return longueur;
}// fin get longeur
//-----------------------------------------------------------------------------------------------------------------------------------
float Road::convertMetterToPIX(float f)
{
	float result;
	result = (f * 14) / 100;
	return result;
}// fin convertMetterToPix
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::setCoordPE(float abs, float ord)
{
	pointEntre.setX(abs);
	pointEntre.setY(ord);
}// fin set coord
//-----------------------------------------------------------------------------------------------------------------------------------
PointSim Road::getCoordPE()
{
	return pointEntre;
}// fin get Coord
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::setCoordPS(float abs, float ord)
{
	pointSortie.setX(abs);
	pointSortie.setY(ord);
}// fin set coord
//-----------------------------------------------------------------------------------------------------------------------------------
PointSim Road::getCoordPS()
{
	return pointSortie;
}// fin get Coord
//-----------------------------------------------------------------------------------------------------------------------------------
void Road::setZoomLVL(float zoom)
{
	zoomLVL = zoomLVL * zoom;
}// fin set zoom LVL 
//-----------------------------------------------------------------------------------------------------------------------------------
float Road::getZoomLVL()
{
	return zoomLVL;
}//fin get Zoom LVL 
//-----------------------------------------------------------------------------------------------------------------------------------

