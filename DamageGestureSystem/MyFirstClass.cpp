// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstClass.h"

// Sets default values
AMyFirstClass::AMyFirstClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	TotalDamage = 200;
	DamageTimeInSeconds = 1.0f;
}

void AMyFirstClass::PostInitProperties()
{
    Super::PostInitProperties();
	CalculateValues();
}

void AMyFirstClass::CalculateValues()
{
    DamagePerSecond = TotalDamage / DamageTimeInSeconds;
}

#if WITH_EDITOR
void AMyFirstClass::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    CalculateValues();

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
// Called when the game starts or when spawned
void AMyFirstClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyFirstClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

