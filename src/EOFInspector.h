/*
 * 自動テストプログラム
 *
 * ファイルが終端に達するか、読込みエラーが発生したときに呼び出され、
 * EOFトークンを追加する。
 *
 * クラス名: EOF[nspector
 * ファイル名: EOFTnspector.h
 *
 * 作成者: FJH
 * 作成日: 2016/8/23
 */
#if !defined(_EOF_INSPECTOR__)
#define __EOF_INSPECTOR__

#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "InspectorBase.h"

class EOFInspector : public InspectorBase {
protected:
	const char* name = "EOFInspector";

public:
	/*
	 * inspect: 識別子(identifier)評価
	 *  inputBuff	: 入力文字
	 *  pRepo		: エレメントを登録するリポジトリ
	 *  pos			: 評価ソース中での文字の位置
	 *
	 * 入力文字を評価し、識別子の条件を満たすか判定する
	 */
	int inspect(char* inputBuff, ElementRepository* pRepo, int pos);

}; // END of Class

#endif //__EOF_INSPECTOR__
