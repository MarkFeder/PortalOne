// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWidget.h"

DEFINE_LOG_CATEGORY(LogPortalOneUI);

void UBaseWidget::Show_Implementation()
{
	SetRenderOpacity(1);
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	StopAnimation(FadeOutAnimation);
	FadeIn();
}

void UBaseWidget::Hide_Implementation()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UBaseWidget::FadeOut_Implementation()
{
	if (FadeOutAnimation)
	{
		PlayAnimation(FadeOutAnimation);
	}
}

void UBaseWidget::FadeIn_Implementation()
{
	if (FadeInAnimation)
	{
		PlayAnimation(FadeInAnimation);
	}
}

bool UBaseWidget::IsFading()
{
	bool IsFadingIn = IsAnimationPlaying(FadeInAnimation);
	bool IsFadingOut = IsAnimationPlaying(FadeOutAnimation);
	
	return IsFadingIn || IsFadingOut;
}

bool UBaseWidget::IsSpawnHidden()
{
	return SpawnHidden;
}

bool UBaseWidget::IsShowing_Implementation()
{
	bool IsWidgetInViewport = IsInViewport();
	ESlateVisibility CurrentVisibility = GetVisibility();

	bool IsVisible = 
		(CurrentVisibility == ESlateVisibility::SelfHitTestInvisible) || 
		(CurrentVisibility == ESlateVisibility::HitTestInvisible) || 
		(CurrentVisibility == ESlateVisibility::Visible);

	bool IsShowing = (IsWidgetInViewport || GetParent()) && IsVisible;
	return IsShowing;
}