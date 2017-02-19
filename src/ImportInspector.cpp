/*
*BOSS業務APL調査用プログラム
*
*本プログラムは、逐次通知されたトークンを評価し、import文であるかを評価します。。
*
*プログラム名：lmportInspector
*
*作成者：FJH
*作成日：2016／8／19
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SourceAnalizer.h"
#include "NodeInspectorBase.h"
#include "ElementRepository.h"
#include "ElementProperties.h"
#include "NodeElement.h"
#include "ImportInspector.h"

/*
 * inspect  : import文評価
 *  pToken  : 入力トークン
 *  pRero   : エレメントリボジトリ（ノード格納先）
 *  context : 外部環境（Class内とか、グローバルとか、そういう情報をビットで表そうかな、と）
 *
 *  InspecterBaseとパラメタ変わっちやったなあ。NodeInspectorBase作ろうかな。
 *
 * 入力トークンを評価し、import文の条件を満たせば、リボジトリに格納します
 *
 */
int
ImportInspector::inspect(Element* pToken, ElementRepository* pRepo, int context){
#ifdef _DEBUG
	printf("Importlnspector::inspect():Start.TokenId=%d\n", pToken->getId());
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
	
	/* import文を解析中かどうか */
	if(status == false){
		/*解析中ではない->import文の開始の可能性をチェック */
		/*Bug Fix importキーワードの検査の前に、要素がTokenであること（Toriviaでないこと）をチェックする。*/
		if(pToken->getElementClass() == Token){
			if(pToken->getTokenKind() == ImportKeyword){
				/* import文開始 */
				/* リボジトリにスタートを通知 */
				pNodeElement = (NodeElement*)pRepo->startElement(Node, pToken->getSpanStart());	// startElement()すると、NodeElementがﾞElement型で返ってくるのでキャスト
				pNodeElement->setToken(pToken); // Tokenを格納
				status = true;
			} else {
				/* import文は開始してない */
				status = false;
			}
		} else {
			/* 要素がTokenではない(=Torivia)ときにはここに来るが、何もしない。*/
		}
	} else {
		/* 解析中->import文の終了の可能性をチェック */
		/* Toriviaである空白が来ることもあるが、TokenListに追加しておく。Nodeの中身をプリントした時に見栄えが良いから。
		 * 開始でToriviaを弾いているので、大丈夫なんじゃないかな。
		 */
		if(pToken->getTokenKind() == SemicolonToken){
			/* 解析中でトークンがimport文の終端文字（セミコロン）*/
			/* チェック終了 */
			/* NodeElementをリボジトリに登録 */
			pNodeElement->setToken(pToken); 						// TokenListに最後のTokenを追加
			//pNodeElement->setNodeType(ImportDirectiveSyntax);		//ノードタイプ設定
			//pNodeElement->setNodeKind(ImportDirective); 			//ノード種別設定
			//pRepo->endElement(pNodeElement, pToken->getSpanEnd());	//リボジトリに登録

			//初期状態に戻す
			init();

		} else {
			/* 解析中でトークンがimport文の終端文字ではない */
			/* トークンをリストに追加して次へ */
			pNodeElement->setToken(pToken);
		}
	}
	
	rc = OK;

#ifdef _DEBUG
	printf("ImportInspector::inspect():End.rc(0x%x)\n", rc);
#endif

	return rc;
}
