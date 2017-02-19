/*
 * 自動テストプログラム
 *
 * 本プログラムは、逐次通知された文字を評価し、Whitespaceかを評価します。。
 *
 * プログラム名：WhitespaceInspector
 *
 * 作成者：FJH
 * 作成日：2016/7/12
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementRepository.h"
#include "WhitespaceInspector.h"

/* inspect		: Whitespace評価
 * 	inputBuff	: 入力文字
 *	pRepo		: ノードの登録先
 *	pos			: inputBuffに通知された文字の先頭からの位置
 * 機能
 *	入力文字を評価し、Whitespaceの条件を満たすか判定する
 * 復帰
 *	return		: OK = 1, NG = 0
 *
 */
int
WhitespaceInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf( "WhitespaceInspector::inspect:%s\n",inputBuff);
#endif

	int rc = NG;
	
	//入力パラメタチェック
	if( inputBuff == NULL || pRepo == NULL ){
		return rc;
	}

	//初期化チェック
	if( initFlag == false ){
		return rc;
	}
	
	// Whitespaceを解析中かどうか
	if( status == false ){
		// 解析中ではない -> Whitespace開始の可能性をチェック
		if( *inputBuff == ' '
			|| *inputBuff == '\t' ){
			// Whiteespace開始
			status = true;
			pElement = pRepo->startElement(Torivia, pos);
			// 入力文字をバッファに格納
			strcat(buff, inputBuff);
		} else {
			//Whitespace未開始
			status = false;
			memset(buff, 0x00, ANALIZE_BUFF_SIZE);		//バッファをクリア
		}
	} else {
		// 解析中->Whitespapeの終了の可能性をチェック
		if( *inputBuff !=' '
			&& *inputBuff != '\t'){
			//条件成立-〉Whitespace終了ｦ通知
			pElement->setContent(buff);
			pElement->setToriviaType(SyntaxTrivia);
			pElement->setToriviaKind(WhitespaceTrivia);
			pRepo->endElement(pElement, pos-1);			// Whitespaceの終わりを検出するposは、ホワイトスペースではないため－1する
			
			//初期状態に戻す
			init();
		} else {
			// Whitespaceの終了ではない
			// 入力文字をバッファに格納
			//ホワイトスペースの終わりを検出するP
			strcat( buff, inputBuff );
		}
	}	
	rc = OK;
	return rc;
}
