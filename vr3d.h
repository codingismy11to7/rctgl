#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
//#include <glut.h>
//#include <afxdlgs.h>
#include <string.h>
#include <vector>

using namespace std;

#include "f:\dxsdk\include\dinput.h"

#include "bbVertex.h"

//#using <mscorlib.dll>
//#using <System.dll>
//#using <System.Drawing.dll>
//#using <System.Windows.Forms.dll>


#include <GL\gl.h>
#include <GL\glu.h>
//#include <GL\glut.h>
#include <GL\glaux.h>

#include "f:/fmod/api/inc/fmod.h"
#include "f:/fmod/api/inc/fmod_errors.h"

#define MULTIPLER 10	/* basic multiplier to make objects larger */

#define UNITWIDTH 3.2	/* each tile has 10 m^2 area */
#define UNITHEIGHT 1.3	/* each 'unit' is 1 1/3 meters tall*/

#define RIDEOFFSETHEIGHT 0.1

#define LOW_CIRCLE_SEGMENTS 2
#define MEDIUM_CIRCLE_SEGMENTS 4
#define HIGH_CIRCLE_SEGMENTS 8
#define TRACK_WIDTH 1.6	/* percentage of one unit */

#define VPD_MIN     200
#define VPD_DEFAULT 256
#define VPD_MAX     4000

#define TARGET_FPS 25
#define FRAME_INTERVAL 40

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define VIRGINIA_REEL_TRACK_WIDTH 1.6
#define VIRGINIA_REEL_RAIL_HEIGHT 0.5

#define FRAME_RATE_SAMPLES 10

#define LOW_DETAIL_DISTANCE 30.0
#define MEDIUM_DETAIL_DISTANCE 15.0

#define ELEMENT_DEPTH	30
#define TREE_DEPTH		5
#define PATH_DEPTH		10

#define TEXTURE_GRASS1	5
//#define TEXTURE_GRASS2	1

//#define TEXTURE_WOOD1	2
//#define TEXTURE_WOOD2	3

//#define TEXTURE_BRICK1	4
//#define TEXTURE_BRICK2	5

#define TEXTURE_DIRT1	6
#define TEXTURE_SAND1	7
#define TEXTURE_GRAVEL1	8
#define TEXTURE_JUNGLE1	9
#define TEXTURE_ROOFING1 10
#define TEXTURE_CHECKER1 11
#define TEXTURE_MARS1 12

#define TEXTURE_GREEN1 13
#define TEXTURE_PURPLE1 14
#define TEXTURE_YELLOW1 15
#define TEXTURE_RED1 16

#define TEXTURE_GREYROOF1 17
#define TEXTURE_IRONROOF1 18
#define TEXTURE_LOGROOF1 19
#define TEXTURE_ICETOP1 20

//standard edge textures
#define TEXTURE_WOODWALL1 21
#define TEXTURE_BRICKWALL1 22
#define TEXTURE_DIRTWALL1 23
#define TEXTURE_IRONWALL1 24
#define TEXTURE_BLACKWALL1 25
#define TEXTURE_GREYWALL1 26
#define TEXTURE_YELLOWWALL1 27
#define TEXTURE_REDWALL1 28

//extended edge textures
#define TEXTURE_ICEWALL1 29
#define TEXTURE_PURPLEWALL1 30
#define TEXTURE_GREENWALL1 31
#define TEXTURE_BROWNSTONEWALL1 32
#define TEXTURE_GRAYSTONEWALL1 33
#define TEXTURE_SKYSCRAPERAWALL1 34
#define TEXTURE_SKYSCRAPERBWALL1 35

#define TEXTURE_WATER1 36

#define TEXTURE_SKYUP 50
#define TEXTURE_SKYDOWN 51
#define TEXTURE_SKYLEFT 52
#define TEXTURE_SKYRIGHT 53
#define TEXTURE_SKYFRONT 54
#define TEXTURE_SKYBACK 55

#define TEXTURE_PARKGATE 56

#define TEXTURE_SKYDOME 57

//textures 100-299 are whole-tile trees
#define TEXTURE_TREE_00_1 100
#define TEXTURE_TREE_00_2 101
#define TEXTURE_TREE_01_1 102
#define TEXTURE_TREE_01_2 103
#define TEXTURE_TREE_02_1 104
#define TEXTURE_TREE_02_2 105
#define TEXTURE_TREE_03_1 106
#define TEXTURE_TREE_03_2 107
#define TEXTURE_TREE_04_1 108
#define TEXTURE_TREE_04_2 109
#define TEXTURE_TREE_05_1 110
#define TEXTURE_TREE_05_2 111
#define TEXTURE_TREE_06_1 112
#define TEXTURE_TREE_06_2 113
#define TEXTURE_TREE_07_1 114
#define TEXTURE_TREE_07_2 115
#define TEXTURE_TREE_0F_1 116
#define TEXTURE_TREE_0F_2 117
#define TEXTURE_TREE_11_1 118
#define TEXTURE_TREE_11_2 119
#define TEXTURE_TREE_12_1 120
#define TEXTURE_TREE_12_2 121
#define TEXTURE_TREE_13_1 122
#define TEXTURE_TREE_13_2 123
#define TEXTURE_TREE_14_1 124
#define TEXTURE_TREE_14_2 125
#define TEXTURE_TREE_16_1 126
#define TEXTURE_TREE_16_2 127
#define TEXTURE_TREE_18_1 128
#define TEXTURE_TREE_18_2 129
#define TEXTURE_TREE_19_1 130
#define TEXTURE_TREE_19_2 131
#define TEXTURE_TREE_1A_1 132
#define TEXTURE_TREE_1A_2 133
#define TEXTURE_TREE_1B_1 134
#define TEXTURE_TREE_1B_2 135
#define TEXTURE_TREE_1C_1 136
#define TEXTURE_TREE_1C_2 137
#define TEXTURE_TREE_1D_1 138
#define TEXTURE_TREE_1D_2 139
#define TEXTURE_TREE_1E_1 140
#define TEXTURE_TREE_1E_2 141
#define TEXTURE_TREE_1F_1 142
#define TEXTURE_TREE_1F_2 143
#define TEXTURE_TREE_20_1 144
#define TEXTURE_TREE_20_2 145
#define TEXTURE_TREE_21_1 146
#define TEXTURE_TREE_21_2 147
#define TEXTURE_TREE_22_1 148
#define TEXTURE_TREE_22_2 149
#define TEXTURE_TREE_24_1 150
#define TEXTURE_TREE_24_2 151
#define TEXTURE_TREE_25_1 152
#define TEXTURE_TREE_25_2 153
#define TEXTURE_TREE_26_1 154
#define TEXTURE_TREE_26_2 155
#define TEXTURE_TREE_27_1 156
#define TEXTURE_TREE_27_2 157
#define TEXTURE_TREE_28_1 158
#define TEXTURE_TREE_28_2 159
#define TEXTURE_TREE_29_1 160
#define TEXTURE_TREE_29_2 161
#define TEXTURE_TREE_2A_1 162
#define TEXTURE_TREE_2A_2 163
#define TEXTURE_TREE_34_1 164
#define TEXTURE_TREE_34_2 165
#define TEXTURE_TREE_36_1 166
#define TEXTURE_TREE_36_2 167
#define TEXTURE_TREE_37_1 168
#define TEXTURE_TREE_37_2 169
#define TEXTURE_TREE_66_1 170
#define TEXTURE_TREE_66_2 171
#define TEXTURE_TREE_77_1 172
#define TEXTURE_TREE_77_2 173
#define TEXTURE_TREE_80_1 174
#define TEXTURE_TREE_80_2 175
#define TEXTURE_TREE_81_1 176
#define TEXTURE_TREE_81_2 177
#define TEXTURE_TREE_82_1 178
#define TEXTURE_TREE_82_2 179
#define TEXTURE_TREE_83_1 180
#define TEXTURE_TREE_83_2 181
#define TEXTURE_TREE_84_1 182
#define TEXTURE_TREE_84_2 183
#define TEXTURE_TREE_97_1 184
#define TEXTURE_TREE_98_1 185
#define TEXTURE_TREE_9E_1 186
#define TEXTURE_TREE_9F_1 187
#define TEXTURE_TREE_A3_1 188


