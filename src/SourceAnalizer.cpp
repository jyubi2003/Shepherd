/*
 * 自動テストプログラム
 * 本プログラムは、指定されたソースファイルを解析し、文章構造を出力します。
 * 下記の情報を出力します。
 * ・トークン情報
 * ・ノード情報
 * ・トリビア情報
 *
 * プログラムのインタフェース
 * コマンドライン： itestall src [OutputFile]
 * パラメータ　　： src ソースファイル名
 *					  ソースファイル名は相対パスでも絶対パスでも良い
 *					OutputFile 出力ファイル名（省略可）
 *					  省略された場合、標準出力に出力する
 *
 * きっとあるべき姿としては、lexやyaccやantIrなんかを使って構文解析するのでしょうが、
 * そういう学術的な方法を理解できないので、自力アルゴリズムですw
 * これがものになれば、そのうち、賢い人が書き直してくれるでしょう。
 *
 *作成者：FJH h．yoshida
 *作成日：2016／7／31
 */

/* システムインクルード */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cstdio>

/* トークン・トリビアのインスベクタ */
#include "SourceAnalizer.h"
#include "CommentInspector.h"
#include "IdentifierInspector.h"
#include "ReservedInspector.h"
#include "WhitespaceInspector.h"
#include "EndOfLineInspector.h"
#include "QuortInspector.h"
#include "BBPInspector.h"
#include "SeparatorInspector.h"
#include "ColonInspector.h"
#include "EOFInspector.h"
#include "OperatorInspector.h"

/* ノードのインスペクタ あれ？ここにいるんだっけ？ */
#include "ImportInspector.h"

/* リボジトリ */
#include "ElementRepository.h"

/*
 * 定数一覧
 */
/*構文解析用の定数群*/
static const char* S_MACRO		= "#if";
static const char* C_MACRO		= "#else";
static const char* E_MACRO		= "#endif";
static const char* D_MACRO		= "#define";
static const char* S_COMMENT	= "/*";
static const char* E_COMMENT	= "*/";
static const char* LITERAL		= "\\";
static const char* LITERAL2		= "\\\\";
static const char* LITERAL3		= "\\\\\\";
static const char* S_FUNC		= "(";
static const char* E_FUNC		= ")";
static const char* S_BLOCK		= "{";
static const char* E_BLOCK		= "}";
static const char* E_PROC		= ";";
static const char* EXEC_SQLl	= "EXEC";
static const char* EXEC_SOL2	= "SQL";
static char 	COMMENT_CHR		= '/';
static char		LITERAL_CHR		= '\"';
static char		S_FUNC_CHR		= '(';
static char		E_FUNC_CHR		= ')';
static char		S_BLOCK_CHR		= '{';
static char		E_BLOCK_CHR		= '}';
static char		E_PROC_CHR		= ';';
static char		BLANK_CHR		= ' ';
static char		COMMA_CHR		= ',';
static char		AND_CHR			= '&';
static char		TAB_CHR			= '\t';
static char		LF_CHR			= '\n';

/*
 * グローバル変数
 */

/* コメント解析中であるか判定1：コメント中0：コメント外 */
int	isComment = 0;

/* リテラル解析中であるか判定1：リテラル解析中0：リテラル解析外 */
int	isLiteral = 0;

/* ブロック解析の階層0：グローバル1～関数内のブロックの階層 */
int blevel = 0;

/* 関数の階層 */
int globaIFuncLevel = 0;

/* 連続コメントチェック連続コメント中加算されていく */
int repeatCommentCount = 0;

/* 関数名を出力してるかチェック */
int	isOutputFunc = 0;

/* マクロの判定中であるか判定1：中0：外 */
int	isMacro= 0;

/* 処理中の関数 */
char currentFuncList[STACK_FUNC_SIZE][FUNC_NAME_SIZE];

/* 処理中関数の1行目のコメント */
char currentFuncComment[FUNC_NAME_SIZE];

/*
 * プロトタイプ関数
 */
/* 文字列のトリム処理 */
char*	trim(char* Str);

/* 文字列中にキーワードがあるかチェック なければ0を返す。あればキーワードの番号を返す */
int search(char* str, int keynum, char** keyword);

/* グローバルの関数名を取得 */
char* getGlobalFunc(char* buf, int checkPos, char* funcName);

/* 関数中で関数名を取得する */
char* getFunc(char* buf, int checkPos, char* funcName);

