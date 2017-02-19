/*
 * 自動テストプログラム
 *
 * 逐次通知された文字を評価し、コロン、セミコロンか評価する
 *
 * クラス名: ColonInspector
 *
 * 作成者  : FJH
 * 作成日  : 2016/8/9
 */
#if !defined(__COLON_INSPECTOR__)
#define __COLON_INSPECTOR__

#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "InspectorBase.h"

class ColonInspector : public InspectorBase {
protected:
	const char* name = "ColonInspector";

public:
	/*
	 * lnspect    : コロン、セミコロン評価
	 *  inputBuff : 入力文字
	 *  pRepo     : エレメントを登録するリボジトリ
	 *  pos       : 評価ソース中での文字の位置
	 *  入力文字を評価し、コロン、セミコロンか判定する
	 */
	int inspect(char* inputBuff, ElementRepository* pRepo, int pos);

};	// END of Class

#endif	//__COLON_INSPECTOR__
