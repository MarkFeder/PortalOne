// Fill out your copyright notice in the Description page of Project Settings.

#include "Environment.h"

#include "Components/ArrowComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/TextureCube.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/MaterialInterface.h" 

AEnvironment::AEnvironment()
{
	PrimaryActorTick.bCanEverTick = true;

    // Create the DefaultSceneRootComponent
    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRootComponent"));
    RootComponent = DefaultSceneRoot;

    // Create the Lights SceneComponent
    LightsComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Lights"));
    LightsComponent->SetupAttachment(DefaultSceneRoot);

    // Create the Sun DirectionalLightComponent
    SunComponent = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("Sun"));
    SunComponent->SetupAttachment(LightsComponent);

    // Create the Arrow ArrowComponent
    ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    ArrowComponent->SetupAttachment(SunComponent);

    // Create the EnvComponent
    EnvComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Env"));
    EnvComponent->SetupAttachment(DefaultSceneRoot);

    // Create the SkyLightComponent
    SkyLightComponent = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
    SkyLightComponent->SetupAttachment(EnvComponent);

    // Create the PostProcessComponent
    PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
    PostProcessComponent->SetupAttachment(EnvComponent);

    // Create the PostProcessComponent
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_BGEnvSphere"));
    StaticMeshComponent->SetupAttachment(EnvComponent);
}

void AEnvironment::VariantInitialize_Implementation()
{
    FullUpdate();
}

void AEnvironment::VariantSwitchedOn_Implementation()
{
    FullUpdate();
}

void AEnvironment::BeginPlay()
{
	Super::BeginPlay();
    
    Init();
    FullUpdate();
}

void AEnvironment::Init()
{
    if (!DefaultMaterialBGEnv || !StaticMeshComponent)
    {
        return;
    }

    BGMaterial = UMaterialInstanceDynamic::Create(DefaultMaterialBGEnv, this, FName("MID_BGEnvMat"));
    StaticMeshComponent->SetMaterial(0, BGMaterial);
}

void AEnvironment::FullUpdate()
{
    UpdateEnv();
    SetSunAttributes();
    SetPostProcessAttributes();
}

void AEnvironment::SetSunAttributes()
{
    if (!LightsComponent || !SunComponent)
    {
        return;
    }

    LightsComponent->SetVisibility(bUseSunLight, true);

    if (bUseSunLight)
    {
        const FRotator& RotatorA = UKismetMathLibrary::RotatorFromAxisAndAngle(UKismetMathLibrary::Vector_Right(), SunHeight);
        const FRotator& RotatorB = UKismetMathLibrary::RotatorFromAxisAndAngle(UKismetMathLibrary::Vector_Up(), SunPosition);
        SunComponent->SetRelativeRotation(UKismetMathLibrary::ComposeRotators(RotatorA, RotatorB));

        SunComponent->SetIntensity(SunIntensity);
        SunComponent->SetTemperature(SunTemperature);
    }
}

void AEnvironment::SetPostProcessAttributes()
{
    if (!PostProcessComponent)
    {
        return;
    }

    const FVector4& PostProcessGamma = UKismetMathLibrary::MakeVector4(1.0f, 1.0f, 1.0f, Gamma);

    FPostProcessSettings& PostProcessSettings = PostProcessComponent->Settings;
    PostProcessSettings.ColorGamma = PostProcessGamma;
    PostProcessSettings.AutoExposureBias = EV;
}

void AEnvironment::UpdateEnv()
{
    if (!SkyLightComponent || !SkyLightCubeMap || !BGMaterial)
    {
        return;
    }

    SkyLightComponent->SetCubemap(SkyLightCubeMap);
    SkyLightComponent->SetIntensity(SkyLightIntensity);

    BGMaterial->SetVectorParameterValue(TEXT("Tint"), EnvTint);
    BGMaterial->SetTextureParameterValue(TEXT("ENVMap"), EnvMap);
}