/*
 *自動テストプログラム
 *
 *  トークンを評価するNodeInspectorクラスの基底クラス
 *
 *
 *  クラス名 : NodeInspectorBase
 *  ファイル名 :NodetnspectorBase.cpp
 *
 *  作成者：FJH
 *  作成日：2016／7／12
 */
 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SourceAnalizer.h"
#include "NodeInspectorBase.h"

/*
 * ‾NodeInspectorBase:デストラクタ
 */
NodeInspectorBase::~NodeInspectorBase(){
	if(pNodeElement){
		delete pNodeElement;
	}
}

/*
 * InspectorBase:コピーコンストラクタ
 */
NodeInspectorBase::NodeInspectorBase(const NodeInspectorBase& rBase){
	// クラス識別
	// 各クラスが固有の文字列を持つので、コピー不要
	// 評価状態を示すフラグ true：要素評価中 false：要素評価外
	status = rBase.status;
	
	// 初期化フラグ
	initFlag = rBase.initFlag;
	
	// エレメント : Elementクラスのコピーコンストラクタ使用
	pNodeElement = new NodeElement(*(rBase.pNodeElement));
}

/*
 * init:初期化
 * 各メンバフィールドを初期化する。
 */
void
NodeInspectorBase::init(void){
#ifdef _DEBUG
	printf("NodeInspectorBase::init:Start.\n");
#endif

	status = false;
	pNodeElement = NULL;		// こんな適当な初期化でいいかなぁ？
								// 最初はNULLクリアで良いし、ノードを登録し終わった後の初期化では、
								// トークンのエレメントはリポジトリに入ってしまってるんで問題ない
								// はずなんだけど．．．
	initFlag = true;

#ifdef _DEBUG
	printf("NodeInspectorBase::init:End.\n");
#endif
	return;
}

