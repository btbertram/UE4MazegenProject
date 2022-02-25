#pragma once
#include "EDirection.h"
#include "FMazeInfo.generated.h"

USTRUCT()
struct FMazeInfo
{
	GENERATED_BODY()

	TArray<EDirection> Walls;
	UClass* TileType = nullptr;
	FVector Pos = FVector(0,0,0);
};