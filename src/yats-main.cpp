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
   
   
// TestRunConsolWin32Project.cpp : définit le point d'entrée pour l'application console.

#include "yats.h"
#include "InitialScreen.h"
  
using namespace std;

void testAccelerationConcept();
void testModifiedAccelerationConcept();
float convertMeterPerHourToMeterPerSec(float f);
float convertMeterToPix(float f);
void printEquation(float x1, float y1, float x2, float y2);
//void testFileSystemFunction();
//---------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	//////////
	// MAIN //
	//////////

	/*float nombre0 = 15;
    float nombre1 = 280;
    if (nombre0 > nombre1)
    {
        cout<<nombre0 << " >"<< nombre1 <<endl;
    }
    else
    {
        cout<<nombre0 << " <"<< nombre1 <<endl;
    }

	system("pause");*/
	//printEquation(140,0,20,60);
	//printEquation(20,60,80,10);
	//printEquation(80,10,170,2);
	//printEquation(90,15,120,26);

	// testAccelerationConcept(); 
	// testModifiedAccelerationConcept();
	//cout << convertMeterToPix(5) << endl; 

	// cout << convertMeterPerHourToMeterPerSec(10000) << endl; 
	// cout << convertMeterToPix( 13 ) << endl ; 
	// cout << convertMeterToPix( 27 ) << endl ; 
	// cout << convertMeterToPix( convertMeterPerHourToMeterPerSec(180000) )/40 << endl;
	// cout << convertMeterPerHourToMeterPerSec(10000) << endl;
	
	fprintf(stderr,"- System - Launching Yats. ( Yet Another Trafic Simulator ) \n");
	//InitialScreen *myScreen = 
	new InitialScreen();
    SDL_Quit();
	
	//testFileSystemFunction();

	//system("pause");

    return 0;
}
//---------------------------------------------------------------------------------------------------------
void testAccelerationConcept()
{
	/* Cas de la pierre jeter depuis la pont */
	const double dt = 0.5;     // frequence d'echantillonage en secondes
    const double accel = 9.81; // m/s²
    double speed = 0.0;        // m/s
    double position = 0.0;     // m
    double time;
	cout << "time  - speed - position " << endl;
    for (time = 0.0; time < 2.5; time += dt)   // Termine au bout de 2.5 secondes
    {
                
            position += (accel * dt * dt / 2.0) + speed * dt;
            speed += accel * dt;
			printf("%05.2f - %05.2f - %05.2f\n", time, speed, position);
    }
	system("pause");
}// fin test Acceleration Concept
//---------------------------------------------------------------------------------------------------------
void testModifiedAccelerationConcept()
{
	const double dt = 0.5;     // frequence d'echantillonage en secondes
    const double accel = 5; // m/s²
    double speed = 0.0;        // m/s
    double position = 0.0;     // m
    double time;
	cout << "time  - speed - position " << endl;
    for (time = 0.0; time < 2.5; time += dt)   // Termine au bout de 2.5 secondes
    {
                
            position += (accel * dt * dt / 2.0) + speed * dt;
			if(speed<50){speed += accel * dt;}else{/*nothing*/}
			printf("%05.2f - %05.2f - %05.2f\n", time, speed, position);
    }
	system("pause");
}// fin modified accelleration concept
//---------------------------------------------------------------------------------------------------------
float convertMeterPerHourToMeterPerSec(float f)
{
	float result = f /60/60;
	return result;
}// fin convertMeterPerHourToMeterPerSec(f)
//---------------------------------------------------------------------------------------------------------
float convertMeterToPix(float f)
{
	float result(0);
	result = (f*100) / 14;
	return result;
}// fin convert meter To pix
//---------------------------------------------------------------------------------------------------------
void printEquation(float x1, float y1, float x2, float y2)
{
	float a = (y2-y1)/(x2-x1);
	float b = y1 - ( x1 * a);

	cout << " y = " << a << " x + " << b << endl;

	system("pause");
}// fin print equation 
//---------------------------------------------------------------------------------------------------------


// originally done for windows systems
// to do: system independant functions
//~ void testFileSystemFunction()
//~ {
	//~ if( _mkdir( "\\testtmp" ) == 0 )// si le repertoire n'existe pas il est creer 
   //~ {
      //~ printf( "Directory '\\testtmp' was successfully created\n" );
      //~ system( "dir \\testtmp" );
      //~ if( _rmdir( "\\testtmp" ) == 0 )
        //~ printf( "Directory '\\testtmp' was successfully removed\n"  );
      //~ else
         //~ printf( "Problem removing directory '\\testtmp'\n" );
   //~ }
   //~ else // sinon rien il existe deja 
      //~ printf( "Problem creating directory '\\testtmp'\n" ); 
//~ }// fin test file system function
//---------------------------------------------------------------------------------------------------------
