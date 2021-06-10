#pragma once

#include "UE4RPG.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractComponent.generated.h"


UCLASS()
class UE4RPG_API UPlayerInteractComponent : public UActorComponent
{
	GENERATED_BODY()

private :
	TArray<class UInteractableAreaComponent*> InteractableComponents;

public:	
	UPlayerInteractComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public :
	// ��ȣ�ۿ� ������ ��ü�� �߰��մϴ�.
	/// - newInteractable : ��ȣ�ۿ� ������ ��ü�� �����մϴ�.
	void AddInteractable(class UInteractableAreaComponent* newInteractable);

	// ��ȣ�ۿ� ������ ��ü���� ���ܽ�ŵ�ϴ�.
	/// - removeInteractable : ��ȣ�ۿ� �����ߴ� ��ü�� �����մϴ�.
	void RemoveInteractable(class UInteractableAreaComponent* removeInteractable);

public :
	// ��ȣ�ۿ��� �õ��մϴ�.
	/// - ���� ��ȣ�ۿ� ������ ��ü�� �������� ���� ���, ��ȣ �ۿ��� �̷������ �ʽ��ϴ�.
	void TryInteraction();
		
};
