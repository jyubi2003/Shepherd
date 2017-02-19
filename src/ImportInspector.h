/*
 * BOSS業務APL調査用プログラム
 *
 * 逐次通知された文字を評価し、import文であるかを評価するクラス
 *
 * クラス名：ImportInspector
 *
 * 作成者：FJH
 * 作成日：2016／7／12
 */
#if !defined(__IMPORT_INSPECTOR__)
#define __IMPORT_INSPECTOR__

#include "SourceAnalizer.h"
#include "InspectorBase.h"
#include "ElementRepository.h"
#include "NodeElement.h"
#include "NodeInspectorBase.h"

/*
 * 定数一覧
 */
/* 各種長さ */
#define IMPORT_BUFF_SIZE	2048

class ImportInspector : public NodeInspectorBase {
protected:
	const char* name = "ImportInspector";

public:
	/*
	 * inspect  : import文評価
	 *  pToken  : 入力トークン
	 *  pRepo   : エレメントを登録するリポジトリ
	 *  context : 外部環境（Class内とか、グローバルとか、そういう情報をビットで表そうかな、と）
	 *  	あ～トークンのインスペクターとパラメタ変わっちやったなあ
	 *
	 * 入力文字を評価し、import文の条件を満たすか判定する
	 */
	int inspect(Element* pToken, ElementRepository* pReoo, int context);

};	//End of Class

#endif	//__IMPORT_INSPECTOR__
