// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "POVariantSet.generated.h"

class UVariantSet;

USTRUCT(BlueprintType)
struct FPOVariantSet
{
	GENERATED_BODY()

public:
	
	/** The actual variant set */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "VariantSet"))
	UVariantSet* VariantSet;

	/** Current index of the variant set */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "CurrentIndex"))
	int32 CurrentIndex;
};