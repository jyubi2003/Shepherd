/*
 * 自動テスト検証プログラム
 *
 * 要素を表すエレメントクラス
 *
 * クラス名   : Element
 * ファイル名 : Element.h
 *
 * 作成者 : FJH
 * 作成日 : 2016/7/12
 */
 
#if !defined(__ELEMENT__)
#define __ELEMENT__

#include <stdlib.h>
#include <string>
#include "SourceAnalizer.h"
#include "ElementProperties.h"

using namespace std;

#define ELEMENT_VALUE_SIZE 4096

enum ValidFlag {
	Valid,
	Invalid
};

/*
 * Elementクラス定義
 */
class Element {
protected:
	/* Elementの属性 */
	int 			elementId;							// 要素ID
	ValidFlag		valid;								// 有効・無効フラグ
	ElementClass	elementClass;						// 要素クラス
	un_TypeKind		typeKind;							// 要素タイプ・種別の共用体
	char			elementValue[ELEMENT_VALUE_SIZE];	// 内容
	int 			elementSpanStart;					// 開始位置
	int				elementSpanEnd;						// 終了位置

public:
	/*
	 * デストラクタ
	 */
	~Element();

	/*
	 * デフォルトコンストラクタ
	 */
	Element();

	/*
	 * コピーコンストラクタ
	 */
	Element(const Element& rElement);

	/*
	 * 引数つきコンストラクタ
	 */
	Element(ElementClass aClass, char* pValue, int spanStart, int spanEnd);

	/*
	 * Idを設定する
	 */
	int setId(int id);

	/*
	 * Idを取得する
	 */
	int getId();

	/*
	 * 要素クラスを設定する
	 */
	void setElementClass(ElementClass elementClass);

	/*
	 * 要素クラスを取得する
	 */
	ElementClass getElementClass();

	/*
	 * ノードタイプを設定する
	 */
	void setNodeType(NodeType nodeType);
	
	/*
	 * ノードタイプを取得する
	 */
	NodeType getNodeType();

	/*
	 * ノード種別を設定する
	 */
	void setNodeKind(NodeKind nodeKind);

	/*
	 * ノード種別を取得する
	 */
	NodeKind getNodeKind();

	/*
	 * トークンタイプを設定する
	 */
	void setTokenType(TokenType tokenType);

	/*
	 * トークンタイプを取得する
	 */
	TokenType getTokenType();

	/*
	 * トークン種別を設定する
	 */
	void setTokenKind(TokenKind tokenKind);

	/*
	 * トークン種別を取得する
	 */
	TokenKind getTokenKind();

	/*
	 * トリビアタイプを設定する
	 */
	void setToriviaType(ToriviaType toriviaType);

	/*
	 * トリビアタイプを取得する
	 */
	ToriviaType getToriviaType();

	/*
	 * トリビア種別を設定する
	 */
	void setToriviaKind(ToriviaKind torivianKind);

	/*
	 * トリビア種別を取得する
	 */
	ToriviaKind getToriviaKind();

	/*
	 *  要素のコンテントを設定する
	 */
	int setContent(char* pContent);

	/*
	 *  要素のコンテントを設定する
	 */
	int setContent(std::string& content);

	/*
	 * 要素のコンテントを取得する
	 * パラメタを参照にしたいよ
	 * ～でも今書き方を調べるのが大変なので、ポインタのポインタにしときます
	 */
	int getContent(char** pContent);

	/*
	 * 要素のコンテントに追加（結合）する
	 */
	int catContent(char* pContent);

	/*
	 * 要素の開始位置を設定する
	 */
	void setSpanStart(int spanStart);

	/*
	 * 要素の開始位置を取得する
	 */
	int getSpanStart();

	/*
	 * 要素の終了位置を設定する
	 */
	void setSpanEnd(int spanEnd);

	/*
	 * 要素の終了位置を取得する
	 */
	int getSpanEnd();

	/*
	 * 要素の長さを取得する
	 */
	int getSpan();

	/*
	 * 要素の有効無効を設定する
	 */
	int validateElement(ValidFlag valid);

	/*
	 * 要素の有効無効を取得する
	 */
	ValidFlag isValidElement();

	/*
	 * 要素を外部形式で出力する
	 */
	virtual	int printOut(FILE* OutFp = NULL);

};	// End of class

#endif	//__ELEMENT__
