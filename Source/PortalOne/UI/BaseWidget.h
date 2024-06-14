// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

PORTALONE_API DECLARE_LOG_CATEGORY_EXTERN(LogPortalOneUI, Log, All);

UCLASS()
class PORTALONE_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visibility")
	void Show();
	virtual void Show_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Visibility")
	void Hide();
	virtual void Hide_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	bool IsSpawnHidden();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Visibility")
	bool IsShowing();

	UFUNCTION(BlueprintNativeEvent, Category = "Animation")
	void FadeOut();

	UFUNCTION(BlueprintNativeEvent, Category = "Animation")
	void FadeIn();

	UFUNCTION(BlueprintPure, Category = "Animation")
	bool IsFading();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Visibility")
	bool SpawnHidden = false;

	UPROPERTY(BlueprintReadWrite, Category = "Animation", meta = (BindWidgetAnimOptional), transient)
	TObjectPtr<UWidgetAnimation> FadeInAnimation;

	UPROPERTY(BlueprintReadWrite, Category = "Animation", meta = (BindWidgetAnimOptional), transient)
	TObjectPtr<UWidgetAnimation> FadeOutAnimation;
};
