#include "PlayerInteractComponent.h"

#include "Component/InteractableArea/InteractableAreaComponent.h"

UPlayerInteractComponent::UPlayerInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerInteractComponent::AddInteractable(UInteractableAreaComponent* newInteractable)
{
	if (!InteractableComponents.Contains(newInteractable))
		InteractableComponents.Add(newInteractable);
}

void UPlayerInteractComponent::RemoveInteractable(UInteractableAreaComponent* removeInteractable)
{
	if (InteractableComponents.Contains(removeInteractable))
		InteractableComponents.Remove(removeInteractable);
}

void UPlayerInteractComponent::TryInteraction()
{
	// ��ȣ�ۿ� ������ ��ü�� �������� ���� ��� ���� X
	if (InteractableComponents.Num() < 1) return;

	// �÷��̾� ĳ���Ϳ� ���� ����� ��ü�� ��ȣ�ۿ��� �����մϴ�.
	InteractableComponents[0]->StartInteract();
}