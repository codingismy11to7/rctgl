/* 
 * Virginia Reel 3D
 * Simulates a ride on a Virginia Reel
 */

#include "vr3d.h"


/*
acceleration tests on virginia reel ride
when starting from station @ 4kph-1 - 500meters - 3:36:05 -3:39:40 (3:35 diff)
when going uphill starting @ 41kph-1 - 2.5 sec til stop
when going downhill 8kph to 41kph - 2.25 sec
lift speed - 8kph-1
no extra friction when going around turns
*/




/* -- main() --
 * This is where everything starts and ends. Get used to it.
 */
GLint oldmain(int argc, char *argv[])
{

	char tempfile[] = "uncomp.sv4";
	/* define the globals */
	StationColor[0] = 1;
	StationColor[1] = 0;
	StationColor[2] = 0;	/* make the station red */
	LiftColor[0] = 0;
	LiftColor[1] = 1;
	LiftColor[2] = 0;		/* make the lift green */
	TrackColor[0] = 0;
	TrackColor[1] = 0;
	TrackColor[2] = 1;	/* make the regular track blue */

	//tempfile = malloc(8);
	
	//*tempfile = "temp.td4";
	
	if(argc < 2)
	{
		printf("syntax: vr3d inputfile\n");
		exit(-1);
	}


	//pre-calc the track orientations
	// increasing through the array is like rotating counter-clockwise
	// decreasing through the array is like rotating clockwise
	TrackOrientationsRad[0] = 0.0f;
	TrackOrientationsRad[1] = 0.785f;
	TrackOrientationsRad[2] = 1.57f;
	TrackOrientationsRad[3] = 2.355f;
	TrackOrientationsRad[4] = 3.14f;
	TrackOrientationsRad[5] = 3.925f;
	TrackOrientationsRad[6] = 4.71f;
	TrackOrientationsRad[7] = 5.495f;

	TrackOrientationsDeg[0] = 0;
	TrackOrientationsDeg[1] = 45;
	TrackOrientationsDeg[2] = 90;
	TrackOrientationsDeg[3] = 135;
	TrackOrientationsDeg[4] = 180;
	TrackOrientationsDeg[5] = 225;
	TrackOrientationsDeg[6] = 270;
	TrackOrientationsDeg[7] = 315;
	

	printf("- decompressing file\n");
	DecompressFile(argv[1], tempfile);

	printf("- loading landscape\n");
	LoadLandscape(tempfile);

	//ReadTrackSetup(tempfile);
	

	/* initialize GLUT: register callbacks, etc */
	//wid = init_glut(&argc, argv);

	/* any OpenGL state initialization we need to do */
	glutInit ( &argc, argv );
	init ();
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode
	glutInitWindowSize ( 500, 500 ); // If glutFullScreen wasn't called this is the window size
	glutInitWindowPosition(10,10);
	glutCreateWindow ( "Virginia Reel Simulator" ); // Window Title (argv[0] for current directory as title)
	//glutFullScreen ( );          // Put Into Full Screen
	glutDisplayFunc ( display );  // Matching Earlier Functions To Their Counterparts
	glutReshapeFunc ( reshape );
	glutKeyboardFunc ( keyboard );
	glutSpecialFunc ( arrow_keys );
	glutIdleFunc ( display );
	glutMainLoop ( );          // Initialize The Main Loop

	return 0;
}


void menu(int value)
{
  switch (value)
  {
	case M_LOW_DETAIL:
		detailLevel = M_LOW_DETAIL;
		break;
	case M_MEDIUM_DETAIL:
		detailLevel = M_MEDIUM_DETAIL;
		break;
	case M_HIGH_DETAIL:
		detailLevel = M_HIGH_DETAIL;
		break;
	case M_PROTOTYPE_DETAIL_1:
		detailLevel = M_PROTOTYPE_DETAIL_1;
		break;
	case M_QUIT:
		exit(0);
  }
  glutPostRedisplay();
} 



GLint main(int argc, char *argv[])
{

	char tempfile[] = "uncomp.sv4";


	/* define the globals */
	StationColor[0] = 1;
	StationColor[1] = 0;
	StationColor[2] = 0;	/* make the station red */
	LiftColor[0] = 0;
	LiftColor[1] = 1;
	LiftColor[2] = 0;		/* make the lift green */
	TrackColor[0] = 0;
	TrackColor[1] = 0;
	TrackColor[2] = 1;	/* make the regular track blue */

	//tempfile = malloc(8);
	
	//*tempfile = "temp.td4";
	
	if(argc < 2)
	{
		printf("syntax: rct3d inputfile\n");
		exit(-1);
	}


	//pre-calc the track orientations
	// increasing through the array is like rotating counter-clockwise
	// decreasing through the array is like rotating clockwise
	TrackOrientationsRad[0] = 0.0f;
	TrackOrientationsRad[1] = M_PI * 0.25f;
	TrackOrientationsRad[2] = M_PI * 0.5f;
	TrackOrientationsRad[3] = M_PI * 0.75f;
	TrackOrientationsRad[4] = M_PI;
	TrackOrientationsRad[5] = M_PI * 1.25f;
	TrackOrientationsRad[6] = M_PI * 1.5f;
	TrackOrientationsRad[7] = M_PI * 1.75f;

	TrackOrientationsDeg[0] = 0;
	TrackOrientationsDeg[1] = 45;
	TrackOrientationsDeg[2] = 90;
	TrackOrientationsDeg[3] = 135;
	TrackOrientationsDeg[4] = 180;
	TrackOrientationsDeg[5] = 225;
	TrackOrientationsDeg[6] = 270;
	TrackOrientationsDeg[7] = 315;
	

	DecompressFile(argv[1], tempfile);

	LoadLandscape(tempfile);

	LoadTrees1(tempfile);

	LoadPaths(tempfile);

	LoadElements(tempfile);

	LoadRides(tempfile);

	//ReadTrackSetup(tempfile);
	

	/* initialize GLUT: register callbacks, etc */
	//wid = init_glut(&argc, argv);

	/* any OpenGL state initialization we need to do */

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(10, 10);
    glutInit(&argc, argv);
    glutCreateWindow("RCT3D");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
	glutSpecialFunc ( arrow_keys );
    glutReshapeFunc(reshape);
	glutPassiveMotionFunc(processMousePassiveMotion);
    //glutVisibilityFunc(visible);

    init();


	printf ( "GL_VENDOR    ='%s'\n", glGetString ( GL_VENDOR     ) ) ;
	printf ( "GL_RENDERER  ='%s'\n", glGetString ( GL_RENDERER   ) ) ;
	printf ( "GL_VERSION   ='%s'\n", glGetString ( GL_VERSION    ) ) ;
	printf ( "GL_EXTENSIONS='%s'\n", glGetString ( GL_EXTENSIONS ) ) ;


	glutCreateMenu(menu);
	glutAddMenuEntry("Lowest detail (no textures, only close objects)", M_LOW_DETAIL);
	glutAddMenuEntry("Medium detail (textures on close objects, close and tall objects)", M_MEDIUM_DETAIL);
	glutAddMenuEntry("High detail (all textures, all objects)", M_HIGH_DETAIL);
	glutAddMenuEntry("Quit", M_QUIT);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
    return 0;
} 


void ourPrintString(void *font, char *str)
{
   int i,l=strlen(str);

   for(i=0;i<l;i++)
      glutBitmapCharacter(font,*str++);
}



