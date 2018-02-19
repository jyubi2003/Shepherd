/*
 * 自動テストプログラム
 *
 * インスペクターからの通知を受け取り、要素を管理するリボジトリクラス
 *
 * クラス名: ElementRepository
 * ファイル名: ElfementRepository.cpp
 *
 * 作成者: FJH
 * 作成日: 2016/7/12
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "SourceAnalizer.h"
#include "Element.h"
#include "ImportInspector.h"
#include "ElementRepository.h"
#include "CompilationUnitInspector.h"
#include "ClassDeclarationInspector.h"

/* ElementRepository::init:初期化
 *
 * エレメントリボジトリを初期化する。
 *
 */
void
ElementRepository::init(){
#ifdef _DEBUG
		printf("ElementRepository::init():Start.\n");
#endif

	/*
	 * トークン格納コンテナの初期化
	 */
	tokens.clear();

	/*
	 * ノード格納コンテナの初期化
	 */
	nodes.clear();

	/*
	 * トリビア格納コンテナの初期化
	 */
	torivias.clear();

	/*
	 * エレメントIDの初期化
	 */
	 
	elementId = 1;
	
	/*
	 * 初期化完了
	 */ 
	initFlag = true;

#ifdef _DEBUG
	//printf("%s::init:End\n",name):
	printf("ElementRepository::init():End.\n");
#endif

	return;
}

/*EJementRepository::startElement:要素の開始を通知
 * elemClass:エレメントのクラス
 * inputBuff:入力文字
 * outFp:出力先
 * 要素のクラス毎にElementクラス（派生クラスを含む）を生成し、リボジトリに追加して、呼び出し元に通知する。
 * 検出時優先：要素は、可能性のある文字やトークンを検出した時に作成し、リボジトリに登録してしまう。
 * 検証が進んで登録済みの要素が、予想された要素でなかった場合、リボジトリから取りく。
 * 検出時優先の考え方をとることにより、リボジトリには出現順に要素が登録される。
 * これを確定時優先とすると、要素が複数の要素タイプを持たない方式では問題ないが、した意味
 * を持つ方式の場合、要素の長さにより確定タイミングが異なり、出現順にならない。（Compilation
 * UnitSyntaxの場合、package文と同時に開始するが、確定は最後のクローズブレースとなり、リボジ
 * トリの最後に登録されることになる。）
 *
 */
Element*
ElementRepository::startElement(ElementClass aClass, int startPos){
#ifdef _DEBUG
	printf("ElementRepository::StartElement():Start.\n");
#endif

	int rc = NG;
	Element* pElement;

	/* 入力パラメタチェック */
	if(startPos < 0){
		return NULL;
	}
	
	/* 初期化チェック */
	if(initFlag == false){
		return NULL;
	}
	
	/* 要素を作成してリボジトリに追加する */
	switch(aClass){
	case Token:
		/*要素を作成してプロパティを設定する*/
		pElement = new Element();
		// pElemenﾄ->setId(elernentId);
		pElement->validateElement(Valid);
		pElement->setElementClass(aClass);
		pElement->setSpanStart(startPos);
		tokens.push_back(pElement);
		break;
		
	case Node:
		/*要素を作成してプロパティを設定する*/
		pElement = (Element*)new NodeElement();
		//pElement->setId(eJementId);
		pElement->validateElement(Valid);
		pElement->setElementClass(aClass);
		pElement->setSpanStart(startPos);
		nodes.push_back(pElement);
		break;
		
	case Torivia:
		pElement = new Element();
		//pE[emenﾄ->setId(eIementId);
		pElement->validateElement(Valid);
		pElement->setElementClass(aClass);
		pElement->setSpanStart(startPos);
		// torivias.push_back(pElement);
	 	// Toriviasに格納しようと思ってましたが、Tokenとの順序を維持するのが難しいので
		// 同じtokensに格納します。
		tokens.push_back(pElement);
		break;

	default:
		return NULL;

	}

	rc = OK;

#ifdef _DEBUG
	printf("ElementRepository::StartElement() End.rc(Ox%x)\n", rc);
#endif
	return pElement;

}

