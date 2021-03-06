/*
 * 自動テストプログラム
 *
 * 本プログラムは、逐次通知された文字を評価し、引用符かを評価します。。
 *
 * プログラム名: QuortInspector
 *
 * 作成者 :FJH
 * 作成日 :2016/7/12
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementRepository.h"
#include "QuortInspector.h"

/* inspect	:シングルクォート、ダブルクォート評価
 * inputBuff	:入力文字
 * outFp		:出力先
 * 入力文字を評価し、シングルクォート、ダブルクォートか判定する
 * return	:OK=1, NG=0
 *
 */
int
QuortInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf("%s::inspect:%s\n",name, inputBuff);
#endif

	int rc = NG;

	//入力パラメタチェック
	if(inputBuff == NULL || pRepo == NULL){
		return rc;
	}
	
	//初期化チェック
	if(initFlag == false){
		return rc;
	}

	//引用符をチェック
	if( 	*inputBuff == '\''
		||	*inputBuff == '\"' ){
		/* 引用符だったら、一撃でトークン追加します。
		 * ２個以上続いた場合って、なんか特別な仕様あったっけ？
		 * とりあえず引用符は、１文字でトークンということで、
		 * 連続して特別な意味があるなら、それはノードでやるということで。
		 * （問題先送り方式^_^;）
		 */
		status = true;
		pElement = pRepo->startElement(Token, pos);

		//入力文字をバッファに格納
		strcat(buff, inputBuff);

		if( *buff == '\''){
			pElement->setTokenKind(SingleQuortToken);
		} else {
			pElement->setTokenKind(DoubleQuortToken);
		}
		pElement->setTokenType( SyntaxToken );
		pElement->setContent( buff );
		pRepo->endElement(pElement, pos);		// 1バイトのトークンなので、POSはスタートと一緒
		//初期状態に戻す
		init();
		
		rc = OK;
	}

#ifdef _DEBUG
	printf("%s::inspect:END rc(Ox%x)\n",name, rc);
#endif
	return rc;
}
