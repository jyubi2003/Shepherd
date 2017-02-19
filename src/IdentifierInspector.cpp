/*
 * BOSS業務APL調査用プログラム
 *
 * 本プログラムは、逐次通知された文字を評価し、識別子（Identifier）であるかを評価します。。
 *
 * プログラム名：identifierInspector
 *
 * 作成者 : FJH
 * 作成日 : 2016/7/12
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SourceAnalizer.h"
#include "IdentifierInspector.h"
#include "ElementRepository.h"
#include "Element.h"

/*
 * insdpect : Identifier評価
 *  inputBuff : 入力文字
 *  pRepo : リボジトリ
 *  pos : 解析中の文字位置
 *
 * 入力文字を評価し、Identifier（識別子）の条件を満たすか判定する
 *
 * return : OK=1, NG=0
 *
 */
int
IdentifierInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf("%s::inspect:START inputBuff(%s)\n", name, inputBuff);
#endif

	int rc = NG;

	// 入力パラメタチェック
	if(inputBuff == NULL || pRepo == NULL){
		return rc;
	}

	// 初期化チェック
	if(initFlag == false){
		return rc;
	}

	// identifierを解析中かどうか
	if(status == false){
		// 解析中ではない->identifierの開始の可能性をチェック
		if(*inputBuff >= 'a' && *inputBuff <='z'
		|| *inputBuff >= 'A' && *inputBuff <='Z'
		|| *inputBuff == '_' ){
			// identifier開始
			status = true;
			pElement = pRepo->startElement(Token, pos);		// startEIement()すると、Elementが返ってくる

			// 入力文字をバッファに格納
			strcat(buff, inputBuff);
		} else {
			// identifier未聞始
			status = false;
			memset(buff, 0x00, ANALIZE_BUFF_SIZE);			// バッファをクリア
		}
	} else {
		// 解析中->identifierの終了の可能性をチェック
		if( !(*inputBuff >= 'a' && *inputBuff <= 'z' ) &&
			!(*inputBuff >= 'A' && *inputBuff <= 'Z' ) &&
			!(*inputBuff >= '0' && *inputBuff <= '9' ) &&
			  *inputBuff != '_' ){ 							// imputBuffをテストしている。識別子に使えない文字がくればそこまで
			// 条件成立->identifier終了を通知
			pElement->setContent(buff);
			pElement->setTokenType(SyntaxToken);
			pElement->setTokenKind(IdentifierToken);
			pRepo->endElement(pElement, pos-1); 			// 識別子が終わったことを決定できた場所は、識別子の最後の次の文字なので、終端位置を－1する
			// 初期状態に戻す
			init();
		} else {
			// 識別子の終了ではない
			// 入力文字をバッファに格納
			strcat(buff, inputBuff);
		}
	}
	
	rc=OK;

#ifdef _DEBUG
	printf("%s::inspect:END rc(Ox%x)\n", name, rc);
#endif
	return rc;
}
