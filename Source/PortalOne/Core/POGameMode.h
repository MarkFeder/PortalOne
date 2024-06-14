// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "POGameMode.generated.h"

class AConfigurator;

UCLASS()
class PORTALONE_API APOGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Variant")
	AConfigurator* GetConfigurator() const;

	UFUNCTION(BlueprintCallable, Category = "Variant")
	void SetConfigurator(AConfigurator* InConfigurator);

	UFUNCTION(BlueprintCallable, Category = "Variant")
	bool HasValidConfigurator() const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Variant")
	AConfigurator* Configurator;
};