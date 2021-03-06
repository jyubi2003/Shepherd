/*
 * 自動テストプログラム
 *
 * 本プログラムは、逐次通知された文字を評価し、改行か評価します。。
 *
 * プログラム名：EndOfLineInspector
 *
 * 作成者：FJH
 * 作成日：2016／8／26
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementRepository.h"
#include "EndOfLineInspector.h"

/* inspect 二改行評価
 *  inputBuff:入力文字
 *  outFp:出力先
 * 入力文字を評価し、改行の条件を満たすか判定する
 *  return:OK=l,NG=0
 *
 */
int
EndOfLineInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf("EndOfLineInspector::inspect:%s\n", inputBuff);
#endif

	int rc = NG;

	//入力パラメタチェック
	if(inputBuff == NULL || pRepo == NULL){
		return rc;
	}
	
	// 初期化チェック
	if (initFlag == false){
		return rc;
	}
	
	// EndOfLineを解析中かどうか
	if(status == false){
		// 解析中ではない->EndOfLine開始の可能性をチェック
		if( *inputBuff == 0x0d
			|| *inputBuff == 0x0a ){
			// EndOfLine開始
			status = true;
			pElement = pRepo->startElement(Torivia, pos);
			// 入力文字をバッファに格納
			strcat(buff, inputBuff);

		} else {
			// EndOfLine未開始
			status = false;
			memset(buff, 0x00, ANALIZE_BUFF_SIZE); //バッファをクリア
		}
	} else {
		// 解析中->EndOfLine終了の可能性をチェック
		if( *inputBuff != 0x0a
			&& *inputBuff!=0x0d){
			// 条件成立->EndOfLine終了を通知
			pElement->setContent(buff);
			pElement->setToriviaType(SyntaxTrivia);
			pElement->setToriviaKind(EndOfLineTrivia);
			pRepo->endElement(pElement, pos-1);			// 改行の終わりを検出するPOSは改行コードではないため－1する
			// 初期状態に戻す
			init();
		} else {
			// EndOfLine終了ではない
			// 入力文字をバッファに格納
			// 改行の終わりを検出するPOSは改行コー
			strcat(buff, inputBuff);
		}
	}
	rc = OK;
	return rc;
}
