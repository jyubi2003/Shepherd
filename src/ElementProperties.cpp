/*
 * 自動テスト検証プログラム
 *
 * 要素のクラス、タイプ、種別
 *
 * クラス名:   EIementProperties
 * ファイル名: ElementProperties.cpp
 *
 * 作成者: FJH
 * 作成日: 2016/8/2
 */
 
#include"ElementProperties.h"
/*
 * 要素クラスの外部表現を返す
 */
const char*
ElementProperties::getElementClassString(ElementClass elemClass){

	return lt_ElementClass[elemClass];
};

/*
 * 要素クラスに応じた、タイプの外部表現を返す
 */
const char*
ElementProperties::getTypeString(ElementClass elemClass, un_TypeKind typeKind){
	const char* retStr = 0;
	if(elemClass == Node){
		retStr = lt_NodeType[typeKind.node.nodeType];
	} else if(elemClass == Token) {
		retStr = lt_TokenType[typeKind.token.tokenType];
	} else if(elemClass == Torivia) {
		retStr = lt_ToriviaType[typeKind.torivia.toriviaType];
	} else {
		retStr = "Element Class undefined.";
	}

	return retStr;
};

/*
 * 要素クラスに応じた、種別の外部表現を返す
 */
const char*
ElementProperties::getKindString(ElementClass elemClass, un_TypeKind typeKind){
	const char* retStr = 0;
	if(elemClass == Node) {
		retStr = lt_NodeKind[typeKind.node.nodeKind];
	} else if(elemClass == Token) {
		retStr = lt_TokenKind[typeKind.token.tokenKind];
	} else if(elemClass == Torivia) {
		retStr = lt_ToriviaKind[typeKind.torivia.toriviaKind];
	} else {
		retStr = "Element Class undefined.";
	}
	return retStr;
	
};
