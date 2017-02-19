/*
 * 自動テストプログラム
 * BBPInspect ブラケット"[]"、ブレース"{}"、パレン"()"を評価するクラス
 *
 * クラス名： BBPInspector
 *
 * 作成者 : FJH
 * 作成日 : 2016/8/9
 */

#if !defined(__BBP_INSPECTOR__)
#define __BBP_INSPECTOR__

#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "InspectorBase.h"

class BBPInspector : public InspectorBase {
protected:
const char *name = "BBPInspector";

public:
/*
 * lnSPeCt:識別子(identifier)評価
 * ipnputBuff：入力文字
 * PRepo ニ エレメントを登録するリボジトリ
 * POS ：評価ソース中での文字の位置
 * 入力文字を評価し、識別子の条件を満たすか判定する
 */
int inspect(char* inputBuff, ElementRepository* pRepo, int pos);

}; //END of Class
#endif //__BBP_INSPECTOR__
