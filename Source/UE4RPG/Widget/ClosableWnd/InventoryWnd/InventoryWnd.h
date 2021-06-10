#pragma once

#include "UE4RPG.h"
#include "Widget/ClosableWnd/ClosableWnd.h"
#include "InventoryWnd.generated.h"

UCLASS()
class UE4RPG_API UInventoryWnd : public UClosableWnd
{
	GENERATED_BODY()

private :
	TSubclassOf<class UInventoryItemSlot> BP_InventoryItemSlot;

private :
	// ������ �κ��丮 ������ ���Ե��� ������ �迭
	TArray<class UInventoryItemSlot*> ItemSlots;

private :
	UPROPERTY(meta = (BindWidget))
	class UGridPanel* GridPanel_ItemSlots;

public :
	UInventoryWnd(const FObjectInitializer& objectInitializer);

protected :
	virtual void NativeConstruct() override;

public :
	void InitializeInventoryWnd();

private :
	// ������ ������ �����մϴ�.
	class UInventoryItemSlot * CreateItemSlot();
	
	
};
