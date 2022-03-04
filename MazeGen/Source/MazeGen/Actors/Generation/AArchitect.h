// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MazeGen/Actors/ATile.h"
#include "MazeGen/Utility/FMazeInfo.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AArchitect.generated.h"

/* An Actor class which designs instructions for builders when placed in a level. */
UCLASS()
class MAZEGEN_API AAArchitect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAArchitect();		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//The size of the level, in Tiles, in the +X Axis direction.
	UPROPERTY(EditAnywhere, Category = "Size")
		int32 LevelSizeX;
	//The size of the level, in Tiles, in the +Y Axis direction.
	UPROPERTY(EditAnywhere, Category = "Size")
		int32 LevelSizeY;

	//Searches the current world for an actor with a tag.
	UFUNCTION()
		void FindActorsWithTag(TArray<AActor*>& OutActorArray, const FGameplayTag& SearchTag);

	/*
	* Gets the currently generated Architect blueprint.
	* 
	* @Return A set of instructions for building a level, to be used by a builder.
	*/	
	TArray<FMazeInfo*> GetArchitectMazeBluprint();

	//Creates a new set of level instructions, resulting in a maze layout.
	void GenerateMazeBluePrint();

	/*
	* Designs a maze by manipulating building instructions.
	* 
	* @Param InstrucitonSetOut	The instructions to manipulate.	
	*/
	void DesignMaze(TArray<FMazeInfo*>& InstructionSetOut);

	/*
	* Sets conceptual nieghbors for instruction objects.
	* @Param MazeInfoOut	The instruction object to be modified.
	* @Param InstructionSet	The set that the instrction object is a part of.
	* @Param XSize	The length of the level in the X direction.
	* @Param YSize	The length of the level in the Y direction.
	* @Param CurrentIndex The index for the instruction object in the instruction set.
	*/
	void AddNeighbors(FMazeInfo* MazeInfoOut, TArray<FMazeInfo*> const& InstructionSet, int const& XSize, int const& YSize, int const& CurrentIndex);

private:
	UWorld* world;
	TArray<AActor*> TileTypes;
	TArray<FMazeInfo*> LevelInstructions;

};
