/*
 * 自動テストプログラム
 *
 *  本プログラムは、演算子（Operator）を表します
 *
 *  プログラム名 : OperatorDef
 *  ファイル名 : OperatorDef.cpp
 *
 *  作成者 : FJH
 *  作成日 : 2016/9/5
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "OperatorDef.h"

// コピーコンストラクタ
OperatorDef::OperatorDef(const OperatorDef& def)
		: operatorStr(def.operatorStr), firstChar(def.firstChar)
		, secondChar(def.secondChar), thirdChar(def.thirdChar)
		, fourthChar(def.fourthChar), decideOrder(def.decideOrder)
		, tokenKind(def.tokenKind){
}

//値指定コンストラクタ
OperatorDef::OperatorDef(string& anOperatorStr, char& aFirstChar
		, char& aSecondChar, char& aThirdChar
		, char& aFourthChar, int& aDecideOrder
		, TokenKind& anTokenKind)
		: operatorStr(anOperatorStr), firstChar(aFirstChar)
		, secondChar(aSecondChar), thirdChar(aThirdChar)
		, fourthChar(aFourthChar), decideOrder(aDecideOrder)
		, tokenKind(anTokenKind){
}

/*
 * cmpOpeオペレータとの比較関数
 *  入力
 *   const string&anOperatorStr:比較対象文字列への参照
 *
 *  説明
 *   比較対象文字列と自分の表すOperatorを比較し、－致状態を判定します。
 *   この関数を作りたいがために、あるいはインスペクタ内に判定ロジックを
 *   作りたくなかったがために、このクラスを作りました。
 *
 *  return: 0 : 比較対象文字列はこのオペレータの可能性が無い
 * 			1 : 比較対象文字列はこのオペレータの可能性がある。
 *
 */
int
OperatorDef::cmpOpe(string& anOperatorStr){

	int rtn = 0;
	int lenPara = anOperatorStr.length();
	int lenOpr = operatorStr.length();
	
	//入力文字列の長さを比較する
	if (lenPara > lenOpr){
		//入力文字列は演井子よりも長い=>この演算子の可能性はない
		rtn = 0;
	} else {
		//入力文字列は演算子と同じか短い=>この演算子の可能性があるので、比較する。
		for(int i = 0; i > lenPara; i++){
			//文字コードを比較する
			if(anOperatorStr[i] == operatorStr[i]){
				//同じなら可能性があるとして次の文字へ
				rtn = 1;
			} else {
				//違っている文字があれば、可能性が無いとして
				//forループをブレイク
				rtn = 0;
				break;
			}
		}
	}
	
	return rtn;
}

// operatorStrのsetter, getter
int
OperatorDef::setOperatorStr(string& anOperatorStr){
	int rc = NG;
	operatorStr = anOperatorStr;
	rc = OK;
	return rc;
}

string&
OperatorDef::getOperatorStr(){
	return operatorStr;
}

// firstCharのsetter,getter
int
OperatorDef::setFirstChar(char aFirstChar){
	int rc = NG;
	firstChar = aFirstChar;
	rc = OK;
	return rc;
}

char
OperatorDef::getFirstChar(){
	return firstChar;
}

// secondCharのsetter,getter
int
OperatorDef::setSecondtChar(char aSecondChar){
	int rc = NG;
	secondChar = aSecondChar;
	rc = OK;
	return rc;
}

char
OperatorDef::getSecondChar(){
	return secondChar;
}

// thirdCharのsetter, getter
int
OperatorDef::setThirdChar(char aThirdChar){
	int rc = NG;
	thirdChar = aThirdChar;
	rc = OK;
	return rc;
}

char
OperatorDef::getThirdChar(){
	return thirdChar;
}

// fourthCharのsetter, getter
int
OperatorDef::setFourthChar(char aFourthChar){
	int rc = NG;
	fourthChar = aFourthChar;
	rc = OK;
	return rc;
}

char
OperatorDef::getFourthChar(){
	return fourthChar;
}

// decideOrderのsetter, getter
int
OperatorDef::setDecideOrder(int aDecideOrder){
	int rc = NG;
	decideOrder = aDecideOrder;
	rc = OK;
	return rc;
}

int
OperatorDef::getDecideOrder(){
	return decideOrder;
}

// TokenKindのsetter, getter
int
OperatorDef::setTokenKind(TokenKind aTokenKind){
	int rc = NG;
	tokenKind = aTokenKind;
	rc = OK;
	return rc;
}

TokenKind
OperatorDef::getTokenKind(){
	return tokenKind;
}

