/*
 * 自動テストプログラム
 *
 * 本プログラムは、逐次通知されたトークンを評価し、クラス定義を判定してリボジトリに格納します
 *
 * プログラム名	: CfassDecJarationInspector
 * ファイル名	: ClassDecIarationInspector.cpp
 *
 * 作成者		:FJH
 * 作成日		:2016/8/24
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SourceAnalizer.h"
#include "NodeInspectorBase.h"
#include "ElementRepository.h"
#include "NodeElement.h"
#include "ClassDeclarationInspector.h"

/* inspect:クラス定義評価
 * 	pToken:入力トークン
 *	 PRero:エレメントリボジトリ（ノード格納先）
 * 	COnteXt:外部環境（Class内とか、グローバルとか、そういう情報をビットで表そうかな、と）
 * 	InspecterBaseとパラメタ変わっちやったなあ。NodelnspectorBase作ろうかな。
 *	 ⇒ 作りました
 *
 *  入力トークンを評価し、クラス定義の条件を満たせば、リボジトリに格納します
 *
 */

int
ClassDeclarationInspector::inspect(Element* pToken, ElementRepository* pRepo, int context){

#ifdef _DEBUG
	printf("ClassDeclarationInspector::inspect():Start, TokenId : %d\n", pToken->getId());
#endif

	int rc = NG;
	int nestDepth = 0; 	//クラス定義の中（）の深さ。初期値(トップレベルの中カツコ)を0とします。

	/* 入力パラメタチェック */
	if(pToken == NULL || pRepo == NULL){
		return rc;
	}

	/* 初期化チェック */
	if (initFlag == false){
		return rc;
	}

	/* identifierとReservedKeywordの2種類で同じ文字列が送られてくる件
	 * 送られてくるすべてのトークンに対して、直前に格納されているトークンと内容が同じか判定して、同じであれば必要な方を残すことにします。
	 * 同じかどうかの判定は、スパンが同じかどうかを使います。
	 * 必要な方の判断は、担当しているノードの都合で決めます。
	 *
	 */
	 
#if(0)	//この修正、うまく動きません。
	if(status != NotStarted){								//始まっていないときはNodeElementが無いので、迂回します。
		Element* pEIem = pNodeElement->getLastToken();
		if(pElem->getSpanStart() == pToken->getSpanStart()
			&& pElem->getSpanEnd() == pToken->getSpanEnd() ){
			/* スタート位置と終了位置が同じならば、2重に解釈されているとみなして、先のを取り除きます
			 * *ここで先のを取り除くのは、CIassDeclarationInspectorの個別仕様で、先のトークンがIdentifier
			 * であると仮定しているためです。本来は両者の種別を調べて、優先度の高い方を残すべきだと思います
			 */
			pNodeElement->removeLastToken():
		}
	}
#endif

	/* クラスの判定仕様
	 * クラスの判定では、以下のようなクラス定義を解釈します。
	 * Type1: public abstruct... class ClassName extends SuperClass impIements Interface1 Interface2...{...}
	 * Type2: public             cIass ClassName extends SuperClass implements Interface1 Interface2...{...}
	 * Type3:					 class CIassName extends SuperClass implements Interface1 Interface2...{...}
	 * Type4: 上記の3Type		 class ClassName extends SuperClass {...}
	 * Tyoe5: 上記の3Type		 class ClassName implements Interface1 Interface2 …{...}
	 * Type6: 上記の3Type		 class ClassName {...}
	 * 直前までに何のトークンが指定されていたかによって、クラス定義として今許されるトークン種別が決まります。
	 * そのため、不本意ながらステータスに複数の値を許し、どの位置のトークンを調べているかを判別することにします。
	 * statusの種類
	 * 未解析 						NotStarted					=0
	 * アクセス修飾子指定済み		AccessDecolaterDeclared		=1
	 * クラス修飾子指定済み			ModifierDefined				=2
	 * クラスキーワード指定済み		ClassKeywordDeclared		=3
	 * クラス名指定済み				ClassNameDeclared			=4
	 * extendsキーワード指定済み	ExtendsKeywordDecIared		=5
	 * 親クラス指定済み				SuperClassDecIared			=6
	 * implementsキーワード指定済み	ImplementsKeywordDecLared	=7
	 * インタフェースクラス指定済み InterfaceClassDeclared		=8
	 * クラス定義開始済み			ClassDeclarationStarted		=9
	 *
	 * クラス定義が開始済みになれば、ブレース(”{","}")の開き・閉じを追跡し、クラス定義開始に対応する閉じブレース
	 * を検出すると、クラス定義が完了したとみなして、ClassDeclarationノードを登録します。
	 * クラスとして記述できないトークンを検出した時は、revokeElement()して未解析に戻ります。
	 * Javaの文法上はアクセス修飾子とクラス修飾子は、差がない(いずれもClass Modifier)。当プログラムはコンパイル
	 * 可能なソースを入力にするという前提で作成しているので、定義の段階を認識する必要はないはずですが、なんとなく
	 * アクセス修飾子は把握しておいた方が良い気がするので、分けておきます。
	 * あと、java8の文法書を見ていて知ったのですが、ClassNameの後にGeneric ClassﾆおけるType Parameterが置けるら
	 * しいのですが、Genelicへの対応は後回しにします。
	 * 同様に、Annotationへの対応も後回しにします。
	 * (テストに影響するかなあ．‥)
	 */
	 
	TokenKind tokenKind = pToken->getTokenKind();

	/*クラス定義を解析中かどうか */
	if(status == NotStarted){
		/* 解析中ではない->クラス定義開始の判定 */
		/* アクセス修飾子かクラス修飾子かclassキーワードならクラス定義開始 */
		if( tokenKind == PublicKeyword
		 || tokenKind == ProtectedKeyword
		 || tokenKind == PrivateKeyword ){
			/* アクセス修飾子なのでリボジトリにスタートを通知 */
			pNodeElement = (NodeElement*)pRepo->startElement(Node, pToken->getSpanStart());	//startEIenent()すると、NodeEIementｶﾞElement型で返ってくるのでキャスト
			pNodeElement->setToken(pToken);													//Tokenを格納
			/* アクセス修飾子指定済みにする */
			status = AccessDecolaterDeclared;

		} else if (tokenKind == AbstructKeyword
			|| tokenKind == StaticKeyword
			|| tokenKind == FinalKeyword
			|| tokenKind == StrictFpKeyword) {
			/* クラス修飾子なのでリボジトリにスタートを通知 */
			pNodeElement = (NodeElement*)pRepo->startElement(Node, pToken->getSpanStart() );
			// 上とおんなじなので、まとめられないかなあ
			pNodeElement->setToken(pToken);
			/* クラス修飾子指定済みにする */
			status = ModifierDeclared;

		} else if (tokenKind == ClassKeyword){
			/* classキーワードなのでリボジトリにスタートを通知 */
			pNodeElement = (NodeElement*)pRepo->startElement(Node, pToken->getSpanStart() );
			// 上とおんなじなので、まとめられないかなあ
			pNodeElement->setToken(pToken);
			/* クラス修飾子指定済みにする */
			status = ClassKeywordDeclared;

		} else {
			/* クラス定義が開始していない */
			;	/* なにもしないで良いんかな？ */
		}

	} else if (status == AccessDecolaterDeclared ){
		/* 解析中でアクセス修飾子指定済み->この判定のとこ、共通関数化しないとやばいかなあ */
		if (tokenKind == AbstructKeyword
		 || tokenKind == StaticKeyword
		 || tokenKind == FinalKeyword
		 || tokenKind == StrictFpKeyword) {
		 	/* クラス修飾子なのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* クラス修飾子指定済みにする */
			status = ModifierDeclared;

		} else if(tokenKind == ClassKeyword){
			/* classキーワードなのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* クラス修飾子指定済みにする */
			status = ClassKeywordDeclared;

		} else {
			/* アクセス修飾子を見つけたけど、クラス定義じやなかった */
			pRepo->revokeElement(pNodeElement);	 		// 要素を破棄
			init();											// インスペクタを初期化
		}

	} else if(status == ModifierDeclared ){
		/* 解析中でクラス修飾子指定済み */
		/* クラス修飾子は複数宣言できるんだよねえ。なのでクラス修飾子も検査します。 */
		if( tokenKind == AbstructKeyword
		 || tokenKind == StaticKeyword
		 || tokenKind == FinalKeyword
		 || tokenKind == StrictFpKeyword) {
			/* クラス修飾子なのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* クラス修飾子指定済みにする(再度) */
			status  =ModifierDeclared;

		} else if ( tokenKind == ClassKeyword){
			/* Classキーワードなのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* クラス修飾子指定済みにする */
			status = ClassKeywordDeclared;
		} else {
			/* クラス修飾子を見つけたけど、クラス定義じやなかった */
			pRepo->revokeElement(pNodeElement); 			//要素を破棄
			init(); 										//インスペクタを初期化
		}

	} else if ( status == ClassKeywordDeclared){
		/* Classキーワード指定済み->クラス名の判定 */
		if ( tokenKind == IdentifierToken){
			/* クラス名を示す識別子なのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* クラス名指定済みにする */
			status = ClassNameDeclared;

		} else {
			/* クラスキーワードを見つけたけど、次がクラス名じやない
			 * でもこれコンパイルエラーだよね
			 */
			pRepo->revokeElement(pNodeElement);				//要素を破棄
			init();											//インスペクタを初期化
		}

	} else if ( status == ClassNameDeclared){
		/* Class名指定済み->Extends,ImpIementsの判定 */
		if ( tokenKind == ExtendsKeyword){
			/* 派生元を示す識別子なのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* クラス名指定済みにする */
			status = ExtendsKeywordDeclared;
			
		} else if ( tokenKind == ImplementsKeyword) {
			/* 派生元を示す識別子なのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* クラス名指定済みにする */
			status =ImplementsKeywordDeclared;

		} else if ( tokenKind == OpenBraceToken) {
			/* 開き中カツコを検出->クラス定義開始 */
			pNodeElement->setToken(pToken);
			/* クラス定義開始済みにする */
			status = ClassDeclarationStarted;
		} else {
			/* クラス名の後がExtendsでもImplementsでもない */
			pRepo->revokeElement(pNodeElement);				// 要素を破棄
			init();											// インスペクタを初期化
		}

	} else if ( status == ExtendsKeywordDeclared ) {
		/* Extendsキーワード指定済み->識別子の判定
		 * 本当はクラス名を判定すべきなんでしょうが、これはコンパイラでも
		 * リンカでもないので、識別子かどうかだけ調べます。
		 */
		if ( tokenKind == IdentifierToken){
			/* 識別子なのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* スーパークラス名指定済みにする */
			status = SuperClassDeclared;

		} else {
			/* Extendsキーワードの後が識別子じやない
			 * でもこれコンパイルエラーだよね
			 */
			pRepo->revokeElement(pNodeElement);				// 要素を破棄
			init();											// インスペクタを初期化
		}

	} else if ( status == ImplementsKeywordDeclared){
		/* Implementssキーワード指定済み->識別子の判定
		 *本当はインタフェース名を判定すべきなんでしょうが、以下略
		 */
		if ( tokenKind == IdentifierToken){
			/* 識別子なのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* スーパークラス名指定済みにする */
			status = InterfaceClassDeclared;
			
		} else {
			/* Implementsキーワードの後が識別子じやない
			 * でもこれ以下略
			 */
			pRepo->revokeElement(pNodeElement);				// 要素を破棄
			init();											// インスペクタを初期化
		}

	} else if ( status == SuperClassDeclared){
			/* SuperClass名指定済み->Implementsかオープンブレースか判定
			 * Javaは多重継承ないので、Extendsは検査しないですみます。
			 */
		if ( tokenKind == ImplementsKeyword){
			/*識別子なのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* Implementsキーワード指定済みにする */
			status = ImplementsKeywordDeclared;

		} else if ( tokenKind == OpenBraceToken){
			/* オープンブレースなのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* クラス定義開始済みにする */
			status = ClassDeclarationStarted;

		} else {
			/* スーパークラス名の後がImplementsでも"l"でもない
			 *でもこれ以下略
			 */
			pRepo->revokeElement(pNodeElement);				// 要素を破棄
			init();			// インスペクタを初期化
		}

	} else if ( status == InterfaceClassDeclared){
		/* InterfaceClass名指定済み->Implementsかオープンブレースか判定
		 * インタフェースは複数実装できるのでしょうがない．
		 */
		if ( tokenKind == ImplementsKeyword){
			/* 識別子なのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* Implementsキーワード指定済みにする */
			status = ImplementsKeywordDeclared;

		} else if ( tokenKind == OpenBraceToken){
			/* オープンブレースなのでトークンを登録 */
			pNodeElement->setToken(pToken);
			/* クラス定義開始済みにする */
			status = ClassDeclarationStarted;
		} else{
			/* インタフェース名の後がImplementsでも"Ⅰ"でもない
			 *でもこれ以下略
			 */
			pRepo->revokeElement(pNodeElement);				// 要素を破棄
			init();											// インスペクタを初期化
		}

	} else if ( status == ClassDeclarationStarted){
		/* クラス定義開始済み->後は対応する閉じ中カツコが出現するまでひたすら登録 */
		if ( tokenKind == CloseBraceToken){
			if ( nestDepth == 0){
				/* ネストの深さが0でクローズブレース出現 */
				pNodeElement->setToken(pToken); 						//トークンを登録
				pNodeElement->setNodeType(ClassDeclarationSyntax);		//ノードタイプ設定
				pNodeElement->setNodeKind(ClassDeclaration); 			//ノード種別設定
				pRepo->endElement(pNodeElement, pToken->getSpanEnd());	//リボジトリに登録 -> クラス定義終了！
			} else {
				/* クローズブレースが出現したが、ネストの深さが0ではない */
				pNodeElement->setToken(pToken);							// トークンを登録
				nestDepth--;											// ネストの深さを減らす
			}

		} else if ( tokenKind == OpenBraceToken){
			/* トークンを登録して */
			pNodeElement->setToken(pToken);
			/* オープンブレースなのでネストの深さを1つ増やす */
			nestDepth++;

		} else {
			/* "{"でも、"}"でもない
			 *トークンの中身に関わらず要素を登録して継続します
			 */
			pNodeElement->setToken(pToken);
		}

	} else {
		/* いずれのステータスでもない場合。こんな場合はバグなんですけどね。 */
		if ( pNodeElement ){
			pRepo->revokeElement(pNodeElement); 			//ノード要素を作ってしまっていたら破棄
		}
		init(); 											//インスペクタを初期化
		rc =  NG;
		goto END; 											//goto‥.ちょっと見逃して．

	}
	
	rc = OK;

END:
#ifdef _DEBUG
	printf("ClassDecrarationInspector::inspect():End.rc(0x%x)\n", rc);
#endif

return rc;
}
