/*
 * 自動テストプログラム
 *
 * BBP ｸブラケット"[]'′､ﾌﾞﾚｰｽ′′II′′､ﾊﾞﾚﾝ′′()′′)を評価するクラス。
 *
 * プログラム名:		BBPInspector
 *
 * 作成者 : FJH
 * 作成日 : 2016/8/9
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementRepository.h"
#include "BBPInspector.h"

/*	inspect			: [{(評価
 *	input* buff		: 入力文字
 *	outFp			: 出力先
 *	入力文字を評価し、カツコ類か判定する
 *	return:OK=1, NG=0
 */
int
BBPInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf("%s:syreko-doinspect:%s\n",name,inputBuff);
#endif

	int rc = NG;

	// 入力パラメタチェック
	if (inputBuff == NULL || pRepo == NULL){
		return rc;
	};

	// 初期化チェック
	if (initFlag == false ){
		return rc;
	}
	
	// BBPの評価
	if(*inputBuff == '[' ){
		pElement = pRepo->startElement( Token, pos );
		pElement->setTokenType( SyntaxToken );
		pElement->setTokenKind( OpenBracketToken );
		pElement->setContent( inputBuff );
		pRepo->endElement( pElement, pos );

	} else if ( *inputBuff == ']' ){
		pElement = pRepo->startElement( Token, pos );
		pElement->setTokenType( SyntaxToken );
		pElement->setTokenKind( CloseBracketToken );
		pElement->setContent( inputBuff );
		pRepo->endElement( pElement, pos );
		
	} else if ( *inputBuff == '{'){
		pElement = pRepo->startElement( Token, pos );
		pElement->setTokenType( SyntaxToken );
		pElement->setTokenKind( OpenBraceToken );
		pElement->setContent( inputBuff );
		pRepo->endElement( pElement, pos );

	} else if (*inputBuff == '}'){
		pElement = pRepo->startElement( Token, pos);
		pElement->setTokenType( SyntaxToken) ;
		pElement->setTokenKind( CloseBraceToken );
		pElement->setContent( inputBuff );
		pRepo->endElement( pElement, pos );
		
	} else if( *inputBuff == '('){
		pElement = pRepo->startElement( Token, pos );
		pElement->setTokenType( SyntaxToken );
		pElement->setTokenKind( OpenParenToken );
		pElement->setContent( inputBuff );
		pRepo->endElement( pElement, pos );

	} else if ( *inputBuff == ')' ){
		pElement = pRepo->startElement( Token, pos );
		pElement->setTokenType( SyntaxToken );
		pElement->setTokenKind( CloseParenToken );
		pElement->setContent( inputBuff );
		pRepo->endElement( pElement, pos );
	}
	
	rc = OK;

#ifdef _DEBUG
	printf("%s::inspect : END rc(0x%x)\n", name, rc);
#endif
	return rc;
}
