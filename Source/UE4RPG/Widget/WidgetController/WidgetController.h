#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Enum/InputModeType.h"

#include "WidgetController.generated.h"

UCLASS()
class UE4RPG_API UWidgetController final : 
	public UUserWidget
{
	GENERATED_BODY()

private :
	class ABasePlayerController* PlayerController;

	// �Ҵ�Ǿ��ִ� Widget ��ü���� ��Ÿ���ϴ�.
	/// - â ��ü�� �߰����� �ʽ��ϴ�.
	TArray<UUserWidget*> AllocatedWidgets;

	// �Ҵ�Ǿ��ִ� ClosableWnd ��ü���� ��Ÿ���ϴ�.
	TArray<class UClosableWnd*> AllocatedWnds;

	// ���� â���� ���� ��ġ�� �����մϴ�.
	TMap<FString, FVector2D> PrevClosedWndPositions;
		

private :
	// â ��ü���� �ƴ� HUD �� �߰��� ĵ����
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WidgetParent;

	// â ��ü���� �߰��� ĵ����
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel_WndParent;

private :
	// �Է� ���, Ŀ�� ǥ�ø� �⺻ ������ �ʱ�ȭ�մϴ�.
	/// - ���� �����̳�, â�� �����Ѵٸ� �Է� ��尡 �ʱ�ȭ���� �ʽ��ϴ�.
	/// - bForceChange : ���� �����̳�, â�� ���� ���θ� �����ϰ� ������ �ʱ�ȭ��ų �������� ���� ���θ� �����մϴ�.
	void ResetInputMode(bool bForceChange = false);

	// â�� ��ġ�� �����մϴ�.
	void SaveWndPosition(const class UClosableWnd* closableWnd);

public :
	// Widget Controller �� �ʱ�ȭ�մϴ�.
	void InitializeWidgetController(class ABasePlayerController* playerController);

	// ���� ������ �߰��մϴ�.
	/// - �߰��� ������ CanvasPanel_WidgetParent ĵ���� ������ �߰��Ǹ�,
	///   â �����麸�� ����, ��ȣ�ۿ� �켱������ �����ϴ�.
	/// - childWidgetInstance : �߰��� ���� ���� ��ü�� �����մϴ�.
	/// - bShowMouseCursor : â�� ��� �� Ŀ���� ǥ���� �������� ���� ���θ� �����մϴ�.
	/// - width : ��� ������ �ʺ� �����մϴ�.
	/// - height : ��� ������ ���̸� �����մϴ�.
	void AddChildWidget(class UUserWidget* childWidgetInstance, 
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float width = 1920.0f, float height = 1080.0f);

	// �߰���Ų ���� ������ �ݽ��ϴ�.
	/// - childWidgetInstance : ���� ���� ��ü�� �����մϴ�.
	void CloseChildWidget(class UUserWidget* childWidgetInstance);

	// â�� �����մϴ�.
	// wndClass : ������ â UClass �� �����մϴ�.
	// bUsePrevPosition : â�� ���� ��ġ ��� ���θ� �����մϴ�.
	// changeInputMode : â�� ��� �� ������ �Է� ��带 �����մϴ�.
	// bShowMouseCursor : Ŀ�� ǥ�� ���θ� �����մϴ�.
	// alignmentX : ���� �������� �Ǵ� X��ġ�� �����մϴ�.
	// alignmentY : ���� �������� �Ǵ� Y��ġ�� �����մϴ�.
	// anchorMinX : ��ġ �� �������� �Ǵ� X��ġ
	// anchorMinY : ��ġ �� �������� �Ǵ� Y��ġ
	// anchorMaxX : ��ġ �� �������� �Ǵ� X��ġ
	// anchorMaxY : ��ġ �� �������� �Ǵ� Y��ġ
	class UClosableWnd* CreateWnd(TSubclassOf<class UClosableWnd> wndClass,
		bool bUsePrevPosition = false,
		EInputModeType changeInputMode = EInputModeType::IM_UIOnly,
		bool bShowMouseCursor = true,
		float alignmentX = 0.5f, float alignmentY = 0.5f,
		float anchorMinX = 0.5f, float anchorMinY = 0.5f,
		float anchorMaxX = 0.5f, float anchorMaxY = 0.5f);

	// â�� �ݽ��ϴ�.
	/// - bAllClose : ��� â�� �ݵ��� �� �������� ���� ���θ� �����մϴ�.
	/// - closableWnd : ���� â�� �����մϴ�.
	///   ���� nullptr �� ���޵ȴٸ� �������� ������ â�� �����ϴ�.
	void CloseWnd(bool bAllClose = false, class UClosableWnd* closableWnd = nullptr);

public :
	// �׸��� �г��� ��ҵ��� ���ʴ�� �����մϴ�.
	/// - gridPanelElem : ���Ľ�ų �׸��� �г� ��Ҹ� �����մϴ�.
	/// - maxColumnCount : �ִ� �� ������ �����մϴ�.
	/// - ref_currentColumnCount : ���� �� ��ȣ�� �����մϴ�.
	///   ������ ������ �޼��� ���ο��� ����˴ϴ�.
	static void SortGridPanelElem(
		class UUserWidget* gridPanelElem,
		int32 maxColumnCount,
		int32& ref_currentColumnCount);


	
};
