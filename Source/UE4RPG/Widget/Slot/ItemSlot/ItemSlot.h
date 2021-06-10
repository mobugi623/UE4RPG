#pragma once

#include "Widget/Slot/BaseSlot.h"
#include "Struct/ItemInfo/ItemInfo.h"
#include "ItemSlot.generated.h"



UCLASS()
class UE4RPG_API UItemSlot : public UBaseSlot
{
	GENERATED_BODY()

private :
	class UDataTable* DT_ItemInfo;
	class UTexture2D* T_Null;

private :
	FItemInfo ItemInfo;


public :
	UItemSlot(const FObjectInitializer& objInitializer);

public :
	// ������ �ʱ�ȭ�մϴ�.
	virtual void InitializeSlot(ESlotType slotType, FName inCode) override;

protected :
	// ������ �̹����� �����մϴ�.
	void UpdateItemImage();

public :
	void SetItemInfo(FName itemCode);
	FORCEINLINE FItemInfo* GetItemInfo()
	{ return &ItemInfo; }
	
};
