#include "PlayerManager.h"


#include "Actor/Character/PlayerCharacter/PlayerCharacter.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"

void UPlayerManager::RegisterPlayer(
	ABasePlayerController* newPlayerController,
	APlayerCharacter* newPlayerCharacter)
{
	PlayerController = newPlayerController;
	(PlayerCharacter = newPlayerCharacter)->Tags.Add(PLAYER_ACTOR_TAG);

}

void UPlayerManager::InitManagerClass()
{
	PlayerInventory = NewObject<UPlayerInventory>(this, UPlayerInventory::StaticClass(),
		NAME_None, EObjectFlags::RF_MarkAsRootSet);
}

void UPlayerManager::ShutdownManagerClass()
{
	// Release PlayerInventory
	// �ش� ��ü�� GC �� ���� ������ ��ü���� Ȯ��
	if (!PlayerInventory->IsValidLowLevel()) return;

	// �ƴ϶�� ��ü �Ҹ�
	PlayerInventory->ConditionalBeginDestroy();
	PlayerInventory = nullptr;
}
