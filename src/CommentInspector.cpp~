/*
 * 自動テストプログラム
 *
 * 本プログラムは、逐次通知された文字を評価し、コメントであるかを評価します。。
 *
 * プログラム名 : CommentInspector
 *
 * 作成者 : FJH
 * 作成日 : 2016/8/1
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SourceAnalizer.h"
#include "CommentInspector.h"
#include "ElementRepository.h"
#include "Element.h"

/*
 * init:初期化
 *
 */
void
CommentInspector::init(void){
#ifdef _DEBUG
	printf("%s::init:start\n", name);
#endif

	InspectorBase::init();
	contStatus = false;
	commentType = NA;

#ifdef _DEBUG
	printf("%s::injt:End\n", name);
#endif
}

/* inspect:コメント評価
 * inputBuff : 入力文字
 *  pRepo : リボジトリ
 *  pos : 解析中の文字位置
 *  入力文字を評価し、コメントの条件を満たすか判定する
 *  return : OK = 1 ,NG = 0
 *
 */
int
CommentInspector::inspect(char* inputBuff, ElementRepository* pRepo, int pos){
#ifdef _DEBUG
	printf("%s::inspect():StartinputBuff(Ox%x)\n", name, *inputBuff);
#endif

	int rc = NG;

	//入力パラメタチェック
	if (inputBuff == NULL || pRepo == NULL){
		return rc;
	}

	// 初期化チェック
	if (initFlag == false){
		return rc;
	}
	
	// コメントを解析中かどうか
	if(status == false){
		//解析中ではない->コメントの開始の可能性をチェック
		if (*inputBuff == '/'){
			// コメント開始
			status = true;
			pElement = pRepo->startElement(Token, pos);			//startElement()すると、Elementが返ってくる
			// 入力文字をバッファに格納
			strcat(buff, inputBuff);
		} else {
			// identifier未開始
			status = false;
			memset(buff, 0x00, ANALIZE_BUFF_SIZE);				//バッファをクリア
		}
	} else {
		// C形式で解析中か、C＋＋形式で解析中かで分岐する

		// C形式の場合
			// コメントの終了の可能性をチェックする
				// コメント終了の場合
					// コメント終了を通知
				// コメント継続の場合
					// バッファに文字を複写
		// C++形式の場合
			// コメントの終了の可能性をチェックする
				// コメント終了の場合
					//コメント終了を通知
				//コメント継続の場合
					// バッファに文字を複写
		// 形式が決まっていない場合（2文字目の判定）
			// "*"の場合 -> C形式の開始
			//"/"の場合 -> C++形式の開始
			// いずれでもない場合 -> コメントではない
				// Revokeする

		// 解析中 ->コメント終了の可能性をチェック
		if(!(buff[strlen(buff)-1] == '*' && *inputBuff == '/' ) && //
		   !(*inputBuff >= 'A' && *inputBuff <= 'Z' ) &&
		   !(*inputBuff >= '0' && *inputBuff <= '9' ) &&
			 *inputBuff !=-'_' ) { 									// imputBuffをテストしている。識別子に使えない文字がくればそこまで
			// 条件成立 -> identifier終了を通知
			pElement->setContent( buff );
			pRepo->endElement(pElement, pos);
			//初期状態に戻す
			init();
		} else {
			//識別子の終了ではない
			//入力文字をバッファに格納
			strcat(buff, inputBuff);
		}
	}

	rc = OK;

#ifdef _DEBUG
	printf("%s::inspect:End rc(Ox%x)\n", name, rc);
#endif

	return rc;
}


/*
 * inspect:コメント評価
 *  inputBuff:入力文字
 *  pRepo :エレメントを登録するリボジ
 *  pos :評価ソース中での文字の位置
 *  pFp :ファイルポインタ
 *
 *  UTﾄ8の日本語を他のインスペクタに渡さないように、コメントの評価
 *  はCommentInspectorクラスで完結させる。そのため、ファイルポインタ
 *  を受け取るinspectメソッドを提供する。
 *
 */
