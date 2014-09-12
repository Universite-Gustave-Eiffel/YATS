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
#include "Body.h"


Body::Body(float a, float b, SDL_Surface * iWillBeOn, float angleInitial)
{
	// surface sur laquelle le vheicle est blitter
	whereIAmBlit=iWillBeOn;
	// coordonnées du vhéicle
	coord.setX(a);coord.setY(b);
	// angle initial du Vehicle (récupérer de la source)
	angle = angleInitial;
	angleBraquage = 0;
	vitesseVehicle = 0;
	 aD1=0;
	 aD2=0;
	 bD1=0;
	 bD2=0;

	// creation d'une surface (typeSurface, longeur, hauteur, type couleur , ?,?,?,?)
	myVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,29,12,32,0,0,0,0);

	// coloration de la surface en rouge
	SDL_FillRect(myVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,255,0,0));

	myVisualPosition.x=a-(myVisualSurface->w / 2);
	myVisualPosition.y=b-(myVisualSurface->h / 2);

	SDL_BlitSurface(myVisualSurface,NULL,whereIAmBlit,&myVisualPosition);

	// placement du point de control
	myPointVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,2,2,32,0,0,0,0);
	SDL_FillRect(myPointVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,255,255,10));
	myPointVisualPosition.x= a;
	myPointVisualPosition.y= b;
	SDL_BlitSurface(myPointVisualSurface,NULL,whereIAmBlit,&myPointVisualPosition);

}//Fin Ctor
//-----------------------------------------------------------------------------------------------------------------------------------
Body::~Body(void)
{

}//Fin Dtor
//-----------------------------------------------------------------------------------------------------------------------------------
PointSim Body::getBodyCoord()
{
	return coord;
}
//-----------------------------------------------------------------------------------------------------------------------------------
float Body::getAngleBraquage()
{
	return angleBraquage;
}
//-----------------------------------------------------------------------------------------------------------------------------------
void Body::setAngleBraquage(float f)
{
	angleBraquage=f;
}
//-----------------------------------------------------------------------------------------------------------------------------------
