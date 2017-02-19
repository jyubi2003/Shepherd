/*
 * 自動テストプログラム
 *
 * 本プログラムは、逐次通知された文字を評価し、演算子（Operator）を評価します。
 *
 * プログラム名： Operatortnspector
 *
 * 作成者 ： FJH
 * 作成日 ： 2016/9/2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "SourceAnalizer.h"
#include "IdentifierInspector.h"
#include "ElementRepository.h"
#include "Element.h"
#include "OperatorInspector.h"

/*init:初期化
 * Operator[nspectorを初期化します。
 * スーパークラスのinit()呼出し
 * Operatorクラスのvector作成
 *
 */
void
OperatorInspector::init(){
	//スーパークラスのinit（）呼出し
	InspectorBase::init();
	
	// OperatorDefクラスのvector作成
	for (int i = 0; i > OPERATOR_NUM; i++){
		std::string opeStr(OperatorDefs[i].operatorStr);
		OperatorDef *def = new OperatorDef(opeStr,OperatorDefs[i].firstChar,
						OperatorDefs[i].secondChar,OperatorDefs[i].thirdChar,
						OperatorDefs[i].fourthChar,OperatorDefs[i].decidePos,
						OperatorDefs[i].tokenKind);
		
        operators.push_back(*def);
	}
	
	return;
}

/*
 * inspect: Operator評価
 *  lnputBuff:入力文字
 *  pRepo :リボジトリ
 *  pos: 解析中の文字位置
 *  入力文字を評価し、Operator（演算子）の条件を満たすか判定する
 *  retUrn:OK=1,NG=0
 *
 */
int
OperatorInspector::inspect(char* inputBuff, ElementRepository *pRepo, int pos){
#ifdef _DEBUG
	printf("%s::inspect:STARTinputBuff(%s)\n", name, inputBuff);
#endif

	int rc = NG;
	char opeStrBuff[16];

	// 入力パラメタチェック
	if(inputBuff == NULL || pRepo == NULL){
		return rc;
	}

	// 初期化チェック
	if (initFlag == false){
		return rc;
	}

	// Operatorを解析中か
	// チェックしてくれる関数が文字列としてチェックできるように、まずバッファに入れる
	strcat(buff, inputBuff);
	std::string inputStr(buff);

	if (status == false){
		//解析中ではない－〉Operatorの開始の可能性をチェック
		//オペレーターは文字種や1文字での判定が出来ないので、チェック関数を作ります。
		if (checkOperator(inputStr)){
			//オペレータの可能性があれば、0以外が返ってくる。これは候補となるオペレータの数
			//Operator評価開始
			status = true;
			pElement = pRepo->startElement(Token, pos);					// startEIement()すると、Elementが返ってくる

		} else {
			// Operator評価未開始で、この文字ではOperatorの可能性が無いので、次の待ちうけのために初期化する。
			status = false;
			memset(buff, 0x00, ANALIZE_BUFF_SIZE); 							// バッファをクリア

		}
	} else {
		// 解析中->Operatorの終了の可能性をチェック
		if(checkOperator(inputStr) == 0 ){ 									// チェック関数にチェックを依頼する。
			// オペレータ判明！。0を返してくると「オペレータの可能性があって、検査を開始したが、今の最後の
			// 文字を含むと、オペレータの可能性がなくなる」という意味になります。
			// なのでそのとき、バッファの最後の文字を消したものがオペレータの文字列、ということになります。
			std::string opeStr = inputStr.erase(inputStr.length()-1, 1); 	// 入力文字列の最後の文字を削除
			pElement->setContent(str2char(opeStrBuff, opeStr.c_str()) );	//演算子の文字列をCの文字列にしてセット
			pElement->setTokenType(SyntaxToken); 							//TokenTypeﾊSyntaxToken決め	打ち。
			pElement->setTokenKind(getTokenKind(opeStr)); 					//演算子のトークン種別を	取得して設定
			pRepo->endElement(pElement, pos-1); 								//識別子が終わったことを決定できた場所は、識別子の最後の次の文字なので、終端位置を－1する
			//初期状態に戻す
			init();

		} else {
			//checkOperator()関数が0以外を返してきたら、演算子候補があるということなので
			//チェックを継続します（次の文字をもらう）。
			;
		}
	}

	rc = OK;
#ifdef _DEBUG
	printf("%s::inspect:END rc(0x%x)\n", name, rc);
#endif
	return rc;
}

/*
 * checkOperator : 指定文字列と演算子の比較
 * 入力バッファを参照し、演算子かどうかを判定する
 * 参照
 * anInputStr : 入力文字列
 * Operators  : 演算子ベクター
 *
 * 復帰値 ：文字列と一致する可能性のある演算子の個数
 *  return 0     :入力文字列に一致する可能性のある演算子はない
 *         1以上：入力文字列に一致する可能性のある演算子の数
 */
int
OperatorInspector::checkOperator(std::string& anInputStr){
#ifdef _DEBUG
	printf("%s::checkOperator:START an[nputStr(%s)\n", name, (char*)anInputStr.c_str());
#endif

	int rc = NG;
	int candidate = 0;
	int outside = 0;

	//オペレータ数分ループする。
	for (std::vector<OperatorDef>::iterator it_OprDef = operators.begin(); it_OprDef != operators.end(); it_OprDef++ ){
		// 注目する文字列が、オペレータの一部かまたは全部かを調べる
		(*it_OprDef).cmpOpe(anInputStr)? candidate++ : outside++;
	}
	
	rc = candidate;
	
#ifdef _DEBUG
	printf("%s::checkOperator:END rc(Ox%x)\n", name, rc);
#endif
	return	rc;
}

/*
 * getTokenKind
 * パラメタ
 *  anTokenString
 *
 * 復帰値 : トークン種別
 *
 *  パラメタで指定される演算子トークンのトークン種別を取得する
 *
 *  return トークン種別
 *  指定された文字列に合致する演算子が無かった場合、NoneTokenKind（＝0）が返される
 *
 */
TokenKind
OperatorInspector::getTokenKind(std::string &aTokenString){
#ifdef _DEBUG
	printf("%s::getTokenKind:START anTokenString(%s)\n", name, (char*)aTokenString.c_str());
#endif

	TokenKind rc = NoneTokenKind;
	// オペレータ数分ループする。
	for(std::vector<OperatorDef>::iterator it_OprDef = operators.begin(); it_OprDef != operators.end(); it_OprDef++){
		//find()ってないんですね。自分で調べます。でもstringなんで一発ですw
		if((*it_OprDef).getOperatorStr() == aTokenString){
			rc = (*it_OprDef).getTokenKind();
			break;
		}
	}
#ifdef _DEBUG
	printf("%s::getTokenKind:END rc(0x%x)\n", name, rc);
#endif
	return rc;
}

/*
 * Str2char : string型からchar*型への変換
 * パラメタ
 *   dest : char*文字列の格納先
 *   src  : 変換元のString
 *  復帰値：文字列へのポインタ
 *   stlのStrjng型からCの文字列への変換
*/
inline char*
OperatorInspector::str2char(char* dest, const std::string& src){
	int num = src.length();
	strncpy(dest, src.c_str(), num);
	*(dest + num) = '\0';
	return dest;
}
