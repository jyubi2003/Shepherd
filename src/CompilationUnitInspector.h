/*
 * 自動テストプログラム
 *
 * 逐次通知されたトークンを評価し、コンパイル単位を評価するクラス
 *
 * クラス名: CompilationUnitlnspector
 *
 * 作成者:FJH
 * 作成日:2016/8/23
 */
#if !defined(__COMPILATION_UNIT_INSPECTORT__)
#define __COMPILATION_UNIT_INSPECTORT__

#include "SourceAnalizer.h"
#include "InspectorBase.h"
#include "ElementRepository.h"
#include "NodeElement.h"
#include "NodeInspectorBase.h"

class CompilationUnitInspector : public NodeInspectorBase {
protected:
	const char*		name = "CompilationUnitInspector";

public:
	/* inspect:コンパイル単位ノード評価
	 * pToken	:入力トークン
	 * pRepo	:エレメントを登録するリボジトリ
	 * context	:外部環境（Class内とか、グローバルとか、そういう情報をビットであらわそうかな、と、
	 *		あ～トークンのインスペクターとパラメタ変わっちゃったなぁ
	 *
	 * 入力トークンを評価し、コンパイル単位の条件を満たす時にコンパイルユニットを登録する
	 *
	 */
	int inspect(Element* pToken, ElementRepository* pReoo, int context);

};	//End of Class

#endif	//__COMPILATION_UNIT_INSPECTOR__
