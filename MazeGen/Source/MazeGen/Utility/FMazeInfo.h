#pragma once
#include "CoreMinimal.h"
#include "EDirection.h"
#include "FMazeInfo.generated.h"

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