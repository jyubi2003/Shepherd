/*
 * 自動テストシステム
 *
 * 逐次通知されたトークンを評価し、クラス定義を評価するクラス
 *
 * クラス名: ClassDeclarationInspector
 *
 * 作成者	: FJH
 * 作成日	: 2016/8/24
 */
#if !defined(__CLASSDECLARATION_INSPECTOR__)
#define __CLASSDECLARATlON_INSPECTOR__

#include "SourceAnalizer.h"
#include "InspectorBase.h"
#include "ElementRepository.h"
#include "NodeElement.h"
#include "NodeInspectorBase.h"

enum classInspectStatus{
	NotStarted,					// 0 未解析
	AccessDecolaterDeclared,	// 1 アクセス修飾子指定済み
	ModifierDeclared,			// 2 クラス修飾子指定済み
	ClassKeywordDeclared,		// 3 クラスキーワード指定済み
	ClassNameDeclared,			// 4 クラス名指定済み
	ExtendsKeywordDeclared,		// 5 extendsキーワード指定済み
	SuperClassDeclared,			// 6 親クラス名指定済み
	ImplementsKeywordDeclared,	// 7 implementsキーワード指定済み
	InterfaceClassDeclared,		// 8 インタフェースクラス指定済み
	ClassDeclarationStarted		// 9 クラス定義開始済み
};
	
class ClassDeclarationInspector : public NodeInspectorBase {
protected:
	const char* name = "ClassDeclarationInspector";

public:
	/*
	 *inspect:クラス定義ノード評価
	 * PToken :入力トークン
	 * pRepo :エレメントを登録するI)ポジトリ
	 * context:外部環境(CIass内とか、グローバルとか、そういう情報をビットで表そうかな、と)
	 * あ～トークンのインスペクターとパラメタ変わっちゃったなあ
	 *
	 * 入力トークンを評価し、クラス定義の条件を満たす時にクラス定義ノードを登録する
	 *
	 */
	int inspect(Element* pToken, ElementRepository* pReoo, int context);

}; //End of CJass
#endif	//__CLASSDECLARAT[ON_INSPECTOR__