/* 関数名のログ出力要 */
int checkFunc(char* func);

/* コメント中のタブを削除する処理 */
char* deltab(char* Str);

/* コメントの整形機能 */
char* funcComment(char* buf);

/* 主処理 */
int
main(int argc, char* argv[]){
	FILE*	fp;
	FILE*	outFp;
	char	inputBuff[INPUT_BUFF_SIZE];
	int		res;
/*
 * パラメタチェック、初期化処理
 * まず、パラメタをチェックして、問題がなければ起動状態を出力します。
 *
 */
	if(argc!=2 && argc!=3){
		/*エラー：パラメタ数*/
		printf("usage:itestall src [outputFile]\n");
		return 1;
	}

#ifdef _DEBUG
	printf("itestall Start.\n");
	if(argc == 2){
		printf(" main(%d, %s, %s, %s : \n", argc, argv[0], argv[1], argv[2]);
	} else {
		printf(" main(%d, %s, %s : \n", argc, argv[0], argv[2]);
	}
#endif

	/***************************************************************
	 * 初期化
	 * ポインタクリア、バッファのクリア、入出力ファイルのオープン
	 ***************************************************************/
	fp = NULL;
	outFp = NULL;
	memset(inputBuff, 0x00, sizeof(inputBuff));
	res = NG;

	/*
	 * 入力ファイルをオープン
	 */
	fp =fopen(argv[1], "r");
	if(fp==NULL){
		printf("file open Error. fileName=%s\n", argv[1]);
		return 1;
	}
	
	/*
	 * 出力ファイルの指定があれば、出力ファイルオープン
	 * しかし、このファイルポインタ、どこでも使われていない∧＿∧
	 * 各モジュールでデバッグメッセージを出してるので、全部に渡さないといけないのか
	 * それとも、結果を印刷するElementRepositoryだけに漉して、デバッグメッセージは
	 * エラー出力にだすか・・・いろいろと考えられるので、今はこのままにしておきます。
	 */
	if(argc==3){
		outFp = fopen(argv[2],"w");
		if(outFp==NULL){
			printf("file open Error.funcName=%s\n", argv[2]);
			return 1;
		}
	}else{
		/* 省略時は標準出力 */
		outFp = stdout;
	}
	
	/**********************************************************************
	 * 処理準備ができたので、処理用の各種オブジェクトをインスタンス化します
	 *********************************************************************/
	/* リボジトリの生成と初期化 */
	ElementRepository* pElementRepository = new ElementRepository();
	pElementRepository->init();

	/* トークンのインスペクタを生成
	 * ここまでエラーを全然拾ってませんが、きっとtry－CatCh構文が必要なんだと思う
	 */
	CommentInspector* 		pCommentInspector = new CommentInspector();			// コメントを評価するインスペクタ
	IdentifierInspector*	pIdentifierInspector = new IdentifierInspector();	// 識別子を評価するインスペクタ
	ReservedInspector*		pReservedInspector = new ReservedInspector();		// 予約語を評価するインスペクタ
	OperatorInspector*		pOperatorInspector = new OperatorInspector();		// 演算子を評価するインスペクタ
	WhitespaceInspector*	pWhitespaceInspector = new WhitespaceInspector();	// ホワイトスペースを評価するインスベクタ
																				// を考えたが、C＋＋型コメントの最後の改行と重なる。
																				// C＋＋型コメントに改行を含まないことにすべきか・・・それ
																				// とも改行はホワイトスペースから外すか、でも改行
																				// プログラム的にはほとんど意味ないし、と悩んで、
																				// Rosaけnの解析結果を見てみると、ホワイトスペース
																				// トークン扱いにしていなくて、トリビア扱いでした
																				// より悩ましくなった…
																				// 改行も、ホワイトスペースも別で扱うことにしまし
																				// た。（2016／8／26）
	EndOfLineInspector* 	pEndOfLineInspector = new EndOfLineInspector();		//改行を評価するインスペクタ
	QuortInspector*			pQuortInspector = new QuortInspector();				//引用符を評価するインスペクタ
	BBPInspector*			pBBPInspector = new BBPInspector();					//カツコ類を評価するイン
	SeparatorInspector*		pSeparatorInspector = new SeparatorInspector();		//コンマ、ドットを評価するインスペクタ
	ColonInspector*			pColonInspector = new ColonInspector(); 			//コロン、セミコロンを評価するインスペクタ
	EOFInspector*			pEOFInspector = new EOFInspector();					//ファイルの終端を評価するインスベクタ

	/* インスペクタの初期化 */
	pCommentInspector->init();
	pIdentifierInspector->init();
	pOperatorInspector->init();
	pReservedInspector->init();
	pWhitespaceInspector->init();
	pEndOfLineInspector->init();
	pQuortInspector->init();
	pBBPInspector->init();
	pSeparatorInspector->init();
	pColonInspector->init();
	pEOFInspector->init();

	/* リポジトリ初期化 */
	pElementRepository->init();

	/****************************************************************************************
	 * 処理は、（1）トークンの解析、（2）ノードの解析、変数の関連の解析の順番でプログラムを
	 * 解析します（たぷんこれで良いと思う）。
	 * そのうち、複数ファイルの解析が必要になるけど、とりあえず1ファイルからやります。
	 ****************************************************************************************/
	/*
	 * まず、ファイルのトークンの解析を行います。
	 * ファイルの内容を、一文字ずつトークンのインスペクタに順次渡します。
	 * 各インスペクタは、自分の担当するトークンを抽出し、トークンになったタイミングで、リポジトリに
	 * 登録します。
	 * ひとつのトークンが、識別子と予約語になることがありますが、そのまま登録して、後でスパンの一致で
	 * 同一文字列を複数の意味で認識していることを判別します。
	 */
	int pos = 1; //先頭文字の位置は"1"
	while (1) {
		if (fread(inputBuff, INPUT_CHAR_NUM, INPUT_MEMBER_NUM, fp) < INPUT_MEMBER_NUM) {
			/*ファイル終端またはエラーの時にトークンの解析を終了します*/
			/*
			 * freadはファイルの終端またはエラーのときに、INPUT＿MEMBEFLNUM（読込みデータの個数）
			 * より小さい値を返します。ノードのCompitationUnitSyntaxを終結させるために、ファイ
			 * ルの終わりを示すトークンを、リボジトリのtokensに登録しておきたいので、ここに来た
			 * 時にEOFトークンをリボジトリに登録する、EOFインスペクタを呼び出します。
			 * 他のインスペクタも呼び出したほうが良いかもしれない（トークン解析中にEOFになった
			 * 時の回収のため）のですが、それは今後の状況をみて判断します。
			 *
			 */
			res = pEOFInspector->inspect(inputBuff, pElementRepository, pos);
			break;
		}
		// printf("%s"',inputBuff); //ん、これなんだ？ まいっか。⇒出力に出たごみの元でした
		/* インスペクタを呼出すインスペクタの呼出し順は検討が必要かも。
		 * コメントは中に識別子やら予約語やらを含んで面倒なので、現れたら
		 * 評価して、まとめて取り除きます。つまり、後のインスペクタには
		 * 渡しません。
		 */
		res = pCommentInspector->inspect(inputBuff, pElementRepository, &pos, &fp);	//コメントを評価する
		if (res == 2) {
			pos += 1;
			continue;	//コメントを処理したので、コメントの次の文字から再開
		}
		res = pIdentifierInspector->inspect(inputBuff, pElementRepository,pos);		// 識別子を評価する
		res = pOperatorInspector->inspect(inputBuff, pElementRepository, pos);		// 演算子を評価する
		res = pReservedInspector->inspect(inputBuff, pElementRepository, pos);		// 予約語を評価する
		res = pWhitespaceInspector->inspect(inputBuff, pElementRepository, pos);	// ホワイトスペースを評価する
		res = pEndOfLineInspector->inspect(inputBuff, pElementRepository, pos);		// 改行コードを評価する
		res = pQuortInspector->inspect(inputBuff, pElementRepository, pos);			// 引用符を評価する
		res = pBBPInspector->inspect(inputBuff, pElementRepository, pos);			// カ ツコ類を評価する
		res = pSeparatorInspector->inspect(inputBuff, pElementRepository, pos);		// コンマ、ドットを評価する
		res = pColonInspector->inspect(inputBuff, pElementRepository, pos); 		//コロン、セミコロンを評価する
		pos += 1;																	//参照位置を＋1
	}

	/*************************************************************************************************
	 * ここまでで、ファイルのトークンへの分割は終了。
	 * 次にこの辺りにトークンを入力として、ノードを作成し、プログラムの構造を解析する仕組みを入れます。
	 * 今は、とりあえず列挙して出力する実装だけしてます
	 ************************************************************************************************/
	pElementRepository->printElements(Token, 0);

	/*************************************************************************************************
	 * トークンを読みだして、ノードのインスペクタに逐次渡す。
	 * トークンのリストからイテレータを取得して、エンドになるまで回す、だけなんだけど、
	 * stlってまだ馴染まないなあ。使えることは使えるけど、調べながらじやないと書けない
	 * のよね。（2016．8．19）
	 * トークンを順次呼び出す処理にiteratorを使うのだけれど、コンテナの実装をSourceAnalyzerモヽヾ■ ンユール
	 * に意識させたくないので、ElementRipositoryに「トークンからノードを組み立てる処理を任せる」。
	 * 上のファイルをトークンに分割する処理では、自分でループを回しているので、階層構造が壊れている。
	 *  あと、どんなインスペクタを使うのか、トークンについては、上で宣言しているけれども、ノードについ
	 * ては、Repositoryに隠ぺいしてしまう？ここからインスペクターを登録するような形にするか。
	 * と色々と悩みますが、後回しにします。（2016．8．22）
	 ************************************************************************************************/
	pElementRepository->analizeNode();
	
	/*************************************************************************************************
	 * ノードを出力する
	 ************************************************************************************************/
	pElementRepository->printElements(Node, 0);
	// pElementRepository,〉printElements(Torivia):

	/****************************************************
	 * 終了
	 * 使ったインスペクタとリボジトリの回収します。
	 * 回収は、作った順の逆に。これ常識。
	 ***************************************************/

	/*
	 * まず、インスベクタ
	 */
	if(pEOFInspector 		!= NULL) delete pEOFInspector;
	if(pColonInspector 		!= NULL) delete pColonInspector;
	if(pSeparatorInspector 	!= NULL) delete pSeparatorInspector;
	if(pBBPInspector 		!= NULL) delete pBBPInspector;
	if(pQuortInspector 		!= NULL) delete pQuortInspector;
	if(pEndOfLineInspector 	!= NULL) delete pEndOfLineInspector;
	if(pWhitespaceInspector != NULL) delete pWhitespaceInspector;
	if(pReservedInspector 	!= NULL) delete pReservedInspector;
	if(pOperatorInspector 	!= NULL) delete pOperatorInspector;
	if(pIdentifierInspector	!= NULL) delete pIdentifierInspector;
	if(pCommentInspector	!= NULL) delete pCommentInspector;

	/*
	 * 次にリボジトリ
	 */
	if(pElementRepository	!= NULL) delete pElementRepository;

	/*入出力ファイルクローズ*/
	fclose(fp);
	if(argc == 3){
			fclose(outFp);
	}

#ifdef _DEBUG
	printf("itestaIIEnd.\n");
#endif

	return 0;
}

