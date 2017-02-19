/*
 * 自動テストプログラム
 *
 *  演算子を表すクラス
 *
 *  クラス名 : OperatorDef
 *  ファイル名 : OperatorDef.h
 *
 *  作成者 : FJH
 *  作成日 : 2016/9/5
 */

#if !defined(__OPERATOR_DEF__)
#define __OPERATOR_DEF__

#include <string>
#include "SourceAnalizer.h"
#include "ElementProperties.h"

// stlを使います。stringいっぱい書いてるし、いちいち"std::"つけるの面倒なので、名前空間宣言しちやいます。
using namespace std;

#define OPERATOR_STR_LEN 11 	//instanceofが10文字なので11にしています。どうやって評価するかまだ考えてないけど。

class OperatorDef {
protected:
	char* name = (char*)"OperatorDef";

private:
	string		operatorStr;
	char		firstChar;
	char		secondChar;
	char		thirdChar;
	char		fourthChar;
	int			decideOrder;
	TokenKind	tokenKind;

public:
	// デフォルトコンストラクタ
	OperatorDef() = default;

	// コピーコンストラクタ
	OperatorDef(const OperatorDef& rDef);

	// 値指定コンストラクタ
	OperatorDef(string& anOperatorStr, char& aFirstChar,
				char& aSecondChar, char& aThirdChar,
				char& aFourthChar, int& aDecideOrder,
				TokenKind& anOprToken);

	// オペレータとの比較関数
	int cmpOpe(string& anOperatorStr);

	// operatorStrのsetter, getter
	int setOperatorStr(string& anOperatorStr);
	string& getOperatorStr();

	// firstCharのsetter, getter
	int setFirstChar(char aFirstChar);
	char getFirstChar();

	// secondCharのsetter, getter
	int setSecondtChar(char aSecondChar);
	char getSecondChar();

	// thirdCharのsetter, getter
	int setThirdChar(char aThirdChar);
	char getThirdChar();

	// fourthCharのsetter, getter
	int setFourthChar(char aFourthChar);
	char getFourthChar();

	// decideOrderのsetter, getter
	int setDecideOrder(int aDecideOrder);
	int getDecideOrder();

	// tokenKindのsetter, getter
	int setTokenKind(TokenKind aTokenKind);
	TokenKind getTokenKind();

};	//END of Class

#endif	// __OPERATOR_DEF__
