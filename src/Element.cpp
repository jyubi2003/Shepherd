/*
 * 自動テスト検証プログラム
 *
 * 要素を表すエレメントクラス
 *
 * クラス名: EIement
 *
 *作成者: FJH
 *作成日: 2016/7/12
 */
 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SourceAnalizer.h"
#include "Element.h"
#include "ElementProperties.h"

using namespace std;

/*
 * デストラクタ
 */
Element::~Element(){
}

/*
 * デフォルトコンストラクタ
 */
Element::Element(){
}

/*
 * 引数付きコンストラクタ
 */
Element::Element(ElementClass aClass, char* pValue, int spanStart, int spanEnd){
	elementClass = aClass;
	memset(elementValue, 0x00, sizeof(elementValue));
	strcpy(elementValue, pValue);
	elementSpanStart = spanStart;
	elementSpanEnd = spanEnd;
	elementId = 0;
}

/*
 * コピーコンストラクタ
 */
Element::Element(const Element& rElement){
	elementClass = rElement.elementClass;
	memcpy(elementValue, rElement.elementValue, sizeof(elementValue));
	elementSpanStart = rElement. elementSpanStart;
	elementSpanEnd = rElement.elementSpanEnd;
	elementId = rElement.elementId;
}

/*
 * Idを設定する
 */
int
Element::setId(int id){
#ifdef _DEBUG
	printf("Elenent::setId():\n");
#endif
	elementId = id;
	return elementId;
}

/*
 * Idを取得する
 */
int
Element::getId(){
#ifdef _DEBUG
	printf("Element::getId(); \n");
#endif
	return elementId;
}

/*
 * 要素クラスを設定する
 */
void
Element::setElementClass(ElementClass elementClass){
#ifdef _DEBUG
	printf("Element::setElementCIass(%d):\n", (int)elementClass);
#endif
	this->elementClass = elementClass;
}

/*
 * 要素クラスを取得する
 */
ElementClass
Element::getElementClass(){
	return elementClass;
}

/*
 *ノードタイプを設定する
 */
void
Element::setNodeType(NodeType nodeType){
	typeKind.node.nodeType = nodeType;
}

/*
 *ノードタイプを取得する
 */
NodeType
Element::getNodeType(){
	return typeKind.node.nodeType;
}

/*
 * ノード種別を設定する
 */
void
Element::setNodeKind(NodeKind nodeKind){
	typeKind.node.nodeKind = nodeKind;
}

/*
 * ノード種別を取得する
 */
NodeKind
Element::getNodeKind(){
	return typeKind.node.nodeKind;
}

/*
 *トークンタイプを設定する
 */
void
Element::setTokenType(TokenType tokenType){
	typeKind.token.tokenType = tokenType;
}

/*
 *トークンタイプを取得する
 */
TokenType
Element::getTokenType(){
	return typeKind.token.tokenType;
}

/*
 *トークン種別を設定する
 */
void
Element::setTokenKind(TokenKind tokenKind){
	typeKind.token.tokenKind = tokenKind;
}
/*
 *トークン種別を取得する
 */
TokenKind
Element::getTokenKind(){
	return typeKind.token.tokenKind;
}

/*
 *トリビアタイプを設定する
 */
void
Element::setToriviaType(ToriviaType toriviaType){
	typeKind.torivia.toriviaType = toriviaType;
}

/*
 *トリビアタイプを取得する
 */
ToriviaType
Element::getToriviaType(){
	return typeKind.torivia.toriviaType;
}

/*
 *トリビア種別を設定する
 */
void
Element::setToriviaKind(ToriviaKind toriviaKind){
	typeKind.torivia.toriviaKind = toriviaKind;
}

/*
 *トリビア種別を取得する
 */
ToriviaKind
Element::getToriviaKind(){
	return typeKind.torivia.toriviaKind;
}

/*
 * 要素のコンテントを設定する
 */
int
Element::setContent(char* pContent){
	int rc = false;
	if (pContent != NULL){
		strcpy(elementValue, pContent);
		rc = true;
	} else {
		;	// NOP
	}

	return rc;
}

/*
 * 要素のコンテントを設定する（string版）
 */
int
Element::setContent(std::string& aContent){
	int rc = false;
	strcpy(elementValue, aContent.c_str());
	rc = true;
	return rc;
}

/*
 * 要素のコンテントを取得する
 * パラメタを参照にしたいよ～
 * でも今書き方を調べるのが大変なので、オアインタのポインタにしときます。
 */
int
Element::getContent(char** ppContent){
	int rc = false;
	if (ppContent != NULL){
		*ppContent = elementValue;
		rc = true;
	} else {
		// NOP
	}
	return rc;
}

/*
 * 要素のコンテントに追加（結合）する
 */
int
Element::catContent(char* pContent){
	int rc = false;
	if(pContent != NULL){
		if(sizeof(elementValue)-strlen(elementValue) > strlen(pContent)){	//バッファの残りサイズがあるか確認
			strcat(elementValue, pContent);
			rc = true;
		} else {
			// NOP
		}
	} else {
		// NOP
	}
	return rc;
}

/*
 * 要素の開始位置を設定する
 */
void
Element::setSpanStart(int spanStart){
	elementSpanStart = spanStart;
}

/*
 * 要素の開始位置を取得する
 */
int
Element::getSpanStart(){
	return elementSpanStart;
}

/*
 * 要素の終了位置を設定する
 */
void
Element::setSpanEnd(int spanEnd){
	elementSpanEnd = spanEnd;
}

/*
 * 要素の終了位置を取得する
 */
int
Element::getSpanEnd(){
	return elementSpanEnd;
}

/*
 * 要素の長さを取得する
 */
int
Element::getSpan(){
	return(elementSpanEnd - elementSpanStart);
}

/*
 * 要素の有効・無効を設定する
 */
int
Element::validateElement(ValidFlag iValid){
	valid = iValid;
	return OK;
}

/*
 * 要素の有効・無効を取得する
 */
ValidFlag
Element::isValidElement(){
	return valid;
}

/*
 * 要素を外部形式で出力する
 */
int
Element::printOut(FILE* outFp){
	FILE* fp;
	if(outFp == NULL){
		fp = stdout;
	} else {
		fp = outFp;
	}

	ElementProperties* ep = new ElementProperties();
	/*
	 * エレメントを出力する
	 */
	fprintf(fp, "Id :%d\n", elementId);														// 要素ID
	fprintf(fp, "valid : %s\n", valid == Valid ? "valid" : "Invalid");						// 有効・無効フラグ
	fprintf(fp, "class : %d%s\n", elementClass, ep->getElementClassString(elementClass));	// 要素クラス
	fprintf(fp, "Type  : %d%s\n", typeKind, ep->getTypeString(elementClass, typeKind));		// 要素タイプ
	fprintf(fp, "Kind  : %s\n", ep->getKindString(elementClass, typeKind));					// 要素種別
	fprintf(fp, "Value : %s\n", elementValue);												// 内容
	fprintf(fp, "Span  :[%d,%d]\n\n", elementSpanStart,elementSpanEnd);						// 開始位置、終了位置

	return OK;

}
