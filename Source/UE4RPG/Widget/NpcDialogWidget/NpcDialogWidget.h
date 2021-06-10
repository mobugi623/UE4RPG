#pragma once

#include "UE4RPG.h"
#include "Blueprint/UserWidget.h"
#include "Struct/NpcDialogInfo/NpcDialogInfo.h"
#include "NpcDialogWidget.generated.h"

UCLASS()
class UE4RPG_API UNpcDialogWidget final : 
	public UUserWidget
{
	GENERATED_BODY()

public :
	class ABaseNpc* ConnectedNpc;
	TSubclassOf<class UNpcShopWnd> BP_NpcShopWnd;
	class UDataTable* DT_ShopInfo;

private : 
	class UNpcShopWnd* NpcShopWnd;

private :
	// ǥ�õǴ� ��ȭ ������ ��Ÿ���ϴ�.
	FNpcDialogInfo DialogInfo;

	// ���� ǥ�õǴ� ��ȭ ���� �ε����� ��Ÿ���ϴ�.
	int32 CurrentDialogIndex;

	// ������ ��ȭ���� ��Ÿ���ϴ�.
	bool bIsLastDialog;

private :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_NpcName;

#pragma region Button Panel

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_GoToFirst;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Quest;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Shop;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button_Exit;

#pragma endregion




#pragma region Dialog Panel

	UPROPERTY(meta = (BindWidget))
	class UTextBlock * Text_Dialog;

	UPROPERTY(meta = (BindWidget))
	class UButton * Button_Next;

#pragma endregion

public :
	UNpcDialogWidget(const FObjectInitializer& ObjectInitializer);

protected :
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private :
	// ������ ������ ��ȭ�� ǥ���մϴ�.
	void ShowDialog(int32 newDialogIndex);

	void SetButtonVisibility(class UButton* button, bool bVisible);


#pragma region Button Events

public :
	void InitializeDialog();

private :
	UFUNCTION()
	void OnNextDialogButtonClicked();

	UFUNCTION()
	void OnShopButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

#pragma endregion


	
};
