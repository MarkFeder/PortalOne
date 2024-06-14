// Fill out your copyright notice in the Description page of Project Settings.

#include "POButton.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

#include "Engine/Texture2D.h" 

#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "PortalOne/Core/Configurator.h"
#include "PortalOne/Core/POVariantSet.h"
#include "PortalOne/Core/POGameMode.h"

#include "Styling/SlateTypes.h" 

void UPOButton::InitButton()
{
	BPConfigGameMode = Cast<APOGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!BPConfigGameMode)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("BPConfigGameMode is not a valid ptr."));
		return;
	}

	const AConfigurator* ConfiguratorActor = BPConfigGameMode->GetConfigurator();
	if (!ConfiguratorActor)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("ConfiguratorActor is not a valid ptr."));
		return;
	}

	UCanvasPanelSlot* ButtonCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ButtonObject);
	if (!ButtonCanvasSlot)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("ButtonCanvasSlot is not a valid ptr."));
		return;
	}

	NormalMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, DefaultMaterialButton);
	HoverMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, DefaultMaterialButton);
	PressedMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, DefaultMaterialButton);

	NormalMI->SetTextureParameterValue(TEXT("Image"), Texture);
	NormalMI->SetVectorParameterValue(TEXT("BorderColor"), ConfiguratorActor->ButtonOutlineNormalColor);
	NormalMI->SetScalarParameterValue(TEXT("OutlineSize"), ConfiguratorActor->ButtonOutlineSize);

	HoverMI->K2_CopyMaterialInstanceParameters(NormalMI, false);
	HoverMI->SetVectorParameterValue(TEXT("BorderColor"), ConfiguratorActor->ButtonOutlineHoverColor);

	PressedMI->K2_CopyMaterialInstanceParameters(NormalMI, false);
	HoverMI->SetVectorParameterValue(TEXT("BorderColor"), ConfiguratorActor->ButtonOutlinePressedColor);

	FButtonStyle ButtonStyle;
	ButtonStyle.Normal = UWidgetBlueprintLibrary::MakeBrushFromMaterial(NormalMI, 96.0f, 96.0f);
	ButtonStyle.Hovered = UWidgetBlueprintLibrary::MakeBrushFromMaterial(HoverMI, 96.0f, 96.0f);
	ButtonStyle.Pressed = UWidgetBlueprintLibrary::MakeBrushFromMaterial(PressedMI, 96.0f, 96.0f);

	ButtonObject->SetStyle(ButtonStyle);
	ButtonCanvasSlot->SetSize(FVector2D(ConfiguratorActor->ButtonSize, ConfiguratorActor->ButtonSize));
}

void UPOButton::UpdateImage(UTexture2D* InNewImage)
{
	if (!InNewImage)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("InNewImage is not a valid ptr."));
		return;
	}

	NormalMI->SetTextureParameterValue(TEXT("Image"), InNewImage);
	HoverMI->SetTextureParameterValue(TEXT("Image"), InNewImage);
	PressedMI->SetTextureParameterValue(TEXT("Image"), InNewImage);
}

void UPOButton::NativeConstruct()
{
	Super::NativeConstruct();

	InitButton();
}

void UPOButton::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ButtonObject->OnClicked.AddDynamic(this, &ThisClass::OnInternalButtonClicked);
}

void UPOButton::OnInternalButtonClicked()
{
	OnButtonClickedEvent.Broadcast(Index);
}