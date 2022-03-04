// Fill out your copyright notice in the Description page of Project Settings.


#include "AMazeBuilder.h"
#include "GameplayTagContainer.h"
#include "Kismet\GameplayStatics.h"
#include "AArchitect.h"

// Sets default values
AAMazeBuilder::AAMazeBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

// Called when the game starts or when spawned
void AAMazeBuilder::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
	world->OnWorldBeginPlay.AddUObject(this, &AAMazeBuilder::BeginBuilding);
}

// Called every frame
void AAMazeBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAMazeBuilder::BeginBuilding() {
	PlaceMaze(GetMazeArchitectInstruction());
}

TArray<FMazeInfo*> AAMazeBuilder::GetMazeArchitectInstruction()
{
	AAArchitect* Architect = Cast<AAArchitect>(UGameplayStatics::GetActorOfClass(this->GetWorld(), AAArchitect::StaticClass()));
	return Architect->GetArchitectMazeBluprint();
}

void AAMazeBuilder::PlaceMaze(const TArray<FMazeInfo*>& InstructionsForTiles)
{
	for (auto It = InstructionsForTiles.begin(); It != InstructionsForTiles.end(); ++It)
	{
		const FMazeInfo* Instructions = *It;
		PlaceTile(Instructions);
	}
}

void AAMazeBuilder::PlaceTile(const FMazeInfo*& Instructions)
{	
	AATile* NewTile = world->SpawnActor<AATile>(Instructions->TileType);
	ConfigureTile(NewTile, Instructions);
}

void AAMazeBuilder::ConfigureTile(AATile *Tile, const FMazeInfo*& Instructions)
{
	for (auto It = Instructions->Walls.begin(); It != Instructions->Walls.end(); ++It)
	{
		Tile->AddWall(*It);
	}
	Tile->RemoveRefWall();

	FMeshBounds Bounds = Tile->GetTilePhysicalSize();
	FVector NewPosVec(Bounds.MaxBounds.X * Instructions->Pos.X,	Bounds.MaxBounds.Y * Instructions->Pos.Y, 0);
	FTransform NewPos = FTransform(NewPosVec);
	Tile->AddActorWorldTransform(NewPos);
}