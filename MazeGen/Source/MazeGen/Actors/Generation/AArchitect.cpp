// Fill out your copyright notice in the Description page of Project Settings.


#include "AArchitect.h"
#include <Runtime/Engine/Public/EngineUtils.h>

// Sets default values
AAArchitect::AAArchitect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAArchitect::BeginPlay()
{
	Super::BeginPlay();
	world = GEngine->GetWorldFromContextObjectChecked(this);
	FindActorsWithTag(TileTypes, FGameplayTag::RequestGameplayTag(FName("Generation.Maze.Tile")));
	GenerateMazeBluePrint();
}

// Called every frame
void AAArchitect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FMazeInfo*> AAArchitect::GetArchitectMazeBluprint()
{
	return LevelInstructions;
}

void AAArchitect::FindActorsWithTag(TArray<AActor*>& OutActorArray, const FGameplayTag& SearchTag)
{
	if (world) {
		FGameplayTagQuery FindAllActorsWithTagQuery;
		FindAllActorsWithTagQuery = FGameplayTagQuery::BuildQuery(FGameplayTagQueryExpression().AnyTagsMatch().AddTag(SearchTag));
	
		for (FActorIterator It(world); It; ++It) {
			AActor* Actor = *It;
			IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(Actor);
			if (TagInterface != nullptr) {
				FGameplayTagContainer TempTagsContainer;
				TagInterface->GetOwnedGameplayTags(TempTagsContainer);

				if (TempTagsContainer.MatchesQuery(FindAllActorsWithTagQuery)) {
					OutActorArray.Add(Actor);
				}
			}
		}
	}
}

void AAArchitect::GenerateMazeBluePrint()
{
	LevelInstructions.Empty(LevelSizeX * LevelSizeY);

	//Populate instructions array
	for (int x = 0; x < LevelSizeX * LevelSizeY; x++)
	{
		FMazeInfo* TileInfo = new FMazeInfo();
		LevelInstructions.Add(TileInfo);
	}

	//configure base info + assign neighbors
	int YCounter = 0;
	int XCounter = 0;
	for (int x = 0; x < LevelSizeX * LevelSizeY; x++)
	{
		FMazeInfo* TileInfo = LevelInstructions[x];

		//Randomly assign tile type from 
		TileInfo->TileType = TileTypes[FMath::RandRange(0, TileTypes.Num() - 1)]->GetClass();

		AddNeighbors(TileInfo, LevelInstructions, LevelSizeX, LevelSizeY, x);

		TileInfo->Pos = FVector(XCounter, YCounter, 0);

		if ((YCounter % LevelSizeY) + 1 == LevelSizeY)
		{
			XCounter += 1;
			YCounter = 0;
		}
		else
		{
			YCounter += 1;
		}

	}

	//modify instructions outline to create maze
	DesignMaze(LevelInstructions);

}

void AAArchitect::AddNeighbors(FMazeInfo* MazeInfoOut, TArray<FMazeInfo*> const& InstructionSet, int const& XSize, int const& YSize, int const& CurrentIndex)
{
	//Self Reminder: Unreal Axis are aligned X fwd, Y right, Z up
	if (CurrentIndex - YSize >= 0)
	{
		MazeInfoOut->Neighbors.Add(EDirection::South, InstructionSet[CurrentIndex - YSize]);
	}
	else
	{
		MazeInfoOut->Neighbors.Add(EDirection::South, nullptr);
	}

	if (CurrentIndex + YSize < XSize * YSize)
	{
		MazeInfoOut->Neighbors.Add(EDirection::North, InstructionSet[CurrentIndex + YSize]);
	}
	else
	{
		MazeInfoOut->Neighbors.Add(EDirection::North, nullptr);
	}

	if ((CurrentIndex % YSize) + 1 < YSize)
	{
		MazeInfoOut->Neighbors.Add(EDirection::East, InstructionSet[CurrentIndex + 1]);
	}
	else
	{
		MazeInfoOut->Neighbors.Add(EDirection::East, nullptr);
	}

	if ((CurrentIndex % YSize) - 1 >= 0)
	{
		MazeInfoOut->Neighbors.Add(EDirection::West, InstructionSet[CurrentIndex - 1]);
	}
	else
	{
		MazeInfoOut->Neighbors.Add(EDirection::West, nullptr);
	}
}

