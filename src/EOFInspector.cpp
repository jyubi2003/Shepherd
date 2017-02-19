/*
 * プログラム名: EOFInspector
 * ファイル名: EOFInspector.cpp
 * 作成者: FJH
 * 作成日: 2016/8/23
 * 自動テストプログラム
 * 本プログラムは、ファイルの終端に達するか、読込みエラーが発生した時に呼出し、リボジトリに
 * ファイル終端を示すEOFトークンを登録します。
 */

#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementRepository.h"
#include "EOFInspector.h"

/*
 * inspect: EOFトークン登録
 *  inPutBuff	: 入力文字
 *  outFp		: 出力先
 *
 * 呼び出されるとEOFトークンを登録する
 * return: OK=1, NG=0
 *
 */
int
EOFInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf("EOFlnspector::inspect:Start.%s\n", inputBuff);
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

	// EOF要素のスタートを通知する。
	pElement = pRepo->startElement(Token, pos);

	// トークンのタイプ、種別、Valueを設定
	pElement->setTokenType(SyntaxToken); 		//ノードタイプ設定
	pElement->setTokenKind(EndOfFileToken); 	//ノード種別設定（仮想トークン）
	pElement->setContent((char*)"EOF"); 		//EOF文字をvaLueに登録

	// 要素の終了を通知し、リボジトリに登録する。
	pRepo->endElement(pElement, pos);

	// 初期状態に戻す
	init();
	rc = OK;
	
#ifdef _DEBUG
	printf("EOFlnspector::inspect:End.rc(0x%x)\n", rc);
#endif
	return rc;
}
