#include "NpcShopWnd.h"

#include "Actor/Controller/PlayerController/BasePlayerController.h"

#include "Single/GameInstance/RPGGameInstance.h"
#include "Single/PlayerManager/PlayerManager.h"


#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/NpcShopWnd/ShopItemWidget/ShopItemWidget.h"
#include "Widget/ClosableWnd/InventoryWnd/InventoryWnd.h"

#include "Components/Button.h"
#include "Components/GridPanel.h"
#include "Components/CanvasPanelSlot.h"

UNpcShopWnd::UNpcShopWnd(const FObjectInitializer& objInitializer) :
	Super(objInitializer)
{
	static ConstructorHelpers::FClassFinder<UShopItemWidget> BP_SHOP_ITEM(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/NpcShopWnd/BP_ShopItem.BP_ShopItem_C'"));
	if (BP_SHOP_ITEM.Succeeded()) BP_ShopItem = BP_SHOP_ITEM.Class;


}

void UNpcShopWnd::NativeConstruct()
{
	Super::NativeConstruct();

	WndSize = FVector2D(665.0f, 600.0f);

	Button_OpenInventory->OnClicked.AddDynamic(this, &UNpcShopWnd::FloatingInventoryWnd);
}

UShopItemWidget* UNpcShopWnd::AddShopItemWidget(const FShopItemInfo& shopItemInfo)
{
	UShopItemWidget * shopItemWidget = CreateWidget<UShopItemWidget>(this, BP_ShopItem);
	GridPanel_ShopItems->AddChild(shopItemWidget);

	shopItemWidget->InitializeShopItemWidget(this, shopItemInfo);

	return shopItemWidget;
}

void UNpcShopWnd::InitializeNpcShop(FShopInfo* shopInfo)
{
	// â ���� ����
	SetTitleText(shopInfo->ShopName);

	const int maxColumnCount = 2;
	int currentColumnCount = 0;

	// �Ǹ� ������ �߰�
	for (auto shopItemInfo : shopInfo->ShopItems)
	{
		UWidgetController::SortGridPanelElem(
			AddShopItemWidget(shopItemInfo),
			maxColumnCount,
			currentColumnCount);
	}

}

void UNpcShopWnd::FloatingInventoryWnd()
{
	auto widgetController = GetManager(UPlayerManager)->GetPlayerController()->GetWidgetController();

	auto inventoryWnd = GetManager(UPlayerManager)->GetPlayerInventory()->CreateInventoryWnd(
		widgetController, EInputModeType::IM_Default, true);

	// npc ���� â ���� ũ�⸦ ����ϴ�.
	FVector2D npcShopWndHalfSize = WndSize * 0.5f;

	// npc ���� â ��ġ�� �����մϴ�.
	FVector2D npcShopWndPosition = GetCanvasPanelSlot()->GetPosition();

	// �κ��丮 â ���� ũ�⸦ ����ϴ�.
	FVector2D inventoryWndHalfSize = inventoryWnd->WndSize * 0.5f;

	// �κ��丮 â�� ��ġ�� ����մϴ�.
	FVector2D newInventoryWndPosition = npcShopWndPosition +
		((npcShopWndHalfSize + inventoryWndHalfSize) * FVector2D(1.0f, 0.0f));

	newInventoryWndPosition.Y += inventoryWndHalfSize.Y - npcShopWndHalfSize.Y;

	// �κ��丮 â�� ��ġ�� �����մϴ�.
	inventoryWnd->GetCanvasPanelSlot()->SetPosition(newInventoryWndPosition);

	// ���� â�� ���� �� �κ��丮 â�� �������� �մϴ�.
	OnWndClosed.AddLambda([this]()
		{ GetManager(UPlayerManager)->GetPlayerInventory()->CloseInventoryWnd(); });

}
