// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "MainGUI.generated.h"

class AConfigurator;
class UCanvasPanel;
class UPOButton;
class UImage;
class UTexture2D;
class UTextBlock;
class UMainSelectorWidget;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVariantSelectedEvent, int32, VariantSetIndex, int32, VariantIndex);

UCLASS()
class PORTALONE_API UMainGUI : public UBaseWidget
{
	GENERATED_BODY()

public:

	/** Invoked when the new part is selected. */
	UPROPERTY(BlueprintAssignable, Category = "UI|Event")
	FOnVariantSelectedEvent OnNewPartSelected;

protected:

	void NativeOnInitialized() override;

	UFUNCTION()
	void OnBackgroundButtonClicked();

	UFUNCTION()
	void OnPartSelected(int32 SetIndex, int32 Index);

protected:
	
	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UCanvasPanel* MainCanvas;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UMainSelectorWidget* MainPartVarSelector;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UButton* BackgroundBTN;
};