/***********************************************************************************
* Contient toutes les fonctons nécessaire pour calculer le nombre d'images/seconde *
************************************************************************************/


__int64 startclock, endclock;  
float rate_inv;
float curFPS, frametime, framestart, frameend; 


// ***********************************************************************
bool Init_FPS(void) // Pour initialiser le compteur 
{
	__int64 rate;
	if( !QueryPerformanceFrequency((LARGE_INTEGER*)&rate) ) 
		return false; 

	if( !rate ) 
		return false;

	rate_inv=float(1.0)/rate;
	if( !QueryPerformanceCounter((LARGE_INTEGER*)&startclock) ) 
		return false; 
	
	return true; // Si on arrive ici, ça marche ! :)

}


// ***********************************************************************
float Prendre_1er_Temps(void) // Pour avoir le 1 er temps
{
	// En divisant le rate, on a les secondes
	QueryPerformanceCounter( (LARGE_INTEGER*)&endclock );
	
	return (float)(endclock - startclock) * rate_inv;

}


// ***********************************************************************
void Compteur_FPS_Tourne() // Le compteur tourne ...
{
	do 
		{
			frameend = Prendre_1er_Temps();  
		}
	while(frameend == framestart);
	
	frametime = frameend - framestart; 
    framestart = frameend;
    
	curFPS = float(1.0) / frametime; // curFPS = nombre d'images par seconde. C'est ce qu'il
									 // faut afficher à l'écran

}


//*************************
// Fin du fichier "Fps.h" *
//*************************