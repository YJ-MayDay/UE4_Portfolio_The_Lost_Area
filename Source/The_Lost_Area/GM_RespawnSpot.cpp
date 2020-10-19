// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_RespawnSpot.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

AGM_RespawnSpot::AGM_RespawnSpot()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = TriggerBox;
}

void AGM_RespawnSpot::BeginPlay()
{
	Super::BeginPlay();
}

void AGM_RespawnSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

