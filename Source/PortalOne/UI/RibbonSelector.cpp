// Fill out your copyright notice in the Description page of Project Settings.

#include "RibbonSelector.h"

#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Engine/Texture2D.h" 

#include "Kismet/GameplayStatics.h"

#include "POButton.h"
#include "PortalOne/Core/Configurator.h"
#include "PortalOne/Core/POGameMode.h"

#include "Styling/SlateColor.h"

#include "Variant.h"
#include "VariantSet.h"

void URibbonSelector::ShowPopup()
{
	SetVisibility(ESlateVisibility::Visible);
	SetIsEnabled(true);
}

void URibbonSelector::HidePopup()
{
	SetVisibility(ESlateVisibility::Hidden);
	SetIsEnabled(false);
}

void URibbonSelector::TogglePopup()
{
	bool bEnabled = !GetIsEnabled();

	SetVisibility(bEnabled ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	SetIsEnabled(bEnabled);
}

FLinearColor URibbonSelector::SetLineColor()
{
	if (!ConfiguratorActor)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("ConfiguratorActor is not a valid ptr."));
		return FLinearColor();
	}

	return ConfiguratorActor->PopupLineColor;
}

FSlateColor URibbonSelector::SetTextColor()
{
	if (!ConfiguratorActor)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("ConfiguratorActor is not a valid ptr."));
		return FSlateColor();
	}

	return FSlateColor(ConfiguratorActor->PopupTextColor);
}

void URibbonSelector::NativeConstruct()
{
	APOGameMode* BPConfigGameMode = Cast<APOGameMode>(UGameplayStatics::GetGameMode(GEngine->GetWorld()));
	if (!BPConfigGameMode)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("BPConfigGameMode is not a valid ptr."));
		return;
	}

	ConfiguratorActor = BPConfigGameMode->GetConfigurator();
	if (!ConfiguratorActor)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("ConfiguratorActor is not a valid ptr."));
		return;
	}

	UVariantSet* InternalVariantSet = VarSet.VariantSet;
	if (!InternalVariantSet)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("InternalVariantSet is not a valid ptr."));
		return;
	}

	VarName->SetText(InternalVariantSet->GetDisplayText());

	int32 NumIntenalVariants = InternalVariantSet->GetNumVariants();

	for (int32 InternalVariantIndex = 0; InternalVariantIndex < NumIntenalVariants; ++InternalVariantIndex)
	{
		UVariant* InternalVariant = InternalVariantSet->GetVariant(InternalVariantIndex);
		if (!InternalVariant)
		{
			UE_LOG(LogPortalOneUI, Error, TEXT("InternalVariant is not a valid ptr."));
			continue;
		}

		UPOButton* VariantSetButton = CreateWidget<UPOButton>(this, ButtonDefaultClass);
		if (!VariantSetButton)
		{
			UE_LOG(LogPortalOneUI, Error, TEXT("VariantSetButton is not a valid ptr."));
			continue;
		}

		VariantSetButton->Index = InternalVariantIndex;
		VariantSetButton->Texture = InternalVariant->GetThumbnail();

		VariantSetButton->OnButtonClickedEvent.AddDynamic(this, &ThisClass::OnVariantSetButtonClicked);

		VarHBox->AddChildToHorizontalBox(VariantSetButton);
	}
}

void URibbonSelector::OnVariantSetButtonClicked(int32 IndexClicked)
{
	OnRibbonOptionSelectedEvent.Broadcast(VariantSetIndex, IndexClicked);
}