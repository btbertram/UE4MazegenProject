// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MazeGen/Actors/ATile.h"
#include "MazeGen/Utility/FMazeInfo.h"
#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMazeBuilder.generated.h"

UCLASS()
class MAZEGEN_API AAMazeBuilder : public AActor
{
	GENERATED_BODY()
	
		//Notes:
		//We can't start building until the Architect is finshed with its work.
		//

public:	
	// Sets default values for this actor's properties
	AAMazeBuilder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Requests information from the Architect for building a maze.
	TArray<FMazeInfo*> GetMazeArchitectInstruction();

	//Takes an Architecht Blueprint and uses it to create a maze.
	void PlaceMaze(const TArray<FMazeInfo*>& InstructionsForTiles);

	//Places a single ATile actor in the world.
	void PlaceTile(const FMazeInfo*& Instructions);

	//Manipulates an ATile's properties based on instructions from the Architect and prepares it to be placed in the world.
	void ConfigureTile(AATile *Tile, const FMazeInfo*& Instructions);

private:
	UWorld* world;
	FActorSpawnParameters TileSpawnParams;

	void BeginBuilding();


};

