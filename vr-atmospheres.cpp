#include "resource.h"
#include "vr3d.h"

float edgeLighting[4][4];
float blendSettings[4];

void initAtmosphere(int atmosphereID)
{
	float ambientLight[4];
	float lightPos[4];

	switch(atmosphereID)
	{
	case MENU_ENV_ORIGINAL:
		/*
		ambientLight[0] = 0.75f;
		ambientLight[1] = 0.75f;
		ambientLight[2] = 0.75f;
		ambientLight[3] = 1.0f;
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);

		lightPos[0] = 0.0f;
		lightPos[1] = 300.0f;
		lightPos[2] = 1000.0f;
		lightPos[3] = 1.0f;
		glLightfv(GL_LIGHT1, GL_POSITION,lightPos);
		*/

		edgeLighting[0][0] = 0.70f;
		edgeLighting[0][1] = 0.70f;
		edgeLighting[0][2] = 0.70f;
		edgeLighting[0][3] = 0.70f;
		
		edgeLighting[1][0] = 0.80f;
		edgeLighting[1][1] = 0.80f;
		edgeLighting[1][2] = 0.80f;
		edgeLighting[1][3] = 0.80f;

		edgeLighting[2][0] = 1.0f;
		edgeLighting[2][1] = 1.0f;
		edgeLighting[2][2] = 1.0f;
		edgeLighting[2][3] = 1.0f;

		edgeLighting[3][0] = 0.95f;
		edgeLighting[3][1] = 0.95f;
		edgeLighting[3][2] = 0.95f;
		edgeLighting[3][3] = 0.95f;

		blendSettings[0] = 1.0f;
		blendSettings[1] = 1.0f;
		blendSettings[2] = 1.0f;
		blendSettings[3] = 0.0f;

		//init_lightsource();

		//glEnable(

		break;
	case MENU_ENV_SUNNY:
		edgeLighting[0][0] = 1.0f;
		edgeLighting[0][1] = 1.0f;
		edgeLighting[0][2] = 1.0f;
		edgeLighting[0][3] = 0.0f;
		
		edgeLighting[1][0] = 0.90f;
		edgeLighting[1][1] = 0.90f;
		edgeLighting[1][2] = 0.90f;
		edgeLighting[1][3] = 0.90f;

		edgeLighting[2][0] = 0.6f;
		edgeLighting[2][1] = 0.6f;
		edgeLighting[2][2] = 0.6f;
		edgeLighting[2][3] = 0.6f;

		edgeLighting[3][0] = 0.75f;
		edgeLighting[3][1] = 0.75f;
		edgeLighting[3][2] = 0.75f;
		edgeLighting[3][3] = 0.75f;

		blendSettings[0] = 1.0f;
		blendSettings[1] = 1.0f;
		blendSettings[2] = 1.0f;
		blendSettings[3] = 0.0f;

		break;
	case MENU_ENV_CLOUDY:
		edgeLighting[0][0] = 0.7f;
		edgeLighting[0][1] = 0.7f;
		edgeLighting[0][2] = 0.7f;
		edgeLighting[0][3] = 0.7f;
		
		edgeLighting[1][0] = 0.9f;
		edgeLighting[1][1] = 0.9f;
		edgeLighting[1][2] = 0.9f;
		edgeLighting[1][3] = 0.9f;

		edgeLighting[2][0] = 0.8f;
		edgeLighting[2][1] = 0.8f;
		edgeLighting[2][2] = 0.8f;
		edgeLighting[2][3] = 0.8f;

		edgeLighting[3][0] = 0.75f;
		edgeLighting[3][1] = 0.75f;
		edgeLighting[3][2] = 0.75f;
		edgeLighting[3][3] = 0.75f;

		blendSettings[0] = 0.2f;
		blendSettings[1] = 0.2f;
		blendSettings[2] = 0.4f;
		blendSettings[3] = 0.2f;

		break;
	case MENU_ENV_STORMY:
		edgeLighting[0][0] = 1.0f;
		edgeLighting[0][1] = 1.0f;
		edgeLighting[0][2] = 1.0f;
		edgeLighting[0][3] = 0.0f;
		
		edgeLighting[1][0] = 0.80f;
		edgeLighting[1][1] = 0.80f;
		edgeLighting[1][2] = 0.80f;
		edgeLighting[1][3] = 0.80f;

		edgeLighting[2][0] = 0.7f;
		edgeLighting[2][1] = 0.7f;
		edgeLighting[2][2] = 0.7f;
		edgeLighting[2][3] = 0.7f;

		edgeLighting[3][0] = 0.9f;
		edgeLighting[3][1] = 0.9f;
		edgeLighting[3][2] = 0.9f;
		edgeLighting[3][3] = 0.9f;

		blendSettings[0] = 0.6f;
		blendSettings[1] = 0.4f;
		blendSettings[2] = 0.2f;
		blendSettings[3] = 0.2f;

		break;
	case MENU_ENV_OCEAN:
		edgeLighting[0][0] = 0.8f;
		edgeLighting[0][1] = 0.8f;
		edgeLighting[0][2] = 0.8f;
		edgeLighting[0][3] = 0.8f;
		
		edgeLighting[1][0] = 1.0f;
		edgeLighting[1][1] = 1.0f;
		edgeLighting[1][2] = 1.0f;
		edgeLighting[1][3] = 1.0f;

		edgeLighting[2][0] = 0.8f;
		edgeLighting[2][1] = 0.8f;
		edgeLighting[2][2] = 0.8f;
		edgeLighting[2][3] = 0.8f;

		edgeLighting[3][0] = 0.65f;
		edgeLighting[3][1] = 0.65f;
		edgeLighting[3][2] = 0.65f;
		edgeLighting[3][3] = 0.65f;

		blendSettings[0] = 0.6f;
		blendSettings[1] = 0.4f;
		blendSettings[2] = 0.2f;
		blendSettings[3] = 0.1f;
		break;
	}
}