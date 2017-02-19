/*
 * 自動テストプログラム
 *
 * 逐次通知された文字を評価し、ホワイトスペースか評価する
 *
 * クラス名： WhitespaceInspector
 *
 * 作成者：FJH
 * 作成日：2016／7／12
 */
#if !defined(__WHITESPACE_INSPECTOR__)
#define __WHITESPACE_INSPECTOR__

#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "InspectorBase.h"

class WhitespaceInspector : public InspectorBase{
protected:
	const char* name = "WhitespaceInspector";

public:

	/*
	 * inspect		: 識別子(identifier)評価
	 *	inputBuff	: 入力文字
	 *	pRepo		: エレメントを登録するリボジトリ
	 *	pos			: 評価ソース中での文字の位置
	 *
	 * 入力文字を評価し、識別子の条件を満たすか判定する
	 */
	int inspect(char* inputBuff, ElementRepository* pRepo, int pos);

}; //END of Class

#endif //__WHITESPACE_INSPECTOR__
