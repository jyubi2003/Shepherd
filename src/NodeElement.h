/*
 * 自動テスト検証プログラム
 *
 * ノード要素を表すノードエレメントクラス
 *
 * クラス名   : NodeElement
 * ファイル名 : NodeEIement.h
 *
 * 作成者 : FJH
 * 作成日 : 2016/8/19
 */
 
#if !defined(__NODE_ELEMENT__)
#define __NODE_ELEMENT__

#include <stdlib.h>
#include <list>
#include "SourceAnalizer.h"
#include "ElementProperties.h"
#include "Element.h"

/*
 * NodeElementクラス定義
 */
class NodeElement : public Element {
protected:
	/*
	 * Elementｶﾗ継承する属性
	 *  int				ErementId; 			// 要素ID
	 *  ElementClass	elementClass:		// 要素タイプ
	 *  un_TypeKind		typeKind:			// 要素タイプ、種別の共用体
	 *  char 			elementValue[512]	// 内容
	 *  int				elementSpanStart:	// 開始位置
	 *  int				elementSpanEnd:		// 終了位置
	 */

	/* NodeElementクラスの属性 */
	std::list<Element*> tokenList;

public:
	/*
	 * デストラクタ
	 */
	~NodeElement();
	
	/*
	 * デフォルトコンストラクタ
	 */
	NodeElement();

	/*
	 * コピーコンストラクタ
	 */
	NodeElement(const NodeElement& rNodeElemnt);

	/*
	 * 引数つきコンストラクタ
	 */
	NodeElement(ElementClass aClass, char* pValue, int spanStart, int spanEnd);

	/*
	 * Idを設定する
	 */
	//int setId(intid);

	/*
	 * Idを取得する
	 */
	//jnt getId():

	/*
	 * 要素クラスを設定する
	 */
	//void setElementClass(EIementClass elementClass);

	/*
	 * 要素クラスを取得する
	 */
	//ElementClass getElementClass();

	/*
	 *ノードタイプを設定する
	 */
	//void setNodeType(NodeType nodeType);

	/*
	 *ノードタイプを取得する
	 */
	//NodeType getNodeType():

	/*
	 * ノード種別を設定する
	 */
	//void setNodeKind(NodeKind nodeKind);

	/*
	 * ノード種別を取得する
	 */
	//NodeKind getNodeKind();

	/*
	 *トークンタイプを設定する
	 */
	//void setTokenType(TokenType tokenType);

	/*
	 *トークンタイプを取得する
	 */
	//TokenType getTokenType();

	/*
	 *トークン種別を設定する
	 */
	//void setTokenKind(TokenKind tokenKind):

	/*
	 *トークン種別を取得する
	 */
	//TokenKind getTokenKind();

	/*
	 *トリビアタイプを設定する
	 */
	//void seToriviaType(ToriviaType toriviaType);

	/*
	 *トリビアタイプを取得する
	 */
	//ToriviaType getToriviaType();

	/*
	 *トリビア種別を設定する
	 */
	//void setToriviaKind(ToriviaKind torivianKind);

	/*
	 *トリビア種別を取得する
	 */
	//ToriviaKind getToriviaKind();

	/*
	 * 要素のコンテントを設定する
	 */
	//int setContent(char*PContent);

	/*
	 * 要素のコンテントを取得する
	 */
	//int getContent(char*pContent);

	/*
	 * 要素の開始位置を設定する
	 */
	//void setSpanStart(int spanStart):

	/*
	 * 要素の開始位置を取得する
	 */
	//int getSpanStart();

	/*
	 * 要素の終了位置を設定する
	 */
	//void setSpanEnd(int spanEnd);

	/*
	 * 要素の終了位置を取得する
	 */
	//int getSpanEnd();

	/*
	 * 要素の長さを取得する
	 */
	//int getSpan():

	/*
	 *要素を外部形式で出力する
	 */
	int printOut(FILE* OutFp = NULL);

	/*
	 *トークンを設定する
	 */
	int setToken(Element* pToken);

	/*
	 *最後のトークンを取得する
	 */
	Element* getLastToken();

	/*
	 *最後のトークンを取り除く
	 */
	int removeLastToken();

};	// End of cIass

#endif //__NODE_ELEMENT__