#define TEXTURE_TREE_AC		200
#define TEXTURE_TREE_AD		201
#define TEXTURE_TREE_AE		202
#define TEXTURE_TREE_AF		203
#define TEXTURE_TREE_B0		204
#define TEXTURE_TREE_B1		205
#define TEXTURE_TREE_B2		206

#define TEXTURE_TREE_41		207
#define TEXTURE_TREE_42		208
#define TEXTURE_TREE_43		209
#define TEXTURE_TREE_44		210
#define TEXTURE_TREE_45		211
#define TEXTURE_TREE_46		212
#define TEXTURE_TREE_47		213
#define TEXTURE_TREE_48		214
#define TEXTURE_TREE_49		215
#define TEXTURE_TREE_4A		216
#define TEXTURE_TREE_4B		217
#define TEXTURE_TREE_4C		218
#define TEXTURE_TREE_4D		219


//textures 300-499 are path textures
/* texture definition prefix list
 * 00 - blue queue
 * 01 - red queue
 * 02 - yellow queue
 * 03 - green queue
 * 04 - gray tarmac
 * 05 - red tarmac
 * 06 - brown tarmac
 * 07 - green tarmac
 * 08 - beige tile
 * 09 - grey tile
 * 0A - red tile
 * 0B - green tile
 * 0C - crazy tile
 * 0D - dirt
 * 0E - black dirt
 */

/* texture definition suffix list
 * 00 - no connections
 * 01 - N
 * 02 - E
 * 03 - S
 * 04 - W
 * 05 - N, E
 * 06 - N, E, NE
 * 07 - N, S
 * 08 - N, W
 * 09 - N, W, NW
 * 0A - E, S
 * 0B - E, S, SE
 * 0C - E, W
 * 0D - S, W
 * 0E - S, W, SW
 * 0F - all
 */
// queues only need certain textures
#define TEXTURE_PATH_00_00 300
#define TEXTURE_PATH_00_05 301
#define TEXTURE_PATH_00_07 302

#define TEXTURE_PATH_01_00 303
#define TEXTURE_PATH_01_05 304
#define TEXTURE_PATH_01_07 305

#define TEXTURE_PATH_02_00 306
#define TEXTURE_PATH_02_05 307
#define TEXTURE_PATH_02_07 308

#define TEXTURE_PATH_03_00 309
#define TEXTURE_PATH_03_05 310
#define TEXTURE_PATH_03_07 311

#define TEXTURE_PATH_04_00 312
#define TEXTURE_PATH_04_01 313
#define TEXTURE_PATH_04_05 314
#define TEXTURE_PATH_04_07 315
#define TEXTURE_PATH_04_0B 316
#define TEXTURE_PATH_04_0C 317
#define TEXTURE_PATH_04_10 318
#define TEXTURE_PATH_04_14 319
#define TEXTURE_PATH_04_15 320
#define TEXTURE_PATH_04_19 321
#define TEXTURE_PATH_04_1D 322
#define TEXTURE_PATH_04_20 323
#define TEXTURE_PATH_04_21 324
#define TEXTURE_PATH_04_22 325
#define TEXTURE_PATH_04_23 326
#define TEXTURE_PATH_04_27 327


#define TEXTURE_PATH_05_00 330
#define TEXTURE_PATH_05_01 331
#define TEXTURE_PATH_05_05 332
#define TEXTURE_PATH_05_07 333
#define TEXTURE_PATH_05_0B 334
#define TEXTURE_PATH_05_0C 335
#define TEXTURE_PATH_05_10 336
#define TEXTURE_PATH_05_14 337
#define TEXTURE_PATH_05_15 338
#define TEXTURE_PATH_05_19 339
#define TEXTURE_PATH_05_1D 340
#define TEXTURE_PATH_05_20 341
#define TEXTURE_PATH_05_21 342
#define TEXTURE_PATH_05_22 343
#define TEXTURE_PATH_05_23 344
#define TEXTURE_PATH_05_27 345

#define TEXTURE_PATH_06_00 350
#define TEXTURE_PATH_06_01 351
#define TEXTURE_PATH_06_05 352
#define TEXTURE_PATH_06_07 353
#define TEXTURE_PATH_06_0B 354
#define TEXTURE_PATH_06_0C 355
#define TEXTURE_PATH_06_10 356
#define TEXTURE_PATH_06_14 357
#define TEXTURE_PATH_06_15 358
#define TEXTURE_PATH_06_19 359
#define TEXTURE_PATH_06_1D 360
#define TEXTURE_PATH_06_20 361
#define TEXTURE_PATH_06_21 362
#define TEXTURE_PATH_06_22 363
#define TEXTURE_PATH_06_23 364
#define TEXTURE_PATH_06_27 365

#define TEXTURE_PATH_07_00 370
#define TEXTURE_PATH_07_01 371
#define TEXTURE_PATH_07_05 372
#define TEXTURE_PATH_07_07 373
#define TEXTURE_PATH_07_0B 374
#define TEXTURE_PATH_07_0C 375
#define TEXTURE_PATH_07_10 376
#define TEXTURE_PATH_07_14 377
#define TEXTURE_PATH_07_15 378
#define TEXTURE_PATH_07_19 379
#define TEXTURE_PATH_07_1D 380
#define TEXTURE_PATH_07_20 381
#define TEXTURE_PATH_07_21 382
#define TEXTURE_PATH_07_22 383
#define TEXTURE_PATH_07_23 384
#define TEXTURE_PATH_07_27 385

#define TEXTURE_PATH_08_00 390
#define TEXTURE_PATH_08_01 391
#define TEXTURE_PATH_08_05 392
#define TEXTURE_PATH_08_07 393
#define TEXTURE_PATH_08_0B 394
#define TEXTURE_PATH_08_0C 395
#define TEXTURE_PATH_08_10 396
#define TEXTURE_PATH_08_14 397
#define TEXTURE_PATH_08_15 398
#define TEXTURE_PATH_08_19 399
#define TEXTURE_PATH_08_1D 400
#define TEXTURE_PATH_08_20 401
#define TEXTURE_PATH_08_21 402
#define TEXTURE_PATH_08_22 403
#define TEXTURE_PATH_08_23 404
#define TEXTURE_PATH_08_27 405

