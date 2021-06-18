// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFirstClass.generated.h"


UCLASS()
class LEARNING_API AMyFirstClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
   	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
    int32 TotalDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
    float DamageTimeInSeconds;

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category="Damage")
    float DamagePerSecond;

	UFUNCTION(BlueprintCallable,Category="Damage")
	void CalculateValues();


	AMyFirstClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitProperties() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

};