/************************************************************************
 * これ以降は、プロジェクトのひな型に使ったプログラムのサブルーチンです。
 * 篠原さん作
 * もしかしたら使うかもと思って残してます。
 ***********************************************************************/
int
Search(char* str, int keynum, char** keyword){
	int		i 	= 0;
	char*	pos	= 0;
	char*	tmppos	= 0;
	int		index	= 0;
	
	for(i=0; i < keynum; i++){
		tmppos = strstr(str, keyword[i]);
		if(tmppos != 0 && (pos == 0 || pos > tmppos)){
			pos = tmppos;
			index = i + 1;
		}
	}
	return	index;
}

char*
getGlobalFunc(char* buf,int checkPos, char* funcName){
	int i = 0;
	int startPos = -1;
	int endPos = -1;
	char* funcEndPos = NULL;
	char tmp[409600];
	
	memset(tmp, 0x00, sizeof(tmp));
	strncpy(tmp, buf, checkPos);

	/* 関数の終端）があるか */
	for(i = checkPos; i>0; i--){
		if(tmp[i-1] == E_FUNC_CHR){
		#ifdef _DEBUG
			printf("fount end func:%c\n", tmp[i-1]);
		#endif
		} else if(tmp[i-1] != BLANK_CHR &&
				tmp[i-1] != TAB_CHR &&
				tmp[i-1] != LF_CHR){
			#ifdef _DEBUG
				printf("not fount end func:%c\n", tmp[i-1]);
			#endif
			return NULL;
		} else {
			tmp[i-1] = 0x00;
		}
	}
	
	funcEndPos = strrchr( tmp, S_FUNC_CHR);
	if(NULL == funcEndPos){
		#ifdef _DEBUG
			printf("not fount start func:%s\n", buf);
		#endif
		return NULL;
	}
	
	return getFunc(tmp, funcEndPos - tmp, funcName);
}

