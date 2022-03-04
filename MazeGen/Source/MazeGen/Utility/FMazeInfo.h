#pragma once
#include "CoreMinimal.h"
#include "EDirection.h"
#include "FMazeInfo.generated.h"

/* A Struct which stores information for building a single tile in a maze. */
USTRUCT()
struct FMazeInfo
{
	GENERATED_BODY()

	TArray<EDirection> Walls;
	TArray<EDirection> Connections;
	TMap<EDirection, FMazeInfo*> Neighbors;
	UClass* TileType = nullptr;
	FVector Pos = FVector(0,0,0);
	bool IsInMaze = false;
};