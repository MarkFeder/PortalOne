// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "MainSelector.generated.h"

class UCanvasPanel;
class UHorizontalBox;
class UPOButton;
class URibbonSelector;

struct FPOVariantSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPartSelectedEvent, int32, SetIndex, int32, Index);

UCLASS()
class PORTALONE_API UMainSelectorWidget : public UBaseWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void PopulateOptions();

	UFUNCTION(BlueprintCallable)
	void CreateEventBindings();

	UFUNCTION(BlueprintCallable)
	void HideRibbons();

public:

	/** Invoked when the part is selected. */
	UPROPERTY(BlueprintAssignable, Category = "UI|Event")
	FOnPartSelectedEvent OnPartSelected;

protected:

	void NativeConstruct() override;

	UFUNCTION()
	void OnVariantSetButtonClicked(int32 IndexClicked);

	UFUNCTION()
	void OnRibbonOptionSelected(int32 RibbonVariantSetIndex, int32 IndexSelected);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UCanvasPanel* UpperRibbonArea;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UHorizontalBox* PartSelectorHBox;

	////////////////////////////////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variant")
	TSubclassOf<UPOButton> ButtonDefaultClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variant")
	TSubclassOf<URibbonSelector> RibbonDefaultClass;

	UPROPERTY(BlueprintReadOnly, Category = "Variant")
	TArray<URibbonSelector*> VariantSetRibbons;

	UPROPERTY(BlueprintReadOnly, Category = "Variant")
	TArray<UPOButton*> VariantSetButtons;

	UPROPERTY(BlueprintReadOnly, Category = "Variant")
	TArray<FPOVariantSet> ObjVarSet;
};