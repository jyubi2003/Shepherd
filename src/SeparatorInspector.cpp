/*
 *自動テストプログラム
 *
 *セパレータ(","､ ".")を評価するクラス。
 *
 *プログラム名： SeparatorInspector
 *
 *作成者:FJH
 *作成日:2016/8/9
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementRepository.h"
#include "SeparatorInspector.h"

/* inspect	: ,.評価
 *		inputBuff	: 入力文字
 *		outFp		：出力先
 * 			入力文字を評価し、セパレータか判定します。
 * 			コロン、セミコロンは別のクラスでやります。
 * 		return	: OK=1, NG=0
 */
int
SeparatorInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf("%s::inspect:%s\n", name, inputBuff);
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

	// セパレータの評価
	if(*inputBuff == ','){
		pElement = pRepo->startElement(Token, pos);
		pElement->setTokenType(SyntaxToken);
		pElement->setTokenKind(CommaToken);
		pElement->setContent(inputBuff);
		pRepo->endElement(pElement, pos);
		
	} else if(*inputBuff == '.'){
		pElement = pRepo->startElement(Token, pos);
		pElement->setTokenType(SyntaxToken);
		pElement->setTokenKind(DotToken);
		pElement->setContent(inputBuff);
		pRepo->endElement(pElement, pos);
	}

	rc = OK;

#ifdef _DEBUG
	printf("%s::inspect:END rc(Ox%x)\n", name, rc);
#endif

	return rc;
}