void AAArchitect::DesignMaze(TArray<FMazeInfo*> &InstructionSetOut)
{
	//TArray can act as a Stack ADS
	TArray<FMazeInfo*> Stack;

	struct ValidConnection
	{
		FMazeInfo* Neighbor;
		EDirection Direction;
	};

	//Seed loop
	Stack.Push(*InstructionSetOut.begin());
	Stack.Top()->IsInMaze = true;

	//create maze
	while (Stack.Num() > 0)
	{
		FMazeInfo* InfoOut = Stack.Top();

		//Get all the valid neighbors, put them in an array
		TArray<ValidConnection*> ValidConnections;		
		for (auto& Nbr : InfoOut->Neighbors)
		{
			if (Nbr.Value != nullptr)
			{
				if(!Nbr.Value->IsInMaze)
				{
					ValidConnection* NewConnection = new ValidConnection;
					NewConnection->Neighbor = Nbr.Value;
					NewConnection->Direction = Nbr.Key;
					ValidConnections.Add(NewConnection);
				}
			}
		}

		//random pick from vaild connections
		if (ValidConnections.Num() > 0)
		{
			int RandomNumber = FMath::RandRange(0, ValidConnections.Num() - 1);

			ValidConnection* ChosenConnection = ValidConnections[RandomNumber];
		
			InfoOut->Connections.Add(ChosenConnection->Direction);
			
			//Add reverse connection to neighbor 
			switch (ChosenConnection->Direction)
			{
			case EDirection::North:
				ChosenConnection->Neighbor->Connections.Add(EDirection::South);
				break;
			case EDirection::East:
				ChosenConnection->Neighbor->Connections.Add(EDirection::West);
				break;
			case EDirection::South:
				ChosenConnection->Neighbor->Connections.Add(EDirection::North);
				break;
			case EDirection::West:
				ChosenConnection->Neighbor->Connections.Add(EDirection::East);
				break;
			case EDirection::Default:
				break;
			default:
				break;
			}

			ChosenConnection->Neighbor->IsInMaze = true;
			Stack.Push(ChosenConnection->Neighbor);
		}
		//No other valid connections to be made
		else
		{
			Stack.Pop();
		}
	}

	//Add Walls for maze
	for (FMazeInfo* Info : InstructionSetOut)
	{
		if (!Info->Connections.Contains(EDirection::North)) 
		{
			if (Info->Neighbors[EDirection::North] != nullptr)
			{
				if(!Info->Neighbors[EDirection::North]->Walls.Contains(EDirection::South))
				{
					Info->Walls.Add(EDirection::North);
				}
			}
			else
			{
				Info->Walls.Add(EDirection::North);
			}
		}				

		if (!Info->Connections.Contains(EDirection::East))
		{
			if(Info->Neighbors[EDirection::East] != nullptr)
			{
				if (!Info->Neighbors[EDirection::East]->Walls.Contains(EDirection::West))
				{
					Info->Walls.Add(EDirection::East);
				}
			}
			else
			{
				Info->Walls.Add(EDirection::East);
			}
		}
		if (!Info->Connections.Contains(EDirection::South))
		{
			if (Info->Neighbors[EDirection::South] != nullptr)
			{
				if (!Info->Neighbors[EDirection::South]->Walls.Contains(EDirection::North))
				{
					Info->Walls.Add(EDirection::South);
				}
			}
			else
			{
				Info->Walls.Add(EDirection::South);
			}

		}
		if (!Info->Connections.Contains(EDirection::West))
		{
			if (Info->Neighbors[EDirection::West] != nullptr)
			{
				if (!Info->Neighbors[EDirection::West]->Walls.Contains(EDirection::East))
				{
					Info->Walls.Add(EDirection::West);
				}
			}
			else
			{
				Info->Walls.Add(EDirection::West);
			}
		}
	}
}