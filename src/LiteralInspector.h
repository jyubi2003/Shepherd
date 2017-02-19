/*
 * 自動テストプログラム
 *
 * 逐次通知された文字を評価し、リテラルかを評価するクラス
 *
 * クラス名   : LiteralInspector
 * ファイル名 : LiteralInspector.h
 *
 * 作成者 : FJH
 * 作成日 : 2016/9/8
 */
 
#if !defined(__LITERAL_INSPECTOR__)
#define __LITERAL_INSPECTOR__

#include "sourceAnalizer,h"
#include "ElementRepository.h"
#include "InspectorBase.h"

// リテラルのタイプ
// Keywordのリテラルは、予約語と区別がつかないため、トークンでは予約語として検出
// し、ノード評価でリテラルと判定します。そのため、このTypeにはWORDリテラルがあ
// りません
enum LiteralType {
	NA,
	NUMELIC,
	CHAR,
	STRING
};

class LiteralInspector : public InspectorBase {
protected:
	const		char* name = "Literaltnspector";

	int			contStatus;
	LiteralType	literalType;
	
	// 数字リテラルの開始は、直前の文字がアルファベット
	// およぴ'_'ではないことを確認する必要があるため、
	// inputBuffの一文字前の文字を覚えておく。
	char	preChar[2];

public:
	/*
	 * init：初期化
	 *
	 */
	void init(void):

	/*
	 * inspect : コメント評価
	 *  InputBuff	: 入力文字 
	 *  pRepo		: エレメントを登録するリポジトリ
	 *  pos			: 評価ソース中での文字の位置
	 *
	 *  入力文字を評価し、識別子の条件を満たすか判定する
	 */
	int inspect(char* inputBuff. ElementRepository* pRepo, int pos):

	/*
	 * inspect		: コメント評価
	 *  inputBuff	: 入力文字
	 *  pRepo		: エレメントを登録するリボジトリ
	 *  pos			: 評価ソース中での文字の位置
	 *  pFp			: ファイルポインタ
	 *
	 * リテラルに含まれる記号、数字などを他のインスペクタに渡さないように、
	 * リテラルの評価はLiteralInspectorクラスで完結させる。
	 * リテラルの完了を検出した時には、呼出し元ではリテラルの次の文字を読み込
	 * んでいるため、他のインスペクタを開始するためファイルポインタを戻す必要
	 * がある。
	 * そこで、ファイルポインタを受け取るinspectメソッドを提供する。
	 *
	 */
	int inspect(char* inputBuff, ElementRepository* pRepo, int* pPos, FILE** pFp);

};	// END of class
 
#endif	// __LITERAL_INSPECTOR__
