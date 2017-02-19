/*
 * 自動テストプログラム
 *
 * セパレータ(","､ ".")を評価するクラス
 *
 * クラス名: SeparatorInspector
 *
 * 作成者:FJH
 * 作成日:2016/8/9
 */
#if !defined(__SEPARATOR_INSPECTOR__)
#define __SEPARATOR_LINSPECTOR__

#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "InspectorBase.h"

class SeparatorInspector : public InspectorBase {
protected:
	const char* name = "SeparaterInspector";

public:

	/*
	 * inspect：セバレータを評価するクラス
	 * 		inputBuff : 入力文字
	 * 		PRepo	  : エレメントを登録するリポジトリ
	 * 		pos		  : 評価ソース中での文字の位置
	 * 入力文字を評価し、識別子の条件を満たすか判定する
	 */
	int inspect(char* inputBuff, ElementRepository* pRepo, int pos);

};	// END of Class

#endif //__SEPARATOR_INSPECTOR__
