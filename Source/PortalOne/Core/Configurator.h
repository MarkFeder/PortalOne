// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "POVariantSet.h"
#include "Configurator.generated.h"

class ALevelVariantSetsActor;
class UVariantSet;
class UMainGUI;

UCLASS()
class PORTALONE_API AConfigurator : public AActor
{
	GENERATED_BODY()
	
public:	
	
    AConfigurator();

	UFUNCTION(BlueprintCallable)
	TArray<FPOVariantSet>& GetObjectVariantSets();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Options")
    float ButtonSize = 96.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Options")
	float ButtonOutlineSize = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Options")
	FLinearColor ButtonOutlineNormalColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Options")
	FLinearColor ButtonOutlineHoverColor = FLinearColor(1.0f, 0.3f, 1.0f, 1.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Options")
	FLinearColor ButtonOutlinePressedColor = FLinearColor(0.0f, 0.3f, 1.0f, 1.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Options")
	FLinearColor PopupLineColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Options")
	FLinearColor PopupTextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

protected:
	
	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintCallable)
	void InitConfigVarSets();

	UFUNCTION(BlueprintCallable)
	void ResetAllVariants();

	UFUNCTION(BlueprintCallable)
	void ResetVariant(FPOVariantSet& InVariantSet);

	UFUNCTION(BlueprintCallable)
	void ActivateVariant(FPOVariantSet& InVariantSet, int32 InVariantIndex);

	UFUNCTION(BlueprintCallable)
	void CallVariantActor(UVariantSet* InVariantSet, int32 InCurrentIndex, bool bInit = true);

	UFUNCTION()
	void OnPartSelected(int32 VariantSetIndex, int32 VariantIndex);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	TArray<FPOVariantSet> ObjectVariantSets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	FPOVariantSet EnviroVarSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	ALevelVariantSetsActor* LVSActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UMainGUI> GUIDefaultClass;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	UMainGUI* GUI;
};
