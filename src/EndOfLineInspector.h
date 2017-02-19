/*
 * 自動テストプログラム
 *
 * 逐次通知された文字を評価し、改行か評価する
 *
 * クラス名: EndOfLineInspector
 *
 * 作成者: FJH
 * 作成日: 2016/8/26
 */
#if !defined(__ENDOFLINE_INSPECTOR__)
#define __ENDOFLINE_INSPECTOR__

#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "InspectorBase.h"

class EndOfLineInspector : public InspectorBase {
protected:
	const char* name = "EndOfLineInspector";

public:
/*
 * lnSP?Ct:識別子(identifier)評価
 * InPutBuff:入力文字
 * PRepo :エレメントを登録するリボジトリ
 * POS :評価ソース中での文字の位置
 * 入力文字を評価し、識別子の条件を満たすか判定する
 */
int inspect(char* inputBuff, ElementRepository* pRepo, int pos);

};	//END of Class

#endif	//__ENDOFLINE_INSPECTOR__
