/*
 * 自動テストプログラム
 *
 * ノードを評価するInspectorクラスの基底クラス
 *
 * クラス名： NodeInspectorBase
 *
 *   トークンを評価するインスペクタの基底クラス、InspectorBaseの派生クラスでは？と思いましたが、
 *   "NodeInspectorBase is lnspectorBase"とは言えない気がするので分けています。
 *
 * 作成者：FJH
 * 作成日：2016／7／12
 */
 
#if !defined(__NODE_INSPECTOR_BASE__)
#define __NODE_INSPECTOR_BASE__

#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementRepository.h"
#include "NodeElement.h"

class NodeInspectorBase{
protected:
	// クラス識別：ログに出力するクラス名を指すプレースホルダ
	// static char*name;//なぜかこれうまくいかない。有効にするとエラーになる。
	// 評価状態を示すフラグtrue：要素評価中false：要素評価外
	int status;
	
	// 初期化フラグ：呼出しシーケンスチェック用
	int initFlag;
	
	//ノードエレメント：リボジトリに登録するエレメントを指すポインタ
	NodeElement* pNodeElement;
	
public:
	/*
	 * ~NodeInspectorBase : デストラクタ
	 */
	virtual ~NodeInspectorBase();
	
	/*
	 * NodeInspectBase : デフォルトコンストラクタ
	 */
	NodeInspectorBase() = default;

	/*
	 * NodeInspectBase : コピーコンストラクタ
	 */
	NodeInspectorBase(const NodeInspectorBase& rBase);

	/*
	 * init: 初期化
	 * 
	 * id評価者を初期化する。
	 */
	virtual void init(void);
	
	/* inspect  : 要素評価
	 *  pToken  : 入力トークン
	 *  pRepo   : 出力先
	 *  context : 関数の呼ばれたコンテキスト
	 *
	 *  入力トークンを評価し、ノード要素の条件を満たすか判定する
	 *  return  : OK = 1, NG = 0
	 */
	virtual int inspect(Element* pToken, ElementRepository* pReoo, int context) = 0;

};	// END of Class

#endif	//__NODE_INSPECTOR_BASE__
