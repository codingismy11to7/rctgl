#include "vr-tracks.h"

#define CENTER_RADIUS		0.075 * UNITWIDTH
#define CENTER_HEIGHT		0.33
#define RAIL_RADIUS			0.025 * UNITWIDTH
#define RAIL_HEIGHT			0.9
#define RAIL_HEIGHT_TILTED	1.25
#define LEFT_RAIL			0.25 * UNITWIDTH
#define RIGHT_RAIL			0.75 * UNITWIDTH

void DrawSteelTwisterRollerCoaster_00(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_04(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_05(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_06(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_07(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_08(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_09(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_0A(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_0B(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_0C(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_0D(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_0E(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_0F(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_10(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_11(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_12(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_13(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_14(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_15(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_16(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_17(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_18(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_19(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_1A(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_1B(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_1C(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_1D(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_1E(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_1F(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_20(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_21(int rideIndex, int colorIndex, bool doDiag);
void DrawSteelTwisterRollerCoaster_22(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_23(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_24(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_25(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_2A(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_2B(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_2C(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_2D(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_2E(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_2F(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_30(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_31(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_5F(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_60(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_61(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_62(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_85(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_86(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_87(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_88(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_89(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_8A(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_8B(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_8C(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_8D(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_8E(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_8F(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_90(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_91(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_92(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_93(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_94(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_95(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_96(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_97(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_98(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_99(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_9E(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_9F(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A0(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A1(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A2(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A3(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A4(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A5(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A6(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A7(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A8(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_A9(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_AA(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_AB(int rideIndex, int colorIndex);

void DrawSteelTwisterRollerCoaster_B7(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_B8(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_B9(int rideIndex, int colorIndex);
void DrawSteelTwisterRollerCoaster_BA(int rideIndex, int colorIndex);
