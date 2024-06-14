// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGUI.h"

#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"

#include "MainSelector.h"
#include "PortalOne/Core/Configurator.h"
#include "PortalOne/Core/POGameMode.h"

void UMainGUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BackgroundBTN->OnClicked.AddDynamic(this, &ThisClass::OnBackgroundButtonClicked);
	MainPartVarSelector->OnPartSelected.AddDynamic(this, &ThisClass::OnPartSelected);
}

void UMainGUI::OnBackgroundButtonClicked()
{
	MainPartVarSelector->HideRibbons();
}

void UMainGUI::OnPartSelected(int32 SetIndex, int32 Index)
{
	OnNewPartSelected.Broadcast(SetIndex, Index);
}