/*
 * 自動テストプログラム
 *
 *  逐次通知された文字を評価し、演算子を評価するクラス
 *
 *  クラス名 : OperatorInspector
 *
 *  作成者 : FJH
 *  作成日 : 2016/9/2
 */
 
#if !defined(__OPERATOR_INSPECTOR__)
#define __OPERATOR_INSPECTOR__

#include <vector>
#include "SourceAnalizer.h"
#include "ElementRepository.h"
#include "InspectorBase.h"
#include "ElementProperties.h"
#include "OperatorDef.h"

#define OPERATOR_NUM 36

typedef struct tag_OperatorDefine{
	char*		operatorStr;
	char		firstChar;
	char		secondChar;
	char		thirdChar;
	char		fourthChar;
	int			decidePos;
	TokenKind	tokenKind;
} OperatorDefine;

class OperatorInspector : public InspectorBase{
protected:
	char* name = (char*)"OperatorInspector";
	
private:
	//演算子の前後って、言語的にはWSでなくてもいいから、変数や記号（カツコとか）と隙間なく記述されたら、このままだと誤動作します。
	//前後になにがあっても、この文字シーケンスなら演算子、つて言えるんだっけ？
	//
	OperatorDefine OperatorDefs[OPERATOR_NUM] = {
		/* 			演算子		一字目	二宇目	三宇目	四宇目	決り字	演算子種別 */
		{(const char*)"=",			'=',	' ',	' ',	' ',	2,		AssignmentEqualOperator},
		{(const char*)">",			'>',	' ',	' ',	' ',	4,		NumericalComparisonGraterThanOperator},
		{(const char*)"<",			'<',	' ',	' ',	' ',	3,		NumericalComparisonLessThanOperator},
		{(const char*)"!",			'!',	' ',	' ',	' ',	2,		NotOperator},
		{(const char*)"=",			'~',	' ',	' ',	' ',	2,		BitwiseComplementOperator},
		{(const char*)"->",			'-',	'>',	' ',	' ',	2,		LambdaExpressionOperator},
		{(const char*)"&&",			'&',	'&',	' ',	' ',	2,		ConditionalAndOperator},
		{(const char*)"||",			'I',	'|',	' ',	' ',	2,		ConditionalOrOperator},
		{(const char*)"==",			'=',	'=',	' ',	' ',	2,		EqualToOperator},
		{(const char*)">=",			'>',	'=',	' ',	' ',	4,		NumericalComparisonGraterThanEqualOperator},
		{(const char*)"<=",			'<',	'=',	' ',	' ',	3,		NumericalComparisonLessThanEqualOperator},
		{(const char*)"!=",			'!',	'=',	' ',	' ',	2,		NotEqualToOperator},
		{(const char*)"++",			'+',	'+',	' ',	' ',	2,		IncrementOperator},
		{(const char*)"--",			'-',	'-',	' ',	' ',	2,		DecrementOperator},
		{(const char*)"+",			'+',	' ',	' ',	' ',	2,		PlusOperator},
		{(const char*)"-",			'-',	' ',	' ',	' ',	2,		MinusOperator},
		{(const char*)"*",			'*',	' ',	' ',	' ',	2,		MultipleOperator},
		{(const char*)"/",			'/',	' ',	' ',	' ',	2,		DevideOperator},
		{(const char*)"&",			'&',	' ',	' ',	' ',	2,		BitwiseLogicalAndOperator},
		{(const char*)"|",			'|',	' ',	' ',	' ',	2,		InclusiveOrOperator},
		{(const char*)"^",			'^',	' ',	' ',	' ',	1,		ExclusiveOrOperator},
		{(const char*)"%",			'%',	' ',	' ',	' ',	2,		ModulusOperator},
		{(const char*)"<<", 		'<',	'<',	' ',	' ',	3,		ShiftLeftOperator},
		{(const char*)">>",			'>',	'>',	' ',	' ',	4,		SignedRightShiftOperator},
		{(const char*)">>>",		'>',	'>',	'>',	' ',	4,		UnsignedRightShiftOperator},
		{(const char*)"+=",			'+',	'=',	' ',	' ',	2,		CompoundAssignmentPlusOperator},
		{(const char*)"-=",			'-',	'=',	' ',	' ',	2,		CompoundAssignmentMinusOperator},
		{(const char*)"*=",			'*',	'=',	' ',	' ',	2,		CompoundAssignmentMultipleOperator},
		{(const char*)"/=",			'/',	'=',	' ',	' ',	2,		CompoundAssignmentDevideOperator},
		{(const char*)"&=",			'&',	'=',	' ',	' ',	2,		CompoundAssignmentLogicalAndOperator},
		{(const char*)"|=",			'l',	'=',	' ',	' ',	2,		CompoundAssignmentInclusiveOrOperator},
		{(const char*)"^=",			'^',	'=',	'=',	' ',	2,		CompoundAssignmentExclusiveOrOperator},
		{(const char*)"%=",			'%',	'=',	' ',	' ',	2,		CompoundAssignmentModulusOperator},
		{(const char*)"<<=",		'<',	'<',	'=',	' ',	3,		CompoundAssignmentLeftShiftOperator},
		{(const char*)">>=",		'>',	'>',	'=',	' ',	4,		CompoundAssignmentSignedRightShiftOperator},
		{(const char*)">>>=",		'>',	'>',	'>',	'=',	4,		CompoundAssignmentUnsignedRightShiftOperator}/*,
		{(const char*)"?:",			'?',	'e',	':',	'e',	1,		ConditionalOperator},
		{(const char*)"instanceof",	'i',	'n',	's',	't',	0,		instanceofOperator} */
	};