#define TEXTURE_PATH_09_00 410
#define TEXTURE_PATH_09_01 411
#define TEXTURE_PATH_09_05 412
#define TEXTURE_PATH_09_07 413
#define TEXTURE_PATH_09_0B 414
#define TEXTURE_PATH_09_0C 415
#define TEXTURE_PATH_09_10 416
#define TEXTURE_PATH_09_14 417
#define TEXTURE_PATH_09_15 418
#define TEXTURE_PATH_09_19 419
#define TEXTURE_PATH_09_1D 420
#define TEXTURE_PATH_09_20 421
#define TEXTURE_PATH_09_21 422
#define TEXTURE_PATH_09_22 423
#define TEXTURE_PATH_09_23 424
#define TEXTURE_PATH_09_27 425

#define TEXTURE_PATH_0A_00 430
#define TEXTURE_PATH_0A_01 431
#define TEXTURE_PATH_0A_05 432
#define TEXTURE_PATH_0A_07 433
#define TEXTURE_PATH_0A_0B 434
#define TEXTURE_PATH_0A_0C 435
#define TEXTURE_PATH_0A_10 436
#define TEXTURE_PATH_0A_14 437
#define TEXTURE_PATH_0A_15 438
#define TEXTURE_PATH_0A_19 439
#define TEXTURE_PATH_0A_1D 440
#define TEXTURE_PATH_0A_20 441
#define TEXTURE_PATH_0A_21 442
#define TEXTURE_PATH_0A_22 443
#define TEXTURE_PATH_0A_23 444
#define TEXTURE_PATH_0A_27 445

#define TEXTURE_PATH_0B_00 450
#define TEXTURE_PATH_0B_01 451
#define TEXTURE_PATH_0B_05 452
#define TEXTURE_PATH_0B_07 453
#define TEXTURE_PATH_0B_0B 454
#define TEXTURE_PATH_0B_0C 455
#define TEXTURE_PATH_0B_10 456
#define TEXTURE_PATH_0B_14 457
#define TEXTURE_PATH_0B_15 458
#define TEXTURE_PATH_0B_19 459
#define TEXTURE_PATH_0B_1D 460
#define TEXTURE_PATH_0B_20 461
#define TEXTURE_PATH_0B_21 462
#define TEXTURE_PATH_0B_22 463
#define TEXTURE_PATH_0B_23 464
#define TEXTURE_PATH_0B_27 465

#define TEXTURE_PATH_0C_00 470
#define TEXTURE_PATH_0C_01 471
#define TEXTURE_PATH_0C_05 472
#define TEXTURE_PATH_0C_07 473
#define TEXTURE_PATH_0C_0B 474
#define TEXTURE_PATH_0C_0C 475
#define TEXTURE_PATH_0C_10 476
#define TEXTURE_PATH_0C_14 477
#define TEXTURE_PATH_0C_15 478
#define TEXTURE_PATH_0C_19 479
#define TEXTURE_PATH_0C_1D 480
#define TEXTURE_PATH_0C_20 481
#define TEXTURE_PATH_0C_21 482
#define TEXTURE_PATH_0C_22 483
#define TEXTURE_PATH_0C_23 484
#define TEXTURE_PATH_0C_27 485

#define TEXTURE_PATH_0D_00 490
#define TEXTURE_PATH_0D_01 491
#define TEXTURE_PATH_0D_05 492
#define TEXTURE_PATH_0D_07 493
#define TEXTURE_PATH_0D_0B 494
#define TEXTURE_PATH_0D_0C 495
#define TEXTURE_PATH_0D_10 496
#define TEXTURE_PATH_0D_14 497
#define TEXTURE_PATH_0D_15 498
#define TEXTURE_PATH_0D_19 499
#define TEXTURE_PATH_0D_1D 500
#define TEXTURE_PATH_0D_20 501
#define TEXTURE_PATH_0D_21 502
#define TEXTURE_PATH_0D_22 503
#define TEXTURE_PATH_0D_23 504
#define TEXTURE_PATH_0D_27 505

#define TEXTURE_PATH_0E_00 510
#define TEXTURE_PATH_0E_01 511
#define TEXTURE_PATH_0E_05 512
#define TEXTURE_PATH_0E_07 513
#define TEXTURE_PATH_0E_0B 514
#define TEXTURE_PATH_0E_0C 515
#define TEXTURE_PATH_0E_10 516
#define TEXTURE_PATH_0E_14 517
#define TEXTURE_PATH_0E_15 518
#define TEXTURE_PATH_0E_19 519
#define TEXTURE_PATH_0E_1D 520
#define TEXTURE_PATH_0E_20 521
#define TEXTURE_PATH_0E_21 522
#define TEXTURE_PATH_0E_22 523
#define TEXTURE_PATH_0E_23 524
#define TEXTURE_PATH_0E_27 525


//here are the ride textures
#define TEXTURE_RIDE_05_00 600
#define TEXTURE_RIDE_LOGLIFT 601
#define TEXTURE_RIDE_ENT1	602
#define TEXTURE_RIDE_ENT2	603
#define TEXTURE_RIDE_ENT3	604
#define TEXTURE_RIDE_0B_00 605
#define TEXTURE_RIDE_32_00 606
#define TEXTURE_RIDE_04_00 607
#define TEXTURE_RIDE_04_01 608
#define TEXTURE_RIDE_11_00 609
#define TEXTURE_RIDE_11_01 610
#define TEXTURE_RIDE_00_00 611
#define TEXTURE_RIDE_00_01 612
#define TEXTURE_RIDE_00_02 613
#define TEXTURE_RIDE_12_00 614
#define TEXTURE_RIDE_06_00 615
#define TEXTURE_RIDE_06_01 616
#define TEXTURE_RIDE_06_02 617
#define TEXTURE_RIDE_0F_00 618
#define TEXTURE_RIDE_0F_01 619
#define TEXTURE_RIDE_0C_00 620
#define TEXTURE_RIDE_09_00 621
#define TEXTURE_RIDE_36_00 622
#define TEXTURE_RIDE_36_01 623
#define TEXTURE_RIDE_3B_00 624

//here are the wall textures
#define TEXTURE_WALL_00 700
#define TEXTURE_WALL_01 701
#define TEXTURE_WALL_02 702
#define TEXTURE_WALL_03 703
#define TEXTURE_WALL_04 704
#define TEXTURE_WALL_05 705
#define TEXTURE_WALL_06 706
#define TEXTURE_WALL_07 707
#define TEXTURE_WALL_08 708
#define TEXTURE_WALL_09 709
#define TEXTURE_WALL_10 710
#define TEXTURE_WALL_11 711
#define TEXTURE_WALL_12 712
#define TEXTURE_WALL_13 713
#define TEXTURE_WALL_14 714
#define TEXTURE_WALL_15 715
#define TEXTURE_WALL_16 716
#define TEXTURE_WALL_17 717
#define TEXTURE_WALL_18 718
#define TEXTURE_WALL_19 719
#define TEXTURE_WALL_1A 720
#define TEXTURE_WALL_1B 721
#define TEXTURE_WALL_1C 722
#define TEXTURE_WALL_20 723
#define TEXTURE_WALL_21 724
#define TEXTURE_WALL_22 725
#define TEXTURE_WALL_23 726
#define TEXTURE_WALL_24 727
#define TEXTURE_WALL_25 728
#define TEXTURE_WALL_26 729
#define TEXTURE_WALL_27 730
#define TEXTURE_WALL_28 731
#define TEXTURE_WALL_29 732
#define TEXTURE_WALL_2A 733
#define TEXTURE_WALL_2B 734
#define TEXTURE_WALL_2C 735
#define TEXTURE_WALL_30 736
#define TEXTURE_WALL_31 737
#define TEXTURE_WALL_32 738
#define TEXTURE_WALL_33 739
#define TEXTURE_WALL_34 740
#define TEXTURE_WALL_35 741
#define TEXTURE_WALL_36 742
#define TEXTURE_WALL_37 743
#define TEXTURE_WALL_38 744
#define TEXTURE_WALL_39 745
#define TEXTURE_WALL_3A 746
#define TEXTURE_WALL_3B 747
#define TEXTURE_WALL_3C 748





