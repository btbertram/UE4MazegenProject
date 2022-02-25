// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ITraversable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UITraversable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAZEGEN_API IITraversable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	FVector Pos;

	virtual void TestFunc() = 0;


};