	std::vector<OperatorDef> operators;
	TokenKind solvedTokenKind;

public:
	/*
	 *lnit:初期化
	 *
	 * メンバ変数を初期化し、演算子定義のベクターを構築します
	 */
	void init();

	/*
	 * inspect:識別子（identifier）評価
	 *   inputBuff : 入力文字
	 *   pRepo     : エレメントを登録するリボジトリ
	 *   pos       : 評価ソース中での文字の位置
	 *
	 *   入力文字を評価し、識別子の条件を満たすか判定する
	 */
	int inspect(char* inputBuff, ElementRepository* pRepo, int pos);

private:
	/*
	 * checkOperator : 指定文字列と演算子の比較
	 *
	 * 参照
	 *  bufff     : 入力文字列
	 *  Operators : 演算子テーブル
	 *
	 * 復帰
	 *  solvedTokenKind : 復帰コードが2のときに、判明した演算子の種別（TokenKind）が入って
	 *  復帰コードが0，1のときには、0（NoneTokenKind）が入っている。
	 *  入力バッファを参照し、演算子かどうかを判定する
	 *
	 * return：0：演算子ではない 1：継続調査 2：演算子と判明した
	 */
	int checkOperator(std::string& anInputStr);

	/*
	* getTokenKind:TokenKindの取得
	*
	* 参照
	*  bufff      : 入力文字列
	*  Operators  : 演算子テーブル
	*
	* 復帰
	*  solvedTokenKind : 復帰コードが2のときに、判明した演算子の種別（TokenKind）が入って
	*  復帰コードが0．1のときには、0（NoneTokenKind）が入っている。
	*
	*  入力バッファを参照し、演算子かどうかを判定する
	*
	* return：0：演算子ではない1：継続調査 2：演算子と判明した
	*/
	TokenKind getTokenKind(std::string& aTokenString);

	/*
	 * str2char:string型からchar*型への変換
	 * パラメタ
	 *  dest : char*文字列の格紳先
	 *  src  : 変換元のstring
	 *
	 * 復帰値：文字列へのポインタ
	 *
	 *  stlのstring型からCの文字列への変換
	 *
	 */
	inline char* str2char(char* dest, const std::string& src);

};		// END of Class

#endif	//	__OPERATOR_INSPECTOR__
