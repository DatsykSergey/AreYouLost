#include "Components/HandPoint.h"

UHandPoint::UHandPoint()
{
}

void UHandPoint::BeginPlay()
{
	Super::BeginPlay();
}

bool UHandPoint::CheckHasObject() const
{
	return AttachedObject != nullptr;
}


void UHandPoint::AttachObject(AActor* Object)
{
	UE_LOG(LogTemp, Warning, TEXT("TRY ATTACH OBJECT"));
	if(Object == nullptr)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("OBJECT %s"), *Object->GetName());
	
	if(AttachedObject)
		return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);
	Object->AttachToComponent(this, AttachmentRules);

	AttachedObject = Object;
}

void UHandPoint::DropObject()
{
	FDetachmentTransformRules AttachmentRules(FDetachmentTransformRules::KeepWorldTransform);
	AttachedObject->DetachFromActor(AttachmentRules);
	AttachedObject = nullptr;
}