#include "BaseNpc.h"

#include "Single/PlayerManager/PlayerManager.h"
#include "Single/GameInstance/RPGGameInstance.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Widget/NpcDialogWidget/NpcDialogWidget.h"
#include "Widget/WidgetController/WidgetController.h"

#include "Component/InteractableArea/InteractableAreaComponent.h"

ABaseNpc::ABaseNpc()
{
	static ConstructorHelpers::FClassFinder<UNpcDialogWidget> BP_NPC_DIALOG(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/NpcDialog/BP_NpcDialog.BP_NpcDialog_C'"));
	if (BP_NPC_DIALOG.Succeeded()) BP_NpcDialog = BP_NPC_DIALOG.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_NPC_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_NpcInfo.DT_NpcInfo'"));
	if (DT_NPC_INFO.Succeeded()) DT_NpcInfo = DT_NPC_INFO.Object;

	InteractableArea = CreateDefaultSubobject<UInteractableAreaComponent>(TEXT("INTERACTABLE_AREA_COMPONENT"));

	InteractableArea->SetupAttachment(GetRootComponent());
	InteractableArea->SetSphereRadius(250.0f);

}

void ABaseNpc::BeginPlay()
{
	Super::BeginPlay();

	// Npc �ʱ�ȭ
	InitializeNpc();

	// �� Npc �� ��ȣ�ۿ� �� ����� ������ �����մϴ�.
	InteractableArea->OnInteractStarted.AddLambda(
		[this](UInteractableAreaComponent* interactableAreaComponent)
		{
			// PlayerController ��ü�� ����ϴ�.
			auto playerController = GetManager(UPlayerManager)->GetPlayerController();

			// NpcDialogWidget ��ü�� �����մϴ�.
			auto npcDialogWidget = CreateWidget<UNpcDialogWidget>(playerController, BP_NpcDialog);

			// ������ ����� Npc ��ü ����
			npcDialogWidget->ConnectedNpc = this;

			// ������ NpcDialogWidet �� ȭ�鿡 ���ϴ�.
			playerController->GetWidgetController()->AddChildWidget(npcDialogWidget);

			// ���� �ʱ�ȭ
			npcDialogWidget->InitializeDialog();
		});

}

void ABaseNpc::InitializeNpc()
{
	// NpcCode �� �̿��Ͽ� Npc ������ ����ϴ�.
	FString contextString;
	NpcInfo = DT_NpcInfo->FindRow<FNpcInfo>(NpcCode, contextString);

	// Npc ������ ��� �� �����ߴٸ�
	if (NpcInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ABaseNpc.cpp :: %d LINE :: NpcInfo is nullptr! (NpcCode : %s)"),
			__LINE__, *NpcCode.ToString());
	}
}
