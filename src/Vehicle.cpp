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
#include "Vehicle.h"

#define PI 3.14159265

Vehicle::Vehicle(int a, int b, SDL_Surface * iWillBeOn)
{
	/* Deprecated */ 
	deleteMe= false;
	vitessePrecedente=0.49;
	haveObjectif = false;
	angleBraquage = 0;
	vitesseVehicle = 0;
	 aD1=0;
	 aD2=0;
	 bD1=0;
	 bD2=0;
	 angle = 0;
	fprintf(stderr,"- System - Lancement d'un vehicule \n");
	
	pointA.setX(a); pointA.setY(b);
	//pointB.setX(a+35); pointB.setY(b);
	//pointA = new PointSim(a,b);
	//pointB = new PointSim(a+35,b);

	whereIAmBlit = iWillBeOn;

	// creation d'une surface (typeSurface, longeur, hauteur, type couleur , ?,?,?,?)
	myVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,29,12,32,0,0,0,0);

	// coloration de la surface
	SDL_FillRect(myVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,255,0,0));

	myVisualPosition.x=a-(myVisualSurface->w / 2);
	myVisualPosition.y=b-(myVisualSurface->h / 2);

	SDL_BlitSurface(myVisualSurface,NULL,whereIAmBlit,&myVisualPosition);

	// placement du point de control
	myPointVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,2,2,32,0,0,0,0);
	SDL_FillRect(myPointVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,255,255,10));
	//myPointVisualPosition.x= myVisualPosition.x;
	//myPointVisualPosition.y= myVisualPosition.y;
	myPointVisualPosition.x= a;
	myPointVisualPosition.y= b;
	SDL_BlitSurface(myPointVisualSurface,NULL,whereIAmBlit,&myPointVisualPosition);

	//init des valeur pour le mouvement du véhicle
	printMyLinearEquation();

}// fin Ctor 1 
//-----------------------------------------------------------------------------------------------------------------------------------
Vehicle::Vehicle(float a, float b, SDL_Surface * iWillBeOn, float angleInitial,std::string n)
{
	zoomLVL=1;
	name = n;
	haveObjectif = false;
	angleBraquage = 0;
	angleBraquageMax = 3;
	vitesseVehicle = 0;
	vitesseMAX = 9; /* = 180 km */
	accel = 0.80;
	deltaT = 0.025;
	aD1=0;
	aD2=0;
	bD1=0;
	bD2=0;
	angle = angleInitial;
	cout << "- System - Launching Vehicle : " << name << endl;
	
	pointA.setX(a); pointA.setY(b);
	//pointB.setX(a+35); pointB.setY(b);
	//pointA = new PointSim(a,b);
	//pointB = new PointSim(a+35,b);

	whereIAmBlit = iWillBeOn;

	// creation d'une surface (typeSurface, longeur, hauteur, type couleur , ?,?,?,?)
	myVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,29,12,32,0,0,0,0);

	// coloration de la surface
	SDL_FillRect(myVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,255,0,0));

	myVisualPosition.x=a-(myVisualSurface->w / 2);
	myVisualPosition.y=b-(myVisualSurface->h / 2);

	SDL_BlitSurface(myVisualSurface,NULL,whereIAmBlit,&myVisualPosition);

	// placement du point de control
	myPointVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,2,2,32,0,0,0,0);
	SDL_FillRect(myPointVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,255,255,10));
	//myPointVisualPosition.x= myVisualPosition.x;
	//myPointVisualPosition.y= myVisualPosition.y;
	myPointVisualPosition.x= a;
	myPointVisualPosition.y= b;
	SDL_BlitSurface(myPointVisualSurface,NULL,whereIAmBlit,&myPointVisualPosition);

	//init des valeur pour le mouvement du véhicle
	printMyLinearEquation();

	//SDL_FreeSurface(myVisualSurface);
	//SDL_FreeSurface(myPointVisualSurface);

}// fin CTor 2
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::afterLaunch()
{
	/* eviter les problèmes de chemins initiaux : */ 
	if(m_Vue->getRoadLink()!=NULL){
	m_Vue->setMyWayLastItem(m_Vue->getRoadLink());
	nextPosition();}

	//if(m_Vue->getRoadLink()->getExitRoad()->getName().compare(m_Vue->getMyWayItemAt(0)->getExitRoad()->getName())==0)
	//{/*nothing*/}else{m_Vue->setRoadLink(m_Vue->getMyWayItemAt(0));}

}// fin after launch
//-----------------------------------------------------------------------------------------------------------------------------------
Vehicle::~Vehicle(void)
{
}// fin Dtor
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::moveFoward()
{
	if(vitesseVehicle<=36.1)
	{
		vitesseVehicle=vitesseVehicle+0.01;
	}

	// test
	//float kmh = ((vitesseVehicle*60)*60)/1000;
	//fprintf (stderr,"- test - actual speed = %f ( %f KM) \n", vitesseVehicle, kmh );
}// fin moveFoward
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::stopSmooth()
{
	if(vitesseVehicle>=0.001)
	{
		vitesseVehicle=vitesseVehicle-0.01;
	}

	if(vitesseVehicle<0)
	{
		vitesseVehicle=0;
	}

	// test
	//float kmh = ((vitesseVehicle*60)*60)/1000;
	//fprintf (stderr,"- test - actual speed = %f ( %f KM) \n", vitesseVehicle, kmh );
}// fin stopSmooth
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::turnLeft()
{
	if(angleBraquage < angleBraquageMax-0.20 )
	{
		//angleBraquage = angleBraquage + 0.0025;
		angleBraquage = angleBraquage + 0.60;
	}

	if(angle>360)
	{
		angle = angle - 360;
	}

	printMyLinearEquation();
}// fin turn Left
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::turnRigth()
{
	if(angleBraquage > -angleBraquageMax + 0.20)
	{
		//angleBraquage = angleBraquage - 0.0025;
		angleBraquage = angleBraquage -0.60;
	}

	if(angle<-360)
	{
		angle = angle + 360;
	}

	printMyLinearEquation();
}// fin Turn Rigth
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::nextPosition()
{
	/* Calcul de la distance de freinage.*/
	float df = 0;
	float tempsSPD = vitesseVehicle;
	while(tempsSPD>0)
			{
			df += tempsSPD;
			tempsSPD +=( -accel * deltaT ) ;
			}// fin while
	/* crazy test */ df+=30*zoomLVL; /* it Work so fine !! XD */
	/* dt = Distance Temporaire*/
	float dt = 0;
	int palier = 0;

	//////////////////////////////////////////////////
	// Creation du chemin jusqu'au palier de vision //
	//////////////////////////////////////////////////
	while(df>dt)
	{	if(m_Vue->getMyWaySize()>palier)
		{
			if(palier==0)
			{dt+=m_Vue->getMyWayItemAt(palier)->getEntryRoad()->getLongueur() - getDistance(pointA,m_Vue->getMyWayItemAt(palier)->getEntryRoad()->getPEntre() ) ;/* - moins la longeur parcourue */
			palier++;
			}else
			{dt+=m_Vue->getMyWayItemAt(palier)->getEntryRoad()->getLongueur() /*- getDistance(pointA,m_Vue->getMyWayItemAt(palier)->getEntryRoad()->getPEntre() ) */;/* - moins la longeur parcourue */
			palier++;
			}
			
		}//fin if(m_Vue->getMyWaySize()>palier)
		else{
			if(palier==0)
			{
				/* si il existe au moins un chemin empruntable */
				if(m_Vue->getNodeSim()->getListExitPointSize()>0)
				{
					RoadLink * rdmRL = m_Vue->getNodeSim()->getRandomRoadLink( m_Vue->getRoad()->getName() );
					dt+=rdmRL->getEntryRoad()->getLongueur()-getDistance(pointA,rdmRL->getEntryRoad()->getPEntre());
					m_Vue->setMyWayLastItem(rdmRL);
				}// fin is il existe au moins un chemin empruntable
				else{/* il n'existe pas de chemin enpruntable, on sort de la boucle */
					dt=df+1;
				}
			}// fin si palier == 0 
			else{/* si le palier est supérieur a 0 */
				/* si il existe au moins un chemin empruntable */
				if(m_Vue->getMyWayItemAt(palier-1)->getExitRoad()->getExitNode()->getListExitPointSize()>0)
				{
					RoadLink * rdmRL = m_Vue->getMyWayItemAt(palier-1)->getExitRoad()->getExitNode()->getRandomRoadLink( 
						m_Vue->getMyWayItemAt(palier-1)->getExitRoad()->getName() );
					dt+=rdmRL->getEntryRoad()->getLongueur();
					m_Vue->setMyWayLastItem(rdmRL);
				}// fin is il existe au moins un chemin empruntable
				else{/* il n'existe pas de chemin enpruntable, on sort de la boucle */
					dt=df+1;
				}
			}
			palier++;
		}// fin else if(m_Vue->getMyWaySize()>palier)
	}// fin while df>dt 

	///////////////////////////////////////////////
	// Ralentir en fonction du plus contraignant //
	///////////////////////////////////////////////
	float dt2 = 0; //, dt3=df;
	bool ralentir = false ; 

	for(int i(0); i<m_Vue->getMyWaySize(); i++)
	{
		/* modif */
		if(vitesseVehicle>m_Vue->getMyWayItemAt(i)->getDesiredSpeed())
		{
			dt2 = m_Vue->getDistToBeAtDesiredSpeed( vitesseVehicle , m_Vue->getMyWayItemAt(i) ,accel);
		}else{dt2=0;}

		
		if( dt2 > getDistance( pointA , m_Vue->getMyWayItemAt(i)->getEntryRoad()->getPSortie())/*+ m_Vue->getMyWayItemAt(i)->getGap()*/
			|| isEqual(dt2,getDistance( pointA , m_Vue->getMyWayItemAt(i)->getEntryRoad()->getPSortie() ) /*+ m_Vue->getMyWayItemAt(i)->getGap()*/ )==true
			 /* FAUX - m_Vue->getMyWayItemAt(i)->getGap()*/ )
		{
			ralentir = true;
		}// fin if ( dt2 > dist (moi , l'objet) ) 
	}// fin for i

	if (ralentir == true) 
	{/* ralentir */
		vitesseVehicle = (vitesseVehicle + ( -accel * deltaT ) ) ;
	}else{/* accelere */ 
		if (vitesseVehicle < vitesseMAX )
		{vitesseVehicle = (vitesseVehicle + ( accel * deltaT ) ) ;}
	}

	/* récup ancien */						
 
	/* Deplacement du point central (en jaune) */ 
	angle = angle + angleBraquage;
	double correctAngle; 
	correctAngle = -angle ;
	// x2 = x1 + Distance * cos ( angle) 
	pointA.setX( pointA.getX() + ( vitesseVehicle * cos ( correctAngle * PI / 180 ) ) );
	pointA.setY( pointA.getY() + ( vitesseVehicle * sin ( correctAngle * PI / 180 ) ) );

	/* Sauvegarde */ 
	vitessePrecedente = vitesseVehicle;

}// fin nextPosition
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::printMe()
{
	/*
	RAPPEL : 

	 NORD
OUEST	 EST
	 SUD
	*/
	rotation = rotozoomSurface(myVisualSurface, angle, 1, 1);  //On transforme la surface image.

	SDL_SetColorKey(rotation, SDL_SRCCOLORKEY, SDL_MapRGB(rotation->format, 0, 0, 0));

	/* maj de la surface (en rouge) */
	myVisualPosition.x=pointA.getX()-(rotation->w / 2);
	myVisualPosition.y=pointA.getY()-(rotation->h / 2);
	SDL_BlitSurface(rotation,NULL,whereIAmBlit,&myVisualPosition);
	SDL_FreeSurface(rotation);

}// fin printMe();
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::printMyLinearEquation()
{
	float result;
	float correctAngle; 

	//test
		correctAngle = -angle;

	if(correctAngle<89.9)
	{
		result = tan ((90 - correctAngle)*PI/180);

		//result * longeur quelconque : 
		result = result * 10;

		aD1 = 10 / result;

		bD1 = -((aD1 * pointA.getX()) - pointA.getY());
	}
	
}// fin void print my linear equation 
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::myRoutine()
{
	
	setPointFocal( m_Vue->getNodeSim()->getNodePoint().getX() , m_Vue->getNodeSim()->getNodePoint().getY() );
	

	if(m_Vue->getRoadLink() != NULL) // Si le roadLink Actuel est différent de NULL
	{	

		if(getDistance(pointFocal,pointA)< m_Vue->getRoadLink()->getGap() || isEqual(m_Vue->getRoadLink()->getGap(),m_Vue->getRoadLink()->getGap()) ) // Si la distance entre moi & pf < au gap 
		{	

			if(m_Vue->getNodeSim()->getListExitPointSize() == 0) // Si la liste de sortie du node actuel est vide
				{if(getDistance(pointFocal,pointA)<10*zoomLVL){
					deleteMe=true;/* if the vehicle is on a Well*/}else{/*cout<<"here ? "<<endl;*/}
			// Visité dans le cas de plus de 1 segment de route !
			}else{/* give to the vehicle a new destination*/
				if( m_Vue->getMyWaySize() > 0 ){
					if( (getDistance(pointFocal,pointA)< m_Vue->getRoadLink()->getGap() || isEqualLigth(m_Vue->getRoadLink()->getGap(),getDistance(pointFocal,pointA)==true )/* fin is equal ligth*/ )/* fin ou */ 
						&& m_Vue->getMyWaySize()==1 && m_Vue->getRoadLink()->getExitRoad()->getExitNode()->getListExitPointSize()==0) // Si la distance entre moi & pf < au gap 
					{
						m_Vue->setRoad(m_Vue->getMyWayItemAt(0)->getExitRoad());
						m_Vue->setNode(m_Vue->getRoad()->getExitNode());//} // fin if null
						m_Vue->setRoadLink( m_Vue->getMyWayItemAt(0) );
					}

					if( (getDistance(pointFocal,pointA)< m_Vue->getRoadLink()->getGap() || isEqualLigth(m_Vue->getRoadLink()->getGap(),getDistance(pointFocal,pointA) )/* fin is equal ligth*/ )/* fin ou */ 
						&& m_Vue->getMyWaySize()>=2) // Si la distance entre moi & pf < au gap 
					{
					m_Vue->supAndDecalFistItemOfMyWay();

					m_Vue->setRoadLink( m_Vue->getMyWayItemAt(0) );
					m_Vue->setRoad(m_Vue->getRoadLink()->getEntryRoad());
					m_Vue->setNode(m_Vue->getRoad()->getExitNode());//} // fin if null
					}
				}// fin if getMyWaySize.size>0
			}// fin else destination
		}// fin if get distance pf pa
	}else{
		if(getDistance(pointFocal,pointA)< 5*zoomLVL)
		{ //cout<<"enter bad bad way"<<endl;
			if(m_Vue->getNodeSim()->getListExitPointSize() == 0)
				{deleteMe=true;/* if the vehicle is on a Well*/
			// Visité seulement dans le cas d'un segment de route unique !
			}else{/* give to the vehicle a new destination*/
					/* nothing */
				}
		}// fin if get Distance
	}// fin else roadlink != null
	if ( haveObjectif == true )
	{
		//putMyFocalPoint();
		decide();
	} // fin if have objectif
	nextPosition();
	printMe();
	putMyControlPoint();
}// fin my routine
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::decide()
{

	float distPF = sqrtf( ( pointA.getX() - pointFocal.getX() ) * ( pointA.getX() - pointFocal.getX() ) 
					+	   ( pointA.getY() - pointFocal.getY() ) * ( pointA.getY() - pointFocal.getY() )
			)/* fin racine*/;

	/*if(distPF<=10)*/if(distPF<10*zoomLVL || isEqualLigth(distPF,10*zoomLVL)==true )
		{
			//vitesseVehicle=0;
			haveObjectif = false;
		}
	
	if(haveObjectif == true)
	{

		aD2 = ( pointFocal.getY() - pointA.getY() )
			/ ( pointFocal.getX() - pointA.getX() );
		bD2 = -((aD1 * pointA.getX()) - pointA.getY());

		if ( ( isEqualLigth(aD1, aD2) == true ) &&
			 ( isEqualLigth(bD1, bD2) == true ) ) 
		{
			angleBraquage = 0;
			//fprintf (stderr,"- test - enter braquage 0 \n");

		}
		else 
		{
			PointSim etatT11 = getPointForState(1);
			float t11 = sqrtf( ( etatT11.getX() - pointFocal.getX() ) * ( etatT11.getX() - pointFocal.getX() ) 
						+	   ( etatT11.getY() - pointFocal.getY() ) * ( etatT11.getY() - pointFocal.getY() )
				)/* fin racine*/;
			//fprintf (stderr,"- test - t11 = %f \n", t11 );

			PointSim etatT12 = getPointForState(2);
			float t12 = sqrtf( ( etatT12.getX() - pointFocal.getX() ) * ( etatT12.getX() - pointFocal.getX() ) 
						+	   ( etatT12.getY() - pointFocal.getY() ) * ( etatT12.getY() - pointFocal.getY() )
				)/* fin racine*/;
			//fprintf (stderr,"- test - t12 = %f \n", t12 );

			PointSim etatT13 = getPointForState(3);
			float t13 = sqrtf( ( etatT13.getX() - pointFocal.getX() ) * ( etatT13.getX() - pointFocal.getX() ) 
						+	   ( etatT13.getY() - pointFocal.getY() ) * ( etatT13.getY() - pointFocal.getY() )
				)/* fin racine*/;
			//fprintf (stderr,"- test - t13 = %f \n \n", t13 );

			float bestResult = std::min(t11,t12);
			bestResult = std::min(bestResult,t13);

			if(isEqual(bestResult,t12) == true )
			{	
				angleBraquage=0;
			}// va tout droit

			if(isEqual(bestResult,t11) == true )
			{	
				turnLeft();
			}// tourne a gauche

			if(isEqual(bestResult,t13) == true )
			{	
				turnRigth();
			}// tourne a droite
		}
	} // fin if have obj == true

}// fin decide (pf) 
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::setPointFocal(int x , int y)
{
	// affichage du point de controle
	myPointFocalVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,2,2,32,0,0,0,0);
	SDL_FillRect(myPointFocalVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,204,101,0));
	myPointFocalVisualPosition.x= pointFocal.getX();
	myPointFocalVisualPosition.y= pointFocal.getY();
	SDL_BlitSurface(myPointFocalVisualSurface,NULL,whereIAmBlit,&myPointFocalVisualPosition);

	pointFocal.setX(x);
	pointFocal.setY(y);
	haveObjectif = true;

	// ?
	alignCount=0;

	SDL_FreeSurface(myPointFocalVisualSurface);

}// fin set point focal
//-----------------------------------------------------------------------------------------------------------------------------------
PointSim Vehicle::getPointForState(int actionForState)
{
	PointSim p;
	float angleTest;
	float correctAngle; 
	float vitesseForTest = 20;

	switch(actionForState)
	{
		case 1: 
			
			angleTest = angle + angleBraquage + 0.60 ;

			
			correctAngle = -angleTest ;

			// x2 = x1 + Distance * cos ( angle) 
			p.setX( pointA.getX() + ( vitesseForTest * cos ( correctAngle * PI / 180 ) ) );
			p.setY( pointA.getY() + ( vitesseForTest * sin ( correctAngle * PI / 180 ) ) );
		break;
		////////////////////////
		case 2: 

			//angleTest = angle + angleBraquage ;
			angleTest = angle  ;

			correctAngle = -angleTest ;

			// x2 = x1 + Distance * cos ( angle) 
			p.setX( pointA.getX() + ( vitesseForTest * cos ( correctAngle * PI / 180 ) ) );
			p.setY( pointA.getY() + ( vitesseForTest * sin ( correctAngle * PI / 180 ) ) );
		break;
		////////////////////////
		case 3: 

			angleTest = angle + angleBraquage - 0.60 ;


			correctAngle = -angleTest ;

			// x2 = x1 + Distance * cos ( angle) 
			p.setX( pointA.getX() + ( vitesseForTest * cos ( correctAngle * PI / 180 ) ) );
			p.setY( pointA.getY() + ( vitesseForTest * sin ( correctAngle * PI / 180 ) ) );
		break;
		////////////////////////
		default :
			p.setX(1);p.setY(1);
			fprintf (stderr,"- Error - enter default switch for decide fonction  \n" );
		break;
		////////////////////////
	}// fin switch

	return p;
}// fin get point for state
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::setObjectifToFalse()
{
	haveObjectif = false;
}// fin set obj to false
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::putMyControlPoint()
{
	myPointVisualPosition.x= pointA.getX();
	myPointVisualPosition.y= pointA.getY();

	SDL_BlitSurface(myPointVisualSurface,NULL,whereIAmBlit,&myPointVisualPosition);
}// fin put my control point
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::putMyFocalPoint()
{
	myPointFocalVisualPosition.x= pointFocal.getX();
	myPointFocalVisualPosition.y= pointFocal.getY();
	
	myPointFocalVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,2,2,32,0,0,0,0);
	SDL_FillRect(myPointFocalVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,204,101,0));
	
	SDL_BlitSurface(myPointFocalVisualSurface,NULL,whereIAmBlit,&myPointFocalVisualPosition);

	SDL_FreeSurface(myPointFocalVisualSurface);

}
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::setAutomaticalSpeed()
{
	/*  DEPRECATED */ 
	if(haveObjectif == true)
	{
		if(angleBraquage<=0.01 || angleBraquage>=-0.01)
		{
			if(vitesseVehicle<=0.8 && alignCount>1)
			{
				moveFoward();
			}

			if(alignCount<1 && vitesseVehicle<=0.2)
			{
				moveFoward();
			}
		}
		else
		{

			if( vitesseVehicle<=0.2)
			{
				moveFoward();
			}	
			else
			{
				stopSmooth();
			}
			
		}// else if angle braquage <= 0.02
	}// fin have obj
	else
	{
		stopSmooth();
	}
	
}// fin set automatical speed
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::setMyVue(VueEnvSim * v)
{
	m_Vue = v;
}// fin set my Vue
//-----------------------------------------------------------------------------------------------------------------------------------
float Vehicle::getDistance(PointSim a, PointSim b)
{
	float dist = sqrtf( ( a.getX() - b.getX() ) * ( a.getX() - b.getX() ) 
					+	   ( a.getY() - b.getY() ) * ( a.getY() - b.getY() )
			)/* fin racine*/;
	return dist;
}// fin get distance
//-----------------------------------------------------------------------------------------------------------------------------------
bool Vehicle::getIfIWannaBeDelete()
{
	return deleteMe;
}// fin get if i wanna be delete
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::setName(std::string n)
{
	name = n;
}// fin setName
//-----------------------------------------------------------------------------------------------------------------------------------
std::string Vehicle::getName()
{
	return name;
}// fin get Name
//-----------------------------------------------------------------------------------------------------------------------------------
float Vehicle::getDistanceToStop()
{
	float dist = 0;
	dist = 0;
	float tempSpeed = vitesseVehicle;

	if(vitesseVehicle>0)
		{
			while(tempSpeed>0)
				{
				dist += tempSpeed;
				tempSpeed = (tempSpeed + ( -accel * deltaT ) ) ;
				}// fin while
		}// fin if 

	return dist;
}// fin get distance to Stop
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::displaySpec()
{/* for emergency use only */
	cout << "- DISPLAY - Vehicle : " << name << endl;
	cout << "            Speed : " << vitesseVehicle << endl;
	cout << "            Angle : " << angleBraquage << endl << endl;
}// fin display spec
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::setCoord(float abs, float ord)
{
	pointA.setX(abs);
	pointA.setY(ord);
}// fin set coord
//-----------------------------------------------------------------------------------------------------------------------------------
PointSim Vehicle::getCoord()
{
	return pointA;
}// fin get Coord
//-----------------------------------------------------------------------------------------------------------------------------------
void Vehicle::setZoomLVL(float r)
{
	zoomLVL=zoomLVL*r;
	SDL_FreeSurface(myVisualSurface);
	// creation d'une surface (typeSurface, longeur, hauteur, type couleur , ?,?,?,?)
	myVisualSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,29*zoomLVL,12*zoomLVL,32,0,0,0,0);
	// coloration de la surface
	SDL_FillRect(myVisualSurface,NULL,SDL_MapRGB(whereIAmBlit->format,255,0,0));

	vitesseMAX=vitesseMAX*r;
	vitesseVehicle=vitesseVehicle*r;
	accel=accel*r;
}// fin set zoom LVL 
//-----------------------------------------------------------------------------------------------------------------------------------
