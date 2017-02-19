/*
 * 自動テスト検証プログラム
 *
 * ノード要素を表すエレメントクラス
 *
 * クラス名： NodeElement
 *
 * 作成者：FJH
 * 作成日：2016／8／19
 */
 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementProperties.h"
#include "NodeElement.h"

/*
 * デストラクタ
 */
NodeElement::~NodeElement(){
	if (!tokenList.empty()){
		tokenList.clear();
	}
}

/*
 * デフォルトコンストラクタ
 */
NodeElement::NodeElement(){
}

/*
 * コピーコンストラクタ
 */
NodeElement::NodeElement(const NodeElement& rElement){
	elementClass = rElement.elementClass;
	memcpy(elementValue, rElement.elementValue, sizeof(elementValue));
	elementSpanStart = rElement.elementSpanStart;
	elementSpanEnd = rElement.elementSpanEnd;
	elementId = rElement.elementId;
	tokenList = rElement.tokenList;
}

/*
 * 引数付きコンストラクタ
 */
NodeElement::NodeElement(ElementClass aClass, char* pValue, int spanStart, int spanEnd){
	elementClass = aClass;
	memset(elementValue, 0x00, sizeof(elementValue));
	strcpy(elementValue, pValue);
	elementSpanStart = elementSpanStart;
	elementSpanEnd = elementSpanEnd;
	tokenList.clear();
	elementId = 0;
}

/*
 * 要素を外部形式で出力する
 */
int
NodeElement::printOut(FILE* outFp){
#ifdef _DEBUG
	printf("NodeElement::printOut():Start.\n");
#endif
	int rc = NG;

	FILE* fp;
	if(outFp == NULL){
		fp = stdout;
	} else {
		fp = outFp;
	}

	ElementProperties* ep = new ElementProperties();

	/*
	 *エレメントを出力する
	 */
	fprintf(fp, "Id    : %d\n", elementId);														// 要素ID
	fprintf(fp, "Valid : %s\n", (valid==Valid)? "Valid" : "Invalid");							// 有効・無効フラグ
	fprintf(fp, "class : %d %s\n", elementClass, ep->getElementClassString(elementClass));		// 要素クラス
	fprintf(fp, "Type  : %d%s\n", typeKind, ep->getTypeString(elementClass, typeKind));			// 要素タイプ
	fprintf(fp, "Kind  : %s￥n", ep->getKindString(elementClass, typeKind));					// 要素種別
	fprintf(fp, "value : %s\n", elementValue); 													// 内容
	fprintf(fp, "Span  : [%d,%d]\n\n", elementSpanStart, elementSpanEnd);						// 開始終了位置
	fprintf(fp, "Tokens\n");											 						// トークンの表題

	/* ここノードに含まれるエレメントを列挙して出力してますが、
	 * コンテンツを結合して出力したほうが親切かも
	 * まあ、とりあえずはこの形で
	 */
	for(std::list<Element*>::iterator it_node = tokenList.begin();
		it_node != tokenList.end();
		it_node++){
		(*it_node)->printOut(fp);
	}
	fprintf(fp,"Tokens End.\n\n"); 		// エンドマーク

	rc =OK;

#ifdef _DEBUG
	printf("NodeEIement::printOut():End. rc(0x%x)\n", rc);
#endif

	return rc;
}

/*
 * トークンを設定する
 */
int
NodeElement::setToken(Element* pToken){
#ifdef _DEBUG
	printf("NodeElement::setToken():Start. TokenId = %d\n", pToken->getId());
#endif
	int rc = NG;

	if(!pToken){
		return rc;
	}
	
	tokenList.push_back(pToken);
	rc = OK;
	
#ifdef _DEBUG
	printf("NodeEIement::setToken():End. rc(Ox%x)\n", rc);
#endif

	return rc;

}

/*
 * 最後のトークンを取得する
 */
Element*
NodeElement::getLastToken(){
#ifdef _DEBUG
	printf("NodeEJement::getLastToken():Start.\n");
#endif

#ifdef _DEBUG
	printf("NodeElement::getLastToken():End.\n");
#endif

return tokenList.back();

}

/*
 * 最後のトークンを取り除く
 */
int
NodeElement::removeLastToken(){
#ifdef _DEBUG
	printf("NodeElement::removeLastToken():Start.\n");
#endif
	int rc = NG;
	tokenList.pop_back();
	rc = OK;
	
#ifdef _DEBUG
	printf("NodeElement::removeLasttToken():End.\n");
#endif
	return rc;
}
