/*
 * 自動テストプログラム
 *
 * トークンを評価するInspectorクラスの基底クラス
 *
 * クラス名 : InspectorBase
 */
 
#if !defined(__INSPECTOR_BASE__)
#define __INSPECTOR_BASE__

#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementRepository.h"

class InspectorBase{
protected:
	// クラス識別:ログに出力するクラス名を指すプレースホルダ
	// static char*name:
	// 評価バッファ：担当要素を評価するためのバッファ
	char buff[ANALIZE_BUFF_SIZE];
	
	// 評価状態を示すフラグtrue：要素評価中false：要素評価外
	int status;

	// 初期化フラグ：呼出しシーケンスチェック用
	int initFlag;

	// エレメント：リボジトリに登録するエレメントを指すポインタ
	Element* pElement;

public:
	/*
	 * ~InspectorBase : デストラクタ
	 */
	virtual ~InspectorBase();

	/*
	 * InspectBase : デフォルトコンストラクタ
	 */
	InspectorBase() = default;

	/*
	 * InspectorBase : コピーコンストラクタ
	 */
	InspectorBase(const InspectorBase& rBase);

	/* 
	 * init: 初期化
	 * id評価者を初期化する。
	 */
	virtual void init(void);
	
	/*
	 * inspect : 要素評価
	 *  inputBuff : 入力文字
	 *  pRepo    : 出力先
	 *  pos      : 評価位置
	 * 入力文字を評価し、要素の条件を満たすか判定する
	 * 	return : OK=1, NG=0
	 */
	virtual int inspect(char* inputBuff, ElementRepository* pRepo, int pos) = 0;

}; 	//END of class

#endif	// __INSPECTOR_BASE__
