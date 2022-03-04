// Fill out your copyright notice in the Description page of Project Settings.


#include "ATile.h"

// Sets default values
AATile::AATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(Root);

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileFloorMesh"));
	FloorMesh->SetupAttachment(Root);
	RefWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RefWallMesh"));
	RefWallMesh->SetupAttachment(Root);

	TagsContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Generation.Maze.Tile")));

}

void AATile::BeginPlay()
{
	Super::BeginPlay();

}

void AATile::AddWall(EDirection Direction) {
	
	FVector FloorMeshMin = FVector(0, 0, 0);
	FVector FloorMeshMax = FVector(0, 0, 0);

	FloorMesh->GetLocalBounds(FloorMeshMin, FloorMeshMax);

	//Location and Rotator values based on Wall extended in +X direction with the inward face in the +Y direction (towards the FloorMesh center) 
	switch (Direction)
	{
	case EDirection::North:
		NorthWall = NewObject<UStaticMeshComponent>(Root, TEXT("NorthWall"));
		NorthWall->SetRelativeLocation(FVector(FloorMeshMax.X, 0, 0));
		NorthWall->SetRelativeRotation(FRotator(0, 90, 0));
		NorthWall->SetStaticMesh(RefWallMesh->GetStaticMesh());
		NorthWall->SetMaterial(0, RefWallMesh->GetMaterial(0));
		NorthWall->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
		NorthWall->RegisterComponent();
		break;
	case EDirection::East:
		EastWall = NewObject<UStaticMeshComponent>(Root, TEXT("EastWall"));
		EastWall->SetRelativeLocation(FVector(FloorMeshMax.X, FloorMeshMax.Y, 0));
		EastWall->SetRelativeRotation(FRotator(0, 180, 0));
		EastWall->SetStaticMesh(RefWallMesh->GetStaticMesh());
		EastWall->SetMaterial(0, RefWallMesh->GetMaterial(0));
		EastWall->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
		EastWall->RegisterComponent();
		break;
	case EDirection::South:
		SouthWall = NewObject<UStaticMeshComponent>(Root, TEXT("SouthWall"));
		SouthWall->SetRelativeLocation(FVector(0, FloorMeshMax.Y, 0));
		SouthWall->SetRelativeRotation(FRotator(0, -90, 0));
		SouthWall->SetStaticMesh(RefWallMesh->GetStaticMesh());
		SouthWall->SetMaterial(0, RefWallMesh->GetMaterial(0));
		SouthWall->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
		SouthWall->RegisterComponent();
		break;
	case EDirection::West:
		WestWall = NewObject<UStaticMeshComponent>(Root, TEXT("WestWall"));
		WestWall->SetRelativeLocation(FVector(0, 0, 0));
		WestWall->SetRelativeRotation(FRotator(0, 0, 0));
		WestWall->SetStaticMesh(RefWallMesh->GetStaticMesh());
		WestWall->SetMaterial(0, RefWallMesh->GetMaterial(0));
		WestWall->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
		WestWall->RegisterComponent();
		break;
	default:
		break;
	}
}

void AATile::RemoveWall(EDirection Direction)
{
	switch (Direction)
	{
	case EDirection::North:
		if (NorthWall != nullptr)
		{
			NorthWall->DestroyComponent();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Attempted to destroy uninitiallized StaticMeshComponent."))
		}
		break;
	case EDirection::East:

		if (EastWall != nullptr)
		{
			EastWall->DestroyComponent();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Attempted to destroy uninitiallized StaticMeshComponent."))
		}
		break;
	case EDirection::South:
		if (SouthWall != nullptr)
		{
			SouthWall->DestroyComponent();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Attempted to destroy uninitiallized StaticMeshComponent."))
		}
		break;
	case EDirection::West:
		if (WestWall != nullptr)
		{
			WestWall->DestroyComponent();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Attempted to destroy uninitiallized StaticMeshComponent."))
		}
		break;
	default:
		break;
	}
}

void AATile::RemoveRefWall()
{
	RefWallMesh->DestroyComponent();
}

FMeshBounds AATile::GetTilePhysicalSize()
{
	FMeshBounds LocalBounds;
	FloorMesh->GetLocalBounds(LocalBounds.MinBounds, LocalBounds.MaxBounds);
	return LocalBounds;
}

void AATile::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = TagsContainer;
}

void AATile::ToggleWallMeshDirection(EDirection Direction)
{
	UE_LOG(LogTemp, Warning, TEXT("Entering ToggleWall"));

	switch (Direction)
	{
	case EDirection::North:
		UE_LOG(LogTemp, Warning, TEXT("North"))
		//NWallMesh->ToggleActive();
		break;
	case EDirection::East:
		UE_LOG(LogTemp, Warning, TEXT("East"))
		//EWallMesh->ToggleActive();
		break;
	case EDirection::South:
		UE_LOG(LogTemp, Warning, TEXT("South"));
		//SWallMesh->ToggleActive();
		break;
	case EDirection::West:
		UE_LOG(LogTemp, Warning, TEXT("West"))
		//WWallMesh->ToggleActive();
		break;
	default:
		break;
	}
}
