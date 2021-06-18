// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.0f,96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f,540.0f,0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	isDead = false;  
	power = 90.0f;
	lifePoint = 100.0f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&AMyCharacter::OnBeginOverlap);
	
	if (Player_Power_Widget_Class != nullptr)
	{
		Player_Power_Widget = CreateWidget(GetWorld(),Player_Power_Widget_Class);
		Player_Power_Widget->AddToViewport();
	}
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (lifePoint <= 0)
	{
		if (!isDead)
		{
			isDead = true;
			GetMesh()->SetSimulatePhysics(true);
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle,this,&AMyCharacter::RestartGame,3.0f,false);
		}
		
	}
	

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward",this,&AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AMyCharacter::MoveRight);


}

void AMyCharacter::MoveForward(float Axis){
	if (!isDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction,Axis); 
	}
	

}

void AMyCharacter::MoveRight(float Axis){
	if (!isDead)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0,Rotation.Yaw,0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction,Axis); 
		}
}

void AMyCharacter::OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor,class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult & SweepResult){
			if(OtherActor->ActorHasTag("Recharge")){//Test Collision
				//UE_LOG(LogTemp,Warning,TEXT("Collided with !"));
				power += 10.0f;
				if(power > 100.0f){
					power = 100.0f;
				}
				OtherActor->Destroy();
			}
}

void AMyCharacter::RestartGame(){
	UGameplayStatics::OpenLevel(this,FName(*GetWorld()->GetName()),false);
}