#include "vr-tracks.h"

#define SLC_LEFTBEAM	 0.45f
#define SLC_RIGHTBEAM	 0.55f 
#define SLC_TOPBEAM		 1.9f
#define SLC_BOTTOMBEAM	 1.7f
#define SLC_RAILHEIGHT	 1.5f
#define SLC_LEFTRAIL	 0.25f
#define SLC_RIGHTRAIL	 0.75f
#define SLC_RAILDIAMETER 0.1f

#define CENTER_RADIUS		0.075 * UNITWIDTH
#define CENTER_HEIGHT		1.9f * UNITHEIGHT
#define RAIL_RADIUS			0.025 * UNITWIDTH
#define RAIL_HEIGHT			1.5f * UNITHEIGHT
#define RAIL_HEIGHT_TILTED	1.85f * UNITHEIGHT
#define LEFT_RAIL			0.25 * UNITWIDTH
#define RIGHT_RAIL			0.75 * UNITWIDTH


void DrawSLCRollerCoaster_00(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_04(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_05(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_06(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_07(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_08(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_09(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_0A(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_0B(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_0C(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_0D(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_0E(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_0F(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_10(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_11(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_12(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_13(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_14(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_15(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_16(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_17(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_18(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_19(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_1A(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_1B(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_1C(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_1D(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_1E(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_1F(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_20(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_21(int rideIndex, int colorIndex, bool doDiag);
void DrawSLCRollerCoaster_22(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_23(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_24(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_25(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_2A(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_2B(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_2C(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_2D(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_2E(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_2F(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_30(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_31(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_5F(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_60(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_61(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_62(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_66(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_67(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_68(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_69(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_6A(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_6B(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_6C(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_6D(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_85(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_86(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_87(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_88(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_89(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_8A(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_8B(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_8C(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_8D(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_8E(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_8F(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_90(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_91(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_92(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_93(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_94(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_95(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_96(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_97(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_98(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_99(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_9E(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_9F(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A0(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A1(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A2(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A3(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A4(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A5(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A6(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A7(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A8(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_A9(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_AA(int rideIndex, int colorIndex);
void DrawSLCRollerCoaster_AB(int rideIndex, int colorIndex);
