#include "InteractableAreaComponent.h"

#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"

#include "Component/PlayerInteract/PlayerInteractComponent.h"


void UInteractableAreaComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UInteractableAreaComponent::OnPlayerCharacterDetected);
	OnComponentEndOverlap.AddDynamic(this, &UInteractableAreaComponent::OnPlayerCharacterLost);

}

void UInteractableAreaComponent::StartInteract()
{
	OnInteractStarted.Broadcast(this);

	LOG(TEXT("StartInteract()!"));
}

void UInteractableAreaComponent::OnPlayerCharacterDetected(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	/// ��ģ ���Ͱ� PLAYER_ACTOR_TAG �� ��ġ�ϴ� Tag ���� �ʴ´ٸ� �÷��̾� ĳ���Ͱ� �ƴϹǷ� ���� X
	if (!OtherActor->ActorHasTag(PLAYER_ACTOR_TAG)) return;

	// ĳ���� ���͸� ����ϴ�.
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(OtherActor);

	// �ڽ��� ��ȣ�ۿ� ������ ��ü�� �߰��մϴ�.
	playerCharacter->GetPlayerInteract()->AddInteractable(this);
}

void UInteractableAreaComponent::OnPlayerCharacterLost(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{
	/// ��ģ ���Ͱ� PLAYER_ACTOR_TAG �� ��ġ�ϴ� Tag ���� �ʴ´ٸ� �÷��̾� ĳ���Ͱ� �ƴϹǷ� ���� X
	if (!OtherActor->ActorHasTag(PLAYER_ACTOR_TAG)) return;

	// ĳ���� ���͸� ����ϴ�.
	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(OtherActor);

	// �ڽ��� ��ȣ�ۿ� �Ұ��� ���·� ����ϴ�.
	playerCharacter->GetPlayerInteract()->RemoveInteractable(this);
}
