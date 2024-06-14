// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RuntimeAction.h"
#include "Environment.generated.h"

class UArrowComponent;
class UDirectionalLightComponent;
class UMaterialInterface;
class UPostProcessComponent;
class USceneComponent;
class USkyLightComponent;
class UStaticMeshComponent;

UCLASS()
class PORTALONE_API AEnvironment : public AActor, public IRuntimeAction
{
	GENERATED_BODY()
	
public:	
	
	AEnvironment();

    void VariantInitialize_Implementation() override;

    void VariantSwitchedOn_Implementation() override;

protected:
	
	virtual void BeginPlay() override;

protected:

    UFUNCTION(BlueprintCallable)
    void Init();

    UFUNCTION(BlueprintCallable)
    void FullUpdate();

    UFUNCTION(BlueprintCallable)
    void SetSunAttributes();

    UFUNCTION(BlueprintCallable)
    void SetPostProcessAttributes();

    UFUNCTION(BlueprintCallable)
    void UpdateEnv();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* DefaultSceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* EnvComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* LightsComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDirectionalLightComponent* SunComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UArrowComponent* ArrowComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkyLightComponent* SkyLightComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPostProcessComponent* PostProcessComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* StaticMeshComponent;

    ////////////////////////////////////////////////////////////////////////////////

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UMaterialInterface* DefaultMaterialBGEnv;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UTextureCube* EnvMap;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UTextureCube* SkyLightCubeMap;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FLinearColor EnvTint = FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float SkyLightIntensity = 1.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float EnvIntensity = 1.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UMaterialInstanceDynamic* BGMaterial;

    ////////////////////////////////////////////////////////////////////////////////

    UPROPERTY(BlueprintReadOnly, Category = "ENV Sun")
    bool bUseSunLight = false;

    UPROPERTY(BlueprintReadOnly, Category = "ENV Sun")
    float SunPosition = 45.0f;

    UPROPERTY(BlueprintReadOnly, Category = "ENV Sun")
    float SunHeight = 45.0f;

    UPROPERTY(BlueprintReadOnly, Category = "ENV Sun")
    float SunIntensity = 8.0f;

    UPROPERTY(BlueprintReadOnly, Category = "ENV Sun")
    float SunTemperature = 6500.0f;

    ////////////////////////////////////////////////////////////////////////////////

    UPROPERTY(BlueprintReadOnly, Category = "ENV Image")
    float EV = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "ENV Image")
    float Gamma = 1.2f;
};
