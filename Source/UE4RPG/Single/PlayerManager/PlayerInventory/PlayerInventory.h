#pragma once

#include "UE4RPG.h"
#include "UObject/NoExportTypes.h"

#include "Enum/InputModeType.h"

#include "PlayerInventory.generated.h"

UCLASS()
class UE4RPG_API UPlayerInventory final : 
	public UObject
{
	GENERATED_BODY()

private :
	TSubclassOf<class UInventoryWnd> BP_InventoryWnd;

private :
	class UInventoryWnd* InventoryWnd;

public :
	UPlayerInventory();

public :
	// �κ��丮 â�� �����մϴ�.
	class UInventoryWnd* CreateInventoryWnd(
		class UWidgetController* const widgetController,
		EInputModeType changeInputMode = EInputModeType::IM_Default, bool bShowCursor = false);

	// �κ��丮 â�� �ݽ��ϴ�.
	void CloseInventoryWnd();

	// �κ��丮 â�� ����մϴ�.
	void ToggleInventoryWnd(class UWidgetController* widgetController);

public :
	FORCEINLINE class UInventoryWnd* GetInventoryWnd() const
	{ return InventoryWnd; }
	
};
