// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "POButton.generated.h"

class APOGameMode;
class UButton;
class UMaterialInstanceDynamic;
class UMaterialInterface;
class UTexture2D;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPOButtonClickedEvent, int32, IndexClicked);

UCLASS()
class PORTALONE_API UPOButton : public UBaseWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void InitButton();

	UFUNCTION(BlueprintCallable)
	void UpdateImage(UTexture2D* InNewImage);

public:

	/** Invoked when the favorite button is clicked. */
	UPROPERTY(BlueprintAssignable, Category = "UI|Event")
	FOnPOButtonClickedEvent OnButtonClickedEvent;

	////////////////////////////////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    UTexture2D* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	int32 Index = -1;

protected:

	void NativeConstruct() override;
	void NativeOnInitialized() override;

protected:

	UFUNCTION()
	void OnInternalButtonClicked();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials")
    UMaterialInstanceDynamic* NormalMI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials")
    UMaterialInstanceDynamic* HoverMI;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Materials")
    UMaterialInstanceDynamic* PressedMI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Materials")
    UMaterialInterface* DefaultMaterialButton;

	////////////////////////////////////////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    FLinearColor NormalColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    FLinearColor HoverColor = FLinearColor(1.0f, 0.3f, 0.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    FLinearColor PressedColor = FLinearColor(0.0f, 0.3f, 1.0f, 1.0f);

	////////////////////////////////////////////////////////////////////////////////

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
	APOGameMode* BPConfigGameMode;

	////////////////////////////////////////////////////////////////////////////////
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UButton* ButtonObject;
};