int
CommentInspector::inspect(char* inputBuff, ElementRepository* pRepo, int* pPos, FILE** pFp){
#ifdef _DEBUG
	printf("%s::inspect():Start inputBuff(0x%x)\n", name, *inputBuff);
#endif

	char readBuff[2];
	int CommentDone = 0;
	int rc = NG;

	// 入力パラメタチェック
	if(inputBuff == NULL || pRepo == NULL ||  pPos == NULL || pFp == NULL){
		return rc;
		goto END;
	}
	
	// 初期化チェック
	if(initFlag == false){
		return rc;
		goto END;
	}

	// バッファ初期化
	memset(readBuff, 0x00, sizeof(readBuff));

	// コメントを解析中かどうか
	if(status == false){
		// 解析中ではない->コメントの開始の可能性をチェック
		if(*inputBuff == '/'){
			// コメント開始？
			status = true;
			pElement = pRepo->startElement(Token, *pPos);	// startElement()すると、Elementが返ってくる
			strcpy(buff, inputBuff);

			// コメント形式を求めるため次の文字を読む
			if(fread(readBuff, INPUT_CHAR_NUM, INPUT_MEMBER_NUM, *pFp) < INPUT_MEMBER_NUM){
				// 読込みエラーならポジションを進めてエラー復帰
				(*pPos)++;
				rc = NG;
				goto END;
			}
			if(*readBuff == '*'){
				// 読込み成功
				(*pPos)++;
				strcat(buff, readBuff);
				// C形式のコメント開始と判定
				// '*' を探す
				while (1){
					if (fread(readBuff, INPUT_CHAR_NUM, INPUT_MEMBER_NUM, *pFp) < INPUT_MEMBER_NUM){
						// 読込みエラーまたはファイル末尾なら、エラーで復帰
						(*pPos)++;
						rc = NG;
						goto END;
					}
					if (*readBuff == '*'){
						// '*'が見つかったらさらに次の文字が'/'か見て、コメントの終了を判定する
						// '*'を複写
						strcat(buff, readBuff);
						(*pPos)++;
						if(fread(readBuff, INPUT_CHAR_NUM, INPUT_MEMBER_NUM, *pFp) < INPUT_MEMBER_NUM){
							(*pPos)++;
							rc = NG;
							goto END;
						}
						if(*readBuff == '/'){
							// '/'だった場合
							// コメントが終了したのでリボジトリに登録する
							strcat(buff, readBuff);
							// ポインタを進める
							(*pPos)++;
							// 条件成立->コメント終了を通知
							pElement->setContent(buff);
							pElement->setTokenType(SyntaxToken);
							pElement->setTokenKind(CStyleCommentToken);
							pRepo->endElement(pElement, *pPos);
							// 初期状態に戻す
							init();
							// コメントを処理した
							CommentDone = 1;
							break;

						} else {
							// C形式のコメントで､'*'に続いで/'ではなかった '
							// *'の検索を継続する
							strcat(buff, readBuff);
							(*pPos)++;
							continue;
						}
					} else {
						// '*'ではない->C形式コメントの終了シーケンス開始ではない
						// 入力文字をバッファに格納
						strcat(buff, readBuff);
						(*pPos)++;
					}
				}
			} else if (*readBuff == '/'){
				// C++形式のコメント開始と判定
				(*pPos)++;
				strcat(buff, readBuff);
				// 行末まで読込みリボジトリに登録する
				while(*readBuff != '\n'){
					if (fread(readBuff, INPUT_CHAR_NUM, INPUT_MEMBER_NUM, *pFp) < INPUT_MEMBER_NUM){
						//読込みエラーまたはファイル末尾なら、エラーで復帰
						(*pPos)++;
						rc = NG;
						goto END;
					}
					// コメントを複写
					(*pPos)++;
					strcat(buff, readBuff);
				}
				// 行末に達した
				// コメントが終了したのでリボジトリに登録する
				strcat(buff, readBuff);
				// ポインタを進める
				(*pPos)++;
				// 条件成立->コメント終了を通知
				pElement->setContent(buff);
				pElement->setTokenType(SyntaxToken);
				pElement->setTokenKind(CppStyleCommentToken);
				pRepo->endElement(pElement, *pPos);
				//初期状態に戻す
				init();
				// コメントを処理した
				CommentDone = 1;
			} else {
				// コメントではなかった場合
				// ファイルポインタを戻して復帰する
				fseek(*pFp, -1, SEEK_CUR);
				// ここにバグあり。
				// ファイルポインタを戻して、識別子の検査から再開しますが、StartElementで登録したEJementを
				// 消していません。このエレメントのtypeKindが不定のため、後のPrintでElementPropertiesに定義
				// してある、要素名配列の要素数を超えたところをアクセスしてしまい、セグメントフォールトに
				// なります。でも、今なぜか、EIementのlistの要素を消せないんですよね～。STLってホント慣れ
				// ないと、うまく使えないわ～。要素の削除なんて、基本的なことにも苦労する。まぁ、慣れてない
				// 私が悪いんですけどね．．．
				pRepo->revokeElement(pElement);
			}
		} else {
			// コメントの開始ではないので復帰
			rc = OK;
			goto END;
		}
	} else {
		// コメント解析中。ただし、初版ではコメント開始のタイミングでコメント要素を処理してしまうので、ここには来ない。
		// C形式で解析中か、C++形式で解析中かで分岐する
		// C形式の場合
			// コメントの終了の可能性をチェックする
				// コメント終了の場合
					// コメント終了を通知
				// コメント継続の場合
					// バッファに文字を複写
		// C++形式の場合
			// コメントの終了の可能性をチェックする
				// コメント終了の場合
					// コメント終了を通知
				// コメント継続の場合
					// バッファに文字を複写
		// 形式が決まっていない場合（２文字目の判定）
			// "*"の場合 -> C形式の開始
			// "/"の場合 -> C++形式の開始
			// いずれでもない場合 -> コメントではない
				// Revokeする
		// 解析中 -> コメント終了の可能性をチェック
		if(!(buff[strlen(buff)-1] == '*' && *inputBuff == '/') && 	//
			!( *inputBuff >= 'A' && *inputBuff <= 'Z') &&
			!( *inputBuff >= '0' && *inputBuff <= '9') &&
			   *inputBuff != '_' ){									// imputBuffをテストしている。識別しに使えない文字がくればそこまで
			// 条件成立 ->identifier終了を通知
			pElement->setContent( buff );
			pRepo->endElement(pElement, *pPos);
			// 初期状態に戻す
			init();
		} else {
			// 識別子の終了ではない
			// 入力文字をバッファに格納
			strcat(buff, inputBuff);
		}
	}
	if (CommentDone == 1){
		rc = 2;
	} else {
		rc = OK;
	}
END:
#ifdef _DEBUG
	printf("%s::inspect : END rc(0x%x)\n", name, rc);
#endif

	return rc;
}
