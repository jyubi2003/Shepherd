/*
 * 自動テストプログラム
 *
 * 本プログラムは、逐次通知された文字を評価し、コロン、セミコロンかを評価します。。
 *
 * プログラム名 : Colon[nspector
 *
 * 作成者       : FJH
 * 作成日       : 2016/7/12
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementRepository.h"
#include "ColonInspector.h"

/*
 * inspect    : コロン、セミコロン評価
 * InputBuff  : 入力文字
 *  outFp     : 出力先
 *  入力文字を評価し、コロン、セミコロンか判定する
 *  return    : OK=1, NG=0
 */
int
ColonInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf("%s::inspect:%s\n", name, inputBuff);
#endif

	int rc=NG;
	
	//入力パラメタチェック
	if(inputBuff == NULL || pRepo == NULL){
		return rc;
	}

	//初期化チェック
	if(initFlag == false){
		return rc;
	}

	//コロン、セミコロンを解析中かどうか
	if(status == false){
		//解析中ではない->コロン、セミコロン開始の可能性をチェック
		if (*inputBuff == ':'
		||  *inputBuff == ';'){
			// コロン、セミコロンの開始
			status = true;
			pElement = pRepo->startElement(Token, pos);
			//入力文字をバッファに格納
			strcat(buff, inputBuff);
	
		} else {
			//コロン、セミコロン未開始
			status = false;
			memset(buff, 0x00, ANALIZE_BUFF_SIZE); //バッファをクリア
		} 

	} else {
	// 解析中->CoIon,Semicolonの終了の可能性をチェック
		if( *inputBuff != ':'
		 && *inputBuff != ';' ){
			// 条件成立-〉Colon,Semicolonの終了を通知。
			// ですが、コロンが2個続いた場合は名前空間接続子。1個の場合は、ケース文の分離子
			// スコープの分離子。
			// セミコロンが1個だとステートメント分離子。2個以上続いた場合は空文、とか色々と
			// あるのでどうしよう。コンパイルの通るソースだけを対象とするので、エラーケースは
			// 考えないとしても、セミコロンの連続はエラーにならないよね。
			// とりあえずトークンとしては、コロントークン、セミコロントークンにしておくかなあ ＜
			// （問題先送り方式 ^_^;)
			
			if( *buff == ':'){
				pElement->setTokenKind(ColonToken);
			} else {
				pElement->setTokenKind(SemicolonToken);
			}
			pElement->setTokenType(SyntaxToken);
			pElement->setContent(buff);
			pRepo->endElement(pElement, pos-1);			// 識別子が終わったことを決定できた場所は、識別子の
														// 最後の次の文字なので、終端位置を-1する

			//初期状態に戻す
			init();
		} else {
			// Whitespaceの終了ではない
			// 入力文字をバッファに格納
			strcat(buff, inputBuff);

		}
	}

	rc = OK;
	
#ifdef _DEBUG
	printf("%s::inspect:END rc(0x%x)\n", name, rc);
#endif
return rc;
}
