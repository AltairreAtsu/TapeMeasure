#include "GameAPI.h"

/************************************************************
	Config Variables (Set these to whatever you need. They are automatically read by the game.)
*************************************************************/
float TickRate = 1;

const int Tape_Measure_Start_Block = 3040;
const int Tape_Measure_End_Block = 3041;

UniqueID ThisModUniqueIDs[] = { Tape_Measure_End_Block, Tape_Measure_Start_Block };

CoordinateInBlocks startPosition;
CoordinateInBlocks endPosition;

/************************************************************* 
//	Functions (Run automatically by the game, you can put any code you want into them)
*************************************************************/

void Event_BlockPlaced(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{
	if      (CustomBlockID == Tape_Measure_End_Block) {
		endPosition = At;
	}
	else if (CustomBlockID == Tape_Measure_Start_Block) {
		startPosition = At;
	}
}

void Event_BlockDestroyed(CoordinateInBlocks At, UniqueID CustomBlockID, bool Moved)
{

}

void Event_BlockHitByTool(CoordinateInBlocks At, UniqueID CustomBlockID, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{
	if (ToolName == L"T_Stick" && CustomBlockID == Tape_Measure_End_Block || CustomBlockID == Tape_Measure_Start_Block) {
		int64_t distanceX = endPosition.X - startPosition.X;
		int64_t distanceY = endPosition.Y - startPosition.Y;
		int16_t distanceZ = endPosition.Z - startPosition.Z;
		int64_t totalDistance = sqrt((distanceX * distanceX) + (distanceY * distanceY) + (distanceZ * distanceZ));

		std::wstring message = L"Distance X: " + std::to_wstring(abs(distanceX)) + std::wstring(L"\n")
							 + L"Distance Y: " + std::to_wstring(abs(distanceY)) + L"\n"
							 + L"Distance Z: " + std::to_wstring(abs(distanceZ)) + L"\n"
							 + L"Distance to point: " + std::to_wstring(abs(totalDistance));
		SpawnHintText(At+CoordinateInCentimeters(0,0,75), message, 6, 2);
	}
}

void Event_Tick()
{}

void Event_OnLoad()
{}

void Event_OnExit()
{}

/*******************************************************

	Advanced functions

*******************************************************/

void Event_AnyBlockPlaced(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{}

void Event_AnyBlockDestroyed(CoordinateInBlocks At, BlockInfo Type, bool Moved)
{}

void Event_AnyBlockHitByTool(CoordinateInBlocks At, BlockInfo Type, wString ToolName, CoordinateInCentimeters ExactHitLocation, bool ToolHeldByHandLeft)
{}