char*
getFunc(char* buf, int checkPos, char* funcName){
	int i = 0;
	int startPos = -1;
	int endPos = -1;
	char* funcEndPos = NULL;

	for(i = checkPos; i > 0; i--){
		if( -1 == endPos ){
			if( buf[i-1] != BLANK_CHR &&
				buf[i-1] != TAB_CHR &&
				buf[i-1] != LF_CHR ){
				endPos = i;
			} else {
				continue;
			}
		}
		if (buf[i-1] == BLANK_CHR	||
			buf[i-1] == TAB_CHR		||
			buf[i-1] == LF_CHR		||
			buf[i-1] == COMMA_CHR	||
			buf[i-1] == AND_CHR		||
			buf[i-1] == COMMENT_CHR	||
			buf[i-1] == LITERAL_CHR	||
			buf[i-1] == S_FUNC_CHR	||
			buf[i-1] == E_FUNC_CHR	||
			buf[i-1] == S_BLOCK_CHR ||
			buf[i-1] == E_BLOCK_CHR	||
			buf[i-1] == ']'			||
			buf[i-1] == '['			||
			buf[i-1] == '*'			||
			buf[i-1] == E_PROC_CHR){
			startPos = i;

			strncpy(funcName, buf + startPos, endPos - startPos);

			trim(funcName);
			if( 0 != strlen(funcName)){
				return funcName;
			} else {
				return NULL;
			}
		}
	}

	#ifdef _DEBUG
	printf("not fount start func:%s\n", buf);
	#endif

	return NULL;
}

