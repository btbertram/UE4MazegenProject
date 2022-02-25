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

UCLASS()
class MAZEGEN_API AATile : public AActor, public IGameplayTagAssetInterface, public IITraversable
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AATile();

	UPROPERTY(VisibleAnywhere)
		FGameplayTagContainer TagsContainer;
	//UPROPERTY()
	//	FVector2D Pos;
	UFUNCTION(BlueprintCallable)
		void AddWall(EDirection Direction);
	UFUNCTION(BlueprintCallable)
		void RemoveWall(EDirection Direction);
	UFUNCTION(BlueprintCallable, Category = GameplayTags)
		void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const;

	void RemoveRefWall();
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

	// Inherited via IITraversable
	virtual void TestFunc() override;
};
