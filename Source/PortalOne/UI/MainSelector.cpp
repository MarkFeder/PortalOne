// Fill out your copyright notice in the Description page of Project Settings.

#include "MainSelector.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"

#include "Engine/Texture2D.h" 

#include "Kismet/GameplayStatics.h"

#include "Layout/Margin.h"

#include "POButton.h"
#include "RibbonSelector.h"

#include "PortalOne/Core/Configurator.h"
#include "PortalOne/Core/POVariantSet.h"
#include "PortalOne/Core/POGameMode.h"

#include "Variant.h"
#include "VariantSet.h"

void UMainSelectorWidget::PopulateOptions()
{
	APOGameMode* POGameMode = Cast<APOGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!POGameMode)
	{	
		UE_LOG(LogPortalOneUI, Error, TEXT("POGameMode is not a valid ptr."));
		return;
	}

	AConfigurator* Configurator = POGameMode->GetConfigurator();
	if (!Configurator)
	{
		UE_LOG(LogPortalOneUI, Error, TEXT("ConfiguratorActor is not a valid ptr."));
		return;
	}

	ObjVarSet = Configurator->GetObjectVariantSets();

	int32 ObjVarSetNum = ObjVarSet.Num();

	for (int32 IndexObjVarSet = 0; IndexObjVarSet < ObjVarSetNum; ++IndexObjVarSet)
	{
		if (!ObjVarSet.IsValidIndex(IndexObjVarSet))
		{
			UE_LOG(LogPortalOneUI, Error, TEXT("ObjVarSet is not a valid ptr."));
			continue;
		}

		const FPOVariantSet& VariantSet = ObjVarSet[IndexObjVarSet];
		
		// Init with image from variant 0
		UVariant* InternalVariant = VariantSet.VariantSet->GetVariant(0);
		if (!InternalVariant)
		{
			UE_LOG(LogPortalOneUI, Error, TEXT("InternalVariant is not a valid ptr."));
			continue;
		}

		// Create Button
		UPOButton* VariantSetButton = CreateWidget<UPOButton>(this, ButtonDefaultClass);
		if (!VariantSetButton)
		{
			UE_LOG(LogPortalOneUI, Error, TEXT("VariantSetButton is not a valid ptr."));
			continue;
		}

		VariantSetButton->Index = IndexObjVarSet;
		VariantSetButton->Texture = InternalVariant->GetThumbnail();

		VariantSetButtons.Add(VariantSetButton);
		PartSelectorHBox->AddChildToHorizontalBox(VariantSetButton);

		URibbonSelector* VariantRibbonSelector = CreateWidget<URibbonSelector>(this, RibbonDefaultClass);
		if (!VariantRibbonSelector)
		{
			UE_LOG(LogPortalOneUI, Error, TEXT("VariantRibbonSelector is not a valid ptr."));
			continue;
		}

		VariantRibbonSelector->VariantSetIndex = IndexObjVarSet;
		VariantRibbonSelector->VarSet = VariantSet;

		VariantSetRibbons.Add(VariantRibbonSelector);
		UCanvasPanelSlot* RibbonPanelSlot = UpperRibbonArea->AddChildToCanvas(VariantRibbonSelector);

		FAnchorData RibbonAnchorData;
		RibbonAnchorData.Anchors = FAnchors(0.5f, 0.5f);
		RibbonAnchorData.Alignment = FVector2D(0.5f, 0.5f);

		RibbonPanelSlot->SetAutoSize(true);
		RibbonPanelSlot->SetLayout(RibbonAnchorData);

		VariantRibbonSelector->HidePopup();
	}
}

void UMainSelectorWidget::CreateEventBindings()
{
	for (UPOButton* VariantSetButton : VariantSetButtons)
	{
		if (!VariantSetButton)
		{
			UE_LOG(LogPortalOneUI, Error, TEXT("VariantSetButton is not a valid ptr."));
			continue;
		}

		if (!VariantSetButton->OnButtonClickedEvent.IsBound())
		{
			VariantSetButton->OnButtonClickedEvent.AddDynamic(this, &ThisClass::OnVariantSetButtonClicked);
		}
	}

	for (URibbonSelector* VariantSetRibbon : VariantSetRibbons)
	{
		if (!VariantSetRibbon)
		{
			UE_LOG(LogPortalOneUI, Error, TEXT("VariantSetRibbon is not a valid ptr."));
			continue;
		}

		if (!VariantSetRibbon->OnRibbonOptionSelectedEvent.IsBound())
		{
			VariantSetRibbon->OnRibbonOptionSelectedEvent.AddDynamic(this, &ThisClass::OnRibbonOptionSelected);
		}
	}
}

void UMainSelectorWidget::HideRibbons()
{
	for (URibbonSelector* RibbonSelector : VariantSetRibbons)
	{
		RibbonSelector->HidePopup();
	}
}

void UMainSelectorWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PopulateOptions();
	CreateEventBindings();
}

void UMainSelectorWidget::OnVariantSetButtonClicked(int32 IndexClicked)
{
	int32 NumVariantSetRibbons = VariantSetRibbons.Num();

	for (int32 IndexSetRibbon = 0; IndexSetRibbon < NumVariantSetRibbons; ++IndexSetRibbon)
	{
		URibbonSelector* RibbonSelector = VariantSetRibbons[IndexSetRibbon];

		if (IndexSetRibbon == IndexClicked)
		{
			RibbonSelector->TogglePopup();
		}
		else
		{
			RibbonSelector->HidePopup();
		}
	}
}

void UMainSelectorWidget::OnRibbonOptionSelected(int32 RibbonVariantSetIndex, int32 IndexSelected)
{
	OnPartSelected.Broadcast(RibbonVariantSetIndex, IndexSelected);

	UPOButton* VariantButton = VariantSetButtons[RibbonVariantSetIndex];
	UVariant* SelectedVariant = ObjVarSet[RibbonVariantSetIndex].VariantSet->GetVariant(IndexSelected);

	VariantButton->UpdateImage(SelectedVariant->GetThumbnail());
}