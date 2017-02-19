/*
 * 自動テストプログラム
 *
 * 本プログラムは、逐次通知された文字を評価し、予約語かを評価します。。
 *
 * プログラム名：ReservedInspector.cpp
 *
 * 作成者: FJH
 * 作成日: 2016/7/12
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Element.h"
#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "ReservedInspector.h"

/*ReservedInspector: 予約語評価
 *	lnputBuff	: 入力文字
 *	pRepo		: リボジトリ
 *	pos			: 解析中の文字位置
 *	入力文字を評価し、予約語の条件を満たすか判定する
 *	return	:OK=1, NG=0
 *
 */
int
ReservedInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf("%s::inspect:STAR TinputBuff(%s)\n", name, inputBuff);
#endif
	int rc = NG;

	//入力パラメタチェック
	if(inputBuff == NULL || pRepo == NULL){
		return rc;
	}
	
	//初期化チェック
	if(initFlag == false){
		return	rc;
	}

	//identifierを解析中かどうか（「予約語は常に識別子の条件を満たす」という考えのため、まず識別子をチェックする）

	if(status==false){
	//解析中ではない-〉identifierﾉ開始ﾉ可能性ｦﾁｪｯｸ

		if(*inputBuff >= 'a' && *inputBuff <= 'z' ||
		   *inputBuff >= 'A' && *inputBuff <= 'Z' ||
		   *inputBuff == '_'){
			//identifier開始
			status = true;
			pElement = pRepo->startElement(Token, pos);		//とりあえず予約語として通知しておく。違ったらrevokeするからいい

			//入力文字を／くッファに格納
			strcat(buff, inputBuff);

		} else {
			//identifier未開始
			status = false;
			memset(buff, 0x00, ANALIZE_BUFF_SIZE);				//バッファクリア
		}
	} else {
		// 解析中 -> identifierの終了の可能性をチェック
		if( !( *inputBuff >= 'a' && *inputBuff <= 'z') &&
		    !( *inputBuff >= 'A' && *inputBuff <= 'Z') &&
		    !( *inputBuff >= '0' && *inputBuff <= '9') &&
		       *inputBuff != '_'){								//imputBuffをテストしている。識別子に使えない文字がくればそこまで
			// 条件成立 -> identifier終了
			// 識別子が予約語かどうか検査する
			TokenKind kind;
			if( chkReserved(kind) ){
				//予約語だった
				pElement->setTokenType(SyntaxToken);
				pElement->setTokenKind(kind);
				pElement->setContent(buff);
				pRepo->endElement(pElement, pos-1);				// 識別子を判定できるのは、文字が条件を満たさなくなったとき。なので、－１の位置が最後の文字となります。
			} else {
				// 予約語ではなかった
				pRepo->revokeElement( pElement );
			}
			// 初期状態に戻す
			init();

		} else {
			// 入力文字をバッファに格納
			strcat(buff, inputBuff);
		}
	}
	rc = OK;

#ifdef _DEBUG
	printf("%s::inspect:END rc(%d)\n", name, rc);
#endif

	return rc;
}

/* inspect	:	予約語検査
 * 	バッファを評価し、予約言責か判定する
 *	return	:予約語 = 1, 予約語ではない = 0
 */
int
ReservedInspector::chkReserved(TokenKind& kind){
#ifdef _DEBUG
	printf("ReservedInspector::chkReserved:\n");
#endif

	int rc = NG;

	st_ReservedKeyword* ptr = (st_ReservedKeyword*)&(reservedTokens[0]);

	while( strcmp(ptr->pKeyword, "EOL") != 0){
		if(!strcmp(buff, ptr->pKeyword)){
			//一致した
			kind = ptr->kind;
			return OK;
		}
		ptr++;
	}
	
	return NG;
}

