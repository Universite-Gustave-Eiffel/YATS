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
#include "RoadLink.h"


RoadLink::RoadLink(Road * e, Road * s)
{
	gap = 0;
	rEntre = e;
	rSortie = s;
	/* new way to calcul angle : ABORTED*/
	float res1, res2;
/*	bool mark1 = false;
	bool mark2 = false;*/

	/* Methode optimisé */
	res1 = rEntre->getAngle();
	res2 = rSortie->getAngle();

	res2 = res2 - res1;
	res1 = res1 - res1; // don't worry i'm not insane, step just to understand well what happen
	

	if(fabs(res2) < 180)
	{ /* gonna happen later */ } else { 
		res2 = fabs(res2) - 360;}

	angleEntreSortie = fabs(res2);

	if(angleEntreSortie<=20) /* si angle <= 20 */ 
	{maxSpeedAllow = -0.5 * angleEntreSortie + 70 ;}
	else{ if(angleEntreSortie>=80) /* si angle >= 80 */
			{maxSpeedAllow = -0.088 * angleEntreSortie + 17.1 ;}
			else{maxSpeedAllow = -0.833 * angleEntreSortie + 76.1 ; }
	}// fin if if 
	
	maxSpeedAllow = convertMeterToPix((maxSpeedAllow*1000)/60/60)/40;
	gap = convertAngleToGap(); /* put the gap at the good distance depending on the angle */
	//cout << maxSpeedAllow << endl;
}// Fin DTor
//-----------------------------------------------------------------------------------------------------------------------------------
RoadLink::~RoadLink(void)
{
}//
//-----------------------------------------------------------------------------------------------------------------------------------
Road * RoadLink::getEntryRoad()
{
	return rEntre;
}// fin get entry road
//-----------------------------------------------------------------------------------------------------------------------------------
Road * RoadLink::getExitRoad()
{
	return rSortie;
}// fin get Road Exit
//-----------------------------------------------------------------------------------------------------------------------------------
float RoadLink::getAngle()
{
	return angleEntreSortie;
}// fin get Angl 
//-----------------------------------------------------------------------------------------------------------------------------------
float RoadLink::getDesiredSpeed()
{
	return maxSpeedAllow;
}// fin Get Desired Speed
//-----------------------------------------------------------------------------------------------------------------------------------
void RoadLink::setDesiredSpeed(float f)
{
	maxSpeedAllow = f;
}// // fin set Desired speed
//-----------------------------------------------------------------------------------------------------------------------------------
void RoadLink::setIDRoadLink(int i)
{
	idRoadLink = i;
}// fin Set Id roadLink
//-----------------------------------------------------------------------------------------------------------------------------------
int RoadLink::getIDRoadLink()
{
	return idRoadLink;
}// fin get ID Road Link 
//-----------------------------------------------------------------------------------------------------------------------------------
void RoadLink::DisplyMe()
{
	cout << "- DISPLAY - LinkRoad : " << idRoadLink << endl;
	cout << "                entry : " << rEntre->getName() << endl;
	cout << "                exit  : " << rSortie->getName() << endl;
	cout << "                Angle : " << angleEntreSortie << endl;
	cout << "                gap : " << gap << endl;
	cout << "                max speed : " << maxSpeedAllow << endl;

}// fin display me
//----------------------------------------------------------------------------------------------------------------------------------
float RoadLink::convertMeterToPix(float f)
{
	float result(0);
	result = (f*100) / 14;
	return result;
}// fin convert meter To pix
//----------------------------------------------------------------------------------------------------------------------------------
float RoadLink::convertAngleToGap()
{
	float result;
	result = 0.367 * angleEntreSortie -18;
	if(result<15)
	{result = 15;}
	return result;
}// fin convert Agne to gap 
//----------------------------------------------------------------------------------------------------------------------------------
void RoadLink::setGap(float f)
{
	gap = f;
}// fin set gap
//----------------------------------------------------------------------------------------------------------------------------------
float RoadLink::getGap()
{
	return gap;
}// fin get Gap 
//----------------------------------------------------------------------------------------------------------------------------------
float RoadLink::diff(float a, float b)
{
	float result = fabs(a) + fabs(b);
	return result;
}// fin diff f_a f_b
