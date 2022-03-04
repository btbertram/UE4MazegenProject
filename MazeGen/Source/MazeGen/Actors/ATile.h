// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MazeGen/Utility/EDirection.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "MazeGen/Interfaces/ITraversable.h"
#include "GameFramework/Actor.h"
#include "ATile.generated.h"

USTRUCT()
	struct FMeshBounds
	{
		GENERATED_BODY()
		FVector MinBounds;
		FVector MaxBounds;
	};

/* An Actor class which represents a unit of the environment. */
UCLASS()
class MAZEGEN_API AATile : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AATile();

	UPROPERTY(VisibleAnywhere)
		FGameplayTagContainer TagsContainer;
	/*
	* Adds a new UStaticMeshComponent wall to the ATile.
	* 
	* @Param	The direction from the center of the tile the wall should block.
	*/
	UFUNCTION(BlueprintCallable)
		void AddWall(EDirection Direction);
	/*
	* Removes a UStaticMeshComponent wall from the ATile.
	*
	* @Param	The direction from the center of the tile the wall should block.
	*/
	UFUNCTION(BlueprintCallable)
		void RemoveWall(EDirection Direction);

	//GameplayTagAssetInterface Function
	UFUNCTION(BlueprintCallable, Category = GameplayTags)
		void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const;

	//Removes the wall reference UStaticMeshComponent from the tile.
	void RemoveRefWall();
	//Gets the bounds of a ATile's FloorMesh UStaticMeshComponent.
	FMeshBounds GetTilePhysicalSize();


protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* FloorMesh;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* RefWallMesh;
	UPROPERTY(VisibleAnywhere, Category="Testing")
		int XLength;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Testing")
		int YLength;

	UFUNCTION(BlueprintCallable)
		void ToggleWallMeshDirection(EDirection Direction);

private:

	UStaticMeshComponent* NorthWall = nullptr;
	UStaticMeshComponent* EastWall = nullptr;
	UStaticMeshComponent* SouthWall = nullptr;
	UStaticMeshComponent* WestWall = nullptr;
};
