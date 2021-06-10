#include "NpcDialogWidget.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"

#include "Actor/Character/BaseNpc/BaseNpc.h"
#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/NpcShopWnd/NpcShopWnd.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Struct/ShopInfo/ShopInfo.h"

UNpcDialogWidget::UNpcDialogWidget(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UNpcShopWnd> BP_NPC_SHOP_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/NpcShopWnd/BP_NpcShopWnd.BP_NpcShopWnd_C'"));
	if (BP_NPC_SHOP_WND.Succeeded()) BP_NpcShopWnd = BP_NPC_SHOP_WND.Class;

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SHOP_INFO(
		TEXT("DataTable'/Game/Resources/DataTable/DT_ShopInfo.DT_ShopInfo'"));
	if (DT_SHOP_INFO.Succeeded()) DT_ShopInfo = DT_SHOP_INFO.Object;

	NpcShopWnd = nullptr;
}

void UNpcDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �� ������ ��Ŀ���� �����ϵ��� �մϴ�.
	bIsFocusable = true;

	// Ű���� ��Ŀ���� �����մϴ�.
	SetKeyboardFocus();

	Button_Exit->OnClicked.AddDynamic(this, &UNpcDialogWidget::OnExitButtonClicked);
	Button_Shop->OnClicked.AddDynamic(this, &UNpcDialogWidget::OnShopButtonClicked);
	Button_Next->OnClicked.AddDynamic(this, &UNpcDialogWidget::OnNextDialogButtonClicked);
}

FReply UNpcDialogWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// R Ű �Է� ��
	if (InKeyEvent.GetKey() == EKeys::R)
	{
		// ���� ��ȭ ������ ǥ���մϴ�.
		OnNextDialogButtonClicked();
		return FReply::Handled();
	}
	else return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UNpcDialogWidget::ShowDialog(int32 newDialogIndex)
{
	// ��ȭ ������ ����ִ��� Ȯ���մϴ�.
	if (DialogInfo.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("NpcDialogWidget.cpp :: %d LINE :: DialogInfo is Empty!"), __LINE__);
		return;
	}

	// ǥ�ý�ų ��ȭ �ε����� ������ ��ȭ �ε����� �ʰ��ϴ��� Ȯ���մϴ�.
	if (DialogInfo.GetLastDialogIndex() < newDialogIndex)
	{
		LOG(TEXT("NpcDialogWidget.cpp :: %d LINE :: [Warning] Out Of Range! newDialogIndex is Changed. (%d -> %d)"),
			__LINE__, newDialogIndex, DialogInfo.GetLastDialogIndex());

		newDialogIndex = DialogInfo.GetLastDialogIndex();
	}

	// ��ȭ ���� �ؽ�Ʈ ����
	Text_Dialog->SetText(DialogInfo.DialogText[newDialogIndex]);

	// ������ ��ȭ���
	bIsLastDialog = (DialogInfo.GetLastDialogIndex() == newDialogIndex);

	// ������ ��ȭ��� Next ��ư�� ����ϴ�.
	if (bIsLastDialog)
	{
		SetButtonVisibility(Button_Next, false);
	}

	// ������ ��ȭ�� �ƴ��ϸ� Next ��ư�� ǥ���մϴ�.
	else SetButtonVisibility(Button_Next, true);
}

void UNpcDialogWidget::SetButtonVisibility(UButton* button, bool bVisible)
{
	button->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UNpcDialogWidget::InitializeDialog()
{
	FNpcInfo* npcInfo = ConnectedNpc->GetNpcInfo();

	if (npcInfo == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NpcDialogWidget.cpp :: %d LINE :: npcInfo is nullptr!"), __LINE__);
		return;
	}

	bIsLastDialog = false;

	// Npc �̸� ����
	Text_NpcName->SetText(npcInfo->NpcName);

	// ��ȭ ������ �⺻ ��ȭ �������� �����մϴ�.
	DialogInfo = npcInfo->DefaultDialogInfo;

	// ��ȭ ������ ó������ �ǵ����ϴ�.
	CurrentDialogIndex = 0;

	// ��ȭ ���� ǥ��
	ShowDialog(CurrentDialogIndex);
}

void UNpcDialogWidget::OnNextDialogButtonClicked()
{
	ShowDialog(++CurrentDialogIndex);
}

void UNpcDialogWidget::OnShopButtonClicked()
{
	if (IsValid(NpcShopWnd)) return;

	// ���� ������ ����ϴ�.
	FString contextString;
	FShopInfo* shopInfo = DT_ShopInfo->FindRow<FShopInfo>(
		ConnectedNpc->GetNpcInfo()->ShopCode, contextString);

	NpcShopWnd = Cast<UNpcShopWnd>(
		GetManager(UPlayerManager)->GetPlayerController()->GetWidgetController()->
		CreateWnd(BP_NpcShopWnd, true));

	// �κ��丮 â ����
	NpcShopWnd->FloatingInventoryWnd();

	// Npc ���� â �ʱ�ȭ
	NpcShopWnd->InitializeNpcShop(shopInfo);

	// ���� â ���� �̺�Ʈ ����
	NpcShopWnd->OnWndClosed.AddLambda([this]() { NpcShopWnd = nullptr; });
}

void UNpcDialogWidget::OnExitButtonClicked()
{
	ABasePlayerController * playerController = GetManager(UPlayerManager)->GetPlayerController();

	// �� ������ �ݽ��ϴ�.
	playerController->GetWidgetController()->CloseChildWidget(this);
}
