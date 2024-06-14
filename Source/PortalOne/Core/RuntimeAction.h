// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RuntimeAction.generated.h"

/*
Empty class for reflection system visibility.
Uses the UINTERFACE macro.
Inherits from UInterface.
*/
UINTERFACE(MinimalAPI, Blueprintable)
class URuntimeAction : public UInterface
{
	GENERATED_BODY()
};

/* Actual Interface declaration. */
class PORTALONE_API IRuntimeAction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Runtime")
	void VariantInitialize();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Runtime")
	void VariantSwitchedOn();
};
