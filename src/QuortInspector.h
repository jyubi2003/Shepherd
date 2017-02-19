/*
 * 自動テストプログラム
 *
 * 逐次通知された文字を評価し、引用符か評価する
 *
 * クラス名	:QuortInspector
 *
 * 作成者	:FJH
 * 作成日	:2016/8/26
 */
#if !defined(__OUORT_INSPECTOR__)
#define __QUORT_INSPECTOR__

#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "InspectorBase.h"

class QuortInspector : public InspectorBase{
protected:
	const char*	name = "QuortInspector";

public:
	/*
	 * inspect	: シングルクォート、ダブルクォートの評価 inutBuff： p入力文字
	 * pRepo	：エレメントを登録するリボジトリ
	 * pos 		：評価ソース中での文字の位置
	 * 入力文字を評価し、シングルクォート、ダブルクォートか判定する
	 */
	int inspect(char* inputBuff, ElementRepository* pRepo,	int pos);

};	//END of Class

#endif	//__OUORｼINSPECTOR__