/*
 * ElementRepository::endElement: 要素を確定する
 * inputBuff: 入力文字
 * outFp: 出力文字
 * 要素の最終ポジションをセットし、要素を確定する。
 * (2016.8.30)
 * オプション機能を追加
 * 　今回登録した要素を同じスパンを持つ要素がすでに登録されている場合、その要素のクラスを調べ
 * 　今回登録した要素との優先順を判定して、優先度の低い要素をリストから取り除く。
 * 　そのまま残しておく考えもあるが、どうもノードの判定に障害になるので、この機能をONにしておく
 * 　インスペクタでやろうかと思ったが、リボジトリの実装を見せたくないし、インスペクタが多くて
 * 　影響範囲が広くなるので、ここで一意にやります。
 */
int
ElementRepository::endElement(Element* pElement, int endPos, Duplicate dupFlag){
#ifdef _DEBUG
	char* pContent;
	pElement->getContent(&pContent);
	printf("ElementRepository::endElement():Start. pElement(%s)\n", pContent);
#endif

	int rc = NG;

	/* 入力パラメタチェック */
	if(pElement == NULL &&
		pElement->getSpanStart() < pElement->getSpanEnd()){
		return rc;
	}

	/*初期化チェック */
	if(initFlag == false){
		return rc;
	}
	
	/*要素をリボジトリに追加する*/
	//要素IDを発行するのはここ？ というかスタートで追加済みなので、endPosを設定するだけ。
	pElement->setSpanEnd(endPos);

	/*
	 *  2016.8.30
	 * 要素の重複を調べ、同一スパンを持つ要素があれば、優先度をチェックして優先度の低い要素を
	 * 削除する機能追加。
	 * 優先度～？ そんな情報も持たんといけんのね．．
	 */
	/* dupFlagとは。説明しよう。dupFlagとは、スパンが同一の要素をリボジトリに格納することを指定するフラグである。
	 * このフラグがon′′であれば、リボジトリにはスパンの同じ要素、つまりコンテントの同じ要素が複数存在することを許可し、
	 * 要素格納時に同一スパン要素の存在をチェックしない。"off"のときには同一スパンの要素の格納を禁止とするため、要素
	 * 格納時に、リボジトリに既に同一スパン要素が存在していないか確認し、存在していれば、優先度の高い要素を残し、その
	 * 他の要素を削除する。なお、dupFlagはデフォルト引数で、デフォルト値は”off”である。
	 */
	if(dupFlag == Off){
		if(pElement->getElementClass() == Node){
			/* とりあえず、トークンだけ有れば良いので ここは後回し*/

		} else if(pElement->getElementClass() == Token){
			/*
			 *  ホントはもっと上手く見つける方法があるはず！
			 * find()に比較関数を渡して、同じエレメントの一覧を取得するとか。
			 * でも、今手元にSTLの解説書が無くてわからないので、ぐるぐる回して調べます。
			 */
			for(std::list<Element*>::iterator it_token = tokens.begin();
				it_token != tokens.end(); it_token++ ){
				if( *it_token == pElement ){
					/* 自分自身ならNOP */
				} else {
					/* 自分じやなければ、比較する。*/
					/* そしてこれ！スパンを比較して、同じものか判定します */
					if( (*it_token)->getSpanStart() == pElement->getSpanStart()
						&& (*it_token)->getSpanEnd() == pElement->getSpanEnd() ){
						/* 同じ文字列だとわかれば、今度はどっちの優先度が高いか判定するテープルかなんか作って
						 * やるべきですが、今は先に入ってるのが識別子で、新しく来たやつがキーワードってわかって
						 * いるので、リボジトリの方を消します。
						 * と、しようとしましたが、STLのeraseは使い方が難しいので、消去はやめてフラグで有効な
						 * 要素か無効な要素かを設定します0ここでは、重複があった場合、リボジトリ側の要素を無効
						 * にします。
						 */
						(*it_token)->validateElement(Invalid);
					}
				}
			}

		} else /* Torivia */ {
		/* ここも後回し*/

		}
	} else {
		/* dupFIagがOnのとき
		 * 同じ内容の複数のコンテンツを許す。つてことですが、驚いたことに、これ呼出しごとに指定できるように
		 * なってしまった。そんな必要あるかどうかわかりませんが、とにかく許可するときは「消さない」というこ
		 * となので、要素の作成時にすでにリボジトリに登録済みとする今の方式では、なにもしません。
		 */
	}
	/* 妻素の登録が成功したので、エレメントIDを更新する。
	 * ただし、ここにはバグがあって、要素の登録によってのみIDが増えるので、
	 * 重なったスパンで2重に要素をnewしたときは、同－のIDが振られてしまいます。
	 * 解決策としては、
	 * 登録時にIDを振る
	 * 重なるときには、基本的に同じスパンなので、同じIDとしておく
	 * 同じIDだと後から困りそうなので、”ID払い出し済みカウンダ’みたいなものを作り、
	 * サブ番号を振る
	 * などが考えられますが、そのうち考えることとして、今はこのままにします。
	 * 2016.8.30
	 * 上に内容が同－のトークンを消す処理を入れちやったので、もしかしたら重複IDも副作用で
	 * なくなったかも。
	 * 2016.09.02
	 * 消す処理を止めて、フラグ管理にしたけど、IDがめちやくちやになった。
	 * 消さなくなったので、綺麗に一意化できればいいんだけど。reVOkeしたエレメントにもID要らないし
	 * やっぱり登録時に振るのが王道かな。
	 */
	pElement->setId(elementId); // ElementIdの初期値が1なので、先にセットしてそれからインクリメントします。
	elementId++;

	rc =OK;

#ifdef _DEBUG
	printf("ElementRepository::endElement():End rc(Ox%x)\n", rc);
#endif
	return rc;
	
}

