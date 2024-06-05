#include "Components/InteractionComponent.h"
#include "Interfaces/InteractableInterface.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractionComponent::Interact() const
{
	AActor* Owner = GetOwner();
	check(Owner);
	FVector StartPosition;
	FRotator LookRotator;

	if(APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		StartPosition = PlayerController->PlayerCameraManager->GetCameraLocation();
		LookRotator = PlayerController->PlayerCameraManager->GetCameraRotation();
	}
	else
	{
		Owner->GetActorEyesViewPoint(StartPosition, LookRotator);
	}

	FVector EndPosition = StartPosition + LookRotator.Vector() * Distance;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(Owner);
	FCollisionResponseParams CollisionResponseParams;
	FHitResult HitResult;
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition,
	                                                  ECollisionChannel::ECC_Visibility, CollisionQueryParams,
	                                                  CollisionResponseParams);

	AActor* HitActor = HitResult.GetActor();
	if (IsHit && HitActor && HitActor->Implements<UInteractableInterface>())
	{
		APawn* Pawn = Cast<APawn>(Owner);
		IInteractableInterface::Execute_Use(HitActor, Pawn);
		DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Green, false, 2.0f, 0, 4.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red, false, 2.0f, 0, 4.0f);
	}
}
