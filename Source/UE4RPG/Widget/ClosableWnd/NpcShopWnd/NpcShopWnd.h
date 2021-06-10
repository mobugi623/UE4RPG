#pragma once

#include "UE4RPG.h"
#include "Widget/ClosableWnd/ClosableWnd.h"

#include "Struct/ShopInfo/ShopInfo.h"
#include "Struct/ShopItemInfo/ShopItemInfo.h"

#include "NpcShopWnd.generated.h"

UCLASS()
class UE4RPG_API UNpcShopWnd : public UClosableWnd
{
	GENERATED_BODY()

private :
	TSubclassOf<class UShopItemWidget> BP_ShopItem;

private :
	UPROPERTY(meta = (BindWidget))
	class UGridPanel * GridPanel_ShopItems;

	UPROPERTY(meta = (BindWidget))
	class UButton * Button_OpenInventory;
	
public :
	UNpcShopWnd(const FObjectInitializer& objInitializer);

protected :
	virtual void NativeConstruct() override;

private :
	// �Ǹ� �������� �߰��մϴ�.
	/// - shopItemInfo : �Ǹ� ������ ������ �����մϴ�.
	class UShopItemWidget* AddShopItemWidget(const FShopItemInfo& shopItemInfo);

public : 
	// ���� â�� �ʱ�ȭ�մϴ�.
	void InitializeNpcShop(FShopInfo* shopInfo);

	UFUNCTION()
	void FloatingInventoryWnd();

};
