/*
 * BOSS業務APL調査用プログラム
 *
 * 本プログラムは、逐次通知されたトークンを評価し、コンパイル単位を判定してリボジトリに格紳します。
 *
 * プログラム名: CompilationUnitInspector
 * ファイル名: CompilationUnitInspector.cpp
 *
 * 作成者:FJH
 * 作成日:2016/8/23
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SourceAnalizer.h"
#include "NodeInspectorBase.h"
#include "ElementRepository.h"
#include "NodeElement.h"
#include "CompilationUnitInspector.h"

/* inspect:import文評価
 *	pToken	:入力トークン
 *	pRero	:エレメントリボジトリ（ノード格納先）
 *	context	:外部環境（Class内とか、グローバルとか、そういう情報をビットで表そうかな、と）
 * InspecterBaseとパラメタ変わっちやったなあ。NodeInspectorBase作ろうかな。
 * ⇒作りました
 *
 * 入力トークンを評価し、コンパイル単位の条件を満たせば、リボジトリに格納します
 *
 */
int
CompilationUnitInspector::inspect(Element* pToken, ElementRepository* pRepo, int context){
#ifdef _DEBUG
	printf("CompilationUnitInspector::inspect():Start.TokenId=%d\n", pToken->getId());
#endif

	int rc = NG;

	/* 入力パラメタチェック */
	if(pToken == NULL || pRepo == NULL){
		return rc;
	}

	/* 初期化チェック */
	if(initFlag == false){
		return rc;
	}

	/* コンパイル範囲を解析中かどうか */
	if(status == false){
		/* 解析中ではない->コンパイル単位の開始 */
		/* CompilationUnit開始 */
		/* リボジトリにスタートを通知 */
		pNodeElement = (NodeElement*)pRepo->startElement(Node, pToken->getSpanStart());		// startEtement()すると、NodeElementがElernent型で返ってくるのでキャスト
		pNodeElement->setToken(pToken); 													// Tokenを格納
		char* pValue = NULL;
		pToken->getContent(&pValue);
		pNodeElement->catContent(pValue);
		status = true;
	} else {
		/* 解析中->コンパイル単位終了の可能性をチェック
		 * どうやって終了を判定しよう‥
		 * 案1．トークン終了のトークンを送ってもらう ⇒ 影響範囲が大きいのでは．．
		 * 案2・デストラクタでノードを登録する⇒その時にリボジトリが存荏する可能性を保証できる？
		 * 案3.init()が呼ばれたときにリストを持っていればノードを登録する ⇒init()で登録なんてアクロバットで理解しにくい。最後のファイルはどうするの？
		 * 結論：他のインスペクタも、現在の処理を終わらせるきっかけにするかもしれないので、トークン終了を送ってもらう方法で
		 */
		if(pToken->getTokenKind() == EndOfFileToken){
			/* 解析中でトークンがEndOfFileTokenだったら */
			/* チェック終了 */
			/* NodeElementをリボジトリに登録 */
			// pNodeElement->setToken(pToken): 							// TokenListに最後のTokenを追加 しない
			pNodeElement->setNodeType(CompilationUnitSyntax);			// ノードタイプ設定
			pNodeElement->setNodeKind(CompilationUnit);				// ノード種別設定
			pRepo->endElement(pNodeElement, pToken->getSpanEnd());		// リボジトリに登録
			// 初期状態に戻す
			init();

		} else {
			/* 解析中でトークンがコンパイル単位の終端ではない
			 * トークンをリストに追加して次へ
			 * 結果的にこのノードは全トークンを含むことになります
			 */
			pNodeElement->setToken(pToken);
			char* pValue = NULL;
			pToken->getContent(&pValue);
			pNodeElement->catContent(pValue);
			status = true;
		}
	}

	rc = OK;

#ifdef _DEBUG
	printf("CompilationUnitInspector::inspect() : End. rc(Ox%x)\n", rc);
#endif
	return rc;
}
