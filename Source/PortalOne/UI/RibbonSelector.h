// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "PortalOne/Core/POVariantSet.h"
#include "RibbonSelector.generated.h"

class AConfigurator;
class UHorizontalBox;
class UPOButton;
class UImage;
class UTexture2D;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRibbonOptionSelectedEvent, int32, RibbonVariantSetIndex, int32, IndexSelected);

UCLASS()
class PORTALONE_API URibbonSelector : public UBaseWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, Category = "Variant")
	int32 VariantSetIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Variant")
	FPOVariantSet VarSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variant")
	UTexture2D* Texture;

	/** Invoked when the ribbon option is selected. */
	UPROPERTY(BlueprintAssignable, Category = "UI|Event")
	FOnRibbonOptionSelectedEvent OnRibbonOptionSelectedEvent;

public:

	UFUNCTION(BlueprintCallable)
	void ShowPopup();

	UFUNCTION(BlueprintCallable)
	void HidePopup();

	UFUNCTION(BlueprintCallable)
	void TogglePopup();

	UFUNCTION(BlueprintCallable)
	FLinearColor SetLineColor();

	UFUNCTION(BlueprintCallable)
	FSlateColor SetTextColor();

protected:

	void NativeConstruct() override;

	UFUNCTION()
	void OnVariantSetButtonClicked(int32 IndexClicked);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UTextBlock* VarName;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UImage* SepBar;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UHorizontalBox* VarHBox;

	////////////////////////////////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variant")
	TSubclassOf<UPOButton> ButtonDefaultClass;

	UPROPERTY(BlueprintReadOnly, Category = "Variant")
	AConfigurator* ConfiguratorActor;
};