/* ELementRepositorY∴revokeElement:要素を破棄する
 *  pElement:破棄する要素
 *
 * 指定された要素をリボジトリから削除する。
 * エレメントのデリートってやってるかなあ。もしかしたらリークしてるかも。
 *
 */
int
ElementRepository::revokeElement(Element* pElement){
#ifdef _DEBUG
	printf("EfementRepository::revokeEfement():Start\n");
#endif

	int rc = NG;
	
	/* 入力パラメタチェック */
	if(pElement == NULL){
		return rc;
	}
	
	/* 初期化チェック */
	if(initFlag == false ){
		return rc;
	}

	/* 指定されたエレメントをコンテナから除去 */
	switch(pElement->getElementClass()) {
	case Token:
		{
			std::list<Element*>::iterator it = find(tokens.begin(), tokens.end(), pElement);
			if(it != tokens.end()){
				tokens.erase(it);
			}
		}
		break;
		
	case Node:
		{
			std::list<Element*>::iterator it = find(nodes.begin(), nodes.end(), pElement);
			if(it != nodes.end()){
				nodes.erase(it);
			}
		}
		nodes.remove(pElement);
		break;
		
	case Torivia:
		{
			std::list<Element*>::iterator it = find(tokens.begin(), tokens.end(), pElement);
			if(it!=tokens.end()){
				tokens.erase(it);
			}
		}
		break;
		
	defauIt:
		return rc;

	}

	/* エレメントをデリートする */
	delete pElement;

	rc = OK;
	
#ifdef _DEBUG
	printf("ElementRepository::revokeElement():End rc(Ox%x)\n", rc);
#endif

	return rc;
}

/*
 * printElements : 要素を指定された出力先に、外部形式で出力する
 *  elemClass: 出力する要素種。NoneElementClassを指定した場合、すべて出力される
 *  outFp: 出力先
 *
 */
int
ElementRepository::printElements(ElementClass elemClass, FILE* outFp){
#ifdef _DEBUG
	printf("ElementRepository::printElements():Start.\n");
#endif
	int rc = NG;

	FILE *fp;
	if(outFp == NULL){
		fp = stdout;
	} else {
		fp = outFp;
	}

	if(elemClass == Node){
		iterateElements(Print, Node, fp);
		
	} else if(elemClass == Token){
		iterateElements(Print, Token, fp);
		
	} else if(elemClass == Torivia){
		iterateElements(Print, Torivia, fp);
		
	} else /* ALL Elements */ {
		iterateElements(Print, Node, fp);
		iterateElements(Print, Token, fp);
		iterateElements(Print, Torivia, fp);

	}

	rc = OK;

#ifdef _DEBUG
	printf("ElementRepository::printElements():End.rc(Ox%x)\n", rc);
#endif

	return OK;
}

