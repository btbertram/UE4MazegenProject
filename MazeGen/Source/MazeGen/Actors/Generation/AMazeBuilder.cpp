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
	//UE_LOG(LogTemp, Warning, TEXT("Test"));
	world = GetWorld();
	world->OnWorldBeginPlay.AddUObject(this, &AAMazeBuilder::BeginBuilding);
	//Cast<AAArchitect>(UGameplayStatics::GetActorOfClass(this->GetWorld(), AAArchitect::StaticClass()))->ArchitectCompleted.AddUObject(this, &AAMazeBuilder::BeginBuilding);

	//Architect->ArchitectCompleted.Add(this, AAMazeBuilder::BeginBuilding);
	//GetMazeArchitectInstruction();
	//TArray<int32> Testing;
	//Testing.Init(5, 3);
	//Not working currently. Add Delegate/Subscribe system to make this work properly!
	//PlaceMaze(GetMazeArchitectInstruction());
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
	int counter = 0;
	for (auto It = InstructionsForTiles.begin(); It != InstructionsForTiles.end(); ++It)
	{
		UE_LOG(LogTemp, Warning, TEXT("Testing placeMazeLoop, %i"), ++counter);

		const FMazeInfo* Instructions = *It;

		PlaceTile(Instructions);
	}
}

void AAMazeBuilder::PlaceTile(const FMazeInfo*& Instructions)
{	
	AATile* NewTile = world->SpawnActor<AATile>(Instructions->TileType);
	ConfigureTile(NewTile, Instructions);
	UE_LOG(LogTemp, Warning, TEXT("Placed Tile."))
}

void AAMazeBuilder::ConfigureTile(AATile *Tile, const FMazeInfo*& Instructions)
{	

	for (auto It = Instructions->Walls.begin(); It != Instructions->Walls.end(); ++It)
	{
		Tile->AddWall(*It);
	}
	Tile->RemoveRefWall();

	//UStaticMesh* newMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400"), NULL, LOAD_None, NULL);

	//if (newMesh != nullptr) {
	//	if (Tile->FindComponentByClass<UStaticMeshComponent>()->SetStaticMesh(newMesh)) {
	//		UE_LOG(LogTemp, Warning, TEXT("Mesh set correctly."));
	//	}
	//	else {
	//		UE_LOG(LogTemp, Warning, TEXT("Mesh failed to set."))
	//	}
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("MESHLOAD FAILURE"));
	//}

	FMeshBounds Bounds = Tile->GetTilePhysicalSize();
	FVector NewPosVec(Bounds.MaxBounds.X * Instructions->Pos.X,	Bounds.MaxBounds.Y * Instructions->Pos.Y, 0);
	FTransform NewPos = FTransform(NewPosVec);
	Tile->AddActorWorldTransform(NewPos);
}