//#define TEXTURE_WALL_28 707


#define NUMTEXTURES		800

//#define LANDSCAPE_LIST 0


typedef struct {
	int TrackType;
	float x;
	float y;
	float z;
	int Modifier;
} TrackStructType;



typedef struct {
	int identity;
	int x;
	int z;
	float ceiling;
	float base;
	bool NWquad, NEquad, SEquad, SWquad;
	bool quarterItem;
} TreeStructType;


typedef struct {
	int identity;
	int x;
	int z;
	float ceiling;
	float base;
	int elementIndex;
} BigSceneryStructType;



typedef struct {
	int isLift;
	int identity;
	int x;
	int z;
	float ceiling;
	float base;
	int elementIndex;
	int rideIndex;
	int baseColor;
	int elementOrientation;
	bool flyingInverted;
	bool wasDrawn;

} ElementStructType;




typedef struct {
	unsigned char rideType;
	int vehicleType;
	int operatingMode;
	int PrimaryColor[4];
	int SupportColor[4];
	int SecondaryColor[4];
	int nameStringOffset;
} RideStructType;




typedef struct {
	int pathType;	//0 queue, 1 tarmac, 2 dirt, 3 crazy tile
					//4 roads, 5 tile
	int pathModifier;
	int x;
	int z;
	float ceiling;
	float base;
	int connectN, connectS, connectE, connectW;
	int connectNW, connectNE, connectSE, connectSW;
	int queueEntry;
	int pathSlope;	//0 flat, 4 up West, 5 up North
					//6 up East, 7 up South
	int rideIndex;
	bool wasDrawn;

} PathStructType;

typedef struct {
	int wallTypeN;
	int wallTypeS;
	int wallTypeE;
	int wallTypeW;
	int x;
	int z;
	float ceiling;
	float base;
	char direction;
	bool wasDrawn;
} WallStructType;

typedef struct {
	int TL, TR, BL, BR;
	int waterlevel;
	int type;
	int toptexture;
	int sidetexture;
	int LLmodifierS, LLmodifierE;
} landscape_t;

typedef struct {
	int TL, TR, BL, BR;
	int waterlevel;
	int type;
	int toptexture;
	int sidetexture;
	int LLmodifierS, LLmodifierE;
	int lowest, highest;
} LandscapeStructType;

enum entranceTypes {parkEnt, rideEnt, rideExit};

typedef struct {
	int x, z;
	float base;
	int pathType;
	entranceTypes entranceType;
	int elementIndex;
	int rideIndex;	
} EntranceStructType;

enum audioTypes {CD, fileAmbient, fileEvent, fileEffect};
enum soundTypes {posititonal, ambient};

typedef struct {
	audioTypes audioType;
	int trackNum;
	int volume;
	//int minX, maxX;
	//int minY, maxY;

	char fileName[128];

	//point that ride vehicle has to hit to trigger sound
	int triggerX, triggerY, triggerZ;
	int triggerRideIndex;

	//min/max time until next occurance of sound
	int minTime, maxTime;

	soundTypes soundType;

	int sourceX, sourceY, sourceZ;
} AudioStructType;


typedef struct {
	char parkName[256];
	
	LandscapeStructType landscape[128][128];
	vector <TrackStructType> tracks[128][128];
	vector <TreeStructType> trees[128][128];
	vector <ElementStructType> elements[128][128];
	vector <RideStructType> rides;
	vector <PathStructType> paths[128][128];
	vector <WallStructType> walls[128][128];
	vector <EntranceStructType> entrances[128][128];
	vector <BigSceneryStructType> bigScenery[128][128];

	/*
	int trackCount[128][128];
	int treeCount[128][128];
	int elementCount[128][128];
	int pathCount[128][128];
	int wallCount[128][128];
	int entranceCount[128][128];
	int bigSceneryCount[128][128];
	*/

	char nameStrings[1024][32];

	int audioSubscriptions[128][128][10];

	int parkEntranceX, parkEntranceY, parkEntranceZ;
	float peepStartX, peepStartY, peepStartZ;

} ParkStructType;

extern ParkStructType thePark;


extern TreeStructType TreeList[15876]; //make a 126x126 array

extern AudioStructType AudioSpecifiers[256];

extern int AudioSpecifierCount;

extern int TreeListSize;


extern PathStructType PathList[15876]; //make a 126x126 array
extern int PathListSize;

extern ElementStructType ElementList[15876]; //make a 126x126 array
extern int ElementListSize;

extern RideStructType RideList[256]; 
extern int RideListSize;

//extern GLint wid;
extern unsigned int sceneID;

extern int FileFormat;		/* indicates whether data is in RCT format (0)
					   or CF/LL format (1) */

extern int StationColor[3];	/* make the station red */
extern int LiftColor[3];		/* make the lift green */
extern int TrackColor[3];	/* make the regular track blue */

//extern GLuint sceneID;

//extern GLint wid;

//extern char *tempfile;

extern GLint wid, /* GLUT window id               */
      vpd; /* (square) viewport dimensions */





/* Globals */
extern char RCTGL_Location[256];
extern char RCTGL_TempFile[256];
extern char RCTGL_InFile[256];

extern float	rtri;
extern float	rquad;

extern int TrackOrientationsDeg[8];
extern float TrackOrientationsRad[8];

extern int TOrientation;		// track orientation. used when drawing the track
extern int TOrientationOrig;	// track orientation. used when drawing the track

extern int TrackLength;
extern int TrackLayout[500];
extern TrackStructType TrackSetup[500];

extern float XV, YV, ZV;
extern float XR, YR, ZR;

extern float xWaterOffset;
extern float zWaterOffset;

extern int FrameCount;
extern float FrameRate;

extern int wd,hd;

/* display lists */
extern GLuint LANDSCAPE_LIST;


extern int detailLevel;

extern int fogLevel;


enum {
  M_LOW_DETAIL, M_MEDIUM_DETAIL, M_HIGH_DETAIL, M_PROTOTYPE_DETAIL_1, M_QUIT
};

enum {
	M_FOG_SMOG, M_FOG_HAZE, M_FOG_NONE
};


typedef struct
{

	// GLubyte will work for images up to 32-bits.
	GLubyte *imageData;
                    
	// Stores the color depth of the image in bits
	// per pixel.
	GLuint   bpp;

	GLuint   width;
	GLuint   height;

	GLuint   texID;     // For texture objects; more later.

} Texture;

