// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"
#include "GamePlayerController.generated.h"

UCLASS()
class UE4RPG_API AGamePlayerController : public ABasePlayerController
{
	GENERATED_BODY()
	
protected :
	virtual void SetupInputComponent() override;

private :
	void MouseXInput(float axis);
	void MouseYInput(float axis);

private :
	void OpenInventory();

};
