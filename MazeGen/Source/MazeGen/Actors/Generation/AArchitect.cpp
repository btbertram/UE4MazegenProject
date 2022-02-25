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
	//ArchitectCompleted.Broadcast();
}

// Called every frame
void AAArchitect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	LevelTiles.Empty();

	for (int y = 0; y < LevelSizeY; y++) {
		for (int x = 0; x < LevelSizeX; x++) {

			FMazeInfo* TileInfo = new FMazeInfo;

			TileInfo->TileType = TileTypes[FMath::RandRange(0, TileTypes.Num() - 1)]->GetClass();

			//AATile* test = Cast<AATile>();

			TileInfo->Pos = FVector(x, y, 0);

			//Hardcode Testing
			TileInfo->Walls.Add(EDirection::North);
			TileInfo->Walls.Add(EDirection::South);

			LevelInstructions.Add(TileInfo);
		}
	}
}

TArray<FMazeInfo*> AAArchitect::GetArchitectMazeBluprint()
{
	//Testing Implementation
	//TArray<AATile*> TilesToBuild;

	//for (auto It = LevelTiles.begin(); It != LevelTiles.end(); ++It)
	//{
	//	AATile* tile = Cast<AATile>(*It);
	//	TilesToBuild.Add(tile);
	//}

	return LevelInstructions;
}