extern int framecount;

extern Texture textures[NUMTEXTURES];

extern GLuint texture_id[NUMTEXTURES];

extern int lastmousex, lastmousey;

extern int InclineDegrees;

extern long NumPolys;

/*
extern LPDIRECTINPUT8 lpdi;
extern LPDIRECTINPUTDEVICE8 m_keyboard;
extern unsigned char KeyBuffer[256];
*/





extern landscape_t parkLandscape[128][128];


//frustum information
extern float frustum[6][4];		//6 planes - 4 vals per plane

extern float RCTColorsR[32];
extern float RCTColorsG[32];
extern float RCTColorsB[32];



/* Headers */
void printBinary(int val);

/* from vr-audio.c */
void clearAudioInformation(void);
FILE* loadAudioDescriptor(FILE* infile);

/* from vr-render.c */
GLvoid draw(GLvoid);
void set_material_color (float r, float g, float b);
GLvoid idle(GLvoid);
GLvoid reshape(GLint w, GLint h);
void renderScene(void);
GLvoid Viz(int state);
void display ( void );
void DoRotate(int step);
void DrawTrack(void);
void ourDoFPS(char *string);
void setOrthographicProjection();
void resetPerspectiveProjection();
void renderBitmapString2f(float x, float y, void *font,char *string);
void renderBitmapString3f(float x, float y, float z, void *font,char *string);
int CalcDetail(float x, float y, float z);
void DrawSkyBox(void);

void ExtractFrustum(void);
int CubeInFrustum( float x, float y, float z, float dx, float dy, float dz );

void calcColor(float baseColor[3], float factor, float *r, float *g, float *b);
double calcLightFactor(double n1, double n2, double n3);




/* from vr-main.c */
GLint main(int argc, char *argv[]);
GLuint create_scene();
void ourPrintString(void *font, char *str);
void InitDInput(void);
void InitFMod(void);
//void processFileOpenRequest(void);

/* from vr-file.c */
void DecompressFile(char *filename, char *tempfilename);
void ReadTrackSetup(char *filename);
void ReadTrackData(int FileFormat, FILE *input);
void LoadTGATexture(Texture *texture, char *filename);
void LoadBMPFromFile(char *fname, int texID);
int LoadTGAFromFile(char *fname, int texID);


/* from vr-init.c */
GLvoid init_lightsource ( GLvoid );
GLint init_glut(GLint *argc, char **argv);
GLvoid init_opengl(GLvoid);
GLvoid Timer( int value );
void init ( GLvoid );
void InitEdgeTextures(void);
void InitSurfaceTextures(void);
void InitPathTextures(void);
void InitTreeTextures(void);
void InitRideTextures(void);
void InitSkyTextures(void);
void InitWallTextures(void);
void ExtensionSetup(void);

void getFaceNormal(float *norm,float pointa[3],float pointb[3],float pointc[3]);

void loadExtendedInfo(char *filename);


/* from vr-objects.c */
GLvoid createStraight(int detail);
GLvoid createStationMiddle(int detail);
GLvoid createStationStart(int detail);
GLvoid createStationEnd(int detail);
GLvoid createSmallTurn(int detail);
GLvoid createMediumTurn(int detail);
GLvoid createFlatHill(int detail);
GLvoid createHillFlat(int detail);
GLvoid createHill(int detail);


/* from vr-input.c */
void arrow_keys ( int a_keys, int x, int y );
void keyboard ( unsigned char key, int x, int y );
void processMousePassiveMotion(int x, int y);


/* from tgaload.cpp */
/* functions listed in tgaload.h */


/* from vr-landscape.c */
void LoadLandscape(char *filename);
void DrawLandscape(void);
void CreateLandscape(void);
float getLowestPoint(int i, int j);
float getHighestPoint(int i, int j);


/* from vr-trees1.c */
void LoadTrees1(char *filename);
void DrawTrees1(int a, int b);
void AddTree(FILE *input, int offset, int x, int z);

void LoadBigScenery(char *filename);
void AddBigScenery(FILE *input, int offset, int x, int z);
void DrawBigScenery(int a, int b);

/* from vr-paths.c */
void LoadPaths(char *filename);
void AddPath(FILE *input, int offset, int x, int z, int modifier);
void DrawPaths(int a, int b);
int calcQueueRide(int xTile, int zTile, int count, int approach);


/* from vr-elements.c */
void LoadElements(char *filename);
void AddElement(FILE *input, int offset, int x, int z, int modifier, int liftpiece);
void DrawElements(int a, int b);


/* from vr-entrances.c */
void LoadEntrances(char *filename);
void AddEntrance(FILE *input, int offset, int x, int z, int modifier, int liftpiece);
void DrawEntrances(int a, int b);


/* from vr-walls.c */
void LoadWalls(char *filename);
void AddWall(FILE *input, int offset, int x, int z, int modifier);
void DrawWalls(int a, int b);

/* from vr-atmospheres.c */
void initAtmosphere(int atmosphereID);

/* from vr-rides.c */
void LoadRides(char *filename);



