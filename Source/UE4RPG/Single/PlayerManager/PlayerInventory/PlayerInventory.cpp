#include "PlayerInventory.h"

#include "Widget/WidgetController/WidgetController.h"
#include "Widget/ClosableWnd/InventoryWnd/InventoryWnd.h"


UPlayerInventory::UPlayerInventory()
{
	static ConstructorHelpers::FClassFinder<UInventoryWnd> BP_INVENTORY_WND(
		TEXT("WidgetBlueprint'/Game/Blueprints/Widget/ClosableWnd/InventoryWnd/BP_InventoryWnd.BP_InventoryWnd_C'"));
	if (BP_INVENTORY_WND.Succeeded()) BP_InventoryWnd = BP_INVENTORY_WND.Class;

	InventoryWnd = nullptr;
}

UInventoryWnd* UPlayerInventory::CreateInventoryWnd(
	UWidgetController* const	widgetController,
	EInputModeType				changeInputMode, 
	bool						bShowCursor)
{
	if (IsValid(InventoryWnd)) return InventoryWnd;

	// â�� ���ϴ�.
	InventoryWnd = Cast<UInventoryWnd>(
		widgetController->CreateWnd(BP_InventoryWnd, true, changeInputMode, bShowCursor));

	// â�� ���� �� InventoryWnd �� nullptr �� �ɼ� �ֵ��� �մϴ�.
	InventoryWnd->OnWndClosed.AddLambda(
		[this]() { InventoryWnd = nullptr; });

	// ������ InventoryWnd �� ��ȯ�ϵ��� �մϴ�.
	return InventoryWnd;
}

void UPlayerInventory::CloseInventoryWnd()
{
	if (IsValid(InventoryWnd))
		InventoryWnd->CloseThisWnd();
}

void UPlayerInventory::ToggleInventoryWnd(UWidgetController* widgetController)
{
	if (IsValid(InventoryWnd)) CloseInventoryWnd();
	else CreateInventoryWnd(widgetController, EInputModeType::IM_GameAndUI, true);
}