/*
 * iterateElements:要素に繰返し処理を行う
 *  ope:実行する処理
 *  elemClass:処理する要素種。NoneEIementClassを指定した場合、すべてが処理される
 *  outFp:出力先
 *
 *  注意：Toriviaをnodesに格納しているため、Toriviaを指定してもなにも出力されず、
 *  Nodeを指定するとToriviaも出力されます。
 */
int
ElementRepository::iterateElements(Operate ope, ElementClass elemClass, FILE* outFp){
#ifdef _DEBUG
	printf("EIementRepository::iterateElements():Start.\n");
#endif

	int rc = NG;
	switch(ope){
	case Print:
		if(elemClass == Node){
			for(std::list<Element*>::iterator it_node = nodes.begin();
				it_node != nodes.end(); it_node++){
				(*it_node)->printOut(outFp);
			}
		} else if(elemClass == Token){
			for(std::list<Element*>::iterator it_token = tokens.begin();
				it_token != tokens.end(); it_token++){
				(*it_token)->printOut(outFp);
			}
		} else if(elemClass == Torivia){
			for(std::list<Element*>::iterator it_torivia = torivias.begin();
				it_torivia != torivias.end(); it_torivia++){
				(*it_torivia)->printOut(outFp);
			}
		}
		
		break;
		
	case Dump:
		break;

	default:
		break;

	};

	rc = OK;

#ifdef _DEBUG
	printf("ElementRepository::iterateElements():End.rc(0x%x)\n", rc);
#endif

	return rc;
}

/*
 * analizeNode:ノードを生成する
 *  引数なし
 *  格納されているトークンを逐次読出し、ノードを生成する
 *
 */
int
ElementRepository::analizeNode(){
#ifdef _DEBUG
	printf("ElementRepository::analizeNode():Start.\n");
#endif

	int rc=NG;
	/******************************************************************************
	*ノードインスペクタの生成
	*******************************************************************************/
	CompilationUnitInspector* pCompilationUnitInspector = new CompilationUnitInspector();		// コンパイル単位検査

	if(pCompilationUnitInspector == NULL){
		return rc;
	}
	
	ImportInspector* pImportInspector = new ImportInspector();					// import文検査
	if(pImportInspector == NULL){
		return rc;
	}

	ClassDeclarationInspector* pClassDeclarationInspector = new ClassDeclarationInspector();	//クラス定義検査
	if(pClassDeclarationInspector == NULL){
		return rc;
	}
	
	/*****************************************************************************
	* インスペクタの初期化
	******************************************************************************/
	pCompilationUnitInspector->init();
	pImportInspector->init();
	pClassDeclarationInspector->init();
	
	/******************************************************************************
	*トークンを読みだして、逐次インスペクタに渡す
	******************************************************亨**********************/
	for(std::list<Element*>::iterator it_token = tokens.begin();
		it_token != tokens.end(); it_token++){
		/* 2重に意味付けされた要素（識別子と予約語など）がノードに重複して登録
		 * されるのを防ぐため、要素をリポジトリに登録するときに有効・無効フラグ
		 * を付けています。ここでは、有効に設定されているトークンのみを処理します。
		 */
		if((*it_token)->isValidElement() == Valid){
			/*
			 * コンパイルユニット
			 */
			rc = pCompilationUnitInspector->inspect(*it_token, this, 0);
			if( rc != OK){
				break;
			}
			/*
			 * 次にimportディレクティブ
			 * ってこんな風に呼出し順を決めないといけない
			 * としたら、そのうち破たんしそうだな～ どうしようかな～
			 * でもノード要素の出現順って決まってそうだし、大丈夫かも
			 */
			rc = pImportInspector->inspect(*it_token, this, 0);
			if(rc != OK){
				break;
			}
			/*
			 * クラス定義
			 */
			rc = pClassDeclarationInspector->inspect(*it_token, this, 0);
			if(rc != OK ){
				break;
			}
		} else {
			; //なにもしない
		}
	}

	/******************************************************************************
	*インスペクタの削除
	*****************************************************************************/
	if(pClassDeclarationInspector){
		delete pClassDeclarationInspector;
	}

	if(pCompilationUnitInspector){
		delete pCompilationUnitInspector;
	}
	
	if(pImportInspector){
		delete pImportInspector;
	}

#ifdef _DEBUG
	printf("ElementRepository::analizeNode():End.rc(Ox%x)\n", rc);
#endif

	return rc;

};
