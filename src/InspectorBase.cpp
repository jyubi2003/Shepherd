/*
 * 自動テストプログラム
 *
 * トークンを評価するInspectorクラスの基底クラス
 *
 * クラス名 : InspectorBase
 *
 * 作成者 : FJH
 * 作成日 : 2016／7／12
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SourceAnalizer.h"
#include "InspectorBase.h"

/*
 *‾InspectorBase:デストラクタ
 */
InspectorBase::~InspectorBase(){
	if (pElement){
		delete pElement;
	}
}

/*
 * InspectorBase : コピーコンストラクタ
 */
InspectorBase::InspectorBase(const InspectorBase& rBase){
	//クラス識別
	//各クラスが固有の文字列を持つので、コピー不要
	//評価バッファ
	memcpy(buff, rBase.buff, ANALIZE_BUFF_SIZE);

	//評価状態を示すフラグtrue：要素評価中false：要素評価外
	status = rBase.status;

	//初期化フラグ
	initFlag = rBase.initFlag;
	
	//エレメント：EJementクラスのコピーコンストラクタ使用
	pElement = new Element(*(rBase.pElement));
}

/*
 * init:初期化
 * 各メンバフィールドを初期化する。
 *
 */
void
InspectorBase::init(void){
#ifdef _DEBUG
	printf("InspectorBase::init:\n");
#endif

	memset(buff, 0x00, ANALIZE_BUFF_SIZE);
	status = false;
	pElement = NULL;
	initFlag = true;

#ifdef _DEBUG
	printf("InspectorBase::End:\n");
#endif

	return;
}