int
checkFunc(char* func){
/*
	if( 0 == strlen( func )){
		return O;
	} else if( 0 == strcmp(func, "if")){
		return O;
	} else if( 0 == strcmp(func, "for")){
		return O;
	} else if( 0 == strcmp(func,"switch")){
		return O;
	}
*/
	/* 除外関数 */
	if( NULL != strstr(func, "NBCOutAlog")){
		return 0;
	}

	if( func[0] == 'n' ){
		return 1;
	}

	if( NULL != strstr(func, "nFunc" )){
		return 1;
	} else if( NULL != strstr(func, "NBC")){
		return 1;
	} else if( NULL != strstr(func, "NBP")){
		return 1;
	} else if( NULL != strstr(func, "NBM")){
		return 1;
	} else if( NULL != strstr(func, "S_")){
		return 1;
	} else if( NULL != strstr(func, "wb_")){
		return 1;
	} else if( NULL != strstr(func, "wk_")){
		return 1;
	} else if( NULL != strstr(func, "WS_")){
		return 1;
	} else if( NULL != strstr(func, "WW_")){
		return 1;
	}
	return 0;
}

char*
trim(char* buf){
	int i = 0;
	int start = 0;
	int end = 0;
	char* tmp;

	if(buf == NULL){
		return NULL;
	}

	tmp = (char*)malloc( strlen( buf ) + 1);
	memset(tmp, 0x00, strlen( buf ) + 1);

	for( i = 0; i < strlen(buf); i++ ){
		if( buf[i] != BLANK_CHR && buf[i] != TAB_CHR){
			break;
		}
	}

	start = i;
	for( i = strlen( buf ); i > 0; i--){
		if( buf[i-1] != BLANK_CHR && buf[i-1] != TAB_CHR && buf[i-1] != LF_CHR){
			break;
		}
	}
	
	end = i;
	memcpy( tmp, buf + start, end - start);
	memset( buf, 0x00, strlen( buf ) );
	strcpy( buf, tmp );
	free( tmp );
	
	return buf;
}
	
char*
deltab(char* buf){
	int i = 0;
	if( buf == NULL ){
		return NULL;
	}

	for( i = 0; i < strlen(buf); i++ ){
		if( buf[i] == TAB_CHR ){
			buf[i] = BLANK_CHR;
		}
	}
	
	return trim( buf );
}

char*
funcComment( char* buf ){
	int i = 0;
	if( buf == NULL ){
		return NULL;
	}
	
	if( 0 == strlen( buf )){
		return(char*) "/**/";
	}
	
	return trim(buf);
}
