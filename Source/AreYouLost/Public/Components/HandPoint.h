#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HandPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AREYOULOST_API UHandPoint : public UPrimitiveComponent
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TestValue = 1.0f;
	
	UHandPoint();

	bool CheckHasObject() const;
	
	UFUNCTION(BlueprintCallable)
	void AttachObject(AActor* Object);
	
	void DropObject();
	
protected:
	AActor* AttachedObject;
	
	virtual void BeginPlay() override;
};
