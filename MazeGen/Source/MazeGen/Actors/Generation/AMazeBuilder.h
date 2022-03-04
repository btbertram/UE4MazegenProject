// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MazeGen/Actors/ATile.h"
#include "MazeGen/Utility/FMazeInfo.h"
#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMazeBuilder.generated.h"

/* An Actor class which builds and spawns a maze when placed in the level with an AArchitect. */
UCLASS()
class MAZEGEN_API AAMazeBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMazeBuilder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Gets information from the Architect for building a maze.
	TArray<FMazeInfo*> GetMazeArchitectInstruction();
	
	/**
	* Takes an Architect Blueprint and uses it to create a maze.
	* 
	* @Param InstructionsForTiles	Instruction set from the Architect which details how tiles should be configured for a maze.	
	*/
	void PlaceMaze(const TArray<FMazeInfo*>& InstructionsForTiles);

	/**
	* Spawns a single ATile actor in the world.
	* 
	* @Param Instructions	Configuration instructions for a single tile in a maze.
	*/
	void PlaceTile(const FMazeInfo*& Instructions);

	/*
	* Manipulates an ATile's properties based on instructions from the Architect after it has been spawned into the world.
	* 
	* @Param *Tile	The tile to configure. 
	* @Param *&Instructions		Configureation instructions for a single tile in a maze.	
	*/
	void ConfigureTile(AATile *Tile, const FMazeInfo*& Instructions);

private:
	UWorld* world;
	FActorSpawnParameters TileSpawnParams;

	//Delegate subscriber function to activate PlaceMaze
	void BeginBuilding();


};