void DrawSteelRC_00(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_04(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_05(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_06(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_07(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_0A(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_0B(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_0C(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_0D(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_10(int rideIndex, int colorIndex);
void DrawSteelRC_11(int rideIndex, int colorIndex);
void DrawSteelRC_12(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_13(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_14(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_15(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_16(int rideIndex, int colorIndex);
void DrawSteelRC_17(int rideIndex, int colorIndex);
void DrawSteelRC_18(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_19(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_1A(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_1B(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_1C(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_1D(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_1E(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_1F(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_20(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_21(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelRC_22(int rideIndex, int colorIndex);
void DrawSteelRC_23(int rideIndex, int colorIndex);
void DrawSteelRC_24(int rideIndex, int colorIndex);
void DrawSteelRC_25(int rideIndex, int colorIndex);
void DrawSteelRC_26(int rideIndex, int colorIndex);
void DrawSteelRC_27(int rideIndex, int colorIndex);
void DrawSteelRC_2A(int rideIndex, int colorIndex);
void DrawSteelRC_2B(int rideIndex, int colorIndex);
void DrawSteelRC_2C(int rideIndex, int colorIndex);
void DrawSteelRC_2D(int rideIndex, int colorIndex);
void DrawSteelRC_2E(int rideIndex, int colorIndex);
void DrawSteelRC_2F(int rideIndex, int colorIndex);
void DrawSteelRC_30(int rideIndex, int colorIndex);
void DrawSteelRC_31(int rideIndex, int colorIndex);
void DrawSteelRC_85(int rideIndex, int colorIndex);
void DrawSteelRC_86(int rideIndex, int colorIndex);
void DrawSteelRC_87(int rideIndex, int colorIndex);
void DrawSteelRC_88(int rideIndex, int colorIndex);
void DrawSteelRC_89(int rideIndex, int colorIndex);
void DrawSteelRC_8A(int rideIndex, int colorIndex);
void DrawSteelRC_8B(int rideIndex, int colorIndex);
void DrawSteelRC_8C(int rideIndex, int colorIndex);
void DrawSteelRC_8D(int rideIndex, int colorIndex);
void DrawSteelRC_8E(int rideIndex, int colorIndex);
void DrawSteelRC_8F(int rideIndex, int colorIndex);
void DrawSteelRC_90(int rideIndex, int colorIndex);
void DrawSteelRC_91(int rideIndex, int colorIndex);
void DrawSteelRC_93(int rideIndex, int colorIndex);
void DrawSteelRC_94(int rideIndex, int colorIndex);
void DrawSteelRC_95(int rideIndex, int colorIndex);
void DrawSteelRC_96(int rideIndex, int colorIndex);
void DrawSteelRC_97(int rideIndex, int colorIndex);
void DrawSteelRC_99(int rideIndex, int colorIndex);
void DrawSteelRC_9E(int rideIndex, int colorIndex);
void DrawSteelRC_9F(int rideIndex, int colorIndex);
void DrawSteelRC_A0(int rideIndex, int colorIndex);
void DrawSteelRC_A1(int rideIndex, int colorIndex);
void DrawSteelRC_A2(int rideIndex, int colorIndex);
void DrawSteelRC_A3(int rideIndex, int colorIndex);
void DrawSteelRC_A4(int rideIndex, int colorIndex);
void DrawSteelRC_A5(int rideIndex, int colorIndex);
void DrawSteelRC_A6(int rideIndex, int colorIndex);
void DrawSteelRC_A7(int rideIndex, int colorIndex);
void DrawSteelRC_A8(int rideIndex, int colorIndex);
void DrawSteelRC_A9(int rideIndex, int colorIndex);
void DrawSteelRC_AA(int rideIndex, int colorIndex);
void DrawSteelRC_AB(int rideIndex, int colorIndex);


void DrawMineTrain_00(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_04(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_05(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_06(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_07(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_0A(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_0B(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_0C(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_0D(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_10(int rideIndex, int colorIndex);
void DrawMineTrain_11(int rideIndex, int colorIndex);
void DrawMineTrain_12(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_13(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_14(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_15(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_16(int rideIndex, int colorIndex);
void DrawMineTrain_17(int rideIndex, int colorIndex);
void DrawMineTrain_18(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_19(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_1A(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_1B(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_1C(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_1D(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_1E(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_1F(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_20(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_21(int rideIndex, int colorIndex, bool isDiag);
void DrawMineTrain_22(int rideIndex, int colorIndex);
void DrawMineTrain_23(int rideIndex, int colorIndex);
void DrawMineTrain_24(int rideIndex, int colorIndex);
void DrawMineTrain_25(int rideIndex, int colorIndex);
void DrawMineTrain_26(int rideIndex, int colorIndex);
void DrawMineTrain_27(int rideIndex, int colorIndex);
void DrawMineTrain_2A(int rideIndex, int colorIndex);
void DrawMineTrain_2B(int rideIndex, int colorIndex);
void DrawMineTrain_2C(int rideIndex, int colorIndex);
void DrawMineTrain_2D(int rideIndex, int colorIndex);
void DrawMineTrain_2E(int rideIndex, int colorIndex);
void DrawMineTrain_2F(int rideIndex, int colorIndex);
void DrawMineTrain_30(int rideIndex, int colorIndex);
void DrawMineTrain_31(int rideIndex, int colorIndex);
void DrawMineTrain_85(int rideIndex, int colorIndex);
void DrawMineTrain_86(int rideIndex, int colorIndex);
void DrawMineTrain_87(int rideIndex, int colorIndex);
void DrawMineTrain_88(int rideIndex, int colorIndex);
void DrawMineTrain_89(int rideIndex, int colorIndex);
void DrawMineTrain_8A(int rideIndex, int colorIndex);
void DrawMineTrain_8B(int rideIndex, int colorIndex);
void DrawMineTrain_8C(int rideIndex, int colorIndex);
void DrawMineTrain_8D(int rideIndex, int colorIndex);
void DrawMineTrain_8E(int rideIndex, int colorIndex);
void DrawMineTrain_8F(int rideIndex, int colorIndex);
void DrawMineTrain_90(int rideIndex, int colorIndex);
void DrawMineTrain_91(int rideIndex, int colorIndex);
void DrawMineTrain_93(int rideIndex, int colorIndex);
void DrawMineTrain_94(int rideIndex, int colorIndex);
void DrawMineTrain_95(int rideIndex, int colorIndex);
void DrawMineTrain_96(int rideIndex, int colorIndex);
void DrawMineTrain_97(int rideIndex, int colorIndex);
void DrawMineTrain_99(int rideIndex, int colorIndex);
void DrawMineTrain_9E(int rideIndex, int colorIndex);
void DrawMineTrain_9F(int rideIndex, int colorIndex);
void DrawMineTrain_A0(int rideIndex, int colorIndex);
void DrawMineTrain_A1(int rideIndex, int colorIndex);
void DrawMineTrain_A2(int rideIndex, int colorIndex);
void DrawMineTrain_A3(int rideIndex, int colorIndex);
void DrawMineTrain_A4(int rideIndex, int colorIndex);
void DrawMineTrain_A5(int rideIndex, int colorIndex);
void DrawMineTrain_A6(int rideIndex, int colorIndex);
void DrawMineTrain_A7(int rideIndex, int colorIndex);
void DrawMineTrain_A8(int rideIndex, int colorIndex);
void DrawMineTrain_A9(int rideIndex, int colorIndex);
void DrawMineTrain_AA(int rideIndex, int colorIndex);
void DrawMineTrain_AB(int rideIndex, int colorIndex);







void DrawSteelCorkscrewRollerCoaster_00(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_04(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_05(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_06(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_07(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_08(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_09(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_0A(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_0B(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_0C(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_0D(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_0E(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_0F(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_10(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_11(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_12(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_13(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_14(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_15(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_16(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_17(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_18(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_19(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_1A(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_1B(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_1C(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_1D(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_1E(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_1F(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_20(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_21(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelCorkscrewRollerCoaster_22(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_23(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_24(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_25(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_2A(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_2B(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_2C(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_2D(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_2E(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_2F(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_30(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_31(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_5F(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_60(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_61(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_62(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_85(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_86(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_87(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_88(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_89(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_8A(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_8B(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_8C(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_8D(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_8E(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_8F(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_90(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_91(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_92(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_93(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_94(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_95(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_96(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_97(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_98(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_99(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_9E(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_9F(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A0(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A1(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A2(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A3(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A4(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A5(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A6(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A7(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A8(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_A9(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_AA(int rideIndex, int colorIndex);
void DrawSteelCorkscrewRollerCoaster_AB(int rideIndex, int colorIndex);





void DrawRailroad_00(int rideIndex, int colorIndex, bool isDiag);
void DrawRailroad_04(int rideIndex, int colorIndex, bool isDiag);
void DrawRailroad_06(int rideIndex, int colorIndex, bool isDiag);
void DrawRailroad_09(int rideIndex, int colorIndex, bool isDiag);
void DrawRailroad_0A(int rideIndex, int colorIndex, bool isDiag);
void DrawRailroad_0C(int rideIndex, int colorIndex, bool isDiag);
void DrawRailroad_0F(int rideIndex, int colorIndex, bool isDiag);
void DrawRailroad_10(int rideIndex, int colorIndex);
void DrawRailroad_11(int rideIndex, int colorIndex);
void DrawRailroad_26(int rideIndex, int colorIndex);
void DrawRailroad_27(int rideIndex, int colorIndex);
void DrawRailroad_2A(int rideIndex, int colorIndex);
void DrawRailroad_2B(int rideIndex, int colorIndex);
void DrawRailroad_85(int rideIndex, int colorIndex);
void DrawRailroad_86(int rideIndex, int colorIndex);
void DrawRailroad_87(int rideIndex, int colorIndex);
void DrawRailroad_88(int rideIndex, int colorIndex);
void DrawRailroad_8D(int rideIndex, int colorIndex);
void DrawRailroad_8E(int rideIndex, int colorIndex);
void DrawRailroad_90(int rideIndex, int colorIndex);
void DrawRailroad_93(int rideIndex, int colorIndex);
void DrawRailroad_94(int rideIndex, int colorIndex);
void DrawRailroad_96(int rideIndex, int colorIndex);
void DrawRailroad_99(int rideIndex, int colorIndex);


void DrawSteelMini_00(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_04(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_05(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_06(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_07(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_0A(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_0B(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_0C(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_0D(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_10(int rideIndex, int colorIndex);
void DrawSteelMini_11(int rideIndex, int colorIndex);
void DrawSteelMini_12(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_13(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_14(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_15(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_16(int rideIndex, int colorIndex);
void DrawSteelMini_17(int rideIndex, int colorIndex);
void DrawSteelMini_18(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_19(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_1A(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_1B(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_1C(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_1D(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_1E(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_1F(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_20(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_21(int rideIndex, int colorIndex, bool isDiag);
void DrawSteelMini_22(int rideIndex, int colorIndex);
void DrawSteelMini_23(int rideIndex, int colorIndex);
void DrawSteelMini_24(int rideIndex, int colorIndex);
void DrawSteelMini_25(int rideIndex, int colorIndex);
void DrawSteelMini_26(int rideIndex, int colorIndex);
void DrawSteelMini_27(int rideIndex, int colorIndex);
void DrawSteelMini_2A(int rideIndex, int colorIndex);
void DrawSteelMini_2B(int rideIndex, int colorIndex);
void DrawSteelMini_2C(int rideIndex, int colorIndex);
void DrawSteelMini_2D(int rideIndex, int colorIndex);
void DrawSteelMini_2E(int rideIndex, int colorIndex);
void DrawSteelMini_2F(int rideIndex, int colorIndex);
void DrawSteelMini_30(int rideIndex, int colorIndex);
void DrawSteelMini_31(int rideIndex, int colorIndex);
void DrawSteelMini_85(int rideIndex, int colorIndex);
void DrawSteelMini_86(int rideIndex, int colorIndex);
void DrawSteelMini_87(int rideIndex, int colorIndex);
void DrawSteelMini_88(int rideIndex, int colorIndex);
void DrawSteelMini_89(int rideIndex, int colorIndex);
void DrawSteelMini_8A(int rideIndex, int colorIndex);
void DrawSteelMini_8B(int rideIndex, int colorIndex);
void DrawSteelMini_8C(int rideIndex, int colorIndex);
void DrawSteelMini_8D(int rideIndex, int colorIndex);
void DrawSteelMini_8E(int rideIndex, int colorIndex);
void DrawSteelMini_8F(int rideIndex, int colorIndex);
void DrawSteelMini_90(int rideIndex, int colorIndex);
void DrawSteelMini_91(int rideIndex, int colorIndex);
void DrawSteelMini_93(int rideIndex, int colorIndex);
void DrawSteelMini_94(int rideIndex, int colorIndex);
void DrawSteelMini_95(int rideIndex, int colorIndex);
void DrawSteelMini_96(int rideIndex, int colorIndex);
void DrawSteelMini_97(int rideIndex, int colorIndex);
void DrawSteelMini_99(int rideIndex, int colorIndex);
void DrawSteelMini_9E(int rideIndex, int colorIndex);
void DrawSteelMini_9F(int rideIndex, int colorIndex);
void DrawSteelMini_A0(int rideIndex, int colorIndex);
void DrawSteelMini_A1(int rideIndex, int colorIndex);
void DrawSteelMini_A2(int rideIndex, int colorIndex);
void DrawSteelMini_A3(int rideIndex, int colorIndex);
void DrawSteelMini_A4(int rideIndex, int colorIndex);
void DrawSteelMini_A5(int rideIndex, int colorIndex);
void DrawSteelMini_A6(int rideIndex, int colorIndex);
void DrawSteelMini_A7(int rideIndex, int colorIndex);
void DrawSteelMini_A8(int rideIndex, int colorIndex);
void DrawSteelMini_A9(int rideIndex, int colorIndex);
void DrawSteelMini_AA(int rideIndex, int colorIndex);
void DrawSteelMini_AB(int rideIndex, int colorIndex);


void DrawWildMouse_00(int rideIndex, int colorIndex);
void DrawWildMouse_04(int rideIndex, int colorIndex);
void DrawWildMouse_05(int rideIndex, int colorIndex);
void DrawWildMouse_06(int rideIndex, int colorIndex);
void DrawWildMouse_07(int rideIndex, int colorIndex);
void DrawWildMouse_0A(int rideIndex, int colorIndex);
void DrawWildMouse_0B(int rideIndex, int colorIndex);
void DrawWildMouse_0C(int rideIndex, int colorIndex);
void DrawWildMouse_0D(int rideIndex, int colorIndex);
void DrawWildMouse_2A(int rideIndex, int colorIndex);
void DrawWildMouse_2B(int rideIndex, int colorIndex);
void DrawWildMouse_32(int rideIndex, int colorIndex);
void DrawWildMouse_33(int rideIndex, int colorIndex);
void DrawWildMouse_3E(int rideIndex, int colorIndex);
void DrawWildMouse_40(int rideIndex, int colorIndex);


void DrawVirginiaReel_00(int rideIndex, int colorIndex);
void DrawVirginiaReel_04(int rideIndex, int colorIndex);
void DrawVirginiaReel_06(int rideIndex, int colorIndex);
void DrawVirginiaReel_0A(int rideIndex, int colorIndex);
void DrawVirginiaReel_0C(int rideIndex, int colorIndex);
void DrawVirginiaReel_2A(int rideIndex, int colorIndex);
void DrawVirginiaReel_2B(int rideIndex, int colorIndex);
void DrawVirginiaReel_32(int rideIndex, int colorIndex);
void DrawVirginiaReel_33(int rideIndex, int colorIndex);


void DrawSteelWildMouse_00(int rideIndex, int colorIndex);
void DrawSteelWildMouse_04(int rideIndex, int colorIndex);
void DrawSteelWildMouse_05(int rideIndex, int colorIndex);
void DrawSteelWildMouse_06(int rideIndex, int colorIndex);
void DrawSteelWildMouse_07(int rideIndex, int colorIndex);
void DrawSteelWildMouse_0A(int rideIndex, int colorIndex);
void DrawSteelWildMouse_0B(int rideIndex, int colorIndex);
void DrawSteelWildMouse_0C(int rideIndex, int colorIndex);
void DrawSteelWildMouse_0D(int rideIndex, int colorIndex);
void DrawSteelWildMouse_2A(int rideIndex, int colorIndex);
void DrawSteelWildMouse_2B(int rideIndex, int colorIndex);
void DrawSteelWildMouse_32(int rideIndex, int colorIndex);
void DrawSteelWildMouse_33(int rideIndex, int colorIndex);
void DrawSteelWildMouse_3E(int rideIndex, int colorIndex);
void DrawSteelWildMouse_40(int rideIndex, int colorIndex);



void DrawGhostTrain_00(int rideIndex, int colorIndex);
void DrawGhostTrain_04(int rideIndex, int colorIndex);
void DrawGhostTrain_06(int rideIndex, int colorIndex);
void DrawGhostTrain_0A(int rideIndex, int colorIndex);
void DrawGhostTrain_0C(int rideIndex, int colorIndex);
void DrawGhostTrain_2A(int rideIndex, int colorIndex);
void DrawGhostTrain_2B(int rideIndex, int colorIndex);
void DrawGhostTrain_32(int rideIndex, int colorIndex);
void DrawGhostTrain_33(int rideIndex, int colorIndex);


void DrawSkyWay_00(int rideIndex, int colorIndex);
void DrawSkyWay_04(int rideIndex, int colorIndex);
void DrawSkyWay_06(int rideIndex, int colorIndex);
void DrawSkyWay_0A(int rideIndex, int colorIndex);
void DrawSkyWay_0C(int rideIndex, int colorIndex);
void DrawSkyWay_32(int rideIndex, int colorIndex);
void DrawSkyWay_33(int rideIndex, int colorIndex);


void DrawCarRide_00(int rideIndex, int colorIndex);
void DrawCarRide_04(int rideIndex, int colorIndex);
void DrawCarRide_06(int rideIndex, int colorIndex);
void DrawCarRide_0A(int rideIndex, int colorIndex);
void DrawCarRide_0C(int rideIndex, int colorIndex);
void DrawCarRide_2A(int rideIndex, int colorIndex);
void DrawCarRide_2B(int rideIndex, int colorIndex);
void DrawCarRide_32(int rideIndex, int colorIndex);
void DrawCarRide_33(int rideIndex, int colorIndex);


void DrawSingleRailRollerCoaster_00(int rideIndex, int colorIndex);
void DrawSingleRailRollerCoaster_04(int rideIndex, int colorIndex);
void DrawSingleRailRollerCoaster_06(int rideIndex, int colorIndex);
void DrawSingleRailRollerCoaster_0A(int rideIndex, int colorIndex);
void DrawSingleRailRollerCoaster_0C(int rideIndex, int colorIndex);
void DrawSingleRailRollerCoaster_10(int rideIndex, int colorIndex);
void DrawSingleRailRollerCoaster_11(int rideIndex, int colorIndex);
void DrawSingleRailRollerCoaster_2A(int rideIndex, int colorIndex);
void DrawSingleRailRollerCoaster_2B(int rideIndex, int colorIndex);


		
void DrawLogFlume_00(int rideIndex, int colorIndex);
void DrawLogFlume_04(int rideIndex, int colorIndex);
void DrawLogFlume_06(int rideIndex, int colorIndex);
void DrawLogFlume_0A(int rideIndex, int colorIndex);
void DrawLogFlume_0C(int rideIndex, int colorIndex);
void DrawLogFlume_10(int rideIndex, int colorIndex);
void DrawLogFlume_11(int rideIndex, int colorIndex);
void DrawLogFlume_26(int rideIndex, int colorIndex);
void DrawLogFlume_27(int rideIndex, int colorIndex);
void DrawLogFlume_2A(int rideIndex, int colorIndex);
void DrawLogFlume_2B(int rideIndex, int colorIndex);

void DrawRiverRide_00(int rideIndex, int colorIndex);
void DrawRiverRide_04(int rideIndex, int colorIndex);
void DrawRiverRide_06(int rideIndex, int colorIndex);
void DrawRiverRide_0A(int rideIndex, int colorIndex);
void DrawRiverRide_0B(int rideIndex, int colorIndex);
void DrawRiverRide_0C(int rideIndex, int colorIndex);
void DrawRiverRide_0D(int rideIndex, int colorIndex);
void DrawRiverRide_0E(int rideIndex, int colorIndex);
void DrawRiverRide_0F(int rideIndex, int colorIndex);
void DrawRiverRide_10(int rideIndex, int colorIndex);
void DrawRiverRide_11(int rideIndex, int colorIndex);
void DrawRiverRide_26(int rideIndex, int colorIndex);
void DrawRiverRide_27(int rideIndex, int colorIndex);
void DrawRiverRide_2A(int rideIndex, int colorIndex);
void DrawRiverRide_2B(int rideIndex, int colorIndex);
void DrawRiverRide_2C(int rideIndex, int colorIndex);

void DrawRapids_00(int rideIndex, int colorIndex);
void DrawRapids_04(int rideIndex, int colorIndex);
void DrawRapids_06(int rideIndex, int colorIndex);
void DrawRapids_0A(int rideIndex, int colorIndex);
void DrawRapids_0C(int rideIndex, int colorIndex);
void DrawRapids_10(int rideIndex, int colorIndex);
void DrawRapids_11(int rideIndex, int colorIndex);
void DrawRapids_32(int rideIndex, int colorIndex);
void DrawRapids_33(int rideIndex, int colorIndex);

void DrawSpaceShot_42(int rideIndex, int colorIndex);
void DrawSpaceShot_43(int rideIndex, int colorIndex);

void DrawRotoDrop_42(int rideIndex, int colorIndex);
void DrawRotoDrop_43(int rideIndex, int colorIndex);

void DrawObservationTower_42(int rideIndex, int colorIndex);
void DrawObservationTower_43(int rideIndex, int colorIndex);

void DrawMonorail_00(int rideIndex, int colorIndex, bool doDiag);
void DrawMonorail_04(int rideIndex, int colorIndex, bool doDiag);
void DrawMonorail_06(int rideIndex, int colorIndex, bool doDiag);
void DrawMonorail_09(int rideIndex, int colorIndex, bool doDiag);
void DrawMonorail_0A(int rideIndex, int colorIndex, bool doDiag);
void DrawMonorail_0C(int rideIndex, int colorIndex, bool doDiag);
void DrawMonorail_10(int rideIndex, int colorIndex);
void DrawMonorail_11(int rideIndex, int colorIndex);
void DrawMonorail_26(int rideIndex, int colorIndex);
void DrawMonorail_27(int rideIndex, int colorIndex);
void DrawMonorail_2A(int rideIndex, int colorIndex);
void DrawMonorail_2B(int rideIndex, int colorIndex);
void DrawMonorail_85(int rideIndex, int colorIndex);
void DrawMonorail_86(int rideIndex, int colorIndex);
void DrawMonorail_87(int rideIndex, int colorIndex);
void DrawMonorail_88(int rideIndex, int colorIndex);
void DrawMonorail_8D(int rideIndex, int colorIndex);
void DrawMonorail_8E(int rideIndex, int colorIndex);
void DrawMonorail_90(int rideIndex, int colorIndex);
void DrawMonorail_93(int rideIndex, int colorIndex);
void DrawMonorail_94(int rideIndex, int colorIndex);
void DrawMonorail_96(int rideIndex, int colorIndex);

