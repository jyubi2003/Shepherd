/*
 * 自動テストプログラム
 *
 * 逐次通知された文字を評価し、コメントであるかを評価するクラス
 *
 * クラス名: CommentInspector
 * ファイル名:Commenttnspector.h
 *
 * 作成者:FJH
 * 作成日:2016/8/1
 */
#if !defined(__COMMENT_INSPECTOR__)
#define __COMMNET_INSPECTOR__

#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "InspectorBase.h"

enum CommentType{
	NA,
	CTYPE,
	CPPTYPE
};

class CommentInspector : public InspectorBase {
protected:
	const	char*	name = "CommentInspector";
	int		contStatus;
	int		commentType;

public:

	/*
	 *init:初期化
	 *
	 */
	void init(void);

	/*
	 * inspect:コメント評価
	 * inputBuff:入力文字
	 * pRepo :エレメントを登録するリボジトリ
	 * pos :評価ソース中での文字の位置
	 *
	 * 入力文字を評価し、識別子の条件を満たすか判定する
	 */
	int	inspect(char* inputBuff, ElementRepository* pRepo, int pos);

	/*
	 * inspect:コメント評価
	 * inputBuff:入力文字
	 * pRepo :エレメントを登録するリボジトリ
	 * pos :評価ソース中での文字の位置
	 * pFp :ファイルポインタ
	 *
	 * UTF-8の日本語を他のインスペクタに渡さないように、コメントの評価
	 * はCommentInspectorクラスで完結させる。そのため、ファイルポインタ
	 * を受け取るinspectメソッドを提供する。
	 */
	int inspect(char* inputBuff, ElementRepository* pRepo, int* pPos, FILE**  pFp);

};	//END of Class

#endif	//__COMMENT_INSPECTOR__
