// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MazeGen/Actors/ATile.h"
#include "MazeGen/Utility/FMazeInfo.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AArchitect.generated.h"

//DECLARE_MULTICAST_DELEGATE(FArchitectCompletedSignature);

UCLASS()
class MAZEGEN_API AAArchitect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAArchitect();

	TArray<AActor*> TileTypes;
	TArray<AActor*> LevelTiles;

	TArray<FMazeInfo*> LevelInstructions;

	UPROPERTY(EditAnywhere, Category = "Size")
		int32 LevelSizeX;
	UPROPERTY(EditAnywhere, Category = "Size")
		int32 LevelSizeY;
		

	//FArchitectCompletedSignature ArchitectCompleted;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Searches the current world for an actor with a tag.
	UFUNCTION()
		void FindActorsWithTag(TArray<AActor*>& OutActorArray, const FGameplayTag& SearchTag);

	//Creates a new maze layout.
	void GenerateMazeBluePrint();

	void DesignMaze(TArray<FMazeInfo*>& InstructionSetOut);

	void AddNeighbors(FMazeInfo* MazeInfoOut, TArray<FMazeInfo*> const& InstructionSet, int const& XSize, int const& YSize, int const& CurrentIndex);

	TArray<FMazeInfo*> GetArchitectMazeBluprint();

private:
	UWorld* world;

};
