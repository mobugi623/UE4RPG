#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractableAreaComponent.generated.h"

DECLARE_EVENT_OneParam(UInteractableAreaComponent, FInteractEvent, UInteractableAreaComponent*)
// �̺�Ʈ
/// - ����� Ŭ���� ���ο����� ȣ���� �� �մ� Multicast_Delegate �Դϴ�.


UCLASS()
class UE4RPG_API UInteractableAreaComponent final : 
	public USphereComponent
{
	GENERATED_BODY()

public :


	// ��ȣ�ۿ��� ���۵� �� �߻��ϴ� �̺�Ʈ
	FInteractEvent OnInteractStarted;

public :
	virtual void BeginPlay() override;

public :
	void StartInteract();

private :
	UFUNCTION()
	void OnPlayerCharacterDetected(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerCharacterLost(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);

		
	
};
