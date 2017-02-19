/*
 * 自動テストプログラム
 *
 * インスペクターからの通知を受け取り、要素を管理するリボジトリクラス
 *
 * クラス名: EJementRepository
 * ファイ名: ElementRepository.h
 *
 * 作成者: FJH
 * 作成日: 2016/7/12
 */
#if !defined(__ELEMENT_REPOSITORY__)
#define __ELEMENT_REPOSITORY__

#include <list>
#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementProperties.h"

enum Operate {
	Print,
	Dump
};

enum Duplicate {
	Off,
	On
};

class ElementRepository {
protected:
	const char* name = "ElementRepository";
	
	/* トークンの格納リスト */
	std::list<Element*> tokens;
	
	/* ノードの格納リスト */
	std::list<Element*> nodes;

	/* トリビアの格納リスト */
	std::list<Element*> torivias;
	/* 初期化フラグ */
	int	initFlag;

	/* エレメントID */
	int elementId;

public:
	/*
	 * elementRepositoryInit:初期化
	 *
	 * エレメントリボジトリを初期化する。
	 *
	 */
	void init();

	/*
	 * StartElement:要素の開始を通知
	 *  aClass:要素のクラス
	 *  startPos:開始位置
	 *  エレメントを仮に作りリボジトリに仮登録する（発生順を記録するため）
	 */
	Element* startElement(ElementClass aClass, int startPos);

	/*
	 * EndElement:要素を確定する
	 *  pEIement:確定する要素
	 *  endPos:要素の最終位置（バイト単位)
	 *  dupFlag:要素の重複登録を許可するか(Off: 許可しない（デフォルト）、On: 許可する）
	 * エレメントの内容を確定する
	 * 
	 */
	int endElement(Element* pElement, int endPos, Duplicate dupFlag = Off);

	/*
	 * revokeElement:要素を破棄する
	 *  pErement:破棄する要素
	 *	エレメントを破棄する。リボジトリからも削除する
	 *\
	 */
	int revokeElement(Element* pElement);

	/*
	 * printElements:要素を指定された出力先に、外部形式で出力する
	 *  elemClass: 出力する要素種。NoneElementClassを指定した場合、すべて出力される
	 *  0UtFp:出力先
	 */
	int printElements(ElementClass elemClass, FILE* outFp);

	/*
	 * analizeNode:トークンを分析し、ノードを生成する
	 * 引数なし
	 */
	int  analizeNode();
	
protected:
	/*
	* iterateElements: 要素に繰返し処理を行う
	*  ope: 実行する処理
	*  elemClass: 処理する要素種。NoneElementClassを指定した場合、すべてが処理される
	*  0utFp: 出力先。処理が印刷系のときに指定する。
	*/
	int iterateElements(Operate ope, ElementClass elemClass, FILE* OutFp);

};	// End of class

#endif	//__ELEMENT_REPOSITORY__
