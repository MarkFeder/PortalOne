#include "Configurator.h"
// Fill out your copyright notice in the Description page of Project Settings.

#include "Configurator.h"

#include "GameFramework/PlayerController.h" 

#include "Kismet/GameplayStatics.h"

#include "LevelVariantSets.h"
#include "LevelVariantSetsActor.h"

#include "PortalOne/Core/POGameMode.h"
#include "PortalOne/UI/MainGUI.h"

#include "RuntimeAction.h"

#include "Variant.h"
#include "VariantSet.h"

AConfigurator::AConfigurator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AConfigurator::BeginPlay()
{
	Super::BeginPlay();

	APOGameMode* POGameMode = Cast<APOGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!POGameMode)
	{
		return;
	}
	
	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PController)
	{
		return;
	}

	GUI = CreateWidget<UMainGUI>(GetWorld(), GUIDefaultClass);
	if (!GUI)
	{
		return;
	}

	// Set our configurator class inside the game mode base class...
	POGameMode->SetConfigurator(this);

	InitConfigVarSets();
	ResetAllVariants();

	GUI->AddToViewport();

	FInputModeUIOnly InputMode; InputMode.SetWidgetToFocus(GUI->GetCachedWidget());

	PController->EnableInput(PController);
	PController->SetInputMode(InputMode);
	PController->SetShowMouseCursor(true);

	GUI->OnNewPartSelected.AddDynamic(this, &ThisClass::OnPartSelected);
}

TArray<FPOVariantSet>& AConfigurator::GetObjectVariantSets()
{
	return ObjectVariantSets;
}

void AConfigurator::InitConfigVarSets()
{
	ObjectVariantSets.Empty();

	ULevelVariantSets* LevelVariantSets = LVSActor->GetLevelVariantSets(true);
	int32 NumLevelVariantSets = LevelVariantSets->GetNumVariantSets();

	for (int32 VariantIndex = 0; VariantIndex < NumLevelVariantSets; ++VariantIndex)
	{	
		UVariantSet* LevelVariantSet = LevelVariantSets->GetVariantSet(VariantIndex);
		if (!LevelVariantSet)
		{
			continue;
		}

		FPOVariantSet OurVariantSet;
		OurVariantSet.VariantSet = LevelVariantSet;
		OurVariantSet.CurrentIndex = VariantIndex;

		if (VariantIndex == 0)
		{
			// Cache the variant set for environment and do not add it to our internal list
			EnviroVarSet = OurVariantSet;
			continue;
		}

		ObjectVariantSets.Add(OurVariantSet);
	}
}

void AConfigurator::ResetAllVariants()
{
	for (FPOVariantSet& VariantSet : ObjectVariantSets)
	{
		ResetVariant(VariantSet);
	}

	ResetVariant(EnviroVarSet);
}

void AConfigurator::ResetVariant(FPOVariantSet& InVariantSet)
{
	UVariantSet* ThisVariantSet = InVariantSet.VariantSet;
	if (!ThisVariantSet)
	{
		return;
	}

	UVariant* ThisInternalVariant = ThisVariantSet->GetVariant(0);
	if (!ThisInternalVariant)
	{
		return;
	}

	ThisInternalVariant->SwitchOn();
	CallVariantActor(ThisVariantSet, 0, true);
}

void AConfigurator::ActivateVariant(FPOVariantSet& InVariantSet, int32 InVariantIndex)
{
	UVariantSet* ThisVariantSet = InVariantSet.VariantSet;
	if (!ThisVariantSet)
	{
		return;
	}

	UVariant* ThisInternalVariant = ThisVariantSet->GetVariant(InVariantIndex);
	if (!ThisInternalVariant)
	{
		return;
	}

	ThisInternalVariant->SwitchOn();
	InVariantSet.CurrentIndex = InVariantIndex;
	CallVariantActor(ThisVariantSet, InVariantIndex, false);
}

void AConfigurator::CallVariantActor(UVariantSet* InVariantSet, int32 InCurrentIndex, bool bInit)
{
	if (!InVariantSet)
	{
		return;
	}
	
	UVariant* InternalVariant = InVariantSet->GetVariant(InCurrentIndex);
	if (!InternalVariant)
	{
		return;
	}

	int32 NumVariantActors = InternalVariant->GetNumActors();

	for (int32 VariantActorIndex = 0; VariantActorIndex < NumVariantActors; ++VariantActorIndex)
	{
		AActor* InternalVariantActor = InternalVariant->GetActor(VariantActorIndex);
		if (!InternalVariantActor)
		{
			continue;
		}

		if (InternalVariantActor->GetClass()->ImplementsInterface(URuntimeAction::StaticClass()))
		{
			if (bInit)
			{
				IRuntimeAction::Execute_VariantInitialize(InternalVariantActor);
			}
			else
			{
				IRuntimeAction::Execute_VariantSwitchedOn(InternalVariantActor);
			}
		}

		for (UActorComponent* InternalVariantActorComponent : InternalVariantActor->GetComponentsByInterface(URuntimeAction::StaticClass()))
		{
			if (!InternalVariantActorComponent)
			{
				continue;
			}

			if (InternalVariantActorComponent->GetClass()->ImplementsInterface(URuntimeAction::StaticClass()))
			{
				if (bInit)
				{
					IRuntimeAction::Execute_VariantInitialize(InternalVariantActorComponent);
				}
				else
				{
					IRuntimeAction::Execute_VariantSwitchedOn(InternalVariantActor);
				}
			}
		}
	}
}

void AConfigurator::OnPartSelected(int32 VariantSetIndex, int32 VariantIndex)
{
	ActivateVariant(ObjectVariantSets[VariantSetIndex], VariantIndex);
}