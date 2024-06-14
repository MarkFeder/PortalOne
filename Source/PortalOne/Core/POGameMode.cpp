// Fill out your copyright notice in the Description page of Project Settings.

#include "POGameMode.h"
#include "Configurator.h"

AConfigurator* APOGameMode::GetConfigurator() const
{
	return Configurator;
}

void APOGameMode::SetConfigurator(AConfigurator* InConfigurator)
{
	Configurator = InConfigurator;
}

bool APOGameMode::HasValidConfigurator() const
{
	return IsValid(Configurator);
}